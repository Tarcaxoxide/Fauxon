#include<DataTypes/Token.hpp>

namespace Fauxon{
    namespace DataTypes{
        Token::Token(const Token& t):Value(t.Value){
            Kind=t.Kind;
        }
        Token::Token(DataTypes::Kinds::Kinds kind,size_t position[2],std::string text){
            Kind=kind;
            Text=text;
            StartPosition=position[0];
            EndPosition=position[1];
        }
        Token::Token(DataTypes::Kinds::Kinds kind,size_t position[2],std::string text,const Fauxon::DataTypes::DecimalNumberValue& value){
            Kind=kind;
            Text=text;
            StartPosition=position[0];
            EndPosition=position[1];
            Value=value;
        }
        std::string Token::ToString(){
            std::string Result="";
            Result+="Kind:`";
            Result+=Fauxon::DataTypes::Kinds::ToString(Kind);
            Result+="`,";
            Result+="Text:`";
            Result+=Text;
            Result+="`,";
            if(Value!="0.0"){
                Result+="Value:`";
                Result+=Value.ToString();
                Result+="`,";
            }
            Result+="Position:`";
            Result+=std::to_string(StartPosition);
            Result+="-";
            Result+=std::to_string(EndPosition);
            Result+="`";
            return Result;
        }
    };
};