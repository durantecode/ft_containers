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
void test_map_empty_ctor(long count){
	//print job name
	test_name = "-MAP EMPTY CONSTRUCTION TEST-";
	print_test_name(count);

	//std working
	timer_start();
	for (int i = 0; i < count; ++i){
		std::map<std::string, int> p1;
	}
	double std_res = timer_stop();
	std::cout << "std result: " << std_res << " sec | " << std::flush;

	//ft working
	timer_start();
	for (int i = 0; i < count; ++i){
		ft::map<std::string, int> p2;
	}
	double ft_res = timer_stop();
	std::cout << "ft result: " << ft_res << " sec | " << std::flush;
	performance_result(std_res, ft_res);
}

int main(){
	test_map_empty_ctor(100000);
}