#include<NeuralNetwork/TextNeuralNetwork.hpp>
#include<fstream>
#include<json/value.h>
#include<json/json.h>
#include<json/writer.h>
#include<json/reader.h>

inline double Function_Random(const double& Vin){
    return (double)rand() / (double)RAND_MAX;
}

std::deque<uint32_t> TopGen(uint32_t numberOfParemeters){
    std::deque<uint32_t> Topology;
    uint32_t Min=numberOfParemeters/2;
    size_t i=numberOfParemeters;
    for(;i>=Min;i--){
        Topology.push_back(i);
    }
    for(;i<=numberOfParemeters;i++){
        Topology.push_back(i);
    }
    return Topology;
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
            SimpleNeuralNetwork.Import(FileName);
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
                DataToImport["ParemData"][a].resize(DataToImport["ParemData"][a].size());
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
            for(uint32_t a=1;a<=ParemData.size();a++){
                std::deque<double> aVector = ParemData[a-1];
                double Similarity=0.0;
                for(uint32_t b=0;b<aVector.size();b++){
                    if(aVector[b] == Vector[b]){Similarity+=0.00000000001;}else{Similarity-=0.00000000001;}
                }
                if(Similarity > CurrentSimilarity){
                    CurrentSimilarity=Similarity;
                    CurrentIndex=a;
                }
            }
            if(!CurrentIndex)return "";
            Result=SentenceData[CurrentIndex-1];
            return Result;
        }
        void TextNeuralNetwork_cl::Input(std::string Sentence){
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
        std::string TextNeuralNetwork_cl::Output(){
            std::string Result="";
            
            return Result;
        }
    };
};