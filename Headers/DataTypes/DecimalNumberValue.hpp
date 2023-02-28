#ifndef __Fauxon_DataType_DecimalNumberValue
#define __Fauxon_DataType_DecimalNumberValue
#include<DataTypes/WholeNumberValue.hpp>

namespace Fauxon{
    namespace DataTypes{
        struct DecimalNumberValue{
            Fauxon::DataTypes::WholeNumberValue WholeNumber;
            Fauxon::DataTypes::WholeNumberValue DecimalNumber;
            size_t DecimalPlaces=0;
            //constructors!, constructors!, constructors!, construct!
            DecimalNumberValue();
            DecimalNumberValue(long double number);
            DecimalNumberValue(std::string number);
            DecimalNumberValue(std::string wholeNumber,std::string decimalNumber);
            DecimalNumberValue(const DecimalNumberValue& number);
            DecimalNumberValue(const WholeNumberValue& number);
            DecimalNumberValue(const WholeNumberValue& wholeNumber,const WholeNumberValue& decimalNumber);
            //To string for printing the number out (shshsh... it's already a string XD)
            std::string ToString()const;
            //Base math function
            void Add(std::string number);inline void Add(const WholeNumberValue& number){Add(number.Number);}
            void Subtract(std::string number);inline void Subtract(const WholeNumberValue& number){Subtract(number.ToString());}
            void Multiply(std::string number);inline void Multiply(const WholeNumberValue& number){Multiply(number.ToString());}
            void Divide(std::string number);inline void Divide(const WholeNumberValue& number){Divide(number.ToString());}
            void Add(std::string wholeNumber,std::string decimalNumber);inline void Add(const DecimalNumberValue& number){Add(number.WholeNumber.ToString(),number.DecimalNumber.ToString());}
            void Subtract(std::string wholeNumber,std::string decimalNumber);inline void Subtract(const DecimalNumberValue& number){Subtract(number.WholeNumber.ToString(),number.DecimalNumber.ToString());}
            void Multiply(std::string wholeNumber,std::string decimalNumber);inline void Multiply(const DecimalNumberValue& number){Multiply(number.WholeNumber.ToString(),number.DecimalNumber.ToString());}
            void Divide(std::string wholeNumber,std::string decimalNumber);inline void Divide(const DecimalNumberValue& number){Divide(number.WholeNumber.ToString(),number.DecimalNumber.ToString());}
            //Comparision operators
            bool operator<(std::string number);
            inline bool operator<(const WholeNumberValue& number){return (*this)<number.ToString();}
            inline bool operator<(const DecimalNumberValue& number){return (*this)<number.ToString();}
            inline bool operator<(long double number){return (*this)<std::to_string(number);}
            bool operator>(std::string number);
            inline bool operator>(const WholeNumberValue& number){return (*this)>number.ToString();}
            inline bool operator>(const DecimalNumberValue& number){return (*this)>number.ToString();}
            inline bool operator>(long double number){return (*this)>std::to_string(number);}
            bool operator<=(std::string number);
            inline bool operator<=(const WholeNumberValue& number){return (*this)<=number.ToString();}
            inline bool operator<=(const DecimalNumberValue& number){return (*this)<=number.ToString();}
            inline bool operator<=(long double number){return (*this)<=std::to_string(number);}
            bool operator>=(std::string number);
            inline bool operator>=(const WholeNumberValue& number){return (*this)>=number.ToString();}
            inline bool operator>=(const DecimalNumberValue& number){return (*this)>=number.ToString();}
            inline bool operator>=(long double number){return (*this)>=std::to_string(number);}
            bool operator==(std::string number);
            inline bool operator==(const WholeNumberValue& number){return (*this)==number.ToString();}
            inline bool operator==(const DecimalNumberValue& number){return (*this)==number.ToString();}
            inline bool operator==(long double number){return (*this)==std::to_string(number);}
            bool operator!=(std::string number);
            inline bool operator!=(const WholeNumberValue& number){return (*this)!=number.ToString();}
            inline bool operator!=(const DecimalNumberValue& number){return (*this)!=number.ToString();}
            inline bool operator!=(long double number){return (*this)!=std::to_string(number);}
            //Math operator
            DecimalNumberValue& operator+=(std::string number);
            inline DecimalNumberValue& operator+=(const WholeNumberValue& number){return (*this)+=number.ToString();}
            inline DecimalNumberValue& operator+=(const DecimalNumberValue& number){return (*this)+=number.ToString();}
            inline DecimalNumberValue& operator+=(long double number){return (*this)+=std::to_string(number);}
            DecimalNumberValue& operator-=(std::string number);
            inline DecimalNumberValue& operator-=(const WholeNumberValue& number){return (*this)-=number.ToString();}
            inline DecimalNumberValue& operator-=(const DecimalNumberValue& number){return (*this)-=number.ToString();}
            inline DecimalNumberValue& operator-=(long double number){return (*this)-=std::to_string(number);}
            DecimalNumberValue& operator*=(std::string number);
            inline DecimalNumberValue& operator*=(const WholeNumberValue& number){return (*this)*=number.ToString();}
            inline DecimalNumberValue& operator*=(const DecimalNumberValue& number){return (*this)*=number.ToString();}
            inline DecimalNumberValue& operator*=(long double number){return (*this)*=std::to_string(number);}
            DecimalNumberValue& operator/=(std::string number);
            inline DecimalNumberValue& operator/=(const WholeNumberValue& number){return (*this)/=number.ToString();}
            inline DecimalNumberValue& operator/=(const DecimalNumberValue& number){return (*this)/=number.ToString();}
            inline DecimalNumberValue& operator/=(long double number){return (*this)/=std::to_string(number);}
            DecimalNumberValue& operator=(std::string number);
            inline DecimalNumberValue& operator=(const WholeNumberValue& number){return (*this)=number.ToString();}
            inline DecimalNumberValue& operator=(const DecimalNumberValue& number){return (*this)=number.ToString();}
            inline DecimalNumberValue& operator=(long double number){return (*this)=std::to_string(number);}
            //Parse
            static bool TryParse(std::string number,DecimalNumberValue& out);
        };
    };
};
#endif