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
void test_map_begin_end(long count) {
	//print job name
	test_name = "-MAP BEGIN END TEST-";
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
	    ft::map<std::string, int> v2;
        for (size_t i = 0; i < num; ++i) {
	        std::string fill = getNewId();
	        int  fill_n = rand() % M;
            v1.insert(std::make_pair<std::string, int>(fill, fill_n));
            v2.insert(ft::make_pair<std::string, int>(fill, fill_n));
        }
		int std_res = v1.size();
		int ft_res = v2.size();
		if (std_res != ft_res)
			++err_count;
        if (!num) continue;
		// std::cout << "size : " << ft_res << std::endl;
		std::map<std::string, int>::iterator it = v1.begin();
		ft::map<std::string, int>::iterator it_ft = v2.begin();
		if (*it != *it_ft) ++err_count;
        std::map<std::string, int>::const_iterator c_it = v1.begin();
		ft::map<std::string, int>::const_iterator c_it_ft = v2.begin();
		if (*c_it != *c_it_ft) ++err_count;
        std::map<std::string, int>::iterator eit = v1.end();
		ft::map<std::string, int>::iterator eit_ft = v2.end();
		--eit; --eit_ft;
		if (*(eit) != *(eit_ft)) ++err_count;
        std::map<std::string, int>::const_iterator c_eit = v1.end();
		ft::map<std::string, int>::const_iterator c_eit_ft = v2.end();
        if (*(--c_eit) != *--(c_eit_ft)) ++err_count;
	}
	double comp_res = timer_stop();
    comparision_result(err_count, comp_res);
	}

	//std working
    size_t num = rand() % N;
	std::map<std::string, int> v1;
    for (size_t i = 0; i < num; ++i) {
	    std::string fill = getNewId();
        v1.insert(std::make_pair<std::string, int>(fill, N));
    }
	timer_start();
	for (int i = 0; i < count; ++i){
	    v1.begin();
        v1.end();
	}
	double std_res = timer_stop();
	std::cout << "std result: " << std_res << " sec | " << std::flush;
	
	//ft working
	ft::map<std::string, int> v2;
    for (size_t i = 0; i < num; ++i) {
	    std::string fill = getNewId();
        v2.insert(ft::make_pair<std::string, int>(fill, N));
    }
	timer_start();
	for (int i = 0; i < count; ++i){
		v2.begin();
        v2.end();
	}
	double ft_res = timer_stop();
	std::cout << "ft result: " << ft_res << " sec | " << std::flush;
	performance_result(std_res, ft_res);
}

int main(){
	test_map_begin_end(100000);
}