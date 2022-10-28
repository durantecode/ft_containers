/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stackt_time_tests.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 11:19:43 by ldurante          #+#    #+#             */
/*   Updated: 2022/10/28 13:54:32 by ldurante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.hpp"

void test_stack_time_empty_constructor(long count)
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

	performance_result(std_res, ft_res);
}

void test_stack_time_copy_constructor(long count)
{
	//init
    const size_t N = 42;
    const int M = std::numeric_limits<int>::max();
	long err_count = 0;
	
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

	//std test
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
	
	performance_result(std_res, ft_res);
    comparision_result(err_count, comp_res);
}

void test_stack_time_assignment(long count)
{
	//init
    const size_t N = 42;
    const int M = std::numeric_limits<int>::max();
	long err_count = 0;
	
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
	
	performance_result(std_res, ft_res);
    comparision_result(err_count, comp_res);
}

void test_stack_time_size_empty_top(long count)
{
	//init
    const size_t N = 42;
    const int M = std::numeric_limits<int>::max();
	long err_count = 0;

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
			if (!std.size()) continue;
			if (std.top() != ft.top())
				++err_count;
		}
	}
	double comp_res = timer_stop();
    comparision_result(err_count, comp_res);
}

void test_stack_time_push_pop(long count)
{
	// //init
    const size_t N = 42;
    const int M = std::numeric_limits<int>::max();
	long err_count = 0;

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

	performance_result(std_res, ft_res);
    comparision_result(err_count, comp_res);
}
