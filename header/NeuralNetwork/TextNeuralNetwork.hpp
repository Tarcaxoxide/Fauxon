#pragma once
#include<NeuralNetwork/SimpleNeuralNetwork.hpp>
#include<cassert>

namespace Fauxon{
    namespace NeuralNetwork{
        class TextNeuralNetwork_cl{
            SimpleNeuralNetwork_cl SimpleNeuralNetwork;
            std::deque<std::string> SentenceData;
            std::deque<std::deque<double>> ParemData;
            uint32_t numberOfParemeters;
            std::string ENDER="____END____";
            public:
            TextNeuralNetwork_cl(uint32_t numberOfParemeters,double LearningRate=0.01);
            std::string Export(std::string FileName="Save.json");
            std::string Import(std::string FileName="Save.json");
            std::deque<double> WordToVector(std::string Word);
            std::string VectorToWord(std::deque<double> Vector);
            void Add(std::string Sentence);
            void Train(std::deque<std::string> Examples,size_t Epoch);
            std::string GetNextWord(std::string WordA,std::string WordB);
        };
    };
};