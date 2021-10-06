#include "MNISTReader.h"

#include <fstream>

MNISTReader::MNISTReader(){}
MNISTReader::~MNISTReader(){}

int32_t MNISTReader::ReverseInt(int32_t i)
{
	uint8_t ch1, ch2, ch3, ch4;
	
    ch1 = i;
    ch2 = (i >> 8);
    ch3 = (i >> 16);
    ch4 = (i >> 24);
	
	int32_t res = 0;
	res += static_cast<int32_t>(ch1) << 24;
	res += static_cast<int32_t>(ch2) << 16;
	res += static_cast<int32_t>(ch3) << 8;
	res += static_cast<int32_t>(ch4);
	
    return res;
}

void MNISTReader::Load(const char* labels_file_name, const char* data_file_name, arma::mat& labels, arma::mat& data)
{
	std::ifstream in_labels_file;
	std::ifstream in_data_file;
	
	in_labels_file.open(labels_file_name, std::ios_base::binary);
	in_data_file.open(data_file_name, std::ios_base::binary);
	
	if(!in_labels_file.is_open())
	{
		std::cout << "ERROR: Could not open input labels file!\n";
        return;
	}
	if(!in_data_file.is_open())
	{
		std::cout << "ERROR: Could not open input data file!\n";
        return;
	}
	
	int32_t magic_number_labels = 0;
	int32_t number_of_items = 0;
	
	in_labels_file.read(reinterpret_cast<char*>(&magic_number_labels), sizeof(magic_number_labels));
	magic_number_labels = ReverseInt(magic_number_labels);
	
	in_labels_file.read(reinterpret_cast<char*>(&number_of_items), sizeof(number_of_items));
	number_of_items = ReverseInt(number_of_items);
	
	
	int32_t magic_number_data = 0;
    int32_t number_of_images = 0;
    int32_t rows = 0;
    int32_t cols = 0;
    
    in_data_file.read(reinterpret_cast<char*>(&magic_number_data), sizeof(magic_number_data));
    magic_number_data = ReverseInt(magic_number_data);

    in_data_file.read(reinterpret_cast<char*>(&number_of_images), sizeof(number_of_images));
    number_of_images = ReverseInt(number_of_images);

    in_data_file.read(reinterpret_cast<char*>(&rows), sizeof(rows));
    rows = ReverseInt(rows);

    in_data_file.read(reinterpret_cast<char*>(&cols), sizeof(cols));
    cols = ReverseInt(cols);
	
	
	if(number_of_items != number_of_images)
	{
		std::cout << "ERROR: Mismatch between images count and labels count!\n";
		return;
	}
	
	labels.resize(1, number_of_items);
	data.resize(rows * cols, number_of_images);
	
	for (uint32_t i = 0; i < number_of_images; ++i)
    {
		uint8_t label;
		in_labels_file.read(reinterpret_cast<char*>(&label), sizeof(label));
		
		arma::colvec img_data(rows * cols);
		
        for (uint32_t r = 0; r < rows; ++r)
        {
            for (uint32_t c = 0; c < cols; ++c)
            {
                uint8_t val;
                in_data_file.read(reinterpret_cast<char*>(&val), sizeof(val));

				double value = static_cast<double>(val / 255.0);
				img_data(r * cols + c) = value;
            }
        }
		
		labels(0, i) = static_cast<int>(label) + 1;
		//data.row(i) = img_data;
		data.col(i) = img_data;

		/*for (int i = 0; i < img_data.size(); i++)
		{
			if (i % 28 == 0 && i != 0)
			{
				std::cout << std::endl;
			}
			float val = static_cast<float>(img_data[i]);
			if (val == 0.0)
			{
				printf("  ");
			}
			else
			{
				printf("##");
			}

		}
		std::cout << std::endl;*/
    }
	
	/*for (unsigned int i = 0; i < labels.size(); i++)
	{
		printf("%f\n", labels(0, i));
	}*/

	
	
	in_labels_file.close();
	in_data_file.close();
}