#pragma once
#include<NeuralNetwork/Matrix.hpp>
#include<cstdlib>
#include<ctime>
#include<deque>
#include<string>

namespace Fauxon{
    namespace NeuralNetwork{
        class SimpleNeuralNetwork_cl{
            public:
                std::deque<uint32_t> _Topology;
                std::deque<Matrix_cl> _WeightMatrices;
                std::deque<Matrix_cl> _ValueMatrices;
                std::deque<Matrix_cl> _BiasMatrices;
                double _LearningRate;
            public:
                SimpleNeuralNetwork_cl(std::deque<uint32_t> Topology,double LearningRate=0.01);
                bool FeedForward(std::deque<double> Vin);
                bool BackPropagate(std::deque<double> Vexpected);
                std::deque<double> getPrediction();
                bool Train(std::deque<std::deque<double>> Inputs,std::deque<std::deque<double>> ExpectedResults,size_t Iterations);
                std::string Export(std::string FileName="Save.json");
                std::string Import(std::string FileName="Save.json");
                std::deque<double> getPrediction(std::deque<double> Vin);
        };
    };
};