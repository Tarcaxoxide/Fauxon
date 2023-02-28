#include<iostream>
#include<string>
#include<fstream>

/*test*/#include<DataTypes/DecimalNumberValue.hpp>
int main(int c,char** v){
    /*test*/
    Fauxon::DataTypes::DecimalNumberValue TestNumber(9000);
    std::cout<<TestNumber.ToString()<<std::endl;
    TestNumber+=1.5;
    std::cout<<TestNumber.ToString()<<std::endl;
    return 0;
    /*test*/
    if(c == 2){
        std::ifstream file(v[1]);
        for(std::string Line;std::getline(file,Line);){
            if(!Line.size())break;
            std::cout<<""<<Line<<std::endl;
        }
        file.close();
    }else if(c == 1){
    std::cout<<":>";
        for(std::string Line;std::getline(std::cin,Line);){
            if(!Line.size())break;
            std::cout<<"<:"<<Line<<std::endl;
            std::cout<<":>";
        }
    }
}