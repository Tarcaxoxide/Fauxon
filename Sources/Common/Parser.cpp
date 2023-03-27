#include<Common/Parser.hpp>



#include<iostream>


namespace Common{	
	std::deque<std::deque<std::string>> Parser(std::deque<std::deque<std::string>> input){
		std::deque<std::deque<std::string>> line;
		
		for(int64_t ia=0;ia<input.size();ia++){
			for(int64_t ib=0;ib<input[ia].size();ib++){
				switch(input[ia][ib][0]){
					case '+':case '-':case '*':case '/':{
						std::string leftBuffer=ib-1>-1?(input[ia][ib-1]):(ia-1>-1?input[ia-1][input[ia-1].size()-1]:"..");
						std::string operatorBuffer=input[ia][ib];
						std::string rightBuffer=ib+1<input[ia].size()?(input[ia][ib+1]):(ia+1<input.size()?input[ia+1][0]:"..");
						std::deque<std::string> Buffer;
						if(leftBuffer[0]==']'||leftBuffer[0]==')'||leftBuffer[0]=='}'||leftBuffer[0]=='>'){leftBuffer="..";}
						if(rightBuffer[0]=='['||rightBuffer[0]=='('||rightBuffer[0]=='{'||rightBuffer[0]=='<'){rightBuffer="..";}
						Buffer.push_back(leftBuffer);
						Buffer.push_back(operatorBuffer);
						Buffer.push_back(rightBuffer);
						line.push_back(Buffer);
						if(ia<input.size()-1&&ib<input[ia].size()){ib++;}
					}break;
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
					default:{}break;
				}
			}
		}
		return line;
	}
};
