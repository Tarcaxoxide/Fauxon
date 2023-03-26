#include<Common/Tokenizer.hpp>
namespace Common{
	std::deque<std::deque<std::string>> Tokenizer(std::string input){
		std::deque<std::deque<std::string>> tokens;
		std::deque<std::string> token;
		std::string buffer="";
		for(size_t i=0;i<input.size();i++){
			switch(input[i]){
				case ' ':case '\n':case '\r':{
					if(buffer.length()){token.push_back(buffer);tokens.push_back(token);token.clear();buffer="";}
				}break;
				case '\'':{
					if(buffer.length()){token.push_back(buffer);tokens.push_back(token);token.clear();buffer="";}
					token.push_back(input.substr(i,1));
					while(++i<input.size()&&(input[i]!='\''||input[i-1]=='\\')){token.push_back(input.substr(i,1));}
					token.push_back(input.substr(i,1));
					tokens.push_back(token);
					token.clear();
				}break;
				case '"':{
					if(buffer.length()){token.push_back(buffer);tokens.push_back(token);token.clear();buffer="";}
					token.push_back(input.substr(i,1));
					while(++i<input.size()&&(input[i]!='"'||input[i-1]=='\\')){token.push_back(input.substr(i,1));}
					token.push_back(input.substr(i,1));
					tokens.push_back(token);
					token.clear();
				}break;
				case '`':{
					if(buffer.length()){token.push_back(buffer);tokens.push_back(token);token.clear();buffer="";}
					token.push_back(input.substr(i,1));
					while(++i<input.size()&&(input[i]!='`'||input[i-1]=='\\')){token.push_back(input.substr(i,1));}
					token.push_back(input.substr(i,1));
					tokens.push_back(token);
					token.clear();
				}break;
				case '0':case '1':case '2':case '3':case '4':case '5':case '6':case '7':case '8':case '9':case '.':{
					if(buffer.length()){token.push_back(buffer);tokens.push_back(token);token.clear();buffer="";}
					std::string numberBuffer=input.substr(i,1);
					while(++i<input.size()&&(input[i]=='0'
										   ||input[i]=='1'
										   ||input[i]=='2'
										   ||input[i]=='3'
										   ||input[i]=='4'
										   ||input[i]=='5'
										   ||input[i]=='6'
										   ||input[i]=='7'
										   ||input[i]=='8'
										   ||input[i]=='9'
										   ||input[i]=='0'
										   ||input[i]=='.')){numberBuffer+=input.substr(i,1);}
					token.push_back(numberBuffer);
					tokens.push_back(token);
					token.clear();i--;
				}break;
				case '+':case '-':case '*':case '/':case '=':{
					if(buffer.length()){token.push_back(buffer);tokens.push_back(token);token.clear();buffer="";}
					token.push_back(input.substr(i,1));
					tokens.push_back(token);
					token.clear();
				}break;
				case '<':case '>':case '(':case ')':case '{':case '}':case '[':case ']':{
					if(buffer.length()){token.push_back(buffer);tokens.push_back(token);token.clear();buffer="";}
					token.push_back(input.substr(i,1));
					tokens.push_back(token);
					token.clear();
				}break;
				default:{
					buffer+=input[i];
				}break;
			}
		}
		if(buffer.length()){token.push_back(buffer);tokens.push_back(token);token.clear();buffer="";}
		return tokens;
	}
};