#include <iostream>
#include "test_utils.hpp"
#include <stack>
#include "vector.hpp"
#include "map.hpp"
#include "stack.hpp"
#include "utils.hpp"
#include "vector_iterator.hpp"

extern std::string	test_name;
void test_stack_push_pop(long count){
	//print job name
	test_name = "-STACK PUSH POP TEST-";
	print_test_name(count);

	// //init
    const size_t N = 42;
    const int M = std::numeric_limits<int>::max();
	srand(time(NULL));
	//output test
	{
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
            if (v1.top() != v2.top())
                ++err_count;
		}
        if (!num) continue;
        size_t op = rand() % num;
        for (size_t i = 0; i < op; ++i){
			v1.pop();
			v2.pop();
		}
		if (v1.size() != v2.size())
			++err_count;
	}
	double comp_res = timer_stop();
    comparision_result(err_count, comp_res);
	}

	//std working
    std::stack<int> v1;
	timer_start();
	for (int i = 0; i < count; ++i){
		for (size_t i = 0; i < N; ++i) v1.push(N);
        for (size_t i = 0; i < N; ++i) v1.pop();
	}
	double std_res = timer_stop();
	std::cout << "std result: " << std_res << " sec | " << std::flush;
	
	//ft working
    ft::stack<int> v2;
	timer_start();
	for (int i = 0; i < count; ++i){
		for (size_t i = 0; i < N; ++i) v2.push(N);
        for (size_t i = 0; i < N; ++i) v2.pop();
	}
	double ft_res = timer_stop();
	std::cout << "ft result: " << ft_res << " sec | " << std::flush;
	performance_result(std_res, ft_res);
}

int main(){
	test_stack_push_pop(100000);
}