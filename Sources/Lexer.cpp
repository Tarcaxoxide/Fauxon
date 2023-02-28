#include<Lexer.hpp>

extern bool IsDigit(char Char);
extern bool IsLetter(char Char);
extern bool IsWhiteSpace(char Char);

namespace Fauxon{
    namespace Lexer{
        std::string SourceCode;
        size_t Position;
        void Lex(std::string srcCode){
            SourceCode=srcCode;
            Position=0;
        }
        /* \/private\/ */
        char Current(){
            if(Position >= SourceCode.size())return '\0';
            return SourceCode[Position];
        }
        void Advance(){
            Position++;
        }
        /* /\private/\ */
        DataTypes::Token* NextToken(){
            while(IsWhiteSpace(Current()))Advance();
            if(Current() == '\0')return new Fauxon::DataTypes::Token(DataTypes::Kinds::Kinds::Eof,(size_t[2]){Position,Position+1},"Eof");
            if(IsDigit(Current())||Current()=='+'||Current()=='-'){
                size_t start = Position;
                if(Current()=='+'||Current()=='-')Advance();
                int dot_count=0;
                while(IsDigit(Current())||Current()=='.'){Advance();}
                size_t end=Position-start;
                std::string text = SourceCode.substr(start,end);
                
                Fauxon::DataTypes::DecimalNumberValue X;
                if(!Fauxon::DataTypes::DecimalNumberValue::TryParse(text,X)){
                    return new Fauxon::DataTypes::Token(DataTypes::Kinds::Kinds::Null,(size_t[2]){Position,++Position},"Null");
                }
                return new Fauxon::DataTypes::Token(DataTypes::Kinds::Kinds::NumberToken,(size_t[2]){start,start+end},text,X);
            }
            if(IsLetter(Current())){
                size_t start = Position;
                while(IsLetter(Current())||Current()=='_'||IsDigit(Current()))Advance();
                size_t end=Position-start;
                std::string text = SourceCode.substr(start,end);
                return new Fauxon::DataTypes::Token(DataTypes::Kinds::Kinds::WordToken,(size_t[2]){start,start+end},text);
            }
            switch(Current()){
                case '+':return new Fauxon::DataTypes::Token(DataTypes::Kinds::Kinds::PlusToken,(size_t[2]){Position,++Position},"+");
                case '-':return new Fauxon::DataTypes::Token(DataTypes::Kinds::Kinds::MinusToken,(size_t[2]){Position,++Position},"-");
                case '*':return new Fauxon::DataTypes::Token(DataTypes::Kinds::Kinds::AstrixToken,(size_t[2]){Position,++Position},"*");
                case '/':return new Fauxon::DataTypes::Token(DataTypes::Kinds::Kinds::ForwardSlashToken,(size_t[2]){Position,++Position},"/");
            }
            return new Fauxon::DataTypes::Token(DataTypes::Kinds::Kinds::Null,(size_t[2]){Position,++Position},"Null");
        }
    };
};