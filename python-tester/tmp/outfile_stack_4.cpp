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
void test_stack_size_empty_top(long count){
	//print job name
	test_name = "-STACK SIZE EMPTY TOP TEST-";
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
		if (v1.size() != v2.size())
			++err_count;
        if (v1.empty() != v2.empty())
            ++err_count;
        if (!v1.size()) continue;
		if (v1.top() != v2.top())
			++err_count;
	}
	double comp_res = timer_stop();
    comparision_result(err_count, comp_res);
	}
}

int main(){
	test_stack_size_empty_top(100000);
}