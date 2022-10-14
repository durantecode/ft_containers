#include <iostream>
#include "test_utils.hpp"
#include <vector>
#include "vector.hpp"
#include "map.hpp"
#include "stack.hpp"
#include "utils.hpp"

extern std::string	test_name;
void test_vector_resize(long count){
	//print job name
	test_name = "-VECTOR RESIZE TEST-";
	print_test_name(count);

	//init
    const size_t N = 42;
    const int M = 99;
	srand(time(NULL));
	{
	//output test
	timer_start();
	long err_count = 0;
	for (int i = 0; i < count; ++i){
		size_t num = rand() % N;
		size_t resize_n = rand() % (N * 2);
		int fill = rand() % std::numeric_limits<int>::max();
		std::vector<int> v1(num, fill);
		ft::vector<int> v2(num, fill);
		v1.resize(resize_n);
		v2.resize(resize_n);
		int std_res = v1.size();
		int ft_res = v2.size();
		if (std_res != ft_res)
			++err_count;
		std::vector<int>::iterator v1_it = v1.begin();
		std::vector<int>::iterator v1_itend = v1.end();
		ft::vector<int>::iterator v2_it = v2.begin();
		while (v1_it != v1_itend)
		{
    		if (!(*v1_it == *v2_it))
				++err_count;
    		++v1_it; ++v2_it;
  		}
	}
	double comp_res = timer_stop();
    print_comp_res(err_count, comp_res);
	}

	//std working
	timer_start();
	for (int i = 0; i < count; ++i){
    	std::vector<int> v1(N, M);
		v1.resize(N * 2);
		v1.resize(N / 2);
	}
	double std_res = timer_stop();
	std::cout << "std result: " << std_res << " sec | " << std::flush;
	
	//ft working 
	timer_start();
	for (int i = 0; i < count; ++i){
		ft::vector<int> v2(N, M);
		v2.resize(N * 2);
		v2.resize(N / 2);
	}
	double ft_res = timer_stop();
	std::cout << "ft result: " << ft_res << " sec | " << std::flush;
	print_result(std_res, ft_res);
}

int main(){
	test_vector_resize(100000);
}