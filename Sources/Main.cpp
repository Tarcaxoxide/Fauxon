#include<iostream>
#include<string>
#include<fstream>

/*test*/#include<DataTypes/DecimalNumberValue.hpp>
int main(int c,char** v){
    /*test*/Fauxon::DataTypes::DecimalNumberValue TestNumber(6.5);

    /*test*/std::cout<<TestNumber.ToString()<<std::endl;

    /*test*/if(TestNumber<6.5)std::cout<<"less than 6.5"<<std::endl;
    /*test*/if(TestNumber<5.6)std::cout<<"less than 5.6"<<std::endl;
    /*test*/if(TestNumber<7.5)std::cout<<"less than 7.6"<<std::endl;
    /*test*/if(TestNumber<5.5)std::cout<<"less than 5.5"<<std::endl;
    /*test*/if(TestNumber<6.7)std::cout<<"less than 6.7"<<std::endl;

    /*test*/if(TestNumber==6.5)std::cout<<"is 6.5"<<std::endl;

    /*test*/if(TestNumber>6.5)std::cout<<"more than 6.5"<<std::endl;
    /*test*/if(TestNumber>5.6)std::cout<<"more than 5.6"<<std::endl;
    /*test*/if(TestNumber>7.5)std::cout<<"more than 7.6"<<std::endl;
    /*test*/if(TestNumber>5.5)std::cout<<"more than 5.5"<<std::endl;
    /*test*/if(TestNumber>6.7)std::cout<<"more than 6.7"<<std::endl;
    

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