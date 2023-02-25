//-Ofast
#include<iostream>
#include<string>
int main(){
    std::cout<<":>";
    for(std::string Line;std::getline(std::cin,Line);){
        if(!Line.size())break;
        std::cout<<"<:"<<Line<<std::endl;
        std::cout<<":>";
    }
}