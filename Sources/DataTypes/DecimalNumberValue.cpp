#include<DataTypes/DecimalNumberValue.hpp>


namespace Fauxon{
    namespace DataTypes{
        //constructors!, constructors!, constructors!, construct!
        DecimalNumberValue::DecimalNumberValue(long double number):WholeNumber("0"),DecimalNumber("0"){
            std::string Xnumber = std::to_string(number);
            std::stringstream input_stringstream(Xnumber);
            std::deque<std::string> parts;
            std::string parsed;
            while (std::getline(input_stringstream,parsed,'.')){
                parts.push_back(parsed);
            }
            if(parts.size() == 0)parts.push_back("0");
            if(parts.size() == 1)parts.push_back("0");
            WholeNumber=parts[0];
            DecimalNumber=parts[1];
            DecimalPlaces=DecimalNumber.Number.size();
            DecimalNumber.Sign=WholeNumber.Sign;
            DecimalNumber.oSign=WholeNumber.oSign;
        }
        DecimalNumberValue::DecimalNumberValue(std::string number):WholeNumber("0"),DecimalNumber("0"){
            WholeNumber=number;
            DecimalPlaces=DecimalNumber.Number.size();
            DecimalNumber.Sign=WholeNumber.Sign;
            DecimalNumber.oSign=WholeNumber.oSign;
        }
        DecimalNumberValue::DecimalNumberValue(std::string wholeNumber,std::string decimalNumber):WholeNumber("0"),DecimalNumber("0"){
            WholeNumber=wholeNumber;
            DecimalNumber=decimalNumber;
            DecimalPlaces=DecimalNumber.Number.size();
            DecimalNumber.Sign=WholeNumber.Sign;
            DecimalNumber.oSign=WholeNumber.oSign;
        }
        DecimalNumberValue::DecimalNumberValue(const DecimalNumberValue& number):WholeNumber("0"),DecimalNumber("0"){
            WholeNumber=number.WholeNumber;
            DecimalNumber=number.DecimalNumber;
            DecimalPlaces=DecimalNumber.Number.size();
            DecimalNumber.Sign=WholeNumber.Sign;
            DecimalNumber.oSign=WholeNumber.oSign;
        }
        DecimalNumberValue::DecimalNumberValue(const WholeNumberValue& number):WholeNumber("0"),DecimalNumber("0"){
            WholeNumber=number;
            DecimalPlaces=DecimalNumber.Number.size();
            DecimalNumber.Sign=WholeNumber.Sign;
            DecimalNumber.oSign=WholeNumber.oSign;
        }
        DecimalNumberValue::DecimalNumberValue(const WholeNumberValue& wholeNumber,const WholeNumberValue& decimalNumber):WholeNumber("0"),DecimalNumber("0"){
            WholeNumber=wholeNumber;
            DecimalNumber=decimalNumber;
            DecimalPlaces=DecimalNumber.Number.size();
            DecimalNumber.Sign=WholeNumber.Sign;
            DecimalNumber.oSign=WholeNumber.oSign;
        }
        //To string for printing the number out (shshsh... it's already a string XD)
        std::string DecimalNumberValue::ToString(){
            return WholeNumber.ToString()+std::string(".")+DecimalNumber.ToString();
        }
        //Base math function
        void DecimalNumberValue::Add(std::string number){WholeNumber.Add(number);}
        void DecimalNumberValue::Subtract(std::string number){WholeNumber.Subtract(number);}
        void DecimalNumberValue::Multiply(std::string number){WholeNumber.Multiply(number);}
        void DecimalNumberValue::Divide(std::string number){WholeNumber.Divide(number);}
        void DecimalNumberValue::Add(std::string wholeNumber,std::string decimalNumber){
            uint8_t Sign=WholeNumber.Sign;
            if(wholeNumber[0]==WholeNumber.Sign){
                if(wholeNumber[0]=='-'||wholeNumber[0]=='+')wholeNumber.erase(0,1);
                Subtract(wholeNumber,decimalNumber);
                return;
            }
            if(Sign=='+'){WholeNumber.Add(wholeNumber);}else{WholeNumber.Subtract(wholeNumber);}
            if(Sign=='+'){DecimalNumber.Add(decimalNumber);}else{DecimalNumber.Subtract(decimalNumber);}
            while(DecimalNumber.Number.size() > DecimalPlaces){
                DecimalNumber.Number.erase(0,1);
                if(Sign=='+'){Add("1");}else{Subtract("1");}
            }
        }
        void DecimalNumberValue::Subtract(std::string wholeNumber,std::string decimalNumber){
            uint8_t Sign=WholeNumber.Sign;
            if(decimalNumber[0]!='-'&&wholeNumber[0]=='-')decimalNumber=std::string("-")+decimalNumber;
            WholeNumber.Subtract(wholeNumber);
            DecimalNumber.Subtract(decimalNumber);
            while(DecimalNumber.Number.size() > DecimalPlaces){
                DecimalNumber.Number.erase(0,1);
                if(Sign=='+'){Add("1");}else{Subtract("1");}
            }
        }
        void DecimalNumberValue::Multiply(std::string wholeNumber,std::string decimalNumber){
            WholeNumber.Multiply(wholeNumber);
            DecimalNumber.Multiply(decimalNumber);
            while(DecimalNumber.Number.size() > DecimalPlaces){
                DecimalNumber.Number.erase(0,1);
                Add("1");
            }
        }
        void DecimalNumberValue::Divide(std::string wholeNumber,std::string decimalNumber){WholeNumber.Divide(wholeNumber);DecimalNumber.Divide(decimalNumber);}
        //Comparision operators
        bool DecimalNumberValue::operator<(std::string number){
            std::stringstream input_stringstream(number);
            std::deque<std::string> parts;
            std::string parsed;
            while (std::getline(input_stringstream,parsed,'.')){
                parts.push_back(parsed);
            }
            if(parts.size() == 0)parts.push_back("0");
            if(parts.size() == 1)parts.push_back("0");
            if(WholeNumber==parts[0]){
                return DecimalNumber<parts[1];
            }
            return WholeNumber<parts[0];
        }
        bool DecimalNumberValue::operator>(std::string number){
            std::stringstream input_stringstream(number);
            std::deque<std::string> parts;
            std::string parsed;
            while (std::getline(input_stringstream,parsed,'.')){
                parts.push_back(parsed);
            }
            if(parts.size() == 0)parts.push_back("0");
            if(parts.size() == 1)parts.push_back("0");
            if(WholeNumber==parts[0]){
                return DecimalNumber>parts[1];
            }
            return WholeNumber>parts[0];
        }
        bool DecimalNumberValue::operator<=(std::string number){
            return ((*this)<number||(*this)==number);
        }
        bool DecimalNumberValue::operator>=(std::string number){
            return ((*this)>number||(*this)==number);
        }
        bool DecimalNumberValue::operator==(std::string number){
            return ((!((*this)>number))&&(!((*this)<number)));
        }
        bool DecimalNumberValue::operator!=(std::string number){
            return (!((*this)==number));
        }
        //Math operator
        DecimalNumberValue& DecimalNumberValue::operator+=(std::string number){
            std::stringstream input_stringstream(number);
            std::deque<std::string> parts;
            std::string parsed;
            while (std::getline(input_stringstream,parsed,'.')){
                parts.push_back(parsed);
            }
            if(parts.size() == 0)parts.push_back("0");
            if(parts.size() == 1)parts.push_back("0");
            Add(parts[0],parts[1]);
            return *this;
        }
        DecimalNumberValue& DecimalNumberValue::operator-=(std::string number){
            std::stringstream input_stringstream(number);
            std::deque<std::string> parts;
            std::string parsed;
            while (std::getline(input_stringstream,parsed,'.')){
                parts.push_back(parsed);
            }
            if(parts.size() == 0)parts.push_back("0");
            if(parts.size() == 1)parts.push_back("0");
            Subtract(parts[0],parts[1]);
            return *this;
        }
        DecimalNumberValue& DecimalNumberValue::operator*=(std::string number){
            std::stringstream input_stringstream(number);
            std::deque<std::string> parts;
            std::string parsed;
            while (std::getline(input_stringstream,parsed,'.')){
                parts.push_back(parsed);
            }
            if(parts.size() == 0)parts.push_back("0");
            if(parts.size() == 1)parts.push_back("0");
            Multiply(parts[0],parts[1]);
            return *this;
        }
        DecimalNumberValue& DecimalNumberValue::operator/=(std::string number){
            std::stringstream input_stringstream(number);
            std::deque<std::string> parts;
            std::string parsed;
            while (std::getline(input_stringstream,parsed,'.')){
                parts.push_back(parsed);
            }
            if(parts.size() == 0)parts.push_back("0");
            if(parts.size() == 1)parts.push_back("0");
            Divide(parts[0],parts[1]);
            return *this;
        }
        DecimalNumberValue& DecimalNumberValue::operator=(std::string number){
            std::stringstream input_stringstream(number);
            std::deque<std::string> parts;
            std::string parsed;
            while (std::getline(input_stringstream,parsed,'.')){
                parts.push_back(parsed);
            }
            if(parts.size() == 0)parts.push_back("0");
            if(parts.size() == 1)parts.push_back("0");
            WholeNumber=parts[0];
            DecimalNumber=parts[1];
            return *this;
        }
    };
};