#include<Lexer.hpp>

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
        bool IsDigit(char Char){
            return (Char > 0x2F && Char < 0x3A);
        }

        /* /\private/\ */
        DataTypes::Token NextToken(){
            if(IsDigit(Current())){
                size_t start = Position;
                while(IsDigit(Current()))Advance();
                size_t end=Position-start;
                std::string text = SourceCode.substr(start,end);
                return Fauxon::DataTypes::Token(DataTypes::Kinds::Kinds::NumberToken,(size_t[2]){start,end},text);
            }
            return Fauxon::DataTypes::Token(DataTypes::Kinds::Kinds::Null,(size_t[2]){Position,Position+1},"Null");
        }
    };
};