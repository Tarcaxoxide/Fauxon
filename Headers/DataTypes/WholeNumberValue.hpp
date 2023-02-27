#ifndef __Fauxon_DataType_WholeNumberValue
#define __Fauxon_DataType_WholeNumberValue
#include<string>
#include<cassert>
#include<deque>
#include<iterator>
#include<algorithm>
#include<iostream>
#include<sstream>
namespace Fauxon{
    namespace DataTypes{
        struct WholeNumberValue{
            uint8_t Sign='+';
            uint8_t oSign='-';
            std::string Number;
            //constructors!, constructors!, constructors!, construct!
            WholeNumberValue(int64_t number);
            WholeNumberValue(std::string number);
            WholeNumberValue(const WholeNumberValue& number);
            //To string for printing the number out (shshsh... it's already a string XD)
            std::string ToString();
            //Base math function
            void Add(std::string number);inline void Add(WholeNumberValue number){Add(number.Number);}
            void Subtract(std::string number);inline void Subtract(WholeNumberValue number){Subtract(number.ToString());}
            void Multiply(std::string number);inline void Multiply(WholeNumberValue number){Multiply(number.ToString());}
            void Divide(std::string number);inline void Divide(WholeNumberValue number){Divide(number.ToString());}
            void FlipSign();
            //Comparision operators
            bool operator<(std::string number);
            inline bool operator<(WholeNumberValue number){return (*this)<number.ToString();}
            inline bool operator<(int64_t number){return (*this)<std::to_string(number);}
            bool operator>(std::string number);
            inline bool operator>(WholeNumberValue number){return (*this)>number.ToString();}
            inline bool operator>(int64_t number){return (*this)>std::to_string(number);}
            bool operator<=(std::string number);
            inline bool operator<=(WholeNumberValue number){return (*this)<=number.ToString();}
            inline bool operator<=(int64_t number){return (*this)<=std::to_string(number);}
            bool operator>=(std::string number);
            inline bool operator>=(WholeNumberValue number){return (*this)>=number.ToString();}
            inline bool operator>=(int64_t number){return (*this)>=std::to_string(number);}
            bool operator==(std::string number);
            inline bool operator==(WholeNumberValue number){return (*this)==number.ToString();}
            inline bool operator==(int64_t number){return (*this)==std::to_string(number);}
            bool operator!=(std::string number);
            inline bool operator!=(WholeNumberValue number){return (*this)!=number.ToString();}
            inline bool operator!=(int64_t number){return (*this)!=std::to_string(number);}
            //Math operator
            WholeNumberValue& operator+=(std::string number);
            inline WholeNumberValue& operator+=(WholeNumberValue number){return (*this)+=number.ToString();}
            inline WholeNumberValue& operator+=(int64_t number){return (*this)+=std::to_string(number);}
            WholeNumberValue& operator-=(std::string number);
            inline WholeNumberValue& operator-=(WholeNumberValue number){return (*this)-=number.ToString();}
            inline WholeNumberValue& operator-=(int64_t number){return (*this)-=std::to_string(number);}
            WholeNumberValue& operator*=(std::string number);
            inline WholeNumberValue& operator*=(WholeNumberValue number){return (*this)*=number.ToString();}
            inline WholeNumberValue& operator*=(int64_t number){return (*this)*=std::to_string(number);}
            WholeNumberValue& operator/=(std::string number);
            inline WholeNumberValue& operator/=(WholeNumberValue number){return (*this)/=number.ToString();}
            inline WholeNumberValue& operator/=(int64_t number){return (*this)/=std::to_string(number);}
            WholeNumberValue& operator=(std::string number);
            inline WholeNumberValue& operator=(WholeNumberValue number){return (*this)=number.ToString();}
            inline WholeNumberValue& operator=(int64_t number){return (*this)=std::to_string(number);}
        };
    };
};
#endif