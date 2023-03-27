#include<Common/Parser.hpp>

namespace Common{	
	std::deque<std::deque<std::string>> Parser(std::deque<std::deque<std::string>> input){
		std::deque<std::deque<std::string>> line;
		
		for(int64_t ia=0;ia<input.size();ia++){
			for(int64_t ib=0;ib<input[ia].size();ib++){
				switch(input[ia][ib][0]){
					case '[':{
						std::deque<std::string> Buffer;
						do{
							do{
								Buffer.push_back(input[ia][ib++]);
							}while(ib<input[ia].size());
							ib=0;
							ia++;
						}while(ia<input.size()&&input[ia][ib][0]!=']');
						Buffer.push_back(input[ia][ib++]);
						line.push_back(Buffer);
					}break;
					case '(':{
						std::deque<std::string> Buffer;
						do{
							do{
								Buffer.push_back(input[ia][ib++]);
							}while(ib<input[ia].size());
							ib=0;
							ia++;
						}while(ia<input.size()&&input[ia][ib][0]!=')');
						Buffer.push_back(input[ia][ib++]);
						line.push_back(Buffer);
					}break;
					case '{':{
						std::deque<std::string> Buffer;
						do{
							do{
								Buffer.push_back(input[ia][ib++]);
							}while(ib<input[ia].size());
							ib=0;
							ia++;
						}while(ia<input.size()&&input[ia][ib][0]!='}');
						Buffer.push_back(input[ia][ib++]);
						line.push_back(Buffer);
					}break;
					case '<':{
						std::deque<std::string> Buffer;
						do{
							do{
								Buffer.push_back(input[ia][ib++]);
							}while(ib<input[ia].size());
							ib=0;
							ia++;
						}while(ia<input.size()&&input[ia][ib][0]!='>');
						Buffer.push_back(input[ia][ib++]);
						line.push_back(Buffer);
					}break;
					default:{
						std::deque<std::string> Buffer;
						Buffer.push_back(input[ia][ib]);
						line.push_back(Buffer);
					}break;
				}
			}
		}
		return line;
	}
};
