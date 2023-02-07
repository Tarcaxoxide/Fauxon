#include<NeuralNetwork/SimpleNeuralNetwork.hpp>
#include<fstream>
#include<json/value.h>
#include<json/json.h>
#include<json/writer.h>
#include<json/reader.h>

void Seed(std::deque<size_t> seeds){
    int64_t Seed=0;
    for(size_t i=0;i<seeds.size();i++){
        Seed=seeds[i]+((size_t)(rand()-Seed));
        srand((size_t)Seed);
    }
}
inline double Function_Random(const double& Vin){
    return (double)rand() / (double)RAND_MAX;
}
inline double Function_Sigmoid(const double& Vin){
    return 1.0/(1.0 + exp(-Vin));
}

inline double Function_SigmoidDerivative(const double& Vin){
    return Vin * (1.0 - Vin);
}
namespace Fauxon{
    namespace NeuralNetwork{
        SimpleNeuralNetwork_cl::SimpleNeuralNetwork_cl(std::deque<uint32_t> Topology,double LearningRate):_Topology(Topology),_WeightMatrices({}),_ValueMatrices({}),_BiasMatrices({}),_LearningRate(LearningRate){
            //Seed the random generator
            for(uint32_t iLayer=0;iLayer<Topology.size()-1;iLayer++){
                Seed({Topology[iLayer+1],Topology[iLayer],(size_t)time(0)});
            }
            
            for(uint32_t iLayer=0;iLayer<Topology.size()-1;iLayer++){
                //fill weights
                Matrix_cl weightMatrix(Topology[iLayer+1],Topology[iLayer]);
                weightMatrix = weightMatrix.ApplyFunction(Function_Random);
                _WeightMatrices.push_back(weightMatrix);
                //fill biases
                Matrix_cl biasMatrix(Topology[iLayer+1],1);
                biasMatrix = biasMatrix.ApplyFunction(Function_Random);
                _BiasMatrices.push_back(biasMatrix);
            }
            //fill values
            _ValueMatrices.resize(Topology.size());
        }
        bool SimpleNeuralNetwork_cl::FeedForward(std::deque<double> Vin){
            if(Vin.size() != _Topology.front())return false;
            Matrix_cl VinMatrix(Vin.size(),1);
            VinMatrix._Values = Vin;
            //FeedForward
            for(uint32_t iConnection=0;iConnection<_WeightMatrices.size();iConnection++){
                _ValueMatrices[iConnection] = VinMatrix;
                VinMatrix = VinMatrix.Multiply(_WeightMatrices[iConnection]);
                VinMatrix = VinMatrix.Add(_BiasMatrices[iConnection]);
                VinMatrix = VinMatrix.ApplyFunction(Function_Sigmoid);
            } 
            _ValueMatrices[_WeightMatrices.size()]=VinMatrix;
            return true;
        }
        bool SimpleNeuralNetwork_cl::BackPropagate(std::deque<double> Vexpected){
            if(Vexpected.size() != _Topology.back())return false;
            Matrix_cl errorMatrix(Vexpected.size(),1);
            errorMatrix._Values = Vexpected;
            Matrix_cl ValueNegativeMatrix=_ValueMatrices.back().Negative();
            errorMatrix=errorMatrix.Add(ValueNegativeMatrix);
            for(int64_t i=_WeightMatrices.size()-1;i>=0;i--){
                Matrix_cl transposedWeights = _WeightMatrices[i].Transpose();
                Matrix_cl prevErrors = errorMatrix.Multiply(transposedWeights);
                Matrix_cl dOutputMatrix = _ValueMatrices[i+1].ApplyFunction(Function_SigmoidDerivative);
                Matrix_cl gradientMatrix = errorMatrix.MultiplyElements(dOutputMatrix);
                gradientMatrix = gradientMatrix.MultiplyScalar(_LearningRate);
                Matrix_cl weightGradientMatrix = _ValueMatrices[i].Transpose().Multiply(gradientMatrix);
                _WeightMatrices[i] = _WeightMatrices[i].Add(weightGradientMatrix);
                _BiasMatrices[i] = _BiasMatrices[i].Add(gradientMatrix);
                errorMatrix = prevErrors;
            }
            return true;
        }
        std::deque<double> SimpleNeuralNetwork_cl::getPrediction(){
            return _ValueMatrices.back()._Values;
        }
        bool SimpleNeuralNetwork_cl::Train(std::deque<std::deque<double>> Inputs,std::deque<std::deque<double>> ExpectedResults,size_t Iterations){
            for(uint32_t i=0;i<Iterations;i++){
                size_t index = rand()%Inputs.size();
                if(!FeedForward(Inputs[index]))return false;
                if(!BackPropagate(ExpectedResults[index]))return false;
            }
            return true;
        }
        std::string SimpleNeuralNetwork_cl::Export(std::string FileName){
            Json::FastWriter fastWriter;
            Json::Value DataToExport;

            for(int a=0;a<_Topology.size();a++){
                DataToExport["NeuralNetwork"]["Topology"][a] = _Topology[a];   
            }
            for(int a=0;a<_WeightMatrices.size();a++){
                for(int b=0;b<_WeightMatrices[a].size();b++){
                    DataToExport["NeuralNetwork"]["Weight"][a][b] = _WeightMatrices[a][b];
                }
            }
            for(int a=0;a<_BiasMatrices.size();a++){
                for(int b=0;b<_BiasMatrices[a].size();b++){
                    DataToExport["NeuralNetwork"]["Bias"][a][b] = _BiasMatrices[a][b];
                }
            }
            DataToExport["NeuralNetwork"]["LearningRate"]=_LearningRate;

            std::ofstream File(FileName.c_str());
            File << fastWriter.write(DataToExport);
            File.close(); 

            return fastWriter.write(DataToExport);
        }
        std::string SimpleNeuralNetwork_cl::Import(std::string FileName){
            std::ifstream File(FileName.c_str());
            if(!File.good())return "";
            Json::FastWriter fastWriter;
            Json::Value DataToImport;
            File >> DataToImport;
            File.close();
            _Topology.clear();
            _WeightMatrices.clear();
            _BiasMatrices.clear();
            _LearningRate = DataToImport["NeuralNetwork"]["LearningRate"].asDouble();
            _Topology.resize(DataToImport["NeuralNetwork"]["Topology"].size(),0);
            for(int a=0;a<DataToImport["NeuralNetwork"]["Topology"].size();a++){
                _Topology[a]=DataToImport["NeuralNetwork"]["Topology"][a].asUInt64();
            }
            for(int a=0;a<_Topology.size()-1;a++){
                //fill weights
                Matrix_cl weightMatrix(_Topology[a+1],_Topology[a]);
                for(int b=0;b<weightMatrix.size();b++){
                    weightMatrix[b] = DataToImport["NeuralNetwork"]["Weight"][a][b].asDouble();
                }
                _WeightMatrices.push_back(weightMatrix);
                //fill biases
                Matrix_cl biasMatrix(_Topology[a+1],1);
                for(int b=0;b<biasMatrix.size();b++){
                    weightMatrix[b] = DataToImport["NeuralNetwork"]["Bias"][a][b].asDouble();
                }
                _BiasMatrices.push_back(biasMatrix);
            }
            //fill values
            _ValueMatrices.resize(_Topology.size());
            return fastWriter.write(DataToImport);
        }
        std::deque<double> SimpleNeuralNetwork_cl::getPrediction(std::deque<double> Vin){
            FeedForward(Vin);
            return getPrediction();
        }
    };
};
