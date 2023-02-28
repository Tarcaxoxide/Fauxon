#include<iostream>
#include<string>
#include<fstream>
#include<DataTypes/Token.hpp>
#include<Lexer.hpp>
int main(int c,char** v){
    
    if(c == 2){
        std::ifstream file(v[1]);
        for(std::string Line;std::getline(file,Line);){
            if(!Line.size())break;
            std::cout<<""<<Line<<std::endl;
        }
        file.close();
    }else if(c == 1){
    std::cout<<":>";
        for(std::string Line;std::getline(std::cin,Line);){
            if(!Line.size())break;
            Fauxon::Lexer::Lex(Line);
            Fauxon::DataTypes::Token* CToken = Fauxon::Lexer::NextToken();
            while((*CToken).Kind != Fauxon::DataTypes::Kinds::Kinds::Eof){
                std::cout<<"<:"<<(*CToken).ToString()<<std::endl;
                delete CToken;
                CToken = Fauxon::Lexer::NextToken();
            }
            delete CToken;
            std::cout<<":>";
        }
    }
}