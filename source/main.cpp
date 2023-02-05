#include<iostream>

int main(int argc,char** argv){
    std::cout<<"Args:{"<<std::endl;
    for(size_t i=0;i<argc;i++){
        std::cout<<"\t["<<i<<"]:"<<argv[i]<<(i<argc-1?",":"")<<std::endl;
    }
    std::cout<<"};"<<std::endl;
}