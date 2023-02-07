#pragma once
#include<NeuralNetwork/SimpleNeuralNetwork.hpp>

namespace Fauxon{
    namespace NeuralNetwork{
        class TextNeuralNetwork_cl{
            SimpleNeuralNetwork_cl SimpleNeuralNetwork;
            std::deque<std::deque<std::string>> SentenceData;
            std::deque<std::deque<std::deque<double>>> ParemData;
            uint32_t numberOfParemeters;
            std::string ENDER="____END____";
            public:
            TextNeuralNetwork_cl(uint32_t numberOfParemeters,double LearningRate=0.01);
            std::string Export(std::string FileName="Save.json");
            std::string Import(std::string FileName="Save.json");
            void Input(std::string Sentence);
            std::string Output();
        };
    };
};