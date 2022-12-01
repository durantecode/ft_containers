#include <iostream>
#include <map>
#include <utility>
#include <vector>
#include "test_utils.hpp"
#include "Utility.hpp"
#include "Vector.hpp"
#include "Map.hpp"
#include "Node.hpp"
#include "Set.hpp"
#include "Stack.hpp"
#include "Iterator.hpp"

extern std::string	test_name;
void test_map_insert_val(long count){
	//print job name
	test_name = "-MAP INSERT VALUE TEST-";
	print_test_name(count);

	//init
    const size_t N = 42;
    const int M = std::numeric_limits<int>::max();    
	srand(time(NULL));
	{
	//output test
	timer_start();
	long err_count = 0;
		std::map<std::string, int> v1;
		ft::map<std::string, int> v2;
		for (size_t i = 0; i < N * N; ++i){
			std::string fill = getNewId();
            int val = rand() % M;
			v1.insert(std::make_pair<std::string, int>(fill, val));
			v2.insert(ft::make_pair<std::string, int>(fill, val));
		if (!std::equal(v1.begin(),v1.end(),v2.begin()))
			++err_count;
	}
	double comp_res = timer_stop();
    comparision_result(err_count, comp_res);
	}

	//std working
	std::map<std::string, int> v1;
	timer_start();
	for (int i = 0; i < count; ++i){
        std::string fill = getNewId();
		v1.insert(std::make_pair<std::string, int>(fill, N));
	}
	double std_res = timer_stop();
	std::cout << "std result: " << std_res << " sec | " << std::flush;
	
	//ft working 
	ft::map<std::string, int> v2;
	timer_start();
	for (int i = 0; i < count; ++i){
        std::string fill = getNewId();
		v2.insert(ft::make_pair<std::string, int>(fill, N));
	}
	double ft_res = timer_stop();
	std::cout << "ft result: " << ft_res << " sec | " << std::flush;
	performance_result(std_res, ft_res);
}

int main(){
	test_map_insert_val(100000);
}