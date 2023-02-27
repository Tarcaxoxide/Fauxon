#include<iostream>
#include<string>
#include<fstream>

/*test*/#include<DataTypes/NumberValue.hpp>
int main(int c,char** v){
    /*test*/Fauxon::DataTypes::NumberValue TestNumber("999999");

    /*test*/std::cout<<TestNumber.ToString()<<std::endl;

    /*test*/TestNumber.Add("1");

    /*test*/std::cout<<TestNumber.ToString()<<std::endl;

    /*test*/return 0;
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