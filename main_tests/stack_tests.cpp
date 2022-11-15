/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_tests.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 19:02:40 by ldurante          #+#    #+#             */
/*   Updated: 2022/11/15 00:02:22 by ldurante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.hpp"

static void test_stack_empty_constructor(void)
{
	test_name = "EMPTY CONSTRUCTOR TEST";
	err_count = 0;
	names.push_back(test_name);
	
	if (verbose)
		print_header(test_name, 0);
	
	ft::stack<int> ft;
	std::stack<int> std;
	check("ft.size() == std.size()", ft.size() == std.size());
	check("ft.empty() == std.empty()", ft.empty() == std.empty());

	test_stack_time_empty_constructor();
}


static void test_stack_copy_constructor(void)
{
	test_name = "COPY CONSTRUCTOR TEST ";
	err_count = 0;
	names.push_back(test_name);

	if (verbose)
		print_header(test_name, 0);
	
	ft::stack<int> ft;
	std::stack<int> std;
	check("ft.size() == std.size()", ft.size() == std.size());
	check("ft.empty() == std.empty()", ft.empty() == std.empty());

	test_stack_time_copy_constructor();
}

static void test_stack_assignment(void)
{
	test_name = "ASSIGNMENT TEST ";
	err_count = 0;
	names.push_back(test_name);
	
	if (verbose)
		print_header(test_name, 0);
	
	test_stack_time_assignment();
}

static void test_stack_size_empty_top(void)
{
	test_name = "SIZE/EMPTY/TOP TEST ";
	err_count = 0;
	names.push_back(test_name);

	if (verbose)
		print_header(test_name, 0);

	test_stack_time_size_empty_top();
}

static void test_stack_push_pop(void)
{
	test_name = "PUSH / POP TEST ";
	err_count = 0;
	names.push_back(test_name);
	
	if (verbose)
		print_header(test_name, 0);

	ft::stack<int> ft;
	std::stack<int> std;
	ft.push(0);
	ft.push(1);
	ft.push(2);
	std.push(0);
	std.push(1);
	std.push(2);
	check("ft.size() == std.size()", ft.size() == std.size());
	check("ft.empty() == std.empty()", ft.empty() == std.empty());
	check("ft.top() == std.top()", ft.top(), std.top());
	ft.pop();
	std.pop();
	check("ft.size() == std.size()", ft.size() == std.size());
	check("ft.top() == std.top()", ft.top(), std.top());

	test_stack_time_push_pop();
}

void test_stack_comparision(void)
{
	test_name = "COMPARISON OP TEST";
	err_count = 0;
	names.push_back(test_name);
	
	if (verbose)
		print_header(test_name, 0);

	ft::stack<int> ft;
	std::stack<int> std;
	ft::stack<int> ft2;
	std::stack<int> std2;
	ft.push(1);
	ft.push(2);
	ft.push(3);
	std.push(1);
	std.push(2);
	std.push(3);
	ft2 = ft;
	std2 = std;
	check("ft == std", (ft == ft2), (std == std2));
	check("ft != std", (ft != ft2), (std != std2));
	check("ft >  std", (ft > ft2), (std > std2));
	check("ft <  std", (ft < ft2), (std < std2));
	check("ft >= std", (ft >= ft2), (std >= std2));
	check("ft <= std", (ft <= ft2), (std <= std2));
	ft.push(42);
	std.push(42);
	check("ft == std", (ft == ft2), (std == std2));
	check("ft != std", (ft != ft2), (std != std2));
	check("ft >  std", (ft > ft2), (std > std2));
	check("ft <  std", (ft < ft2), (std < std2));
	check("ft >= std", (ft >= ft2), (std >= std2));
	check("ft <= std", (ft <= ft2), (std <= std2));
	ft2.push(43);
	std2.push(43);
	check("ft == std", (ft == ft2), (std == std2));
	check("ft != std", (ft != ft2), (std != std2));
	check("ft >  std", (ft > ft2), (std > std2));
	check("ft <  std", (ft < ft2), (std < std2));
	check("ft >= std", (ft >= ft2), (std >= std2));
	check("ft <= std", (ft <= ft2), (std <= std2));

	test_stack_time_comparison();
}

void test_stack(void)
{
	print_header("STACK TESTS", 1);

	test_name.clear();
	names.clear();
	errors.clear();
	time_perf.clear();

	test_stack_empty_constructor();
	test_stack_copy_constructor();
	test_stack_assignment();
	test_stack_size_empty_top();
	test_stack_push_pop();
	test_stack_comparision();

	print_test_results();
}
