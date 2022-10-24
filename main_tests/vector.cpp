/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 18:41:53 by ldurante          #+#    #+#             */
/*   Updated: 2022/10/24 13:19:55 by ldurante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.hpp"

template <typename T>
static void print_vector(T vec, std::string type)
{
	typename T::iterator it;

	std::cout << BOLD << type << ", size: " << vec.size() << ", empty: " << vec.empty() << ", capacity: " << vec.capacity() << RESET << std::endl;
	it = vec.begin();
	while (it != vec.end())
	{
		std::cout << *it;
		if (it + 1 != vec.end())
			std::cout << " - ";
		++it;
	}
	std::cout << std::endl;
}

template <typename T>
static void print_vector_reverse(T vec, std::string type)
{
	typename T::iterator it;

	std::cout << BOLD << type << ", size: " << vec.size() << ", empty: " << vec.empty() << ", capacity: " << vec.capacity() << RESET << std::endl;
	it = vec.rbegin();
	while (it != vec.rend())
	{
		std::cout << *it;
		if (it + 1 != vec.rend())
			std::cout << " - ";
		++it;
	}
	std::cout << std::endl;
}

static void default_constructor(void)
{
	print_header("Default constructor");
	ft::vector<int> ft;
	std::vector<int> std;
	check("ft == std", ft == std);
	ft.push_back(1);
	ft.push_back(2);
	ft.push_back(3);
	std.push_back(1);
	std.push_back(2);
	std.push_back(3);
	check("ft == std", ft == std);
}

static void copy_constructor(void)
{
	print_header("Copy");
	ft::vector<int> ft;
	std::vector<int> std;
	ft.push_back(1);
	ft.push_back(2);
	ft.push_back(3);
	std.push_back(1);
	std.push_back(2);
	std.push_back(3);
	ft::vector<int> ft2(ft);
	std::vector<int> std2(std);
	ft.push_back(42);
	std.push_back(42);
	check("ft == std", (ft == std));
	check("ft2 == std2", (ft2 == std2));
	check("ft != ft2", (ft != ft2));
	check("std != std2", (std != std2));
}

static void max_size(void)
{
	print_header("Max size");
	ft::vector<std::string> ft;
	std::vector<std::string> std;
	check("ft.max_size() == std.max_size()", ft.max_size(), std.max_size());
	ft.push_back("test");
	std.push_back("test");
	check("ft.max_size() == std.max_size()", ft.max_size(), std.max_size());
}

static void resize(void)
{
	print_header("Resize");
	ft::vector<std::string> ft;
	std::vector<std::string> std;
	ft.resize(10, "test");
	std.resize(10, "test");
	check("ft == std", (ft == std));
	ft.resize(2, "42");
	std.resize(2, "42");
	check("ft == std", (ft == std));
}

static void reserve(void)
{
	print_header("Reserve");
	ft::vector<std::string> ft;
	std::vector<std::string> std;
	ft.reserve(10);
	std.reserve(10);
	check("ft == std", (ft == std));
	ft.reserve(123213);
	std.reserve(123213);
	check("ft == std", (ft == std));
}

static void access_operator(void)
{
	print_header("[] operator, at()");
	ft::vector<int> ft;
	std::vector<int> std;
	ft.push_back(1);
	ft.push_back(2);
	ft.push_back(3);
	std.push_back(1);
	std.push_back(2);
	std.push_back(3);
	check("ft[0] == std[0]", ft[0], std[0]);
	check("ft[1] == std[1]", ft[1], std[1]);
	check("ft[2] == std[2]", ft[2], std[2]);
	try
	{
		std::cout << "ft.at(100): " << ft.at(100) << ": " << FAIL << std::endl;
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << ": " << std::string(7, ' ') << BOLD << GREEN << GOOD << RESET << std::endl;
	}
	try
	{
		std::cout << "std.at(100): " << std.at(100) << ": " << FAIL  << std::endl;
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << ": " << std::string(20, ' ') << BOLD << GREEN << GOOD << RESET << std::endl;
	}
	try
	{
		std::cout << "ft.at(-1): " << ft.at(-1) << ": " << FAIL  << std::endl;
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << ": " << std::string(8, ' ') << BOLD << GREEN << GOOD << RESET << std::endl;
	}
	try
	{
		std::cout << "std.at(-1): " << std.at(-1) << ": " << FAIL  << std::endl;
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << ": " << std::string(21, ' ') << BOLD << GREEN << GOOD << RESET << std::endl;
	}
}

static void front_back(void)
{
	print_header("Front / Back");
	ft::vector<int> ft;
	std::vector<int> std;
	ft.push_back(1);
	ft.push_back(2);
	ft.push_back(3);
	std.push_back(1);
	std.push_back(2);
	std.push_back(3);
	check("ft.front() == std.front()", ft.front(), std.front());
	check("ft.back() == std.back()", ft.front(), std.front());
}

static void insert(void)
{
	print_header("Insert");
	int test[] = {1, 2, 3};
	ft::vector<int> ft;
	std::vector<int> std;
	ft.insert(ft.begin(), 42);
	std.insert(std.begin(), 42);
	check("ft == std", ft == std);
	ft.insert(ft.end(), 21);
	std.insert(std.end(), 21);
	check("ft == std", ft == std);
	ft.insert(ft.begin(), 10);
	std.insert(std.begin(), 10);
	check("ft == std", ft == std);
	ft.insert(ft.begin() + 1, 11);
	std.insert(std.begin() + 1, 11);
	check("ft == std", ft == std);
	ft.insert(ft.begin() + 2, (size_t)3, 0);
	std.insert(std.begin() + 2, (size_t)3, 0);
	check("ft == std", ft == std);
	ft.insert(ft.begin() + 1, test, test + 3);
	std.insert(std.begin() + 1, test, test + 3);
	check("ft == std", ft == std);
}

static void assign(void)
{
	print_header("Assign");
	std::string test[] = {"Hey", "what's", "up", "?"};
	ft::vector<std::string> ft;
	std::vector<std::string> std;
	ft.assign(test, test + 4);
	std.assign(test, test + 4);
	check("ft == std", ft == std);
	ft.assign(10, "?");
	std.assign(10, "?");
	check("ft == std", ft == std);
}


static void erase(void)
{
	print_header("Erase / Clear");
	std::string test[] = {"Hey", "what's", "up", "?"};
	ft::vector<std::string> ft;
	std::vector<std::string> std;
	ft.assign(test, test + 4);
	std.assign(test, test + 4);
	check("ft == std", ft == std);
	ft.erase(ft.begin() + 2);
	std.erase(std.begin() + 2);
	check("ft == std", ft == std);
	ft.clear();
	std.clear();
	check("ft == std", ft == std);
}

static void swap(void)
{
	print_header("Swap");
	ft::vector<int> ft;
	std::vector<int> std;
	ft::vector<int> ft2;
	std::vector<int> std2;
	ft.push_back(1);
	ft.push_back(2);
	ft.push_back(3);
	std.push_back(1);
	std.push_back(2);
	std.push_back(3);
	ft2.push_back(42);
	ft2.push_back(43);
	std2.push_back(42);
	std2.push_back(43);
	ft.swap(ft2);
	std.swap(std2);
	check("ft == std", ft == std);
	check("ft2 == std2", ft2 == std2);
}

static void operators(void)
{
	print_header("Operators");
	ft::vector<int> ft;
	std::vector<int> std;
	ft::vector<int> ft2;
	std::vector<int> std2;
	ft.push_back(1);
	ft.push_back(2);
	ft.push_back(3);
	std.push_back(1);
	std.push_back(2);
	std.push_back(3);
	ft2 = ft;
	std2 = std;
	check("ft == std", (ft == ft2), (std == std2));
	check("ft != std", (ft != ft2), (std != std2));
	check("ft > std", (ft > ft2), (std > std2));
	check("ft < std", (ft < ft2), (std < std2));
	check("ft >= std", (ft >= ft2), (std >= std2));
	check("ft <= std", (ft <= ft2), (std <= std2));
	ft.push_back(42);
	std.push_back(42);
	check("ft == std", (ft == ft2), (std == std2));
	check("ft != std", (ft != ft2), (std != std2));
	check("ft > std", (ft > ft2), (std > std2));
	check("ft < std", (ft < ft2), (std < std2));
	check("ft >= std", (ft >= ft2), (std >= std2));
	check("ft <= std", (ft <= ft2), (std <= std2));
	ft2.push_back(43);
	std2.push_back(43);
	check("ft == std", (ft == ft2), (std == std2));
	check("ft != std", (ft != ft2), (std != std2));
	check("ft > std", (ft > ft2), (std > std2));
	check("ft < std", (ft < ft2), (std < std2));
	check("ft >= std", (ft >= ft2), (std >= std2));
	check("ft <= std", (ft <= ft2), (std <= std2));
}

void	test_vector(void)
{

	// default_constructor();
	// copy_constructor();
	// max_size();
	// resize();
	// reserve();
	// access_operator();
	// front_back();
	// insert();
	// assign();
	// erase();
	// swap();
	// operators();
	long count = 1;

	// test_vector_empty_constructor(count);
 	// test_vector_param_constructor(count);
	// test_vector_two_param_ctor(count);
	// test_vector_size_capacity_empty(count);
	// test_vector_size_capacity_random(count);
 	// test_vector_reserve(count);
 	// test_vector_resize(count);
 	// test_vector_push_back(count);
 	// test_vector_pop_back(count);
 	// test_vector_erase_pos(count);
 	// test_vector_erase_iter(count);
 	// test_vector_clear(count);
 	// test_vector_reverse_iter(count);
 	// test_vector_swap(count);
 	// test_vector_insert_pos(count);
 	// test_vector_insert_pos_num(count);
 	// test_vector_insert_iter(count);
 	// test_vector_comparison(count);
 	// test_vector_assign_n(count);
 	// test_vector_assign_range(count);
 	// test_vector_assignment(count);
 	// test_vector_copy_ctor(count);
 	test_vector_copy_range_ctor(count); // MAKES SOME ERRORS IN VALGRIND
 	// test_vector_access(count);

	// print_header("Time Performance");

}

