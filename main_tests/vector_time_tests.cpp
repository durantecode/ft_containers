/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_time_tests.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 12:50:27 by ldurante          #+#    #+#             */
/*   Updated: 2022/12/06 20:49:11 by ldurante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.hpp"

void test_vector_time_empty_constructor()
{
	//std test
	timer_start();
	for (int i = 0; i < count; ++i)
		std::vector<int> std;
	double std_res = timer_stop();

	//ft test
	timer_start();
	for (int i = 0; i < count; ++i)
		ft::vector<int> ft;
	double ft_res = timer_stop();
	if (verbose)
	{
		performance_result(std_res, ft_res);
		comparision_result(0);
	}
	if (std_res != 0)
		time_perf.push_back(std_res / ft_res);
	else	
		time_perf.push_back(0);
	errors.push_back(err_count);
}

void test_vector_time_param_constructor()
{
    const size_t N = 42;
	std::vector<int> std(N);
	ft::vector<int> ft(N);

	//loop test
	timer_start();
	for (int i = 0; i < count; ++i)
	{
		int std_res = *(std.begin() + i % N);
		int ft_res = *(ft.begin() + i % N);
		if (std_res != ft_res)
			++err_count;
	}
	double comp_res = timer_stop();

	//std test
	timer_start();
	for (int i = 0; i < count; ++i)
        std::vector<int> std(N);
	double std_res = timer_stop();
	
	//ft test 
	timer_start();
	for (int i = 0; i < count; ++i)
        ft::vector<int> ft(N);
	double ft_res = timer_stop();

	//print results
	if (verbose)
	{
		performance_result(std_res, ft_res);
    	comparision_result(comp_res);
	}
	if (std_res != 0)
		time_perf.push_back(std_res / ft_res);
	else	
		time_perf.push_back(0);
	errors.push_back(err_count);
}

void test_vector_time_two_param_constructor()
{
    const size_t N = 42;
    const int M = 99;
	std::vector<int> std(N, M);
	ft::vector<int> ft(N, M);

	//loop test
	timer_start();
	for (int i = 0; i < count; ++i)
	{
		int std_res = *(std.begin() + i % N);
		int ft_res = *(ft.begin() + i % N);
		if (std_res != ft_res)
			++err_count;
	}
	double comp_res = timer_stop();
    
	//std test
	timer_start();
	for (int i = 0; i < count; ++i)
        std::vector<int> std(N, M);
	double std_res = timer_stop();
	
	//ft test 
	timer_start();
	for (int i = 0; i < count; ++i)
        ft::vector<int> ft(N, M);
	double ft_res = timer_stop();

	if (verbose)
	{
		performance_result(std_res, ft_res);
    	comparision_result(comp_res);
	}
	if (std_res != 0)
		time_perf.push_back(std_res / ft_res);
	else	
		time_perf.push_back(0);
	errors.push_back(err_count);
}

void test_vector_time_copy_constructor()
{
    const size_t N = 42;
    const int M = std::numeric_limits<int>::max();
	srand(time(NULL));
	{
		//loop test
		timer_start();
		for (int i = 0; i < count; ++i){
			size_t num = rand() % N;
			std::vector<int> std;
			ft::vector<int> ft;
			for (size_t i = 0; i < num; ++i)
			{
				int fill = rand() % M;
				std.push_back(fill);
				ft.push_back(fill);
			}
			if (!num) continue;
			std::vector<int> std_r(std);
			ft::vector<int> ft_r(ft);
			int std_res = std_r.size();
			int ft_res = ft_r.size();
			if (std_res != ft_res)
				++err_count;
			if (!std::equal(std_r.begin(),std_r.end(),ft_r.begin()))
				++err_count;
		}
	}
	double comp_res = timer_stop();

	//std test
    std::vector<int> std(N * N, M);
	timer_start();
	for (int i = 0; i < count; ++i)
	    std::vector<int> std_r(std);
	double std_res = timer_stop();
	
	//ft test
	ft::vector<int> ft(N * N, M);
	timer_start();
	for (int i = 0; i < count; ++i)
		ft::vector<int> ft_r(ft);
	double ft_res = timer_stop();

	//print results
	if (verbose)
	{
		performance_result(std_res, ft_res);
    	comparision_result(comp_res);
	}
	if (std_res != 0)
		time_perf.push_back(std_res / ft_res);
	else	
		time_perf.push_back(0);
	errors.push_back(err_count);
}

void test_vector_time_copy_range_constructor()
{
    const size_t N = 42;
    const int M = std::numeric_limits<int>::max();
	srand(time(NULL));
	{
		//loop test
		timer_start();
		for (int i = 0; i < count; ++i)
		{
			size_t num = rand() % N;
			std::vector<int> std;
			ft::vector<int> ft;
			for (size_t i = 0; i < num; ++i)
			{
				int fill = rand() % M;
				std.push_back(fill);
				ft.push_back(fill);
			}
			if (!num) continue;
			std::vector<int> std_r(std.begin(), std.end());
			ft::vector<int> ft_r(ft.begin(), ft.end());
			int std_res = std_r.size();
			int ft_res = ft_r.size();
			if (std_res != ft_res)
				++err_count;
			if (!std::equal(std_r.begin(),std_r.end(),ft_r.begin()))
				++err_count;
		}
	}
	double comp_res = timer_stop();

	//std test
    std::vector<int> std(N * N, M);
	timer_start();
	for (int i = 0; i < count; ++i)
	    std::vector<int> std_r(std.begin(), std.end());
	double std_res = timer_stop();
	
	//ft test
	ft::vector<int> ft(N * N, M);
	timer_start();
	for (int i = 0; i < count; ++i)
		ft::vector<int> ft_r(ft.begin(), ft.end());
	double ft_res = timer_stop();

	//print results
	if (verbose)
	{
		performance_result(std_res, ft_res);
		comparision_result(comp_res);
	}
	if (std_res != 0)
		time_perf.push_back(std_res / ft_res);
	else	
		time_perf.push_back(0);
	errors.push_back(err_count);
}

void test_vector_time_size_capacity_empty()
{
	//test: size, capacity, empty, max_size
	{
		std::vector<int> std;
		ft::vector<int> ft;

		//loop test
		timer_start();
		for (int i = 0; i < count; ++i)
		{
			int std_res = std.size();
			int ft_res = ft.size();
			if (std_res != ft_res)
				++err_count;
			std_res = std.capacity();
			ft_res = ft.capacity();
			if (std_res != ft_res)
				++err_count;
			size_t std_res_t = std.max_size();
			size_t ft_res_t = ft.max_size();
			if (std_res_t != ft_res_t)
				++err_count;
			bool std_res_b = std.empty();
			bool ft_res_b = ft.empty();
			if (std_res_b != ft_res_b)
				++err_count;
		}
	}
	double comp_res = timer_stop();
	
	//std test
    std::vector<int> std;
	timer_start();
	for (int i = 0; i < count; ++i){
		std.size();
		std.capacity();
		std.max_size();
		std.empty();
	}
	double std_res = timer_stop();
	
	//ft test 
	ft::vector<int> ft;
	timer_start();
	for (int i = 0; i < count; ++i){
		ft.size();
		ft.capacity();
		ft.max_size();
		ft.empty();
	}
	double ft_res = timer_stop();
	if (verbose)
	{
		performance_result(std_res, ft_res);
    	comparision_result(comp_res);
	}
	if (std_res != 0)
		time_perf.push_back(std_res / ft_res);
	else	
		time_perf.push_back(0);
	errors.push_back(err_count);
}

void test_vector_time_size_capacity_random()
{
    const size_t N = 42;
    const int M = 99;
	
	//random test: size, capacity, empty
	srand(time(NULL));
	{
		//loop test
		timer_start();
		for (int i = 0; i < count; ++i)
		{
			size_t num = rand() % N;
			int fill = rand() % std::numeric_limits<int>::max();
			std::vector<int> std(num, fill);
			ft::vector<int> ft(num, fill);
			int std_res = std.size();
			int ft_res = ft.size();
			if (std_res != ft_res)
				++err_count;
			std_res = std.capacity();
			ft_res = ft.capacity();
			if (std_res != ft_res)
				++err_count;
			bool std_res_b = std.empty();
			bool ft_res_b = ft.empty();
			if (std_res_b != ft_res_b)
				++err_count;
		}
	}
	double comp_res = timer_stop();
	
	//std test
    std::vector<int> std(N, M);
	timer_start();
	for (int i = 0; i < count; ++i){
		std.size();
		std.capacity();
		std.empty();
	}
	double std_res = timer_stop();
	
	//ft test 
	ft::vector<int> ft(N, M);
	timer_start();
	for (int i = 0; i < count; ++i){
		ft.size();
		ft.capacity();
		ft.empty();
	}
	double ft_res = timer_stop();
	
	if (verbose)
	{
		performance_result(std_res, ft_res);
		comparision_result(comp_res);
	}
	if (std_res != 0)
		time_perf.push_back(std_res / ft_res);
	else	
		time_perf.push_back(0);
	errors.push_back(err_count);
}

void test_vector_time_access()
{
    const size_t N = 42;
    const int M = std::numeric_limits<int>::max();

	srand(time(NULL));
	{
		//loop test
		timer_start();
		for (int i = 0; i < count; ++i)
		{
			size_t num = rand() % N;
			std::vector<int> std;
			ft::vector<int> ft;
			for (size_t i = 0; i < num; ++i)
			{
				int fill = rand() % M;
				std.push_back(fill);
				ft.push_back(fill);
			}
			if (!num) continue;
			int std_res = std.size();
			int ft_res = ft.size();
			if (std_res != ft_res)
				++err_count;
			if (std.front() != ft.front())
				++err_count;
			if (std.back() != ft.back())
				++err_count;
			size_t pos = rand() % num;
			if (std.at(pos) != ft.at(pos))
				++err_count;
			if (std[pos] != ft[pos])
				++err_count;
		}
	}
	double comp_res = timer_stop();

	//print results
	if (verbose)
	{
		performance_result(0, 0);
		comparision_result(comp_res);
	}
	time_perf.push_back(0);
	errors.push_back(err_count);
}

void test_vector_time_resize()
{
    const size_t N = 42;
    const int M = 99;

	srand(time(NULL));
	{
		//loop test
		timer_start();
		for (int i = 0; i < count; ++i)
		{
			size_t num = rand() % N;
			size_t resize_n = rand() % (N * 2);
			int fill = rand() % std::numeric_limits<int>::max();
			std::vector<int> std(num, fill);
			ft::vector<int> ft(num, fill);
			std.resize(resize_n);
			ft.resize(resize_n);
			int std_res = std.size();
			int ft_res = ft.size();
			if (std_res != ft_res)
				++err_count;
			if (!std::equal(std.begin(),std.end(),ft.begin()))
				++err_count;
		}
	}
	double comp_res = timer_stop();

	//std test
	timer_start();
	for (int i = 0; i < count; ++i)
	{
    	std::vector<int> std(N, M);
		std.resize(N * 2);
		std.resize(N / 2);
	}
	double std_res = timer_stop();
	
	//ft test 
	timer_start();
	for (int i = 0; i < count; ++i)
	{
		ft::vector<int> ft(N, M);
		ft.resize(N * 2);
		ft.resize(N / 2);
	}
	double ft_res = timer_stop();
	
	//print results
	if (verbose)
	{
		performance_result(std_res, ft_res);
		comparision_result(comp_res);
	}
	if (std_res != 0)
		time_perf.push_back(std_res / ft_res);
	else	
		time_perf.push_back(0);
	errors.push_back(err_count);
}

void test_vector_time_reserve()
{
    const size_t N = 42;
    const int M = 99;
	
	srand(time(NULL));
	{
		//loop test
		timer_start();
		for (int i = 0; i < count; ++i)
		{
			size_t num = rand() % N;
			std::vector<int> std(num);
			ft::vector<int> ft(num);
			for (size_t i = 0; i < num; ++i)
			{
				int fill = rand() % M;
				std.push_back(fill);
				ft.push_back(fill);
			}
			size_t reserve_n = rand() % (N * 2);
			std.reserve(reserve_n);
			ft.reserve(reserve_n);
			int std_res = std.size();
			int ft_res = ft.size();
			if (std_res != ft_res)
				++err_count;
			std_res = std.capacity();
			ft_res = ft.capacity();
			if (std_res != ft_res)
				++err_count;
			if (!std::equal(std.begin(),std.end(),ft.begin()))
				++err_count;
		}
	}
	double comp_res = timer_stop();

	//std test
	timer_start();
	for (int i = 0; i < count; ++i)
	{
    	std::vector<int> std(N, M);
		std.reserve(N * 2);
	}
	double std_res = timer_stop();
		
	//ft test 
	timer_start();
	for (int i = 0; i < count; ++i)
	{
		ft::vector<int> ft(N, M);
		ft.reserve(N * 2);
	}
	double ft_res = timer_stop();
	
	//print results
	if (verbose)
	{
		performance_result(std_res, ft_res);
		comparision_result(comp_res);
	}
	if (std_res != 0)
		time_perf.push_back(std_res / ft_res);
	else	
		time_perf.push_back(0);
	errors.push_back(err_count);
}

void test_vector_time_push_back()
{
    const size_t N = 21;
    const int M = std::numeric_limits<int>::max();
	
	srand(time(NULL));
	{
		//loop test
		timer_start();
		for (int i = 0; i < count; ++i)
		{
			std::vector<int> std(N);
			ft::vector<int> ft(N);
			for (size_t i = 0; i < N * 2; ++i)
			{
				int fill = rand() % M;
				std.push_back(fill);
				ft.push_back(fill);
			}		
			int std_res = std.size();
			int ft_res = ft.size();
			if (std_res != ft_res)
				++err_count;
			if (!std::equal(std.begin(),std.end(),ft.begin()))
				++err_count;
		}
	}
	double comp_res = timer_stop();

	//std test
    std::vector<int> std;
	timer_start();
	for (int i = 0; i < count; ++i)
		std.push_back(N);
	double std_res = timer_stop();
	
	//ft test 
	ft::vector<int> ft;
	timer_start();
	for (int i = 0; i < count; ++i)
		ft.push_back(N);
	double ft_res = timer_stop();
		
	//print result
	if (verbose)
	{
		performance_result(std_res, ft_res);
		comparision_result(comp_res);
	}
	if (std_res != 0)
		time_perf.push_back(std_res / ft_res);
	else	
		time_perf.push_back(0);
	errors.push_back(err_count);
}

void test_vector_time_pop_back()
{
    const size_t N = 42;
    const int M = std::numeric_limits<int>::max();

	srand(time(NULL));
	{
		//loop test
		timer_start();
		for (int i = 0; i < count; ++i)
		{
			size_t num = rand() % N;
			std::vector<int> std(num);
			ft::vector<int> ft(num);
			for (size_t i = 0; i < num; ++i)
			{
				int fill = rand() % M;
				std.push_back(fill);
				ft.push_back(fill);
			}
			if (num)
			{ 
				size_t del = rand() % num;
				for (size_t i = 0; i < del; ++i)
				{
					std.pop_back();
					ft.pop_back();
				}
			}
			int std_res = std.size();
			int ft_res = ft.size();
			if (std_res != ft_res)
				++err_count;
			if (!std::equal(std.begin(),std.end(),ft.begin()))
				++err_count;
		}
	}
	double comp_res = timer_stop();

	//std test
    std::vector<int> std(count, M);
	timer_start();
	for (int i = 0; i < count; ++i)
		std.pop_back();
	double std_res = timer_stop();
	
	//ft test 
	ft::vector<int> ft(count, M);
	timer_start();
	for (int i = 0; i < count; ++i)
		ft.pop_back();
	double ft_res = timer_stop();
	
	//print result
	if (verbose)
	{
		performance_result(std_res, ft_res);
    	comparision_result(comp_res);
	}
	if (std_res != 0)
		time_perf.push_back(std_res / ft_res);
	else	
		time_perf.push_back(0);
	errors.push_back(err_count);
}

void test_vector_time_erase_position()
{
    const size_t N = 42;
    const int M = std::numeric_limits<int>::max();
	
	srand(time(NULL));
	{
		//loop test
		timer_start();
		count = 0;
		for (int i = 0; i < count; ++i){
			size_t num = rand() % N;
			std::vector<int> std;
			ft::vector<int> ft;
			for (size_t i = 0; i < num; ++i){
				int fill = rand() % M;
				std.push_back(fill);
				ft.push_back(fill);
			}
			if (!num) continue;
			size_t it_pos = rand() % num;
			std::vector<int>::iterator it = std.begin() + it_pos;
			ft::vector<int>::iterator its = ft.begin() + it_pos;
			std::vector<int>::iterator res_std = std.erase(it);
			ft::vector<int>::iterator res_ft = ft.erase(its);
			if (res_std != std.end() && res_ft != ft.end() && *res_std != *res_ft)
				++err_count;
			if (res_std - std.begin() != res_ft - ft.begin())
				++err_count;
			int std_res = std.size();
			int ft_res = ft.size();
			if (std_res != ft_res)
				++err_count;
			if (!std::equal(std.begin(),std.end(),ft.begin()))
				++err_count;
		}
	}
	double comp_res = timer_stop();

	//std test
    std::vector<int> std(count, M);
	timer_start();
	for (int i = 0; i < count; ++i)
		std.erase(std.begin());
	double std_res = timer_stop();
	
	//ft test 
	ft::vector<int> ft(count, M);
	timer_start();
	for (int i = 0; i < count; ++i)
		ft.erase(ft.begin());
	double ft_res = timer_stop();
	
	//print results
	if (verbose)
	{
		performance_result(std_res, ft_res);
    	comparision_result(comp_res);
	}
	if (std_res != 0)
		time_perf.push_back(std_res / ft_res);
	else	
		time_perf.push_back(0);
	errors.push_back(err_count);
}

void test_vector_time_erase_iter()
{
    const size_t N = 42;
    const int M = std::numeric_limits<int>::max();
	
	srand(time(NULL)); 
	{
		//loop test
		timer_start();
		for (int i = 0; i < count; ++i)
		{
			size_t num = rand() % N;
			std::vector<int> std;
			ft::vector<int> ft;
			for (size_t i = 0; i < num; ++i)
			{
				int fill = rand() % M;
				std.push_back(fill);
				ft.push_back(fill);
			}
			if (!num) continue;
			size_t it_pos = rand() % num;
			std::vector<int>::iterator it = std.begin() + it_pos;
			ft::vector<int>::iterator its = ft.begin() + it_pos;
			std::vector<int>::iterator res_std = std.erase(std.begin(), it);
			ft::vector<int>::iterator res_ft = ft.erase(ft.begin(), its);
			if (res_std != std.end() && res_ft != ft.end() && *res_std != *res_ft)
				++err_count;
			if (res_std - std.begin() != res_ft - ft.begin())
				++err_count;
			int std_res = std.size();
			int ft_res = ft.size();
			if (std_res != ft_res)
				++err_count;
			if (!std::equal(std.begin(),std.end(),ft.begin()))
				++err_count;
		}
	}
	double comp_res = timer_stop();

	//std test
    std::vector<int> std(count, M);
	timer_start();
	for (int i = 0; i < count; ++i)
		std.erase(std.begin(), std.begin() + 1);
	double std_res = timer_stop();
	
	//ft test 
	ft::vector<int> ft(count, M);
	timer_start();
	for (int i = 0; i < count; ++i)
		ft.erase(ft.begin(), ft.begin() + 1);
	double ft_res = timer_stop();
	
	//print results
	if (verbose)
	{
		performance_result(std_res, ft_res);
    	comparision_result(comp_res);
	}
	if (std_res != 0)
		time_perf.push_back(std_res / ft_res);
	else	
		time_perf.push_back(0);
	errors.push_back(err_count);
}

void test_vector_time_clear()
{
    const size_t N = 42;
    const int M = std::numeric_limits<int>::max();
	
	srand(time(NULL));
	{
		//loop test
		timer_start();
		for (int i = 0; i < count; ++i)
		{
			size_t num = rand() % N;
			std::vector<int> std;
			ft::vector<int> ft;
			for (size_t i = 0; i < num; ++i)
			{
				int fill = rand() % M;
				std.push_back(fill);
				ft.push_back(fill);
			}
			std.clear();
			ft.clear();
			int std_res = std.size();
			int ft_res = ft.size();
			if (std_res != ft_res)
				++err_count;
			if (!std::equal(std.begin(),std.end(),ft.begin()))
				++err_count;
		}
	}
	double comp_res = timer_stop();

	//std test
	timer_start();
	for (int i = 0; i < count; ++i)
	{
		std::vector<int> std(N * N / 2, M);
		std.clear();
	}
	double std_res = timer_stop();
	
	//ft test 
	timer_start();
	for (int i = 0; i < count; ++i)
	{
		ft::vector<int> ft(N * N / 2, M);
		ft.clear();
	}
	double ft_res = timer_stop();

	//print results
	if (verbose)
	{
		performance_result(std_res, ft_res);
    	comparision_result(comp_res);
	}
	if (std_res != 0)
		time_perf.push_back(std_res / ft_res);
	else	
		time_perf.push_back(0);
	errors.push_back(err_count);
}

void test_vector_time_insert_position()
{
    const size_t N = 42;
    const int M = std::numeric_limits<int>::max();
	
	srand(time(NULL));
	{
		//loop test
		timer_start();
		for (int i = 0; i < count; ++i)
		{
			size_t num = rand() % N;
			std::vector<int> std;
			ft::vector<int> ft;
			for (size_t i = 0; i < num; ++i)
			{
				int fill = rand() % M;
				std.push_back(fill);
				ft.push_back(fill);
			}
			if (!num) continue;
			size_t it_pos = rand() % num;
			std::vector<int>::iterator it = std.begin() + it_pos;
			ft::vector<int>::iterator its = ft.begin() + it_pos;
			std::vector<int>::iterator res_std = std.insert(it, N);
			ft::vector<int>::iterator res_ft = ft.insert(its, N);
			if (*res_std != *res_ft)
				++err_count;
			if (res_std - std.begin() != res_ft - ft.begin())
				++err_count;
			int std_res = std.size();
			int ft_res = ft.size();
			if (std_res != ft_res)
				++err_count;
			if (!std::equal(std.begin(),std.end(),ft.begin()))
				++err_count;
		}
	}
	double comp_res = timer_stop();
	
	//std test
    std::vector<int> std(N, M);
	timer_start();
	for (int i = 0; i < count; ++i)
		std.insert(std.begin(), N);
	double std_res = timer_stop();
	
	//ft test 
	ft::vector<int> ft(N, M);
	timer_start();
	for (int i = 0; i < count; ++i)
		ft.insert(ft.begin(), N);
	double ft_res = timer_stop();
	
	//print results
	if (verbose)
	{
		performance_result(std_res, ft_res);
    	comparision_result(comp_res);
	}
	if (std_res != 0)
		time_perf.push_back(std_res / ft_res);
	else	
		time_perf.push_back(0);
	errors.push_back(err_count);
}

void test_vector_time_insert_pos_value()
{
    const size_t N = 42;
    const int M = std::numeric_limits<int>::max();

	srand(time(NULL));
	{
		//loop test
		timer_start();
		for (int i = 0; i < count; ++i)
		{
			size_t num = rand() % N;
			std::vector<int> std;
			ft::vector<int> ft;
			for (size_t i = 0; i < num; ++i)
			{
				int fill = rand() % M;
				std.push_back(fill);
				ft.push_back(fill);
			}
			if (!num) continue;
			size_t it_pos = rand() % num;
			int fill = rand() % N;
			std::vector<int>::iterator it = std.begin() + it_pos;
			ft::vector<int>::iterator its = ft.begin() + it_pos;
			std.insert(it, (size_t) fill, fill);
			ft.insert(its, (size_t) fill, fill);
			int std_res = std.size();
			int ft_res = ft.size();
			if (std_res != ft_res)
				++err_count;
			if (!std::equal(std.begin(),std.end(),ft.begin()))
				++err_count;
		}
	}
	double comp_res = timer_stop();

	//std test
    std::vector<int> std(N, M);
	timer_start();
	for (int i = 0; i < count; ++i)
		std.insert(std.begin(), (size_t) 1, 42);
	double std_res = timer_stop();
	
	//ft test 
	ft::vector<int> ft(N, M);
	timer_start();
	for (int i = 0; i < count; ++i)
		ft.insert(ft.begin(), (size_t) 1, 42);
	double ft_res = timer_stop();
	
	//print results
	if (verbose)
	{
		performance_result(std_res, ft_res);
    	comparision_result(comp_res);
	}
	if (std_res != 0)
		time_perf.push_back(std_res / ft_res);
	else	
		time_perf.push_back(0);
	errors.push_back(err_count);
}

void test_vector_time_insert_iter()
{
    const size_t N = 42;
    const int M = std::numeric_limits<int>::max();

	srand(time(NULL));
	{
		//loop test
		timer_start();
		for (int i = 0; i < count; ++i)
		{
			size_t num = rand() % N;
			std::vector<int> std;
			std::vector<int> std_s;
			ft::vector<int> ft;
			ft::vector<int> ft_s;
			for (size_t i = 0; i < num; ++i)
			{
				int fill = rand() % M;
				std.push_back(fill);
				ft.push_back(fill);
				fill = rand() % M;
				std_s.push_back(fill);
				ft_s.push_back(fill);
			}
			if (!num) continue;
			size_t it_pos = rand() % num;
			std::vector<int>::iterator it = std.begin() + it_pos;
			ft::vector<int>::iterator its = ft.begin() + it_pos;
			std.insert(it, std_s.begin(), (std_s.begin() + it_pos));
			ft.insert(its, ft_s.begin(), (ft_s.begin() + it_pos));
			int std_res = std.size();
			int ft_res = ft.size();
			if (std_res != ft_res)
				++err_count;
			if (!std::equal(std.begin(),std.end(),ft.begin()))
				++err_count;
		}
	}
	double comp_res = timer_stop();

	//std test
    std::vector<int> std(N, M);
    std::vector<int> std_s(1, M);
	timer_start();
	for (int i = 0; i < count; ++i)
		std.insert(std.begin(), std_s.begin(), std_s.end());
	double std_res = timer_stop();
	
	//ft test 
	ft::vector<int> ft(N, M);
	ft::vector<int> ft_s(N, M);
	timer_start();
	for (int i = 0; i < count; ++i)
		ft.insert(ft.begin(), std_s.begin(), std_s.end());
	double ft_res = timer_stop();
	
	//print results
	if (verbose)
	{
		performance_result(std_res, ft_res);
    	comparision_result(comp_res);
	}
	if (std_res != 0)
		time_perf.push_back(std_res / ft_res);
	else	
		time_perf.push_back(0);
	errors.push_back(err_count);
}

void test_vector_time_assign()
{
    const size_t N = 42;
    const int M = std::numeric_limits<int>::max();

	srand(time(NULL));
	{
		//loop test
		timer_start();
		for (int i = 0; i < count; ++i)
		{
			size_t num = rand() % N;
			std::vector<int> std;
			ft::vector<int> ft;
			for (size_t i = 0; i < num; ++i)
			{
				int fill = rand() % M;
				std.push_back(fill);
				ft.push_back(fill);
			}
			std::vector<int> std_r;
			ft::vector<int> ft_r;
			std_r = std;
			ft_r = ft;
			int std_res = std_r.size();
			int ft_res = ft_r.size();
			if (std_res != ft_res)
				++err_count;
			if (!std::equal(std_r.begin(),std_r.end(),ft_r.begin()))
				++err_count;
		}
	}
	double comp_res = timer_stop();

	//std test
    std::vector<int> std(N * N, M);
	timer_start();
	for (int i = 0; i < count; ++i)
	{
    	std::vector<int> std_r;
		std_r = std;
	}
	double std_res = timer_stop();
	
	//ft test
	ft::vector<int> ft(N * N, M);
	timer_start();
	for (int i = 0; i < count; ++i)
	{
		ft::vector<int> ft_r;
		ft_r = ft;
	}
	double ft_res = timer_stop();
	
	//print results
	if (verbose)
	{
		performance_result(std_res, ft_res);
    	comparision_result(comp_res);
	}
	if (std_res != 0)
		time_perf.push_back(std_res / ft_res);
	else	
		time_perf.push_back(0);
	errors.push_back(err_count);
}

void test_vector_time_assign_range()
{
    const size_t N = 42;
    const int M = std::numeric_limits<int>::max();

	srand(time(NULL));
	{
		//loop test
		timer_start();
		for (int i = 0; i < count; ++i)
		{
			size_t num = rand() % N;
			std::vector<int> std;
			ft::vector<int> ft;
			for (size_t i = 0; i < num; ++i)
			{
				int fill = rand() % M;
				std.push_back(fill);
				ft.push_back(fill);
			}
			std::vector<int> std_r;
			ft::vector<int> ft_r;
			std_r.assign(std.begin(), std.end());
			ft_r.assign(ft.begin(), ft.end());
			int std_res = std_r.size();
			int ft_res = ft_r.size();
			if (std_res != ft_res)
				++err_count;
			if (!std::equal(std_r.begin(),std_r.end(),ft_r.begin()))
				++err_count;
		}
	}
	double comp_res = timer_stop();

	//std test
    std::vector<int> std(N * N, M);
	timer_start();
	for (int i = 0; i < count; ++i)
	{
    	std::vector<int> std_r;
		std_r.assign(std.begin(), std.end());
	}
	double std_res = timer_stop();
		
	//ft test
	ft::vector<int> ft(N * N, M);
	timer_start();
	for (int i = 0; i < count; ++i)
	{
		ft::vector<int> ft_r;
		ft_r.assign(ft.begin(), ft.end());
	}
	double ft_res = timer_stop();
	
	//print results
	if (verbose)
	{
		performance_result(std_res, ft_res);
    	comparision_result(comp_res);
	}
	if (std_res != 0)
		time_perf.push_back(std_res / ft_res);
	else	
		time_perf.push_back(0);
	errors.push_back(err_count);
}

void test_vector_time_assign_value()
{
    const size_t N = 42;
    const int M = std::numeric_limits<int>::max();

	srand(time(NULL));
	{
		//loop test
		timer_start();
		for (int i = 0; i < count; ++i)
		{
			size_t num = rand() % N;
			int fill = rand() % M;
			std::vector<int> std;
			ft::vector<int> ft;
			std.assign(num, fill);
			ft.assign(num, fill);
			int std_res = std.size();
			int ft_res = ft.size();
			if (std_res != ft_res)
				++err_count;
			if (!std::equal(std.begin(),std.end(),ft.begin()))
				++err_count;
		}
	}
	double comp_res = timer_stop();

	//std test
	timer_start();
	for (int i = 0; i < count; ++i)
	{
    	std::vector<int> std;
		std.assign(N * N, M);
	}
	double std_res = timer_stop();
	
	//ft test
	timer_start();
	for (int i = 0; i < count; ++i)
	{
		ft::vector<int> ft;
		ft.assign(N * N, M);
	}
	double ft_res = timer_stop();
	
	//print results
	if (verbose)
	{
		performance_result(std_res, ft_res);
    	comparision_result(comp_res);
	}
	if (std_res != 0)
		time_perf.push_back(std_res / ft_res);
	else	
		time_perf.push_back(0);
	errors.push_back(err_count);
}

void test_vector_time_iter()
{
    const size_t N = 42;
    const int M = std::numeric_limits<int>::max();

	srand(time(NULL));
	{
		//loop test
		timer_start();
		for (int i = 0; i < count; ++i)
		{
			size_t num = rand() % N;
			if (!num) continue;
			std::vector<int> std;
			ft::vector<int> ft;
			for (size_t i = 0; i < num; ++i)
			{
				int fill = rand() % M;
				std.push_back(fill);
				ft.push_back(fill);
			}
			std::vector<int>::iterator it_rb = std.begin();
			std::vector<int>::iterator it_re = std.end();
			ft::vector<int>::iterator its_rb = ft.begin();
			ft::vector<int>::iterator its_re = ft.end();

			if (*it_rb != *its_rb)
				++err_count;
			if (it_rb - it_re != its_rb - its_re)
				++err_count;
			if (!std::equal(it_rb, it_re, its_rb))
				++err_count;
		}
	}
	double comp_res = timer_stop();
	//print results
	if (verbose)
	{
		performance_result(0, 0);
    	comparision_result(comp_res);
	}
	time_perf.push_back(0);
	errors.push_back(err_count);
}

void test_vector_time_const_iter()
{
    const size_t N = 42;
    const int M = std::numeric_limits<int>::max();

	srand(time(NULL));
	{
		//loop test
		timer_start();
		for (int i = 0; i < count; ++i)
		{
			size_t num = rand() % N;
			if (!num) continue;
			std::vector<int> std;
			ft::vector<int> ft;
			for (size_t i = 0; i < num; ++i)
			{
				int fill = rand() % M;
				std.push_back(fill);
				ft.push_back(fill);
			}
			std::vector<int>::const_iterator it_rb = std.begin();
			std::vector<int>::const_iterator it_re = std.end();
			ft::vector<int>::const_iterator its_rb = ft.begin();
			ft::vector<int>::const_iterator its_re = ft.end();

			if (*it_rb != *its_rb)
				++err_count;
			if (it_rb - it_re != its_rb - its_re)
				++err_count;
			if (!std::equal(it_rb, it_re, its_rb))
				++err_count;
		}
	}
	double comp_res = timer_stop();
	//print results
	if (verbose)
	{
		performance_result(0, 0);
    	comparision_result(comp_res);
	}
	time_perf.push_back(0);
	errors.push_back(err_count);
}

void test_vector_time_reverse_iter()
{
    const size_t N = 42;
    const int M = std::numeric_limits<int>::max();

	srand(time(NULL));
	{
		//loop test
		timer_start();
		for (int i = 0; i < count; ++i)
		{
			size_t num = rand() % N;
			if (!num) continue;
			std::vector<int> std;
			ft::vector<int> ft;
			for (size_t i = 0; i < num; ++i)
			{
				int fill = rand() % M;
				std.push_back(fill);
				ft.push_back(fill);
			}
			std::vector<int>::reverse_iterator it_rb = std.rbegin();
			std::vector<int>::reverse_iterator it_re = std.rend();
			ft::vector<int>::reverse_iterator its_rb = ft.rbegin();
			ft::vector<int>::reverse_iterator its_re = ft.rend();

			if (*it_rb != *its_rb)
				++err_count;
			if (it_rb - it_re != its_rb - its_re)
				++err_count;
			if (!std::equal(it_rb, it_re, its_rb))
				++err_count;
		}
	}
	double comp_res = timer_stop();
	//print results
	if (verbose)
	{
		performance_result(0, 0);
    	comparision_result(comp_res);
	}
	time_perf.push_back(0);
	errors.push_back(err_count);
}

void test_vector_time_const_reverse_iter()
{
    const size_t N = 42;
    const int M = std::numeric_limits<int>::max();

	srand(time(NULL));
	{
		//loop test
		timer_start();
		for (int i = 0; i < count; ++i)
		{
			size_t num = rand() % N;
			if (!num) continue;
			std::vector<int> std;
			ft::vector<int> ft;
			for (size_t i = 0; i < num; ++i)
			{
				int fill = rand() % M;
				std.push_back(fill);
				ft.push_back(fill);
			}
			std::vector<int>::const_reverse_iterator it_rb = std.rbegin();
			std::vector<int>::const_reverse_iterator it_re = std.rend();
			ft::vector<int>::const_reverse_iterator its_rb = ft.rbegin();
			ft::vector<int>::const_reverse_iterator its_re = ft.rend();

			if (*it_rb != *its_rb)
				++err_count;
			if (it_rb - it_re != its_rb - its_re)
				++err_count;
			if (!std::equal(it_rb, it_re, its_rb))
				++err_count;
		}
	}
	double comp_res = timer_stop();
	//print results
	if (verbose)
	{
		performance_result(0, 0);
    	comparision_result(comp_res);
	}
	time_perf.push_back(0);
	errors.push_back(err_count);
}

void test_vector_time_swap()
{
    const size_t N1 = 21;
    const size_t N2 = 42;
    const int M1 = 99;
    const int M2 = 44;
	
	{
		//loop test
		timer_start();
		for (int i = 0; i < count; ++i)
		{
			ft::vector<int> std(N1, M1);
			ft::vector<int> ft(N2, M2);

			std.swap(ft);
			if (std.size() != N2) ++err_count;
			if (ft.size() != N1) ++err_count;
			if (*(std.begin()) != M2) ++err_count;
			if (*(ft.begin()) != M1) ++err_count;
			if (std.capacity() != N2) ++err_count;
			if (ft.capacity() != N1) ++err_count;
			
			ft::swap(std, ft);
			if (std.size() != N1) ++err_count;
			if (ft.size() != N2) ++err_count;
			if (*(std.begin()) != M1) ++err_count;
			if (*(ft.begin()) != M2) ++err_count;
			if (std.capacity() != N1) ++err_count;
			if (ft.capacity() != N2) ++err_count;
		}
	}
	double comp_res = timer_stop();
	
	//std test
    std::vector<int> std(count, M1);
    std::vector<int> ft(count, M2);
	timer_start();
	for (int i = 0; i < count; ++i)
		std.swap(ft);
	double std_res = timer_stop();
	
	//ft test 
	ft::vector<int> v3(count, M1);
	ft::vector<int> v4(count, M2);
	timer_start();
	for (int i = 0; i < count; ++i)
		v3.swap(v4);
	double ft_res = timer_stop();
	
	//print results
	if (verbose)
	{
		performance_result(std_res, ft_res);
    	comparision_result(comp_res);
	}
	if (std_res != 0)
		time_perf.push_back(std_res / ft_res);
	else	
		time_perf.push_back(0);
	errors.push_back(err_count);
}

void test_vector_time_comparison()
{
    const size_t N = 42;
    const int M = std::numeric_limits<int>::max();
	
	srand(time(NULL));
	{
		//loop test
		timer_start();
		for (int i = 0; i < count; ++i)
		{
			size_t num = rand() % N;
			std::vector<int> std(N);
			std::vector<int> std_s(N);
			ft::vector<int> ft(N);
			ft::vector<int> ft_s(N);
			for (size_t i = 0; i < num; ++i)
			{
				int fill = rand() % M;
				std.push_back(fill);
				std_s.push_back(fill);
				ft.push_back(fill);
				ft_s.push_back(fill);
			}
			if ((std==std_s) != (ft==ft_s)) ++err_count;
			if ((std<std_s) != (ft<ft_s)) ++err_count;
			if ((std!=std_s) != (ft!=ft_s)) ++err_count;
			if ((std>std_s) != (ft>ft_s)) ++err_count;
			if ((std<=std_s) != (ft<=ft_s)) ++err_count;
			if ((std>=std_s) != (ft>=ft_s)) ++err_count;
		}
	}
	double comp_res = timer_stop();
	
	//print results
	if (verbose)
	{
		performance_result(0, 0);
    	comparision_result(comp_res);
	}
	time_perf.push_back(0);
	errors.push_back(err_count);
}
