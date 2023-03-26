#include<iostream>
#include<string>
#include<Interpreter/Interpreter.hpp>

int main(){
	std::cout<<"user> ";
	for(std::string Line="";std::getline(std::cin,Line);){
		std::cout<<Interpreter::Interpreter(Line)<<std::endl;
		std::cout<<"user> ";
	}
}
