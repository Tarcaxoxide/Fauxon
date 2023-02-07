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
            for(int iPosition=0;iPosition<SentenceData.size();iPosition++){
                for(int iWord=0;iWord<SentenceData[iPosition].size();iWord++){
                    DataToExport["SentenceData"][iPosition][iWord] = SentenceData[iPosition][iWord];
                }
            }
            for(int a=0;a<ParemData.size();a++){
                for(int b=0;b<ParemData[a].size();b++){
                    for(int c=0;c<ParemData[a][b].size();c++){
                        DataToExport["ParemData"][a][b][c] = ParemData[a][b][c];
                    }
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
            for(int iPosition=0;iPosition<DataToImport["SentenceData"].size();iPosition++){
                SentenceData[iPosition].resize(DataToImport["SentenceData"][iPosition].size());
                for(int iWord=0;iWord<DataToImport["SentenceData"][iPosition].size();iWord++){
                    SentenceData[iPosition][iWord] = DataToImport["SentenceData"][iPosition][iWord].asString();
                }
            }
            ParemData.clear();
            ParemData.resize(DataToImport["ParemData"].size());
            for(int a=0;a<DataToImport["ParemData"].size();a++){
                ParemData[a].resize(DataToImport["ParemData"][a].size());
                for(int b=0;b<DataToImport["ParemData"][a].size();b++){
                    ParemData[a][b].resize(DataToImport["ParemData"][a][b].size());
                    for(int c=0;c<DataToImport["ParemData"][a][b].size();c++){
                        ParemData[a][b][c] = DataToImport["ParemData"][a][b][c].asDouble();
                    }
                }
            }
            return "";
        }
        void TextNeuralNetwork_cl::Input(std::string Sentence){
            std::deque<std::string> Words;
            std::string s;
            std::istringstream f(Sentence);
            while (std::getline(f, s, ' ')) {
                if(s[s.size()-1] == '\n')s[s.size()-1]=0;
                Words.push_back(s);
            }
            Words.push_back(ENDER);
            for(size_t iPosition=0;iPosition<Words.size();iPosition++){
                if(iPosition >= SentenceData.size()){
                    SentenceData.push_back({Words[iPosition]});
                    ParemData.resize(Sentence.size());
                    ParemData[iPosition].resize(SentenceData.back().size());
                    for(uint32_t Parem=0;Parem<numberOfParemeters;Parem++){
                        ParemData[iPosition].back().push_back(Function_Random(1.0));
                    }
                }else{
                    bool New=true;
                    for(size_t iWord=0;iWord<SentenceData[iPosition].size();iWord++){
                        if(SentenceData[iPosition][iWord] == Words[iPosition])New=false;
                    }
                    if(New){
                        SentenceData[iPosition].push_back(Words[iPosition]);
                        ParemData[iPosition].resize(SentenceData[iPosition].size());
                        for(uint32_t Parem=0;Parem<numberOfParemeters;Parem++){
                            ParemData[iPosition].back().push_back(Function_Random(1.0));
                        }
                    }
                }
            }
        }
        std::string TextNeuralNetwork_cl::Output(){
            std::string Result="";
            for(size_t iPosition=0;iPosition<SentenceData.size();iPosition++){
                size_t WordIndex = rand()%SentenceData[iPosition].size();
                std::string subResult=SentenceData[iPosition][WordIndex];
                if(subResult == ENDER)break;
                Result+=subResult+std::string(" ");
            }
            return Result;
        }
    };
};