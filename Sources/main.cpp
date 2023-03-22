#include <iostream>
#include <fstream>
#include <Tokenize.hpp>
#include <Parse.hpp>
#include <Evaluate.hpp>


int main(int c,char** v){
	if(c==1){
		std::cout<<"user>";
		for(std::string Line="";std::getline(std::cin,Line);){
			std::deque<Token::Token> tokens = Tokenize(Line);
			std::shared_ptr<Node::BlockNode> block = Parse_Block(tokens);
			Evalutate(block);
			std::cout<<"user>";
		}
	}else if(c==2){
		std::ifstream File(v[1]);
		std::string Contents="";
		for(std::string Line="";std::getline(File,Line);){Contents+=Line;}
		File.close();
		std::deque<Token::Token> tokens = Tokenize(Contents);
		std::shared_ptr<Node::BlockNode> block = Parse_Block(tokens);
		Evalutate(block);
	}
}