#ifndef __Fauxon_DataType_Token
#define __Fauxon_DataType_Token
#include<DataTypes/Kinds.hpp>
#include<string>
#include<DataTypes/DecimalNumberValue.hpp>
namespace Fauxon{
    namespace DataTypes{
        struct Token{
            Fauxon::DataTypes::Kinds::Kinds Kind{Fauxon::DataTypes::Kinds::Kinds::Null};
            std::string Text{""};
            Fauxon::DataTypes::DecimalNumberValue Value;
            size_t StartPosition;
            size_t EndPosition;
            Token(const Token& T);
            Token(DataTypes::Kinds::Kinds kind,size_t position[2],std::string text);
            Token(DataTypes::Kinds::Kinds kind,size_t position[2],std::string text,const Fauxon::DataTypes::DecimalNumberValue& value);
            std::string ToString();
        };
    };
};
#endif