#include "MLTest.h"

#include <mlpack/core.hpp>
#include <mlpack/methods/neighbor_search/neighbor_search.hpp>

#include <mlpack/methods/ann/layer/layer.hpp>
#include <mlpack/methods/ann/ffn.hpp>

#include <iostream>
#include "MNISTReader.h"
#include <mlpack_sandbox-version.h>

#include "TrainingCallbacks.hpp"
//#include <armadillo>

using namespace mlpack;
using namespace mlpack::neighbor; // NeighborSearch and NearestNeighborSort
using namespace mlpack::metric; // ManhattanDistance

class ProgressBar
{
public:
    /**
     * Set up the progress bar callback class with the given width and output
     * stream.
     *
     * @param widthIn Width of the bar.
     * @param ostream Ostream which receives output from this object.
     */
    ProgressBar(){}
    /*ProgressBar(const size_t widthIn = 70,
        std::ostream& output = arma::get_cout_stream()) :
        width(100.0 / widthIn),
        output(output),
        objective(0),
        epochs(0),
        epochSize(0),
        step(1),
        steps(0),
        newEpoch(false),
        epoch(1)


    }*/


    

    /**
     * Callback function called at the begin of a pass over the data.
     *
     * @param optimizer The optimizer used to update the function.
     * @param function Function to optimize.
     * @param coordinates Starting point.
     * @param epochIn The index of the current epoch.
     * @param objective Objective value of the current point.
     */
    template<typename OptimizerType, typename FunctionType, typename MatType>
    void BeginEpoch(OptimizerType& /* optimizer */,
        FunctionType& /* function */,
        const MatType& /* coordinates */,
        const size_t epochIn,
        const double /* objective */)
    {
        std::cout << "BeginEpoch\n";
    }

    /**
     * Callback function called once a step is taken.
     *
     * @param optimizer The optimizer used to update the function.
     * @param function Function to optimize.
     * @param coordinates Starting point.
     * @param objective Objective value of the current point.
     */
    template<typename OptimizerType, typename FunctionType, typename MatType>
    void StepTaken(OptimizerType& /* optimizer */,
        FunctionType& /* function */,
        const MatType& /* coordinates */)
    {
        std::cout << "StepTaken loss: " << objective / (double)step << "\n";
        
    }

    /**
     * Callback function called at any call to Evaluate().
     *
     * @param optimizer The optimizer used to update the function.
     * @param function Function to optimize.
     * @param coordinates Starting point.
     * @param objectiveIn Objective value of the current point.
     */
    template<typename OptimizerType, typename FunctionType, typename MatType>
    void Evaluate(OptimizerType& optimizer,
        FunctionType& /* function */,
        const MatType& /* coordinates */,
        const double objectiveIn)
    {
        objective += objectiveIn / optimizer.BatchSize();
        steps++;
        std::cout << "Evaluate\n";
    }

    /**
     * Callback function called at the end of a pass over the data.
     *
     * @param optimizer The optimizer used to update the function.
     * @param function Function to optimize.
     * @param coordinates Starting point.
     * @param epoch The index of the current epoch.
     * @param objective Objective value of the current point.
     */
    template<typename OptimizerType, typename FunctionType, typename MatType>
    void EndEpoch(OptimizerType& /* optimizer */,
        FunctionType& /* function */,
        const MatType& /* coordinates */,
        const size_t /* epoch */,
        const double objective)
    {
        std::cout << "EndEpoch\n";
    }

private:
    //! Length of a single step (1%).
    double width;

    //! The output stream that all data is to be sent to; example: std::cout.
    //std::ostream& output;

    //! Objective over the current epoch.
    double objective;

    //! Total number of epochs
    size_t epochs;

    //! Number of steps per epoch.
    size_t epochSize;

    //! Current step number.
    size_t step;

    //! Number of steps taken.
    size_t steps;

    //! Indicates a new epoch.
    bool newEpoch;

    //! Locally-stored epoch.
    size_t epoch;

    //! Locally-stored step timer object.
    arma::wall_clock stepTimer;

    //! Locally-stored epoch timer object.
    arma::wall_clock epochTimer;
};


class ExponentialDecay
{
public:
    // Set up the exponential decay learning rate scheduler with the user
    // specified decay value.
    ExponentialDecay(const double decay) : learningRate(0) { }


    // Callback function called at the start of the optimization process.
    // In this example we will use this to save the initial learning rate.
    template<typename OptimizerType, typename FunctionType, typename MatType>
    void BeginOptimization(OptimizerType&  optimizer ,
        FunctionType&  function,
        MatType& coordinates)
    {
        // Save the initial learning rate.
        learningRate = optimizer.StepSize();
    }

    // Callback function called at the end of a pass over the data. We are only
    // interested in the current epoch and the optimizer, we ignore the rest.
    template<typename OptimizerType, typename FunctionType, typename MatType>
    void EndEpoch(OptimizerType& optimizer,
        FunctionType& /* function */,
        const MatType& /* coordinates */,
        const size_t epoch,
        const double objective)
    {
        // Update the learning rate.
        /*optimizer.StepSize() = learningRate * (1.0 - std::pow(decay,
            (double)epoch));*/
        int a = 0;
    }

    template<typename OptimizerType, typename FunctionType, typename MatType>
    bool Evaluate(OptimizerType& opt, FunctionType& function, const MatType& coordinates, const double objective)
    {
        int a = 0;
        std::cout << "\nThe optimization process called Evaluate()!" << std::endl;
        return false; // Do not terminate, continue the optimization process.
    }

    double learningRate;
};

class CustomCallback
{
public:
    template<typename OptimizerType, typename FunctionType, typename MatType>
    bool Evaluate(OptimizerType& opt, FunctionType& function, const MatType& coordinates, const double objective)
    {
        int a = 0;
        std::cout << "\nThe optimization process called Evaluate()!" << std::endl;
        return false; // Do not terminate, continue the optimization process.
    }
};

namespace mv
{
    
    MLTest::MLTest()
	{
	}

    MLTest::~MLTest()
	{
	}

	void MLTest::Run()
	{
        // Load the data from data.csv (hard-coded).  Use CLI for simple command-line
        // parameter handling.
        /*arma::mat data("0.339406815,0.843176636,0.472701471; \
                  0.212587646,0.351174901,0.81056695;  \
                  0.160147626,0.255047893,0.04072469;  \
                  0.564535197,0.943435462,0.597070812");
        data = data.t();

        // Use templates to specify that we want a NeighborSearch object which uses
        // the Manhattan distance.
        NeighborSearch<NearestNeighborSort, ManhattanDistance> nn(data);

        // Create the object we will store the nearest neighbors in.
        arma::Mat<size_t> neighbors;
        arma::mat distances; // We need to store the distance too.

        // Compute the neighbors.
        nn.Search(1, neighbors, distances);

        
        // Write each neighbor and distance using Log.
        for (size_t i = 0; i < neighbors.n_elem; ++i)
        {
            std::cout << "Nearest neighbor of point " << i << " is point "
                << neighbors[i] << " and the distance is " << distances[i] << "." << std::endl;
        }*/


        //arma::arma_rng::set_seed_random();
        //
        //// Create a 4x4 random matrix and print it on the screen
        //arma::Mat<double> A = arma::randu(4,4);
        //std::cout << "A:\n" << A << "\n";
        //
        //// Multiply A with his transpose:
        //std::cout << "A * A.t() =\n";
        //std::cout << A * A.t() << "\n";
        //
        //// Access/Modify rows and columns from the array:
        //A.row(0) = A.row(1) + A.row(3);
        //A.col(3).zeros();
        //std::cout << "add rows 1 and 3, store result in row 0, also fill 4th column with zeros:\n";
        //std::cout << "A:\n" << A << "\n";
        //
        //// Create a new diagonal matrix using the main diagonal of A:
        //arma::Mat<double>B = arma::diagmat(A);
        //std::cout << "B:\n" << B << "\n";

        /*arma::mat mnistTrain;
        data::Load("C:\\Users\\User\\Desktop\\mnist_train.csv", mnistTrain, true);
        arma::mat mnistTest;
        data::Load("C:\\Users\\User\\Desktop\\mnist_test.csv", mnistTest, true);*/

        arma::mat mnistTrainLabels;
        arma::mat mnistTrainData;

        arma::mat mnistTestLabels;
        arma::mat mnistTestData;

        std::string mnist_data_path(MLPACK_SANDBOX_MNIST_DATA_PATH);

        MNISTReader reader;
        reader.Load(std::string(mnist_data_path + "/training/train-labels.idx1-ubyte").c_str(), std::string(mnist_data_path + "/training/train-images.idx3-ubyte").c_str(), mnistTrainLabels, mnistTrainData);

        reader.Load(std::string(mnist_data_path + "/testing/t10k-labels.idx1-ubyte").c_str(), std::string(mnist_data_path + "/testing/t10k-images.idx3-ubyte").c_str(), mnistTestLabels, mnistTestData);

        const int L1 = 200; //number of neurons in the first layer
        const int L2 = 100; //number of neurons in the second layer

        const double RATIO = 0.1;
        const int MAX_ITERATIONS = 60000;
        const double STEP_SIZE = 1.2e-3;
        const int BATCH_SIZE = 100;

        const int INPUT_SIZE = mnistTrainData.n_rows;
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


        /*neural_network.Train(
            mnistTrainData,
            mnistTrainLabels,
            optimizer,
            ens::PrintLoss(),
            ens::ProgressBar(),
            // Stop the training using Early Stop at min loss.
            ens::EarlyStopAtMinLoss(
                [&](const arma::mat&)
                {
                    double validationLoss = neural_network.Evaluate(validX, validY);
                    std::cout << "Validation loss: " << validationLoss
                        << "." << std::endl;
                    return validationLoss;
                })
            );*/

        neural_network.Train(
            mnistTrainData,
            mnistTrainLabels,
            optimizer,
            TrainingCallbacks()
        );

        ens::PrintLoss();
        ens::ProgressBar();
        ens::EarlyStopAtMinLoss();

        arma::mat predictionTemp;
        neural_network.Predict(mnistTestData, predictionTemp);

        arma::mat prediction = arma::zeros<arma::mat>(1, predictionTemp.n_cols);
        

        for (size_t i = 0; i < predictionTemp.n_cols; ++i)
        {
            // we add 1 to the max index, so that it matches the actual test labels.
            prediction(i) = arma::as_scalar(arma::find(
                arma::max(predictionTemp.col(i)) == predictionTemp.col(i), 1)) + 1;
        }

        size_t correct = arma::accu(prediction == mnistTestLabels);
        double classificationError = 1 - double(correct) / mnistTestData.n_cols;
        // Print out the classification error for the testing dataset.
        std::cout << "\nClassification Error for the Test set: " << classificationError << std::endl;

        data::Save("model.xml", "model", neural_network, false);
	}
}
