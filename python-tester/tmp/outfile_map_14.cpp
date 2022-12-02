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
void test_map_insert_range(long count){
	//print job name
	test_name = "-MAP INSERT RANGE TEST-";
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
		std::map<std::string, int> v1_r;
		ft::map<std::string, int> v2;
		ft::map<std::string, int> v2_r;
		for (size_t i = 0; i < N * 10; ++i){
			std::string fill = getNewId();
            int val = rand() % M;
			v1.insert(std::make_pair<std::string, int>(fill, val));
			v2.insert(ft::make_pair<std::string, int>(fill, val));
		v1_r.insert(v1.begin(), v1.end());
		v2_r.insert(v2.begin(), v2.end());

		if (!std::equal(v1_r.begin(),v1_r.end(),v2_r.begin()))
			++err_count;
	}
	double comp_res = timer_stop();
    comparision_result(err_count, comp_res);
	}

	//std working
	std::map<std::string, int> v1;
	std::map<std::string, int> v1_r;
	for (int i = 0; i < count; ++i){
        std::string fill = getNewId();
		v1.insert(std::make_pair<std::string, int>(fill, N));
	}
	timer_start();
	v1_r.insert(v1.begin(), v1.end());
	double std_res = timer_stop();
	std::cout << "std result: " << std_res << " sec | " << std::flush;
	
	//ft working 
	ft::map<std::string, int> v2;
	ft::map<std::string, int> v2_r;
	for (int i = 0; i < count; ++i){
        std::string fill = getNewId();
		v2.insert(ft::make_pair<std::string, int>(fill, N));
	}
	timer_start();
	v2_r.insert(v2.begin(), v2.end());
	double ft_res = timer_stop();
	std::cout << "ft result: " << ft_res << " sec | " << std::flush;
	performance_result(std_res, ft_res);
}

int main(){
	test_map_insert_range(100000);
}