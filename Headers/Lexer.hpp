#ifndef __Fauxon_Lexer
#define __Fauxon_Lexer
#include<string>
#include<DataTypes/Token.hpp>
#include<deque>
namespace Fauxon{
    namespace Lexer{
        void Lexer(std::string srcCode);
        DataTypes::Token NextToken();
    };
};
#endif