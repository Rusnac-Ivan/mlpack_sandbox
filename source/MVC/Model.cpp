#include "Model.h"

#include <iostream>
#include "MNISTReader.h"
#include <mlpack_sandbox-version.h>

Model::Model()
{
    std::string mnist_data_path(MLPACK_SANDBOX_MNIST_DATA_PATH);

    MNISTReader reader;

    std::string train_labels_full_name(mnist_data_path + "/training/train-labels.idx1-ubyte");
    std::string train_data_full_name(mnist_data_path + "/training/train-images.idx3-ubyte");

    std::string test_labels_full_name(mnist_data_path + "/testing/t10k-labels.idx1-ubyte");
    std::string test_data_full_name(mnist_data_path + "/testing/t10k-images.idx3-ubyte");

    reader.Load(train_labels_full_name.c_str(), train_data_full_name.c_str(), mMnistTrainLabels, mMnistTrainData);

    reader.Load(test_labels_full_name.c_str(), test_data_full_name.c_str(), mMnistTestLabels, mMnistTestData);
}
Model::~Model(){}




void Model::Train()
{
 

    const int L1 = 200; //number of neurons in the first layer
    const int L2 = 100; //number of neurons in the second layer

    const double RATIO = 0.1;
    const int MAX_ITERATIONS = 100000;
    const double STEP_SIZE = 1.2e-3;
    const int BATCH_SIZE = 100;

    const int INPUT_SIZE = mMnistTrainData.n_rows;
    const int OUTPUT_SIZE = 10;

    mlpack::ann::FFN<> neural_network;

    neural_network.Add<mlpack::ann::Linear<> >(INPUT_SIZE, L1);
    neural_network.Add<mlpack::ann::SigmoidLayer<> >();
    neural_network.Add<mlpack::ann::Linear<> >(L1, L2);
    neural_network.Add<mlpack::ann::SigmoidLayer<> >();
    neural_network.Add<mlpack::ann::Linear<> >(L2, OUTPUT_SIZE);
    neural_network.Add<mlpack::ann::LogSoftMax<> >();



    std::cout << "Start training ..." << std::endl;


    ens::Adam optimizer(
        STEP_SIZE,  // Step size of the optimizer.
        BATCH_SIZE, // Batch size. Number of data points that are used in each
                    // iteration.
        0.9,        // Exponential decay rate for the first moment estimates.
        0.999, // Exponential decay rate for the weighted infinity norm estimates.
        1e-8,  // Value used to initialise the mean squared gradient parameter.
        MAX_ITERATIONS, // Max number of iterations.
        1e-6,           // Tolerance.
        true
    );

    neural_network.Train(
        mMnistTrainData,
        mMnistTrainLabels,
        optimizer,
        *this
    );

    ens::PrintLoss();
    ens::ProgressBar();
    ens::EarlyStopAtMinLoss();

    arma::mat predictionTemp;
    neural_network.Predict(mMnistTestData, predictionTemp);

    arma::mat prediction = arma::zeros<arma::mat>(1, predictionTemp.n_cols);


    for (size_t i = 0; i < predictionTemp.n_cols; ++i)
    {
        // we add 1 to the max index, so that it matches the actual test labels.
        prediction(i) = arma::as_scalar(arma::find(
            arma::max(predictionTemp.col(i)) == predictionTemp.col(i), 1)) + 1;
    }

    size_t correct = arma::accu(prediction == mMnistTestLabels);
    double classificationError = 1 - double(correct) / mMnistTestData.n_cols;
    // Print out the classification error for the testing dataset.
    std::cout << "\nClassification Error for the Test set: " << classificationError << std::endl;

    //data::Save("model.xml", "model", neural_network, false);
}
