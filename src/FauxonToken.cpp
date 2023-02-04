#include <FauxonToken.hpp>

namespace Fauxon{
    const std::string NUMBERS="1234567890";
    const std::string LETTERS="abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLPMNPQRSTUVWXYZ";
    TokenType_en check_type(char x){
        for(size_t i=0;i<NUMBERS.size();i++){
            if(x == NUMBERS[i])return TokenType_en::__SINGLE_NUMBER;
        }
        for(size_t i=0;i<LETTERS.size();i++){
            if(x == LETTERS[i])return TokenType_en::__SINGLE_LETTER;
        }
        if(x == '.')return TokenType_en::__PERIOD;
        return TokenType_en::__NULL;
    }
    std::string TypeAsString(TokenType_en Type){
        std::string Result="";
        switch(Type){
            case TokenType_en::__NULL:{Result="__NULL";}break;
            case TokenType_en::__PLUS:{Result="__PLUS";}break;
            case TokenType_en::__MINUS:{Result="__MINUS";}break;
            case TokenType_en::__MULTIPLY:{Result="__MULTIPLY";}break;
            case TokenType_en::__DIVIDE:{Result="__DIVIDE";}break;
            case TokenType_en::__INT:{Result="__INT";}break;
            case TokenType_en::__FLOAT:{Result="__FLOAT";}break;
            case TokenType_en::__WORD:{Result="__WORD";}break;
            case TokenType_en::__PERIOD:{Result="__PERIOD";}break;
            case TokenType_en::__SINGLE_NUMBER:{Result="__SINGLE_NUMBER";}break;
            case TokenType_en::__SINGLE_LETTER:{Result="__SINGLE_LETTER";}break;
            case TokenType_en::__EQUAL:{Result="__EQUAL";}break;
            case TokenType_en::__LESS:{Result="__LESS";}break;
            case TokenType_en::__MORE:{Result="__MORE";}break;
            case TokenType_en::__LEFT_PARENTHESIS:{Result="__LEFT_PARENTHESIS";}break;
            case TokenType_en::__RIGHT_PARENTHESIS:{Result="__RIGHT_PARENTHESIS";}break;
            case TokenType_en::__EQUAL_EQUAL:{Result="__EQUAL_EQUAL";}break;
            case TokenType_en::__LESS_EQUAL:{Result="__LESS_EQUAL";}break;
            case TokenType_en::__MORE_EQUAL:{Result="__MORE_EQUAL";}break;
            case TokenType_en::__QUESTION:{Result="__QUESTION";}break;
            case TokenType_en::__VERBOSE_QUESTION:{Result="__VERBOSE_QUESTION";}break;
            case TokenType_en::__COLON:{Result="__COLON";}break;
            case TokenType_en::__SEMI_COLON:{Result="__SEMI_COLON";}break;
            case TokenType_en::__SHIFT_RIGHT:{Result="__SHIFT_RIGHT";}break;
            case TokenType_en::__SHIFT_LEFT:{Result="__SHIFT_LEFT";}break;
            case TokenType_en::__ERROR:{Result="__ERROR";}break;
            case TokenType_en::__EOF:{Result="__EOF";}break;
        }
        return Result;
    }
};
