#ifndef _TRAINING_CALLBACKS_H_
#define _TRAINING_CALLBACKS_H_

class TrainingCallbacks
{
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

		//! Locally-stored epoch.
		size_t epoch;


	public:
		template<typename OptimizerType, typename FunctionType, typename MatType>
		void BeginOptimization(OptimizerType& optimizer, FunctionType& function, MatType& coordinates)
		{
			std::cout << "BeginOptimization\n";
		}
		
		
		template<typename OptimizerType, typename FunctionType, typename MatType>
		void BeginEpoch(OptimizerType& optimizer, 
					FunctionType& function, 
					const MatType& coordinates,
					const size_t epoch,
					const double objective)
		{
			std::cout << "BeginEpoch objective: "<< objective << " epochIn: " << epoch << "\n";
			this->epoch = epoch;
		}
		
		template<typename OptimizerType, typename FunctionType, typename MatType>
		void Evaluate(OptimizerType& optimizer ,
					FunctionType& function,
					const MatType& coordinates,
					const double objective)
		{
			std::cout << "Evaluate objective: " << objective << "\n";
			this->objective = objective;
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
			std::cout << "Gradient gradientNorm: " << gradientNorm << "\n";
		}

		template<typename OptimizerType, typename FunctionType, typename MatType>
		void StepTaken(OptimizerType& optimizer,
					FunctionType& function,
					const MatType& coordinates)
		{
			std::cout << "StepTaken\n";
		}
		
		template<typename OptimizerType, typename FunctionType, typename MatType>
		void EndEpoch(OptimizerType& optimizer,
					FunctionType& function,
					const MatType& coordinates,
					const size_t epoch,
					const double objective)
		{
			std::cout << "EndEpoch objective: "<< objective << " epoch: " << epoch << "\n";
		}
		
		template<typename OptimizerType, typename FunctionType, typename MatType>
		void EndOptimization(OptimizerType& optimizer, FunctionType& function, MatType& coordinates)
		{
			std::cout << "EndOptimization\n";
		}

};

#endif
