#include <iostream>
#include <map>
#include <utility>
#include <vector>
#include "test_utils.hpp"
#include "pair.hpp"
#include "equal.hpp"
#include "vector.hpp"
#include "map.hpp"
#include "red_black_tree.hpp"
#include "is_integral.hpp"
#include "lexicographical_compare.hpp"
#include "iterator_traits.hpp"
#include "make_pair.hpp"
#include "stack.hpp"
#include "utils.hpp"
#include "vector_iterator.hpp"
#include "enable_if.hpp"

extern std::string	test_name;
void test_map_comparison(long count) {
	//print job name
	test_name = "-MAP COMPARISON OPERATORS TEST-";
	print_test_name(count);

	//init
    const size_t N = 42;
    const int M = std::numeric_limits<int>::max();
	srand(time(NULL));
	{
	//output test
	timer_start();
	long err_count = 0;
	for (int i = 0; i < count / 3; ++i) {
	    size_t num = rand() % N;
	    std::map<std::string, int> v1;
	    std::map<std::string, int> v1_r;
	    ft::map<std::string, int> v2;
	    ft::map<std::string, int> v2_r;
        for (size_t i = 0; i < num; ++i) {
	        std::string fill = getNewId();
	        int  fill_n = rand() % M;
            v1.insert(std::make_pair<std::string, int>(fill, fill_n));
            v1_r.insert(std::make_pair<std::string, int>(fill, fill_n));
            v2.insert(ft::make_pair<std::string, int>(fill, fill_n));
            v2_r.insert(ft::make_pair<std::string, int>(fill, fill_n));
        }
		if ((v1==v1_r) != (v2==v2_r)) ++err_count;
		if ((v1<v1_r) != (v2<v2_r)) ++err_count;
		if ((v1!=v1_r) != (v2!=v2_r)) ++err_count;
		if ((v1>v1_r) != (v2>v2_r)) ++err_count;
		if ((v1<=v1_r) != (v2<=v2_r)) ++err_count;
		if ((v1>=v1_r) != (v2>=v2_r)) ++err_count;
	}
	double comp_res = timer_stop();
    comparision_result(err_count, comp_res);
	}
}

int main(){
	test_map_comparison(100000);
}