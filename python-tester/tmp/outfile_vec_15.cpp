#include <iostream>
#include "test_utils.hpp"
#include <vector>
#include "vector.hpp"
#include "map.hpp"
#include "stack.hpp"
#include "utils.hpp"
#include "vector_iterator.hpp"

extern std::string	test_name;
void test_vector_time_insert_position(long count){
	//print job name
	test_name = "-VECTOR INSERT POS TEST-";
	print_test_name(count);

	//init
	count = 50;
    const size_t N = 42;
    const int M = std::numeric_limits<int>::max();
	srand(time(NULL));
	{
	//output test
	timer_start();
	long err_count = 0;
	for (int i = 0; i < count; ++i){
		size_t num = rand() % N;
		std::vector<int> v1;
		ft::vector<int> v2;
		for (size_t i = 0; i < num; ++i){
			int fill = rand() % M;
			v1.push_back(fill);
			v2.push_back(fill);
		}
		if (!num) continue;
		size_t it_pos = rand() % num;
		std::vector<int>::iterator it = v1.begin() + it_pos;
		ft::vector<int>::iterator its = v2.begin() + it_pos;
		std::vector<int>::iterator res_std = v1.insert(it, N);
		ft::vector<int>::iterator res_ft = v2.insert(its, N);
		if (*res_std != *res_ft)
		 	++err_count;
		if (res_std - v1.begin() != res_ft - v2.begin())
			++err_count;
		int std_res = v1.size();
		int ft_res = v2.size();
		if (std_res != ft_res)
			++err_count;
		if (!std::equal(v1.begin(),v1.end(),v2.begin()))
			++err_count;
	}
	double comp_res = timer_stop();
    comparision_result(err_count, comp_res);
	}
	//std working
    std::vector<int> v1(N, M);
	timer_start();
	for (int i = 0; i < count; ++i){
		v1.insert(v1.begin(), N);
	}
	double std_res = timer_stop();
	std::cout << "std result: " << std_res << " sec | " << std::flush;
	
	//ft working 
	ft::vector<int> v2(N, M);
	timer_start();
	for (int i = 0; i < count; ++i){
		v2.insert(v2.begin(), N);
	}
	double ft_res = timer_stop();
	std::cout << "ft result: " << ft_res << " sec | " << std::flush;
	performance_result(std_res, ft_res);
}

int main(){
	test_vector_time_insert_position(100000);
}