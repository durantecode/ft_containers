/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_time_tests.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 11:19:43 by ldurante          #+#    #+#             */
/*   Updated: 2022/10/31 17:27:27 by ldurante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.hpp"

void test_stack_time_empty_constructor()
{
	//std test
	timer_start();
	for (int i = 0; i < count; ++i)
		std::stack<int> std;
	double std_res = timer_stop();

	//ft test
	timer_start();
	for (int i = 0; i < count; ++i)
		ft::stack<int> ft;
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

void test_stack_time_copy_constructor()
{
	//init
    const size_t N = 42;
    const int M = std::numeric_limits<int>::max();
	
	srand(time(NULL));
	{
		//loop test
		timer_start();
		for (int i = 0; i < count; ++i)
		{
			size_t num = rand() % N;
			std::stack<int> std;
			ft::stack<int> ft;
			for (size_t i = 0; i < num; ++i)
			{
				int fill = rand() % M;
				std.push(fill);
				ft.push(fill);
			}
			std::stack<int> std_r(std);
			ft::stack<int> ft_r(ft);
			int std_res = std_r.size();
			int ft_res = ft_r.size();
			if (std_res != ft_res)
				++err_count;
		}
	}
	double comp_res = timer_stop();

	// std test
    std::stack<int> std;
    for (size_t i = 0; i < N * N; ++i)
		std.push(N);
	timer_start();
	for (int i = 0; i < count; ++i)
	    std::stack<int> std_r(std);
	double std_res = timer_stop();
	
	//ft test
	ft::stack<int> ft;
    for (size_t i = 0; i < N * N; ++i)
		ft.push(N);
	timer_start();
	for (int i = 0; i < count; ++i)
		ft::stack<int> ft_r(ft);
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

void test_stack_time_assignment()
{
	//init
    const size_t N = 42;
    const int M = std::numeric_limits<int>::max();
	
	srand(time(NULL));
	{
		//loop test
		timer_start();
		for (int i = 0; i < count; ++i)
		{
			size_t num = rand() % N;
			std::stack<int> std;
			ft::stack<int> ft;
			for (size_t i = 0; i < num; ++i)
			{
				int fill = rand() % M;
				std.push(fill);
				ft.push(fill);
			}
			std::stack<int> std_r;
			ft::stack<int> ft_r;
			std_r = std;
			ft_r = ft;
			int std_res = std_r.size();
			int ft_res = ft_r.size();
			if (std_res != ft_res)
				++err_count;
		}
	}
	double comp_res = timer_stop();

	//std test
    std::stack<int> std;
    for (size_t i = 0; i < N * N; ++i)
		std.push(N);
	timer_start();
	for (int i = 0; i < count; ++i)
	{
    	std::stack<int> std_r;
		std_r = std;
	}
	double std_res = timer_stop();
	
	//ft test
    ft::stack<int> ft;
    for (size_t i = 0; i < N * N; ++i)
		ft.push(N);
	timer_start();
	for (int i = 0; i < count; ++i)
	{
    	ft::stack<int> ft_r;
		ft_r = ft;
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

void test_stack_time_size_empty_top()
{
	//init
    const size_t N = 42;
    const int M = std::numeric_limits<int>::max();

	srand(time(NULL));
	{
		//loop test
		timer_start();
 		for (int i = 0; i < count; ++i)
		{
			size_t num = rand() % N;
			std::stack<int> std;
			ft::stack<int> ft;
			for (size_t i = 0; i < num; ++i)
			{
				int fill = rand() % M;
				std.push(fill);
				ft.push(fill);
			}
			if (std.size() != ft.size())
				++err_count;
			if (std.empty() != ft.empty())
				++err_count;
			if (!std.size())
				continue;
			if (std.top() != ft.top())
				++err_count;
		}
	}
	double comp_res = timer_stop();

	if (verbose)
	{
		performance_result(0, 0);
    	comparision_result(comp_res);
	}
	time_perf.push_back(0);
	errors.push_back(err_count);
}

void test_stack_time_push_pop()
{
	// //init
    const size_t N = 42;
    const int M = std::numeric_limits<int>::max();

	srand(time(NULL));
	{
		//loop test
		timer_start();
		for (int i = 0; i < count; ++i)
		{
			size_t num = rand() % N;
			std::stack<int> std;
			ft::stack<int> ft;
			for (size_t i = 0; i < num; ++i)
			{
				int fill = rand() % M;
				std.push(fill);
				ft.push(fill);
				if (std.top() != ft.top())
					++err_count;
			}
			if (!num) continue;
			size_t op = rand() % num;
			for (size_t i = 0; i < op; ++i)
			{
				std.pop();
				ft.pop();
			}
			if (std.size() != ft.size())
				++err_count;
		}
	}
	double comp_res = timer_stop();

	//std test
    std::stack<int> std;
	timer_start();
	for (int i = 0; i < count; ++i)
	{
		for (size_t i = 0; i < N; ++i) std.push(N);
        for (size_t i = 0; i < N; ++i) std.pop();
	}
	double std_res = timer_stop();
	
	//ft test
    ft::stack<int> ft;
	timer_start();
	for (int i = 0; i < count; ++i)
	{
		for (size_t i = 0; i < N; ++i) ft.push(N);
        for (size_t i = 0; i < N; ++i) ft.pop();
	}
	double ft_res = timer_stop();

	if (verbose)
	{
		performance_result(std_res, ft_res);
		comparision_result(comp_res);
	}
	if (std_res != 0)
	{	
		time_perf.push_back(std_res / ft_res);
	}
	else	
		time_perf.push_back(0);
	errors.push_back(err_count);
}


void test_stack_time_comparison()
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
			std::stack<int> std;
			std::stack<int> std_s;
			ft::stack<int> ft;
			ft::stack<int> ft_s;
			for (size_t i = 0; i < num; ++i)
			{
				int fill = rand() % M;
				std.push(fill);
				std_s.push(fill);
				ft.push(fill);
				ft_s.push(fill);
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
