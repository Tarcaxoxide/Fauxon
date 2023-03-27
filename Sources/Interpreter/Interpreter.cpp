#include<Interpreter/Interpreter.hpp>
#include<Common/Tokenizer.hpp>
#include<Common/Parser.hpp>
#include<deque>


#include<iostream>
#include<cassert>

std::deque<std::deque<std::string>> stack;

std::deque<std::string> Calculate_ArrayOnArray(const std::deque<std::string>& A,const std::deque<std::string>& B,const char op){
	std::deque<std::string> Result;
	Result.push_back("[");
	switch(op){
		case '+':{
			for(size_t i=0;(i<A.size()||i<B.size());i++){
				if(A[i][0]=='['||A[i][0]==']')continue;
				if(B[i][0]=='['||B[i][0]==']')continue;
				if(!(i<A.size())){
					Result.push_back(B[i]);
				}else if(!(i<B.size())){
					Result.push_back(A[i]);
				}else{
					Result.push_back(std::to_string(std::stoll(A[i])+std::stoll(B[i])));
				}
			}
		}break;
		case '-':{
			for(size_t i=0;(i<A.size()||i<B.size());i++){
				if(A[i][0]=='['||A[i][0]==']')continue;
				if(B[i][0]=='['||B[i][0]==']')continue;
				if(!(i<A.size())){
					Result.push_back(B[i]);
				}else if(!(i<B.size())){
					Result.push_back(A[i]);
				}else{
					Result.push_back(std::to_string(std::stoll(A[i])-std::stoll(B[i])));
				}
			}
		}break;
		case '*':{
			for(size_t i=0;(i<A.size()||i<B.size());i++){
				if(A[i][0]=='['||A[i][0]==']')continue;
				if(B[i][0]=='['||B[i][0]==']')continue;
				if(!(i<A.size())){
					Result.push_back(B[i]);
				}else if(!(i<B.size())){
					Result.push_back(A[i]);
				}else{
					Result.push_back(std::to_string(std::stoll(A[i])*std::stoll(B[i])));
				}
			}
		}break;
		case '/':{
			for(size_t i=0;(i<A.size()||i<B.size());i++){
				if(A[i][0]=='['||A[i][0]==']')continue;
				if(B[i][0]=='['||B[i][0]==']')continue;
				if(!(i<A.size())){
					Result.push_back(B[i]);
				}else if(!(i<B.size())){
					Result.push_back(A[i]);
				}else{
					Result.push_back(std::to_string(std::stoll(A[i])/std::stoll(B[i])));
				}
			}
		}break;
	}
	Result.push_back("]");
	return Result;
}
std::deque<std::string> Calculate_ArrayOnList(const std::deque<std::string>& A,const std::deque<std::string>& B,const char op){
	std::deque<std::string> Result;
	Result.push_back("<");
	switch(op){
		case '+':{
			for(size_t i=0;(i<A.size()||i<B.size());i++){
				if(A[i][0]=='['||A[i][0]==']')continue;
				if(B[i][0]=='<'||B[i][0]=='>')continue;
				if(!(i<A.size())){
					Result.push_back(B[i]);
				}else if(!(i<B.size())){
					Result.push_back(A[i]);
				}else{
					Result.push_back(std::to_string(std::stoll(A[i])+std::stoll(B[i])));
				}
			}
		}break;
		case '-':{
			for(size_t i=0;(i<A.size()||i<B.size());i++){
				if(A[i][0]=='['||A[i][0]==']')continue;
				if(B[i][0]=='<'||B[i][0]=='>')continue;
				if(!(i<A.size())){
					Result.push_back(B[i]);
				}else if(!(i<B.size())){
					Result.push_back(A[i]);
				}else{
					Result.push_back(std::to_string(std::stoll(A[i])-std::stoll(B[i])));
				}
			}
		}break;
		case '*':{
			for(size_t i=0;(i<A.size()||i<B.size());i++){
				if(A[i][0]=='['||A[i][0]==']')continue;
				if(B[i][0]=='<'||B[i][0]=='>')continue;
				if(!(i<A.size())){
					Result.push_back(B[i]);
				}else if(!(i<B.size())){
					Result.push_back(A[i]);
				}else{
					Result.push_back(std::to_string(std::stoll(A[i])*std::stoll(B[i])));
				}
			}
		}break;
		case '/':{
			for(size_t i=0;(i<A.size()||i<B.size());i++){
				if(A[i][0]=='['||A[i][0]==']')continue;
				if(B[i][0]=='<'||B[i][0]=='>')continue;
				if(!(i<A.size())){
					Result.push_back(B[i]);
				}else if(!(i<B.size())){
					Result.push_back(A[i]);
				}else{
					Result.push_back(std::to_string(std::stoll(A[i])/std::stoll(B[i])));
				}
			}
		}break;
	}
	Result.push_back(">");
	return Result;
}
std::deque<std::string> Calculate_ArrayOnSingle(const std::deque<std::string>& A,const std::deque<std::string>& B,const char op){
	std::deque<std::string> Result;
	switch(op){
		case '+':{
			Result.push_back(std::to_string(std::stoll(A[1])+std::stoll(B[0])));
		}break;
		case '-':{
			Result.push_back(std::to_string(std::stoll(A[1])-std::stoll(B[0])));
		}break;
		case '*':{
			Result.push_back(std::to_string(std::stoll(A[1])*std::stoll(B[0])));
		}break;
		case '/':{
			Result.push_back(std::to_string(std::stoll(A[1])/std::stoll(B[0])));
		}break;
	}
	return Result;
}
std::deque<std::string> Calculate_ListOnArray(const std::deque<std::string>& A,const std::deque<std::string>& B,const char op){
	std::deque<std::string> Result;
	switch(op){
		case '+':{
			for(size_t iA=1;iA<A.size()-1;iA++){
				for(size_t iB=1;iB<B.size()-1;iB++){
					if(iB-1){
						std::string SubResult = std::to_string(((std::stoll(Result[iA-1])+std::stoll(A[iA])))+std::stoll(B[iB]));
						Result.erase(Result.begin()+(iA-1));
						Result.insert(Result.begin()+(iA-1),SubResult);
					}else{
						Result.push_back(std::to_string(std::stoll(A[iA])+std::stoll(B[iB])));
					}
				}
			}
		}break;
		case '-':{
			for(size_t iA=1;iA<A.size()-1;iA++){
				for(size_t iB=1;iB<B.size()-1;iB++){
					if(iB-1){
						std::string SubResult = std::to_string(((std::stoll(Result[iA-1])+std::stoll(A[iA])))-std::stoll(B[iB]));
						Result.erase(Result.begin()+(iA-1));
						Result.insert(Result.begin()+(iA-1),SubResult);
					}else{
						Result.push_back(std::to_string(std::stoll(A[iA])-std::stoll(B[iB])));
					}
				}
			}
		}break;
		case '*':{
			for(size_t iA=1;iA<A.size()-1;iA++){
				for(size_t iB=1;iB<B.size()-1;iB++){
					if(iB-1){
						std::string SubResult = std::to_string(((std::stoll(Result[iA-1])+std::stoll(A[iA])))*std::stoll(B[iB]));
						Result.erase(Result.begin()+(iA-1));
						Result.insert(Result.begin()+(iA-1),SubResult);
					}else{
						Result.push_back(std::to_string(std::stoll(A[iA])*std::stoll(B[iB])));
					}
				}
			}
		}break;
		case '/':{
			for(size_t iA=1;iA<A.size()-1;iA++){
				for(size_t iB=1;iB<B.size()-1;iB++){
					if(iB-1){
						std::string SubResult = std::to_string(((std::stoll(Result[iA-1])+std::stoll(A[iA])))/std::stoll(B[iB]));
						Result.erase(Result.begin()+(iA-1));
						Result.insert(Result.begin()+(iA-1),SubResult);
					}else{
						Result.push_back(std::to_string(std::stoll(A[iA])/std::stoll(B[iB])));
					}
				}
			}
		}break;
	}
	Result.push_front("[");
	Result.push_back("]");
	return Result;
}
std::deque<std::string> Calculate_ListOnList(const std::deque<std::string>& A,const std::deque<std::string>& B,const char op){
	std::deque<std::string> Result;
	switch(op){
		case '+':{
			for(size_t iA=1;iA<A.size()-1;iA++){
				for(size_t iB=1;iB<B.size()-1;iB++){
					if(iB-1){
						std::string SubResult = std::to_string(((std::stoll(Result[iA-1])+std::stoll(A[iA])))+std::stoll(B[iB]));
						Result.erase(Result.begin()+(iA-1));
						Result.insert(Result.begin()+(iA-1),SubResult);
					}else{
						Result.push_back(std::to_string(std::stoll(A[iA])+std::stoll(B[iB])));
					}
				}
			}
		}break;
		case '-':{
			for(size_t iA=1;iA<A.size()-1;iA++){
				for(size_t iB=1;iB<B.size()-1;iB++){
					if(iB-1){
						std::string SubResult = std::to_string(((std::stoll(Result[iA-1])+std::stoll(A[iA])))-std::stoll(B[iB]));
						Result.erase(Result.begin()+(iA-1));
						Result.insert(Result.begin()+(iA-1),SubResult);
					}else{
						Result.push_back(std::to_string(std::stoll(A[iA])-std::stoll(B[iB])));
					}
				}
			}
		}break;
		case '*':{
			for(size_t iA=1;iA<A.size()-1;iA++){
				for(size_t iB=1;iB<B.size()-1;iB++){
					if(iB-1){
						std::string SubResult = std::to_string(((std::stoll(Result[iA-1])+std::stoll(A[iA])))*std::stoll(B[iB]));
						Result.erase(Result.begin()+(iA-1));
						Result.insert(Result.begin()+(iA-1),SubResult);
					}else{
						Result.push_back(std::to_string(std::stoll(A[iA])*std::stoll(B[iB])));
					}
				}
			}
		}break;
		case '/':{
			for(size_t iA=1;iA<A.size()-1;iA++){
				for(size_t iB=1;iB<B.size()-1;iB++){
					if(iB-1){
						std::string SubResult = std::to_string(((std::stoll(Result[iA-1])+std::stoll(A[iA])))/std::stoll(B[iB]));
						Result.erase(Result.begin()+(iA-1));
						Result.insert(Result.begin()+(iA-1),SubResult);
					}else{
						Result.push_back(std::to_string(std::stoll(A[iA])/std::stoll(B[iB])));
					}
				}
			}
		}break;
	}
	Result.push_front("<");
	Result.push_back(">");
	return Result;
}
std::deque<std::string> Calculate_ListOnSingle(const std::deque<std::string>& A,const std::deque<std::string>& B,const char op){
	std::deque<std::string> Result;
	switch(op){
		case '+':{
			for(size_t iA=0;iA<A.size();iA++){
				if(A[iA][0]=='<'||A[iA][0]=='>')continue;
				Result.push_back(std::to_string(std::stoll(A[iA])+std::stoll(B[0])));
			}
		}break;
		case '-':{
			for(size_t iA=0;iA<A.size();iA++){
				if(A[iA][0]=='<'||A[iA][0]=='>')continue;
				Result.push_back(std::to_string(std::stoll(A[iA])-std::stoll(B[0])));
			}
		}break;
		case '*':{
			for(size_t iA=0;iA<A.size();iA++){
				if(A[iA][0]=='<'||A[iA][0]=='>')continue;
				Result.push_back(std::to_string(std::stoll(A[iA])*std::stoll(B[0])));
			}
		}break;
		case '/':{
			for(size_t iA=0;iA<A.size();iA++){
				if(A[iA][0]=='<'||A[iA][0]=='>')continue;
				Result.push_back(std::to_string(std::stoll(A[iA])/std::stoll(B[0])));
			}
		}break;
	}
	return Result;
}
std::deque<std::string> Calculate_SingleOnList(const std::deque<std::string>& A,const std::deque<std::string>& B,const char op){
	std::deque<std::string> Result;
	switch(op){
		case '+':{
			for(size_t iB=0;iB<B.size();iB++){
				if(A[iB][0]=='<'||A[iB][0]=='>')continue;
				Result.push_back(std::to_string(std::stoll(A[0])+std::stoll(B[iB])));
			}
		}break;
		case '-':{
			for(size_t iB=0;iB<B.size();iB++){
				if(A[iB][0]=='<'||A[iB][0]=='>')continue;
				Result.push_back(std::to_string(std::stoll(A[0])-std::stoll(B[iB])));
			}
		}break;
		case '*':{
			for(size_t iB=0;iB<B.size();iB++){
				if(A[iB][0]=='<'||A[iB][0]=='>')continue;
				Result.push_back(std::to_string(std::stoll(A[0])*std::stoll(B[iB])));
			}
		}break;
		case '/':{
			for(size_t iB=0;iB<B.size();iB++){
				if(A[iB][0]=='<'||A[iB][0]=='>')continue;
				Result.push_back(std::to_string(std::stoll(A[0])/std::stoll(B[iB])));
			}
		}break;
	}
	return Result;
}
std::deque<std::string> Calculate_SingleOnArray(const std::deque<std::string>& A,const std::deque<std::string>& B,const char op){
	std::deque<std::string> Result;
	switch(op){
		case '+':{
			for(size_t iB=0;iB<B.size();iB++){
				if(A[iB][0]=='['||A[iB][0]==']')continue;
				Result.push_back(std::to_string(std::stoll(A[0])+std::stoll(B[iB])));
			}
		}break;
		case '-':{
			for(size_t iB=0;iB<B.size();iB++){
				if(A[iB][0]=='['||A[iB][0]==']')continue;
				Result.push_back(std::to_string(std::stoll(A[0])-std::stoll(B[iB])));
			}
		}break;
		case '*':{
			for(size_t iB=0;iB<B.size();iB++){
				if(A[iB][0]=='['||A[iB][0]==']')continue;
				Result.push_back(std::to_string(std::stoll(A[0])*std::stoll(B[iB])));
			}
		}break;
		case '/':{
			for(size_t iB=0;iB<B.size();iB++){
				if(A[iB][0]=='['||A[iB][0]==']')continue;
				Result.push_back(std::to_string(std::stoll(A[0])/std::stoll(B[iB])));
			}
		}break;
	}
	return Result;
}
std::deque<std::string> Calculate_SingleOnSingle(const std::deque<std::string>& A,const std::deque<std::string>& B,const char op){
	std::deque<std::string> Result;
	switch(op){
		case '+':{
			Result.push_back(std::to_string(std::stoll(A[0])+std::stoll(B[0])));
		}break;
		case '-':{
			Result.push_back(std::to_string(std::stoll(A[0])-std::stoll(B[0])));
		}break;
		case '*':{
			Result.push_back(std::to_string(std::stoll(A[0])*std::stoll(B[0])));
		}break;
		case '/':{
			Result.push_back(std::to_string(std::stoll(A[0])/std::stoll(B[0])));
		}break;
	}
	return Result;
}
namespace Interpreter{
	std::string Interpreter(std::string input){
		std::deque<std::deque<std::string>> tokens = Common::Tokenizer(input);
		std::deque<std::deque<std::string>> parsed = Common::Parser(tokens);
		std::string Result="";
		for(auto token:parsed){
			switch(token[0][0]){
				case '?':{
					assert(stack.size()>0);
					for(auto stackElement:stack){
						for(auto stackItem:stackElement){
							std::cout<<stackItem<<" ";
						}
					}
					stack.clear();
				}break;
				case '+':case '-':case '*':case '/':{
					assert(stack.size()>0);
					std::deque<std::string> local_stack_B = stack.back();stack.pop_back();
					assert(stack.size()>0);
					std::deque<std::string> local_stack_A = stack.back();stack.pop_back();
					std::deque<std::string> local_stack_Results;
					switch(local_stack_A[0][0]){
						case '<'/*list*/:{
							switch(local_stack_B[0][0]){
								case '<'/*list*/:{local_stack_Results = Calculate_ListOnList(local_stack_A,local_stack_B,token[0][0]);}break;
								case '['/*array*/:{local_stack_Results = Calculate_ListOnArray(local_stack_A,local_stack_B,token[0][0]);}break;
								case '{'/*body*/:{assert(false);/*you can't do math with this*/}break;
								case '('/*argument list*/:{assert(false);/*you can't do math with this*/}break;
								default/*single number, hopefully*/:{local_stack_Results = Calculate_ListOnSingle(local_stack_A,local_stack_B,token[0][0]);}break;
							}
						}break;
						case '['/*array*/:{
							switch(local_stack_B[0][0]){
								case '<'/*list*/:{local_stack_Results = Calculate_ArrayOnList(local_stack_A,local_stack_B,token[0][0]);}break;
								case '['/*array*/:{local_stack_Results = Calculate_ArrayOnArray(local_stack_A,local_stack_B,token[0][0]);}break;
								case '{'/*body*/:{assert(false);/*you can't do math with this*/}break;
								case '('/*argument list*/:{assert(false);/*you can't do math with this*/}break;
								default/*single number, hopefully*/:{local_stack_Results = Calculate_ArrayOnSingle(local_stack_A,local_stack_B,token[0][0]);}break;
							}
						}break;
						case '{'/*body*/:{assert(false);/*you can't do math with this*/}break;
						case '('/*argument list*/:{assert(false);/*you can't do math with this*/}break;
						default/*single number, hopefully*/:{
							switch(local_stack_B[0][0]){
								case '<'/*list*/:{local_stack_Results = Calculate_SingleOnList(local_stack_A,local_stack_B,token[0][0]);}break;
								case '['/*array*/:{local_stack_Results = Calculate_SingleOnArray(local_stack_A,local_stack_B,token[0][0]);}break;
								case '{'/*body*/:{assert(false);/*you can't do math with this*/}break;
								case '('/*argument list*/:{assert(false);/*you can't do math with this*/}break;
								default/*single number, hopefully*/:{local_stack_Results = Calculate_SingleOnSingle(local_stack_A,local_stack_B,token[0][0]);}break;
							}
						}break;
					}
					stack.push_back(local_stack_Results);
				}break;
				default:{
					stack.push_back(token);
				}break;
			}
		}
		//Result.erase(Result.length()-1,1);
		return Result;
	}
};