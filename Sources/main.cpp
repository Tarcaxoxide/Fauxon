#include<iostream>
#include<string>
#include<Interpreter/Interpreter.hpp>

int main(){
	for(std::string Line="";std::getline(std::cin,Line);){
		std::cout<<Interpreter::Interpreter(Line)<<std::endl;
	}
}

/*
(pizza)"is"<awesome>{lol}[123]'7'

*/