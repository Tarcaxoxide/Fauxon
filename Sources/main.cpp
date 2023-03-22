#include <iostream>
#include <Tokenize.hpp>
#include <Parse.hpp>
#include <Evaluate.hpp>

int main(){
	std::cout<<"user>";
	for(std::string Line="";std::getline(std::cin,Line);){
		std::deque<Token::Token> tokens = Tokenize(Line);
		std::shared_ptr<Node::BlockNode> block = Parse_Block(tokens);
		Evalutate(block);
		std::cout<<"user>";
	}
}