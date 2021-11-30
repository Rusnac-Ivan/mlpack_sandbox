#ifndef _MODEL_H_
#define _MODEL_H_

#include <vector>

#include <mlpack/core.hpp>
#include <mlpack/methods/ann/layer/layer.hpp>
#include <mlpack/methods/ann/ffn.hpp>
#include <vector>


class Model
{
	arma::mat mMnistTrainLabels;
	arma::mat mMnistTrainData;

	arma::mat mMnistTestLabels;
	arma::mat mMnistTestData;

	mlpack::ann::FFN<> mNeuralNetwork;

	std::vector<float> mValues;
	std::vector<float> mGradients;

	uint32_t mInputSize;
	uint32_t mOutputSize;

	std::vector<uint32_t> mLayersSize;
public:
	Model();
	~Model();

	std::vector<float>& GetValues() { return mValues; }
	std::vector<float>& GetGradients() { return mGradients; }

	template<typename OptimizerType, typename FunctionType, typename MatType>
	void BeginOptimization(OptimizerType& optimizer, FunctionType& function, MatType& coordinates)
	{
		//std::cout << "BeginOptimization\n";
	}


	template<typename OptimizerType, typename FunctionType, typename MatType>
	void BeginEpoch(OptimizerType& optimizer,
		FunctionType& function,
		const MatType& coordinates,
		const size_t epoch,
		const double objective)
	{
		//std::cout << "BeginEpoch objective: " << objective << " epochIn: " << epoch << "\n";
		//this->epoch = epoch;
	}

	template<typename OptimizerType, typename FunctionType, typename MatType>
	void Evaluate(OptimizerType& optimizer,
		FunctionType& function,
		const MatType& coordinates,
		const double objective)
	{
		//std::cout << "Evaluate objective: " << objective << "\n";
		//this->objective = objective;

		mValues.push_back(objective);
	}


	template<typename OptimizerType, typename FunctionType, typename MatType>
	void Gradient(OptimizerType& optimizer,
		FunctionType& function,
		const MatType& coordinates,
		const MatType& gradientIn)
	{
		//hasGradient = true;
		double gradientNorm = arma::norm(gradientIn);
		//gradientCalls++;
		mGradients.push_back(gradientNorm);
		//std::cout << "Gradient gradientNorm: " << gradientNorm << "\n";
	}

	template<typename OptimizerType, typename FunctionType, typename MatType>
	void StepTaken(OptimizerType& optimizer,
		FunctionType& function,
		const MatType& coordinates)
	{
		//std::cout << "StepTaken\n";
	}

	template<typename OptimizerType, typename FunctionType, typename MatType>
	void EndEpoch(OptimizerType& optimizer,
		FunctionType& function,
		const MatType& coordinates,
		const size_t epoch,
		const double objective)
	{
		//std::cout << "EndEpoch objective: " << objective << " epoch: " << epoch << "\n";
	}

	template<typename OptimizerType, typename FunctionType, typename MatType>
	void EndOptimization(OptimizerType& optimizer, FunctionType& function, MatType& coordinates)
	{
		//std::cout << "EndOptimization\n";
	}

	void Train();

	float Predict(float data[][28]);
private:

};


#endif // !_MODEL_H_
