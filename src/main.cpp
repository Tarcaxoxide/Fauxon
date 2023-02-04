//#define DEBUG
#include<FauxonLexer.hpp>
#include<FauxonExec.hpp>
#include<fstream>
#include<iostream>
#include<deque>
#include<string>


void Run(std::string& text){
    if(!(text.size()))return;
    if(text == " ")return;
    Fauxon::Lexer_cl Lex(text);
    std::deque<Fauxon::Token_st>* Tokens = Lex.make_tokens();
    Fauxon::Exec(Tokens);
}

int main(int ArgC,char** ArgV){
    std::string Line=" ";
    if(ArgC < 2){
        for(Line=" ";;std::getline(std::cin,Line)){
            Run(Line);
        }
    }else{
        std::ifstream File(ArgV[1]);
        bool eof=false;
        std::string FileText="";
        for(Line=" ";!eof;std::getline(File,Line)){
            FileText+=Line;
            eof=File.eof();
        }
        File.close();
        Run(FileText);
    }
}