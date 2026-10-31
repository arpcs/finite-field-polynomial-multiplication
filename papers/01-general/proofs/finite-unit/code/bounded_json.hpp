#ifndef FASTMUL_RECORD_BOUNDED_JSON_HPP
#define FASTMUL_RECORD_BOUNDED_JSON_HPP
// Adapted from this workspace's croc_word_screen_bounded_20261030.cpp.
// Only bounded, plain-string source JSON is accepted. Arithmetic uses Q.
#include <cctype>
#include <string>
#include <vector>
namespace recordjson {
struct Token{char type;unsigned begin,end,next;};
class Json {
    std::string text;
    std::vector<Token> tok;
    unsigned pos=0,token_cap;
    void space(){while(pos<text.size()&&std::isspace(static_cast<unsigned char>(text[pos])))++pos;}
    unsigned parse(unsigned depth){
        need(depth<24&&tok.size()<token_cap,"JSON depth/token cap");space();
        need(pos<text.size(),"JSON unexpected end");
        const unsigned id=unsigned(tok.size()),start=pos;const char c=text[pos++];
        tok.push_back({c,start,0,0});
        if(c=='['||c=='{'){
            const char close=c=='['?']':'}';space();
            if(pos<text.size()&&text[pos]!=close)for(;;){
                if(c=='{'){const auto k=parse(depth+1);need(tok[k].type=='"',"JSON object key");
                    space();need(pos<text.size()&&text[pos++]==':',"JSON colon");}
                parse(depth+1);space();need(pos<text.size(),"JSON terminator");
                if(text[pos]==close)break;
                need(text[pos++]==',',"JSON comma");
            }
            need(pos<text.size()&&text[pos++]==close,"JSON container close");
        }else if(c=='"'){
            while(pos<text.size()&&text[pos]!='"'){need(text[pos]!='\\',"plain JSON strings only");++pos;}
            need(pos<text.size(),"JSON string close");++pos;
        }else{
            while(pos<text.size()&&text[pos]!=','&&text[pos]!=']'&&text[pos]!='}'&&
                  !std::isspace(static_cast<unsigned char>(text[pos])))++pos;
        }
        tok[id].end=pos;tok[id].next=unsigned(tok.size());return id;
    }
public:
    explicit Json(const char* path,unsigned byte_cap=65536,unsigned tokens=20000):token_cap(tokens){
        need(byte_cap<=2097152&&tokens<=220000,"JSON caller caps");
        std::ifstream in(path,std::ios::binary);need(bool(in),"JSON input open");
        in.seekg(0,std::ios::end);const auto size=in.tellg();
        need(size>0&&size<=byte_cap,"JSON byte cap");
        text.resize(static_cast<std::size_t>(size));in.seekg(0);in.read(&text[0],size);
        need(bool(in),"JSON complete read");tok.reserve(tokens);parse(0);space();
        need(pos==text.size(),"JSON trailing data");
    }
    std::string str(unsigned id)const{
        const auto a=tok.at(id);need(a.type=='"',"JSON string token");
        return text.substr(a.begin+1,a.end-a.begin-2);
    }
    std::string raw(unsigned id)const{const auto a=tok.at(id);return text.substr(a.begin,a.end-a.begin);}
    int integer(unsigned id)const{
        const auto a=tok.at(id);unsigned j=a.begin;bool negative=false;
        if(j<a.end&&text[j]=='-'){negative=true;++j;}
        need(j<a.end,"JSON integer digits");int n=0;
        for(;j<a.end;++j){need(text[j]>='0'&&text[j]<='9',"JSON integer token");
            n=10*n+int(text[j]-'0');need(n<10000000,"JSON integer cap");}
        return negative?-n:n;
    }
    unsigned natural(unsigned id)const{const int n=integer(id);need(n>=0,"JSON natural");return unsigned(n);}
    bool boolean(unsigned id)const{
        const auto s=raw(id);need(s=="true"||s=="false","JSON boolean");return s=="true";
    }
    Q rational(unsigned id)const{
        const auto s=tok.at(id).type=='"'?str(id):raw(id);need(!s.empty()&&s.size()<=32,"small source rational");
        Q q;need(mpq_set_str(q.v,s.c_str(),10)==0&&mpz_sgn(mpq_denref(q.v))>0,"source rational parse");
        mpq_canonicalize(q.v);q.bound();return q;
    }
    std::vector<unsigned> children(unsigned id)const{
        need(tok.at(id).type=='['||tok.at(id).type=='{',"JSON container");
        std::vector<unsigned> out;for(unsigned j=id+1;j<tok[id].next;j=tok[j].next)out.push_back(j);
        return out;
    }
    unsigned key(unsigned id,const std::string& name)const{
        need(tok.at(id).type=='{',"JSON key object");
        for(unsigned j=id+1;j<tok[id].next;){const unsigned value=j+1;
            if(str(j)==name)return value;
            j=tok[value].next;}
        throw std::runtime_error("missing source JSON key: "+name);
    }
};
}
#endif
