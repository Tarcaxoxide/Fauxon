#include<Interpreter/Interpreter.hpp>
#include<Common/Tokenizer.hpp>
#include<Common/Parser.hpp>
#include<deque>

namespace Interpreter{
	std::string Interpreter(std::string input){
		std::deque<std::deque<std::string>> tokens = Common::Tokenizer(input);
		std::deque<std::deque<std::string>> parsed = Common::Parser(tokens);
		std::string Result="";
		for(auto token:parsed){
			for(auto part:token){
				Result+=part;
			}
			Result+="\n";
		}
		Result.erase(Result.length()-1,1);
		return Result;
	}
};