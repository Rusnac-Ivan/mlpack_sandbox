#ifndef _MNIST_READER_H_
#define _MNIST_READER_H_


#include <armadillo>

class MNISTReader
{		
	public:
		MNISTReader();
		~MNISTReader();
		
		void Load(const char* labels_file_name, const char* data_file_name, arma::mat& labels, arma::mat& data);
		
	private:
		int32_t ReverseInt(int32_t i);
		
};

#endif