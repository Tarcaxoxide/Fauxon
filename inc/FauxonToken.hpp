#pragma once
#include<deque>
#include<string>
#include<functional>
#include<iostream>
#include<typeinfo>
namespace Fauxon{
    enum TokenType_en:size_t{
        __NULL=0,
        __PLUS,
        __MINUS,
        __MULTIPLY,
        __DIVIDE,
        __INT,
        __FLOAT,
        __WORD,
        __PERIOD,
        __SINGLE_NUMBER,
        __SINGLE_LETTER,
        __EQUAL,
        __LESS,
        __MORE,
        __LEFT_PARENTHESIS,
        __RIGHT_PARENTHESIS,
        __EQUAL_EQUAL,
        __LESS_EQUAL,
        __MORE_EQUAL,
        __QUESTION,
        __VERBOSE_QUESTION,
        __COLON,
        __SEMI_COLON,
        __SHIFT_RIGHT,
        __SHIFT_LEFT,
        __ERROR,
        __EOF
    };

    extern const std::string NUMBERS;
    extern const std::string LETTERS;
    extern TokenType_en check_type(char x);
    extern std::string TypeAsString(TokenType_en Type);
    inline std::string check_type_AsString(char* x){
        if(x == nullptr){return "__NULL";}
        std::string sType = TypeAsString(check_type(*x));
        if(sType != "__NULL")return sType;
        char xType[2]{0x00};
        xType[0]=*x;
        return std::string(xType);
    }
    inline std::string ToString(std::string Value){return Value;}
    inline std::string ToString(int64_t Value){return std::to_string(Value);}
    inline std::string ToString(double Value){return std::to_string(Value);}

    template<typename Vt>
    struct ValueBase_st{
        Vt RealValue;
        ValueBase_st(Vt V):RealValue(V){}
        Vt Real(){return RealValue;}
        std::string String(){
            return ToString(RealValue);
        }
    };

    struct Token_st{
        TokenType_en Type;
        void* Value{nullptr};
        double* dResult{nullptr};
        int64_t* iResult{nullptr};
        std::string* sResult{nullptr};
        Token_st* LeftToken{nullptr};
        Token_st* CenterToken{nullptr};
        Token_st* RightToken{nullptr};

        double operator=(double Value){
            if(LeftToken != nullptr){LeftToken->Delete();delete LeftToken;LeftToken=nullptr;}
            if(CenterToken != nullptr){CenterToken->Delete();delete CenterToken;CenterToken=nullptr;}
            if(RightToken != nullptr){RightToken->Delete();delete RightToken;RightToken=nullptr;}
            if(Type != TokenType_en::__FLOAT && Type != TokenType_en::__INT && Type != TokenType_en::__WORD){
                CenterToken = new Token_st(TokenType_en::__FLOAT,Value);
            }else{
                Copy(Token_st(TokenType_en::__FLOAT,Value));
            }
            return Value;
        }
        int64_t operator=(int64_t Value){
            if(LeftToken != nullptr){LeftToken->Delete();delete LeftToken;LeftToken=nullptr;}
            if(CenterToken != nullptr){CenterToken->Delete();delete CenterToken;CenterToken=nullptr;}
            if(RightToken != nullptr){RightToken->Delete();delete RightToken;RightToken=nullptr;}
            if(Type != TokenType_en::__FLOAT && Type != TokenType_en::__INT && Type != TokenType_en::__WORD){
                CenterToken = new Token_st(TokenType_en::__INT,Value);
            }else{
                Copy(Token_st(TokenType_en::__INT,Value));
            }
            return Value;
        }
        std::string operator=(std::string Value){
            if(LeftToken != nullptr){LeftToken->Delete();delete LeftToken;LeftToken=nullptr;}
            if(CenterToken != nullptr){CenterToken->Delete();delete CenterToken;CenterToken=nullptr;}
            if(RightToken != nullptr){RightToken->Delete();delete RightToken;RightToken=nullptr;}
            if(Type != TokenType_en::__FLOAT && Type != TokenType_en::__INT && Type != TokenType_en::__WORD){
                CenterToken = new Token_st(TokenType_en::__WORD,Value);
            }else{
                Copy(Token_st(TokenType_en::__WORD,Value));
            }
            return Value;
        }
        Token_st operator=(const Token_st& Value){
            Copy(Value);
            return Value;
        }
        Token_st(TokenType_en Type){
            this->Type=Type;
            this->Value = nullptr;
        }
        Token_st(TokenType_en Type,std::string Value){
            this->Type=Type;
            this->Value = new ValueBase_st<std::string>(Value);
        }
        Token_st(TokenType_en Type,double Value){
            this->Type=Type;
            this->Value = new ValueBase_st<double>(Value);
        }
        Token_st(TokenType_en Type,int64_t Value){
            this->Type=Type;
            this->Value = new ValueBase_st<int64_t>(Value);
        }
        void Copy(const Token_st& Other){
            this->Type = Other.Type;
            this->Value = Other.Value;
            this->dResult = Other.dResult;
            this->iResult = Other.iResult;
            this->sResult = Other.sResult;
            this->LeftToken = Other.LeftToken;
            this->CenterToken = Other.CenterToken;
            this->RightToken = Other.RightToken;
        }
        Token_st(const Token_st& Other){
            Copy(Other);
        }
        #ifdef DEBUG
            ~Token_st(){
                std::cout<<TypeAsString(Type)<<":\"my 'destructor' called XD what a loser.\""<<std::endl;
            }
        #endif
        void Delete(){
            if(Value != nullptr){
                if(Type == TokenType_en::__FLOAT){
                    delete ((ValueBase_st<double>*)Value);
                    Value=nullptr;
                }else if(Type == TokenType_en::__INT){
                    delete ((ValueBase_st<int64_t>*)Value);
                    Value=nullptr;
                }else{
                    delete ((ValueBase_st<std::string>*)Value);
                    Value=nullptr;
                }
            }
            if(dResult != nullptr){delete dResult;dResult=nullptr;}
            if(iResult != nullptr){delete iResult;iResult=nullptr;}
            if(sResult != nullptr){delete sResult;sResult=nullptr;}
            if(LeftToken != nullptr){LeftToken->Delete();delete LeftToken;LeftToken=nullptr;}
            if(CenterToken != nullptr){CenterToken->Delete();delete CenterToken;CenterToken=nullptr;}
            if(RightToken != nullptr){RightToken->Delete();delete RightToken;RightToken=nullptr;}
        }
        std::string* asString(bool WithTypeInfo){
            if(sResult==nullptr)sResult=new std::string("");
            if(WithTypeInfo)(*sResult)="(";
            if(WithTypeInfo)(*sResult)+=TypeAsString(Type);
            if(Value != nullptr){
                if(WithTypeInfo)(*sResult)+=":";
                if(Type == TokenType_en::__FLOAT){
                    (*sResult)+=(*((ValueBase_st<double>*)Value)).String();
                }else if(Type == TokenType_en::__INT){
                    (*sResult)+=(*((ValueBase_st<int64_t>*)Value)).String();
                }else{
                    (*sResult)+=(*((ValueBase_st<std::string>*)Value)).String();
                }
            }
            if(LeftToken != nullptr){if(WithTypeInfo)(*sResult)+=":";(*sResult)+=(*(LeftToken->asString(WithTypeInfo)));}
            if(CenterToken != nullptr){if(WithTypeInfo)(*sResult)+=":";(*sResult)+=(*(CenterToken->asString(WithTypeInfo)));}
            if(RightToken != nullptr){if(WithTypeInfo)(*sResult)+=":";(*sResult)+=(*(RightToken->asString(WithTypeInfo)));}
            if(WithTypeInfo)(*sResult)+=")";
            return sResult;
        }
        double* asDouble(){
            if(dResult==nullptr)dResult = new double(0.0f);
            std::string sType = TypeAsString(Type);
            if(sType == "__FLOAT"){
                (*dResult)=(*((ValueBase_st<double>*)Value)).Real();
            }
            else if(sType == "__INT"){
                (*dResult)=double((*((ValueBase_st<int64_t>*)Value)).Real());
            }
            else{return nullptr;}
            return dResult;
        }
        int64_t* asInt(){
            if(iResult==nullptr)iResult = new int64_t(0);
            std::string sType = TypeAsString(Type);
            if(sType == "__FLOAT"){
                (*iResult)=int64_t((*((ValueBase_st<double>*)Value)).Real());
            }
            else if(sType == "__INT"){
                (*iResult)=(*((ValueBase_st<int64_t>*)Value)).Real();
            }
            else{return nullptr;}
            return iResult;
        }
        struct SubBase_st{
            TokenType_en Type{TokenType_en::__NULL};
            Token_st* Ptr{nullptr};
        };
        struct Sub_st{
            SubBase_st Left;
            SubBase_st Center;
            SubBase_st Right;
        };
        Sub_st GetSub(){
            Sub_st Sub;
            if(LeftToken != nullptr){
                Sub.Left.Type=LeftToken->Type;
                Sub.Left.Ptr=LeftToken;
            }
            if(CenterToken != nullptr){
                Sub.Center.Type=CenterToken->Type;
                Sub.Center.Ptr=CenterToken;
            }
            if(RightToken != nullptr){
                Sub.Right.Type=RightToken->Type;
                Sub.Right.Ptr=RightToken;
            }
            return Sub;
        }
        
    };
};