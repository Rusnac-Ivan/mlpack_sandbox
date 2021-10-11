#ifndef _MODEL_H_
#define _MODEL_H_

#include <mlpack/core.hpp>
#include <mlpack/methods/ann/layer/layer.hpp>
#include <mlpack/methods/ann/ffn.hpp>



class Model
{
	mlpack::ann::FFN<> mNeuralNetwork;
public:
	Model();
	~Model();


	
private:

};


#endif // !_MODEL_H_
