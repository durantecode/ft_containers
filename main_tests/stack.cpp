/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 19:02:40 by ldurante          #+#    #+#             */
/*   Updated: 2022/10/28 21:16:00 by ldurante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.hpp"

long counter = 50;

static void test_stack_empty_constructor(void)
{
	print_header("EMPTY CONSTRUCTOR TEST", 0);
	
	ft::stack<int> ft;
	std::stack<int> std;
	check("ft.size() == std.size()", ft.size() == std.size());
	check("ft.empty() == std.empty()", ft.empty() == std.empty());

	test_stack_time_empty_constructor(counter);
}


static void test_stack_copy_constructor(void)
{
	print_header("COPY CONSTRUCTOR TEST", 0);
	ft::stack<int> ft;
	std::stack<int> std;
	check("ft.size() == std.size()", ft.size() == std.size());
	check("ft.empty() == std.empty()", ft.empty() == std.empty());
}

static void test_stack_assignment(void)
{
	print_header("ASSIGNMENT TEST", 0);
	
	test_stack_time_assignment(counter);
}

static void test_stack_size_empty_top(void)
{
	print_header("SIZE/EMPTY/TOP TEST", 0);
	
	test_stack_time_size_empty_top(counter);
}

static void test_stack_push_pop(void)
{
	print_header("PUSH / POP TEST", 0);
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
}

void test_stack(void)
{
	print_header("STACK TESTS", 1);

	test_stack_empty_constructor();
	test_stack_copy_constructor();
	test_stack_assignment();
	test_stack_size_empty_top();
	test_stack_push_pop();
}
