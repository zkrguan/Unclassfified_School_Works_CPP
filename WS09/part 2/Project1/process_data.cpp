/*
	Course_Name:	OOP 345
	Section:		A
	Title:			Workshop 9 Part 2
	Module:			Process_data
	File_Name:		Process_data.cpp
	Student_Name:	Zhaokai_Guan
	Student_ID:		130988215
*/

// Workshop 9 - Multi-Threading, Thread Class
// process_data.cpp
// 2021/1/5 - Jeevan Pant

#include <thread>
#include "process_data.h"

namespace sdds_ws9 {

	void computeAvgFactor(const int* arr, int size, int divisor, double& avg) {
		avg = 0;
		for (int i = 0; i < size; i++) {
			avg += arr[i];
		}
		avg /= divisor;
	}

	void computeVarFactor(const int* arr, int size, int divisor, double avg, double& var) {
		var = 0;
		for (int i = 0; i < size; i++) {
			var += (arr[i] - avg) * (arr[i] - avg);
		}
		var /= divisor;
	}
	ProcessData::operator bool() const {
		return total_items > 0 && data && num_threads>0 && averages && variances && p_indices;
	}

	ProcessData::ProcessData(std::string filename, int n_threads) {  
		// TODO: Open the file whose name was received as parameter and read the content
		//         into variables "total_items" and "data". Don't forget to allocate
		//         memory for "data".
		//       The file is binary and has the format described in the specs.
		std::ifstream ifstr(filename, std::ios_base::binary);
		if (ifstr) {
			ifstr.read((char*)&total_items, sizeof(total_items));
		}
		data = new int[total_items];
		int index = 0;
		while (ifstr.good()) {
			ifstr.read((char*)&(data[index]), sizeof(data[index]));
			index++;
		}
		ifstr.close();

		std::cout << "Item's count in file '"<< filename << "': " << total_items << std::endl;
		std::cout << "  [" << data[0] << ", " << data[1] << ", " << data[2] << ", ... , "
		          << data[total_items - 3] << ", " << data[total_items - 2] << ", "
		          << data[total_items - 1] << "]\n";
		// Following statements initialize the variables added for multi-threaded 
		//   computation
		num_threads = n_threads; 
		averages = new double[num_threads] {};
		variances = new double[num_threads] {};
		p_indices = new int[num_threads+1] {};
		for (int i = 0; i < num_threads+1; i++)
			p_indices[i] = i * (total_items / num_threads);
	}
	ProcessData::~ProcessData() {
		delete[] data;
		delete[] averages;
		delete[] variances;
		delete[] p_indices;
	}

	// TODO Improve operator() function from part-1 for multi-threaded operation. Enhance the  
	//   function logic for the computation of average and variance by running the 
	//   function computeAvgFactor and computeVarFactor in multile threads. 
	// The function divides the data into a number of parts, where the number of parts is 
	//   equal to the number of threads. Use multi-threading to compute average-factor for 
	//   each part of the data by calling the function computeAvgFactor. Add the obtained 
	//   average-factors to compute total average. Use the resulting total average as the 
	//   average value argument for the function computeVarFactor, to compute variance-factors 
	//   for each part of the data. Use multi-threading to compute variance-factor for each 
	//   part of the data. Add computed variance-factors to obtain total variance.
	// Save the data into a file with filename held by the argument fname_target. 
	// Also, read the workshop instruction.

	int ProcessData::operator()(std::string target, double& average, double& variance) {
	    auto avg = std::bind(computeAvgFactor,std::placeholders::_1, std::placeholders::_2,total_items, std::placeholders::_3);	
		std::vector<std::thread> threads;

		for (size_t i = 0; i <(size_t)num_threads; i++) {
			threads.push_back(std::thread(avg, &data[p_indices[i]],(total_items/num_threads), std::ref(averages[i])));
		}
		// literally should slap myself for this//
		// Learned this in a hard way, we must received the returned values after you joined the thread//
		// Think about this you are asking the kid to get the soy sauce in grocery shop//
		// That's what happen on the line 88//
		// Collecting the soy sauce bottle before your kid even comes back//
		// Of course you got nothing cuz your kid is not even back yet//
		size_t iterator = 0;
		for (size_t i = 0; i < (size_t)num_threads;i++) {
			threads[i].join();
			average += averages[iterator++];
		}

		// God!!!!!!!!!!!!!!!!!!!!!!!//
		// Don't try to be a smart butt, naming the placeholder 5 because it is the fifth parameter of the function//
		// The compiler will actually look for the missing 3 and 4// 
		// JUST NAME YOUR PLACE HOLDERS FOLLOW THE RULES OF MOTHER NATURE, 1 IS 1 2 IS 2//
		std::vector<std::thread> var_threads;
		auto vari = std::bind(computeVarFactor, std::placeholders::_1, std::placeholders::_2,total_items, average, std::placeholders::_3);
		for (size_t i = 0; i < (size_t)num_threads; i++){
			var_threads.push_back(std::thread(vari, &data[p_indices[i]], (total_items / num_threads), std::ref(variances[i])));
		}
		iterator = 0;
		for (size_t i = 0; i < (size_t)num_threads; i++) {
			var_threads[i].join();
			variance += variances[i];
		
		//	// Something I need to think about here // 
		//	// Why would this cause the destructor crush???//
		//	/*variance += *(variances++);*/
		}

		// Binary write here//
		std::ofstream ofstr(target, std::ios::binary);
		ofstr.write((const char*)&total_items, sizeof(total_items));
		for (int i = 0; i < total_items; i++) {
			ofstr.write((const char*)&data[i], sizeof(data[i]));
		}
		return 0;
	}



}