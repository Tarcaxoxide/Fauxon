#ifndef __Fauxon_Common_Tokenizer
#define __Fauxon_Common_Tokenizer
#include<string>
#include<deque>

namespace Common{	
	std::deque<std::deque<std::string>> Tokenizer(std::string input);
};
#endif