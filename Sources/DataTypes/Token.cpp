#include<DataTypes/Token.hpp>

namespace Fauxon{
    namespace DataTypes{
        Token::~Token(){
            switch(ValueKind){
                case Fauxon::DataTypes::Kinds::Kinds::Null:break;
                case Fauxon::DataTypes::Kinds::Kinds::Int64ValueType:{
                    delete ((int64_t*)Value);
                    Value=nullptr;
                }break;
                default:break;
            }
        }
        Token::Token(const Token& t){
            Kind=t.Kind;
            ValueKind=t.ValueKind;
            switch(ValueKind){
                case Fauxon::DataTypes::Kinds::Kinds::Null:break;
                case Fauxon::DataTypes::Kinds::Kinds::Int64ValueType:{
                    Value = new int64_t(*((int64_t*)t.Value));
                }break;
                default:break;
            }
        }
        Token::Token(DataTypes::Kinds::Kinds kind,size_t position[2],std::string text){
            Kind=kind;
            Text=text;
            StartPosition=position[0];
            EndPosition=position[1];
        }
    };
};