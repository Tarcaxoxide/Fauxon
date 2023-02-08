#include<NeuralNetwork/TextNeuralNetwork.hpp>
#include<fstream>
#include<json/value.h>
#include<json/json.h>
#include<json/writer.h>
#include<json/reader.h>
#include <iostream>

inline double Function_Random(const double& Vin){
    return (double)rand() / (double)RAND_MAX;
}

std::deque<uint32_t> TopGen(uint32_t numberOfParemeters){
    std::deque<uint32_t> Topology;
    Topology.push_back(numberOfParemeters);
    Topology.push_back(numberOfParemeters);
    Topology.push_back(numberOfParemeters);
    return Topology;
}

// 'WordA' + 'WordB' ~= 'WordC'
// I love pizza
// 'WordA'="I" 'WordB'="love" 'WordC'="pizza"

bool Similar(double A,double B,double offset){
    if( (B-offset) < A && A < (B+offset) )return true;
    // [B-offset] < [A] < [B+offset]
    return false;
}

namespace Fauxon{
    namespace NeuralNetwork{
        TextNeuralNetwork_cl::TextNeuralNetwork_cl(uint32_t numberOfParemeters,double LearningRate):SimpleNeuralNetwork(TopGen(numberOfParemeters),LearningRate){
            this->numberOfParemeters=numberOfParemeters;
        }
        std::string TextNeuralNetwork_cl::Export(std::string FileName){
            Json::FastWriter fastWriter;
            Json::Value DataToExport;
            SimpleNeuralNetwork.Export(FileName);
            std::ifstream iFile(FileName.c_str());
            iFile>>DataToExport;
            iFile.close();
            DataToExport["numberOfParemeters"] = numberOfParemeters;
            //write data to export
            for(int a=0;a<SentenceData.size();a++){
                DataToExport["SentenceData"][a] = SentenceData[a];
            }
            for(int a=0;a<ParemData.size();a++){
                for(int b=0;b<ParemData[a].size();b++){
                    DataToExport["ParemData"][a][b] = ParemData[a][b];
                }
            }
            std::ofstream oFile(FileName.c_str());
            oFile << fastWriter.write(DataToExport);
            oFile.close();
            return fastWriter.write(DataToExport);
        }
        std::string TextNeuralNetwork_cl::Import(std::string FileName){
            Json::FastWriter fastWriter;
            Json::Value DataToImport;
            std::string a = SimpleNeuralNetwork.Import(FileName);
            if(!a.size())return "";
            std::ifstream File(FileName.c_str());
            if(!File.good())return "";
            File>>DataToImport;
            File.close();
            numberOfParemeters = DataToImport["numberOfParemeters"].asUInt();
            SentenceData.clear();
            SentenceData.resize(DataToImport["SentenceData"].size());
            for(int a=0;a<DataToImport["SentenceData"].size();a++){
                SentenceData[a] = DataToImport["SentenceData"][a].asString();
            }
            ParemData.clear();
            ParemData.resize(DataToImport["ParemData"].size());
            for(int a=0;a<DataToImport["ParemData"].size();a++){
                ParemData[a].resize(DataToImport["ParemData"][a].size());
                for(int b=0;b<DataToImport["ParemData"][a].size();b++){
                    ParemData[a][b] = DataToImport["ParemData"][a][b].asDouble();
                    
                }
            }
            return fastWriter.write(DataToImport);
        }
        std::deque<double> TextNeuralNetwork_cl::WordToVector(std::string Word){
            std::deque<double> Result;
            for(uint32_t i=0;i<SentenceData.size();i++){
                if(SentenceData[i] == Word){Result=ParemData[i];break;}
            }
            return Result;
        }
        std::string TextNeuralNetwork_cl::VectorToWord(std::deque<double> Vector){
            assert(Vector.size() == numberOfParemeters);
            std::string Result="";
            uint32_t CurrentIndex=0;
            double CurrentSimilarity=0.0;
            static double OffSet=0.0000000000000001;
            TryAgain:
            for(uint32_t a=1;a<=ParemData.size();a++){
                std::deque<double> aVector = ParemData[a-1];
                double Similarity=0.0;
                for(uint32_t b=0;b<aVector.size();b++){
                    if(Similar(aVector[b],Vector[b],OffSet)){Similarity+=0.00000000001;}else{Similarity-=0.00000000001;}
                }
                if(Similarity > CurrentSimilarity){
                    CurrentSimilarity=Similarity;
                    CurrentIndex=a;
                }
            }
            if(CurrentIndex == 0){
                OffSet*=10;
                goto TryAgain;
            }
            Result=SentenceData[CurrentIndex-1];
            return Result;
        }
        void TextNeuralNetwork_cl::Add(std::string Sentence){
            std::deque<std::string> Words;
            std::string s;
            std::istringstream f(Sentence);
            while (std::getline(f, s, ' ')) {
                if(s[s.size()-1] == '\n')s[s.size()-1]=0;
                bool New=true;
                for(size_t iWord=0;iWord<SentenceData.size();iWord++){
                    if(SentenceData[iWord] == s)New=false;
                }
                if(New){
                    SentenceData.push_back(s);
                    ParemData.resize(SentenceData.size());
                    ParemData[SentenceData.size()-1].resize(numberOfParemeters);
                    for(size_t iParem=0;iParem<numberOfParemeters;iParem++){
                        ParemData[SentenceData.size()-1][iParem] = Function_Random(0.0);
                    }
                }
            }
        }
        void TextNeuralNetwork_cl::Train(std::deque<std::string> Examples,size_t Epoch){
            for(size_t i=0;i<Examples.size();i++)Add(Examples[i]);//make sure all the words exist.
            for(size_t i=0;i<Epoch;i++){
                std::cout<<"Training:"<<i<<"/"<<Epoch<<std::endl;
                std::cout<<"?1"<<std::endl;
                size_t index=rand()%Examples.size();
                std::string ThisSentence=Examples[index];
                std::deque<std::string> Words;
                Words.clear();
                std::istringstream f(ThisSentence);
                std::string s="";
                while (std::getline(f, s, ' ')){
                    Words.push_back(s);
                }
                // 0 1 2
                for(size_t pos=2;pos<Words.size();pos++){
                    std::deque<double> WordVectorC=WordToVector(Words[pos]);
                    std::deque<double> WordVectorB=WordToVector(Words[pos-1]);
                    std::deque<double> WordVectorA=WordToVector(Words[pos-2]);
                    std::deque<double> InputVector=WordVectorA;
                    std::deque<double> ExpectedVector=WordVectorC;
                    InputVector.insert(InputVector.end(),WordVectorB.begin(),WordVectorB.end());
                    SimpleNeuralNetwork.FeedForward(InputVector);
                    SimpleNeuralNetwork.BackPropagate(ExpectedVector);
                }
            }
            std::cout<<"Training:"<<Epoch<<"/"<<Epoch<<std::endl;
        }
        std::string TextNeuralNetwork_cl::GetNextWord(std::string WordA,std::string WordB){
            std::deque<double> WordVectorB=WordToVector(WordB);
            std::deque<double> WordVectorA=WordToVector(WordA);
            std::deque<double> InputVector=WordVectorA;
            InputVector.insert(InputVector.end(),WordVectorB.begin(),WordVectorB.end());
            SimpleNeuralNetwork.FeedForward(InputVector);
            std::deque<double> Res=SimpleNeuralNetwork.getPrediction();
            return VectorToWord(Res);
        }
    };
};
