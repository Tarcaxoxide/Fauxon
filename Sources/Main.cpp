#include<iostream>
#include<string>
#include<fstream>

/*test*/#include<DataTypes/NumberValue.hpp>
int main(int c,char** v){
    /*test*/Fauxon::DataTypes::NumberValue TestNumber("100");

    /*test*/std::cout<<TestNumber.ToString()<<std::endl;

    /*test*/TestNumber*=4;

    /*test*/if(TestNumber > 100)std::cout<<"bigger than 100"<<std::endl;
    /*test*/if(TestNumber > 200)std::cout<<"bigger than 200"<<std::endl;
    /*test*/if(TestNumber > 300)std::cout<<"bigger than 300"<<std::endl;
    /*test*/if(TestNumber > 400)std::cout<<"bigger than 400"<<std::endl;
    /*test*/if(TestNumber > 500)std::cout<<"bigger than 500"<<std::endl;
    /*test*/if(TestNumber > 600)std::cout<<"bigger than 600"<<std::endl;
    /*test*/if(TestNumber == 100)std::cout<<"equal to 100"<<std::endl;
    /*test*/if(TestNumber == 200)std::cout<<"equal to 200"<<std::endl;
    /*test*/if(TestNumber == 300)std::cout<<"equal to 300"<<std::endl;
    /*test*/if(TestNumber == 400)std::cout<<"equal to 400"<<std::endl;
    /*test*/if(TestNumber == 500)std::cout<<"equal to 500"<<std::endl;
    /*test*/if(TestNumber == 600)std::cout<<"equal to 600"<<std::endl;
    /*test*/if(TestNumber < 100)std::cout<<"lesser than 100"<<std::endl;
    /*test*/if(TestNumber < 200)std::cout<<"lesser than 200"<<std::endl;
    /*test*/if(TestNumber < 300)std::cout<<"lesser than 300"<<std::endl;
    /*test*/if(TestNumber < 400)std::cout<<"lesser than 400"<<std::endl;
    /*test*/if(TestNumber < 500)std::cout<<"lesser than 500"<<std::endl;
    /*test*/if(TestNumber < 600)std::cout<<"lesser than 600"<<std::endl;

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