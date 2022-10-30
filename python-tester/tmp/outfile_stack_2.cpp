#include <iostream>
#include "test_utils.hpp"
#include <stack>
#include "vector.hpp"
#include "map.hpp"
#include "stack.hpp"
#include "utils.hpp"
#include "vector_iterator.hpp"

extern std::string	test_name;
void test_stack_copy_constructor(long count){
	//print job name
	test_name = "-STACK COPY CONSTRUCTOR TEST-";
	print_test_name(count);

	//init
    const size_t N = 42;
    const int M = std::numeric_limits<int>::max();
	srand(time(NULL));
	{
	//output test
	timer_start();
	long err_count = 0;
	for (int i = 0; i < count; ++i){
		size_t num = rand() % N;
		std::stack<int> v1;
		ft::stack<int> v2;
		for (size_t i = 0; i < num; ++i){
			int fill = rand() % M;
			v1.push(fill);
			v2.push(fill);
		}
		std::stack<int> v1_r(v1);
		ft::stack<int> v2_r(v2);
		int std_res = v1_r.size();
		int ft_res = v2_r.size();
		if (std_res != ft_res)
			++err_count;
	}
	double comp_res = timer_stop();
    comparision_result(err_count, comp_res);
	}

	//std working
    std::stack<int> v1;
    for (size_t i = 0; i < N * N; ++i) v1.push(N);
	timer_start();
	for (int i = 0; i < count; ++i){
	    std::stack<int> v1_r(v1);
	}
	double std_res = timer_stop();
	std::cout << "std result: " << std_res << " sec | " << std::flush;
	
	//ft working
	ft::stack<int> v2;
    for (size_t i = 0; i < N * N; ++i) v2.push(N);
	timer_start();
	for (int i = 0; i < count; ++i){
		ft::stack<int> v2_r(v2);
	}
	double ft_res = timer_stop();
	std::cout << "ft result: " << ft_res << " sec | " << std::flush;
	performance_result(std_res, ft_res);
}

int main(){
	test_stack_copy_constructor(100000);
}