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
            std::deque<Fauxon::DataTypes::Token> Tokens=Fauxon::Lexer::Lex(Line);

            for(size_t i=0;i<Tokens.size();i++){
                std::cout<<"<:"<<Tokens[i].ToString()<<std::endl;
            }

            
            std::cout<<":>";
        }
    }
}