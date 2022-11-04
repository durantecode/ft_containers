#include <iostream>
#include "test_utils.hpp"
#include <stack>
#include "pair.hpp"
#include "equal.hpp"
#include "vector.hpp"
#include "map.hpp"
#include "is_integral.hpp"
#include "lexicographical_compare.hpp"
#include "make_pair.hpp"
#include "stack.hpp"
#include "utils.hpp"
#include "vector_iterator.hpp"
#include "enable_if.hpp"

extern std::string	test_name;
void test_stack_empty_constructor(long count){
	//print job name
	test_name = "-STACK EMPTY CONSTRUCTION TEST-";
	print_test_name(count);

	//std working
	timer_start();
	for (int i = 0; i < count; ++i){
		std::stack<int> p1;
	}
	double std_res = timer_stop();
	std::cout << "std result: " << std_res << " sec | " << std::flush;

	//ft working
	timer_start();
	for (int i = 0; i < count; ++i){
		ft::stack<int> p1;
	}
	double ft_res = timer_stop();
	std::cout << "ft result: " << ft_res << " sec | " << std::flush;
	performance_result(std_res, ft_res);
}

int main(){
	test_stack_empty_constructor(100000);
}