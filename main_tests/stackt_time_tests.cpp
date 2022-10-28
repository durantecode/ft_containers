/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stackt_time_tests.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 11:19:43 by ldurante          #+#    #+#             */
/*   Updated: 2022/10/28 12:42:41 by ldurante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.hpp"

void test_stack_time_empty_constructor(long count)
{
	//std test
	timer_start();
	for (int i = 0; i < count; ++i)
		std::stack<int> p1;
	double std_res = timer_stop();

	//ft test
	timer_start();
	for (int i = 0; i < count; ++i)
		ft::stack<int> p1;
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
			std::stack<int> v1;
			ft::stack<int> v2;
			for (size_t i = 0; i < num; ++i)
			{
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
	}
	double comp_res = timer_stop();

	//std test
    std::stack<int> v1;
    for (size_t i = 0; i < N * N; ++i)
		v1.push(N);
	timer_start();
	for (int i = 0; i < count; ++i)
	    std::stack<int> v1_r(v1);
	double std_res = timer_stop();
	
	//ft test
	ft::stack<int> v2;
    for (size_t i = 0; i < N * N; ++i)
		v2.push(N);
	timer_start();
	for (int i = 0; i < count; ++i)
		ft::stack<int> v2_r(v2);
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
			std::stack<int> v1;
			ft::stack<int> v2;
			for (size_t i = 0; i < num; ++i)
			{
				int fill = rand() % M;
				v1.push(fill);
				v2.push(fill);
			}
			std::stack<int> v1_r;
			ft::stack<int> v2_r;
			v1_r = v1;
			v2_r = v2;
			int std_res = v1_r.size();
			int ft_res = v2_r.size();
			if (std_res != ft_res)
				++err_count;
		}
	}
	double comp_res = timer_stop();

	//std test
    std::stack<int> v1;
    for (size_t i = 0; i < N * N; ++i)
		v1.push(N);
	timer_start();
	for (int i = 0; i < count; ++i)
	{
    	std::stack<int> v1_r;
		v1_r = v1;
	}
	double std_res = timer_stop();
	
	//ft test
    ft::stack<int> v2;
    for (size_t i = 0; i < N * N; ++i)
		v2.push(N);
	timer_start();
	for (int i = 0; i < count; ++i)
	{
    	ft::stack<int> v2_r;
		v2_r = v2;
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
			std::stack<int> v1;
			ft::stack<int> v2;
			for (size_t i = 0; i < num; ++i)
			{
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
			std::stack<int> v1;
			ft::stack<int> v2;
			for (size_t i = 0; i < num; ++i)
			{
				int fill = rand() % M;
				v1.push(fill);
				v2.push(fill);
				if (v1.top() != v2.top())
					++err_count;
			}
			if (!num) continue;
			size_t op = rand() % num;
			for (size_t i = 0; i < op; ++i)
			{
				v1.pop();
				v2.pop();
			}
			if (v1.size() != v2.size())
				++err_count;
		}
	}
	double comp_res = timer_stop();

	//std test
    std::stack<int> v1;
	timer_start();
	for (int i = 0; i < count; ++i)
	{
		for (size_t i = 0; i < N; ++i) v1.push(N);
        for (size_t i = 0; i < N; ++i) v1.pop();
	}
	double std_res = timer_stop();
	
	//ft test
    ft::stack<int> v2;
	timer_start();
	for (int i = 0; i < count; ++i)
	{
		for (size_t i = 0; i < N; ++i) v2.push(N);
        for (size_t i = 0; i < N; ++i) v2.pop();
	}
	double ft_res = timer_stop();

	performance_result(std_res, ft_res);
    comparision_result(err_count, comp_res);
}
