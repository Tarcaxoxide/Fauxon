#include<Common/Parser.hpp>
namespace Common{	
	std::deque<std::deque<std::string>> Parser(std::deque<std::deque<std::string>> input){
		std::deque<std::deque<std::string>> line;
		
		for(int64_t ia=0;ia<input.size();ia++){
			for(int64_t ib=0;ib<input[ia].size();ib++){
				switch(input[ia][ib][0]){
					case '+':case '-':case '*':case '/':{
						std::string leftBuffer=ib-1>-1?(input[ia][ib-1]):(ia-1>-1?input[ia-1][input[ia-1].size()-1]:"...");
						std::string operatorBuffer=input[ia][ib];
						std::string rightBuffer=ib+1<input[ia].size()?(input[ia][ib+1]):(ia+1<input.size()?input[ia+1][0]:"...");
						std::deque<std::string> Buffer;
						Buffer.push_back(leftBuffer);
						Buffer.push_back(operatorBuffer);
						Buffer.push_back(rightBuffer);
						line.push_back(Buffer);
						ia++;ib++;
					}break;
					case '[':{
						std::deque<std::string> Buffer;
						while(ia<input.size()&&ib<input[ia].size()&&input[ia][ib][0] != ']'){
							Buffer.push_back(input[ia][ib]);
							if(++ib>input[ia].size()){ib=0;ia++;}
						}
						if(ia<input.size()){Buffer.push_back(input[ia][ib]);}
						line.push_back(Buffer);
					}break;
					case '(':{
						std::deque<std::string> Buffer;
						while(ia<input.size()&&ib<input[ia].size()&&input[ia][ib][0] != ')'){
							Buffer.push_back(input[ia][ib]);
							if(++ib>input[ia].size()){ib=0;ia++;}
						}
						if(ia<input.size()){Buffer.push_back(input[ia][ib]);}
						line.push_back(Buffer);
					}break;
					case '{':{
						std::deque<std::string> Buffer;
						while(ia<input.size()&&ib<input[ia].size()&&input[ia][ib][0] != '}'){
							Buffer.push_back(input[ia][ib]);
							if(++ib>input[ia].size()){ib=0;ia++;}
						}
						if(ia<input.size()){Buffer.push_back(input[ia][ib]);}
						line.push_back(Buffer);
					}break;
					case '<':{
						std::deque<std::string> Buffer;
						while(ia<input.size()&&ib<input[ia].size()&&input[ia][ib][0] != '>'){
							Buffer.push_back(input[ia][ib]);
							if(++ib>input[ia].size()){ib=0;ia++;}
						}
						if(ia<input.size()){Buffer.push_back(input[ia][ib]);}
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
