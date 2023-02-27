#ifndef __Fauxon_DataType_Token
#define __Fauxon_DataType_Token
#include<DataTypes/Kinds.hpp>
#include<string>
namespace Fauxon{
    namespace DataTypes{
        struct Token{
            Fauxon::DataTypes::Kinds::Kinds Kind{Fauxon::DataTypes::Kinds::Kinds::Null};
            Fauxon::DataTypes::Kinds::Kinds ValueKind{Fauxon::DataTypes::Kinds::Kinds::Null};
            std::string Text{""};
            void* Value{nullptr};
            size_t StartPosition;
            size_t EndPosition;
            ~Token();
            Token(const Token& t);
            Token(DataTypes::Kinds::Kinds kind,size_t position[2],std::string text);
            Token(DataTypes::Kinds::Kinds kind,size_t position[2],std::string text,int64_t Value);
        };
    };
};
#endif