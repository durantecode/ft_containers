/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 19:02:40 by ldurante          #+#    #+#             */
/*   Updated: 2022/10/28 12:47:32 by ldurante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.hpp"

long count = 50;

static void test_stack_empty_constructor(void)
{
	print_header("EMPTY CONSTRUCTOR TEST", 0);
	
	ft::stack<int> q1;
	std::stack<int> q2;
	check("q1.size() == q2.size()", q1.size() == q2.size());
	check("q1.empty() == q2.empty()", q1.empty() == q2.empty());

	test_stack_time_empty_constructor(count);
}

static void test_stack_assignment(void)
{
	
}

static void test_stack_size_empty_top(void)
{
	
}

static void test_stack_copy_constructor(void)
{
	print_header("COPY CONSTRUCTOR TEST", 0);
	ft::stack<int> q1;
	std::stack<int> q2;
	check("q1.size() == q2.size()", q1.size() == q2.size());
	check("q1.empty() == q2.empty()", q1.empty() == q2.empty());
}

static void test_stack_push_pop(void)
{
	print_header("PUSH / POP TEST", 0);
	ft::stack<int> q1;
	std::stack<int> q2;
	q1.push(0);
	q1.push(1);
	q1.push(2);
	q2.push(0);
	q2.push(1);
	q2.push(2);
	check("q1.size() == q2.size()", q1.size() == q2.size());
	check("q1.empty() == q2.empty()", q1.empty() == q2.empty());
	check("q1.top() == q2.top()", q1.top(), q2.top());
	q1.pop();
	q2.pop();
	check("q1.size() == q2.size()", q1.size() == q2.size());
	check("q1.top() == q2.top()", q1.top(), q2.top());
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
