#ifndef __Fauxon_DataType_Kinds
#define __Fauxon_DataType_Kinds
#include<stddef.h>
#include<stdint.h>
#include<string>
namespace Fauxon{
    namespace DataTypes{
        namespace Kinds{
            enum Kinds:size_t{
                Null=0,
                Eof,
                //Tokens
                NumberToken,
                WordToken,
                PlusToken,
                MinusToken,
                AstrixToken,
                ForwardSlashToken,
            };
            inline std::string ToString(Kinds kind){
                switch(kind){
                    case Kinds::Null:return std::string("Null");
                    case Kinds::Eof:return std::string("Eof");
                    case Kinds::NumberToken:return std::string("NumberToken");
                    case Kinds::WordToken:return std::string("WordToken");
                    case Kinds::PlusToken:return std::string("PlusToken");
                    case Kinds::MinusToken:return std::string("MinusToken");
                    case Kinds::AstrixToken:return std::string("AstrixToken");
                    case Kinds::ForwardSlashToken:return std::string("ForwardSlashToken");
                    default:return std::string("Unknown kind");
                }
            }
        };
    };
};
#endif