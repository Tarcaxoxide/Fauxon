#include<deque>
#include<string>
#include<iostream>
#include<cpp_wrapper/CommonParem.hpp>

namespace Fauxon{void Main(CommonParem_cl& Args);};

int main(int argc,char** argv){
    std::deque<std::string> Args;
    for(size_t i=(size_t)argc;(bool)i;i--){
        Args.push_back(std::string(argv[argc-i]));
    }
    
    CommonParem_cl Params;
    for(size_t i=0;i<Args.size();i++){
        if(!i){
            Params.set("Path",Args[i]);
        }else{
            Params.set(std::to_string(i),Args[i]);
        }
    }
    
    LeepBack:
    Params.FlipState();
    Fauxon::Main(Params);

    switch(Params.GetState()){
        case State_en::STATE_BAD:{
            return -1;
        }break;
        case State_en::STATE_GOOD:{
            return 0;
        }break;
        case State_en::STATE_LOOPBACK_REQUEST:{
            goto LeepBack;
        }break;
        case State_en::STATE_LOOPBACK_REPLY:{
            //do nothing?
        }break;
    }
    return 0;
}