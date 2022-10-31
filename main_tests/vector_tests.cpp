/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_tests.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 18:41:53 by ldurante          #+#    #+#             */
/*   Updated: 2022/10/31 16:57:38 by ldurante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.hpp"

/* PRINT VECTOR */

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

static void test_vector_empty_constructor(void)
{
	test_name = "EMPTY CONSTRUCTOR TEST";
	err_count = 0;
	names.push_back(test_name);

	if (verbose)
		print_header(test_name, 0);

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

	test_vector_time_empty_constructor();
}

static void test_vector_param_constructor(void)
{
	test_name = "ONE PARAM CONSTRUCTION TEST ";
	err_count = 0;
	names.push_back(test_name);

	if (verbose)
		print_header(test_name, 0);

    const size_t N = 42;

	ft::vector<int> ft(N);
	std::vector<int> std(N);
	check("ft == std", ft == std);
	ft.push_back(1);
	ft.push_back(2);
	ft.push_back(3);
	std.push_back(1);
	std.push_back(2);
	std.push_back(3);
	check("ft == std", ft == std);
	int std_res = *(ft.begin() + 50 % N);
	int ft_res = *(std.begin() + 50 % N);
	check("ft == std", ft == std);

	test_vector_time_param_constructor();
}

static void test_vector_two_param_constructor(void)
{
	test_name = "TWO PARAM CONSTRUCTION TEST ";
	err_count = 0;
	names.push_back(test_name);

	if (verbose)
		print_header(test_name, 0);

    const size_t N = 42;
    const int M = 99;

	ft::vector<int> ft(N, M);
	std::vector<int> std(N, M);
	check("ft == std", ft == std);
	ft.push_back(1);
	ft.push_back(2);
	ft.push_back(3);
	std.push_back(1);
	std.push_back(2);
	std.push_back(3);
	check("ft == std", ft == std);
	int std_res = *(ft.begin() + M % N);
	int ft_res = *(std.begin() + M % N);
	check("ft == std", ft == std);

	test_vector_time_two_param_constructor();
}

static void test_vector_copy_constructor(void)
{
	test_name = "COPY CONSTRUCTOR TEST ";
	err_count = 0;
	names.push_back(test_name);

	if (verbose)
		print_header(test_name, 0);

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

	test_vector_time_copy_constructor();
}

static void test_vector_copy_range_constructor(void)
{
	test_name = "COPY RANGE CONSTRUCTOR TEST ";
	err_count = 0;
	names.push_back(test_name);

	if (verbose)
		print_header(test_name, 0);

	const size_t N = 42;
    const int M = std::numeric_limits<int>::max();
    
	std::vector<int> std(N * N, M);
	for (int i = 0; i < count; ++i)
	    std::vector<int> std_r(std.begin(), std.end());
	
	ft::vector<int> ft(N * N, M);
	for (int i = 0; i < count; ++i)
		ft::vector<int> ft_r(ft.begin(), ft.end());
	check("ft == std", (ft == std));
	ft.push_back(42);
	std.push_back(42);
	check("ft == std", (ft == std));

	test_vector_time_copy_range_constructor();
}

static void test_vector_size_capacity_empty(void)
{
	test_name = "SIZE, CAPACITY, EMPTY TEST";
	err_count = 0;
	names.push_back(test_name);

	if (verbose)
		print_header(test_name, 0);

	ft::vector<std::string> ft;
	std::vector<std::string> std;
	check("ft.size() == std.size()", ft.size(), std.size());
	check("ft.max_size() == std.max_size()", ft.max_size(), std.max_size());
	check("ft.capacity() == std.capacity()", ft.capacity(), std.capacity());
	check("ft.empty() == std.empty()", ft.empty(), std.empty());
	ft.push_back("test");
	std.push_back("test");
	check("ft.size() == std.size()", ft.size(), std.size());
	check("ft.max_size() == std.max_size()", ft.max_size(), std.max_size());
	check("ft.capacity() == std.capacity()", ft.capacity(), std.capacity());
	check("ft.empty() == std.empty()", ft.empty(), std.empty());

	test_vector_time_size_capacity_empty();
}

static void test_vector_size_capacity_empty_random(void)
{
	test_name = "SIZE, CAPACITY, EMPTY RANDOM TEST ";
	err_count = 0;
	names.push_back(test_name);

	if (verbose)
		print_header(test_name, 0);

	ft::vector<std::string> ft;
	std::vector<std::string> std;
	check("ft.size() == std.size()", ft.size(), std.size());
	check("ft.max_size() == std.max_size()", ft.max_size(), std.max_size());
	check("ft.capacity() == std.capacity()", ft.capacity(), std.capacity());
	check("ft.empty() == std.empty()", ft.empty(), std.empty());
	ft.push_back("test");
	std.push_back("test");
	check("ft.size() == std.size()", ft.size(), std.size());
	check("ft.max_size() == std.max_size()", ft.max_size(), std.max_size());
	check("ft.capacity() == std.capacity()", ft.capacity(), std.capacity());
	check("ft.empty() == std.empty()", ft.empty(), std.empty());

	test_vector_time_size_capacity_random();
}

static void test_vector_access(void)
{
	test_name = "ACCESS - [] operator, at() TEST ";
	err_count = 0;
	names.push_back(test_name);

	if (verbose)
		print_header(test_name, 0);
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
	if (verbose)
	{
		try
		{
			std::cout << MAGENTA << "*         " << RESET;
			std::cout << "ft.at(100): " << ft.at(100) << ": " << FAIL << std::endl;
		}
		catch (std::exception &e)
		{
			std::cout << e.what() << ": " << GREEN << GOOD << MAGENTA << "          *" << RESET << std::endl;
		}
		try
		{
			std::cout << MAGENTA << "*         " << RESET;
			std::cout << "std.at(100): " << std.at(100) << ": " << FAIL  << std::endl;
		}
		catch (std::exception &e)
		{
			std::cout << e.what() << ": " << GREEN << GOOD << MAGENTA << "         *" << RESET << std::endl;
		}
		try
		{
			std::cout << MAGENTA << "*         " << RESET;
			std::cout << "ft.at(-1): " << ft.at(-1) << ": " << FAIL  << std::endl;
		}
		catch (std::exception &e)
		{
			std::cout << e.what() << ": " << GREEN << GOOD << MAGENTA << "           *" << RESET << std::endl;
		}
		try
		{
			std::cout << MAGENTA << "*         " << RESET;
			std::cout << "std.at(-1): " << std.at(-1) << ": " << FAIL  << std::endl;
		}
		catch (std::exception &e)
		{
			std::cout << e.what() << ": " << GREEN << GOOD << MAGENTA << "          *" << RESET << std::endl;
		}
	}
	
	test_vector_time_access();
}

static void test_vector_resize(void)
{
	test_name = "RESIZE TEST ";
	err_count = 0;
	names.push_back(test_name);

	if (verbose)
		print_header(test_name, 0);

	ft::vector<std::string> ft;
	std::vector<std::string> std;
	ft.resize(10, "test");
	std.resize(10, "test");
	check("ft == std", (ft == std));
	ft.resize(2, "42");
	std.resize(2, "42");
	check("ft == std", (ft == std));

	test_vector_time_resize();
}

static void test_vector_reserve(void)
{
	test_name = "RESERVE TEST";
	err_count = 0;
	names.push_back(test_name);

	if (verbose)
		print_header(test_name, 0);

	ft::vector<std::string> ft;
	std::vector<std::string> std;
	ft.reserve(10);
	std.reserve(10);
	check("ft == std", (ft == std));
	ft.reserve(123213);
	std.reserve(123213);
	check("ft == std", (ft == std));

	test_vector_time_reserve();
}

static void test_vector_push_back(void)
{
	test_name = "PUSH BACK TEST";
	err_count = 0;
	names.push_back(test_name);

	if (verbose)
		print_header(test_name, 0);

	ft::vector<int> ft;
	std::vector<int> std;
	ft.push_back(1);
	ft.push_back(2);
	ft.push_back(42);
	std.push_back(1);
	std.push_back(2);
	std.push_back(42);
	check("ft == std", ft == std);

	test_vector_time_push_back();
}

static void test_vector_pop_back(void)
{
	test_name = "POP BACK TEST ";
	err_count = 0;
	names.push_back(test_name);

	if (verbose)
		print_header(test_name, 0);

    const int M = std::numeric_limits<int>::max();
	
    std::vector<int> std(count, M);
	ft::vector<int> ft(count, M);
	for (int i = 0; i < count; ++i)
		std.pop_back();
	for (int i = 0; i < count; ++i)
		ft.pop_back();
	check("ft == std", ft == std);

	test_vector_time_pop_back();
}

static void test_vector_erase_position(void)
{
	test_name = "ERASE POSITION TEST ";
	err_count = 0;
	names.push_back(test_name);

	if (verbose)
		print_header(test_name, 0);
	
	std::string test[] = {"Hey", "what's", "up", "?"};
	ft::vector<std::string> ft;
	std::vector<std::string> std;
	ft.assign(test, test + 4);
	std.assign(test, test + 4);
	check("ft == std", ft == std);
	ft.erase(ft.begin() + 2);
	std.erase(std.begin() + 2);
	check("ft == std", ft == std);

	test_vector_time_erase_position();
}

static void test_vector_erase_iter(void)
{
	test_name = "ERASE ITER TEST ";
	err_count = 0;
	names.push_back(test_name);

	if (verbose)
		print_header(test_name, 0);
	
    const int M = std::numeric_limits<int>::max();
    std::vector<int> std(count, M);
	ft::vector<int> ft(count, M);
	for (int i = 0; i < count; ++i)
		std.erase(std.begin(), std.begin() + 1);
	for (int i = 0; i < count; ++i)
		ft.erase(ft.begin(), ft.begin() + 1);
	check("ft == std", ft == std);

	test_vector_time_erase_iter();
}

static void test_vector_clear(void)
{
	test_name = "CLEAR TEST";
	err_count = 0;
	names.push_back(test_name);

	if (verbose)
		print_header(test_name, 0);
	
	std::string test[] = {"Hey", "what's", "up", "?"};
	ft::vector<std::string> ft;
	std::vector<std::string> std;
	ft.assign(test, test + 4);
	std.assign(test, test + 4);
	check("ft == std", ft == std);
	ft.clear();
	std.clear();
	check("ft == std", ft == std);

	test_vector_time_clear();
}


static void test_vector_insert_position(void)
{
	test_name = "INSERT POSITION TEST";
	err_count = 0;
	names.push_back(test_name);

	if (verbose)
		print_header(test_name, 0);

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

	test_vector_time_insert_position();
}

static void test_vector_insert_position_value(void)
{
	test_name = "INSERT POSITION VALUE TEST";
	err_count = 0;
	names.push_back(test_name);

	if (verbose)
		print_header(test_name, 0);
	
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

	test_vector_time_insert_pos_value();
}

static void test_vector_insert_iter(void)
{
	test_name = "INSERT ITER TEST";
	err_count = 0;
	names.push_back(test_name);

	if (verbose)
		print_header(test_name, 0);

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

	test_vector_time_insert_iter();
}

static void test_vector_assign(void)
{
	test_name = "ASSIGNMENT OP TEST";
	err_count = 0;
	names.push_back(test_name);

	if (verbose)
		print_header(test_name, 0);

	std::string test[] = {"Hey", "what's", "up", "?"};
	ft::vector<std::string> ft;
	std::vector<std::string> std;
	ft.assign(test, test + 4);
	std.assign(test, test + 4);
	check("ft == std", ft == std);
	ft.assign(10, "?");
	std.assign(10, "?");
	check("ft == std", ft == std);

	test_vector_time_assign();
}

static void test_vector_assign_range(void)
{
	test_name = "ASSIGN RANGE TEST ";
	err_count = 0;
	names.push_back(test_name);

	if (verbose)
		print_header(test_name, 0);
	std::string test[] = {"Hey", "what's", "up", "?"};
	ft::vector<std::string> ft;
	std::vector<std::string> std;
	ft.assign(test, test + 4);
	std.assign(test, test + 4);
	check("ft == std", ft == std);
	ft.assign(10, "?");
	std.assign(10, "?");
	check("ft == std", ft == std);

	test_vector_time_assign_range();
}

static void test_vector_assign_value(void)
{
	test_name = "ASSIGN VALUE TEST ";
	err_count = 0;
	names.push_back(test_name);

	if (verbose)
		print_header(test_name, 0);
	std::string test[] = {"Hey", "what's", "up", "?"};
	ft::vector<std::string> ft;
	std::vector<std::string> std;
	ft.assign(test, test + 4);
	std.assign(test, test + 4);
	check("ft == std", ft == std);
	ft.assign(10, "?");
	std.assign(10, "?");
	check("ft == std", ft == std);

	test_vector_time_assign_value();
}

static void test_vector_reverse_iterator(void)
{
	test_name = "REVERSE ITERATOR TEST ";
	err_count = 0;
	names.push_back(test_name);

	if (verbose)
		print_header(test_name, 0);

	test_vector_time_reverse_iter();
}

static void test_vector_swap(void)
{
	test_name = "SWAP TEST ";
	err_count = 0;
	names.push_back(test_name);

	if (verbose)
		print_header(test_name, 0);

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

	test_vector_time_swap();
}

static void test_vector_comparison(void)
{
	test_name = "COMPARISON OP TEST";
	err_count = 0;
	names.push_back(test_name);

	if (verbose)
		print_header(test_name, 0);

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
	check("ft >  std", (ft > ft2), (std > std2));
	check("ft <  std", (ft < ft2), (std < std2));
	check("ft >= std", (ft >= ft2), (std >= std2));
	check("ft <= std", (ft <= ft2), (std <= std2));
	ft.push_back(42);
	std.push_back(42);
	check("ft == std", (ft == ft2), (std == std2));
	check("ft != std", (ft != ft2), (std != std2));
	check("ft >  std", (ft > ft2), (std > std2));
	check("ft <  std", (ft < ft2), (std < std2));
	check("ft >= std", (ft >= ft2), (std >= std2));
	check("ft <= std", (ft <= ft2), (std <= std2));
	ft2.push_back(43);
	std2.push_back(43);
	check("ft == std", (ft == ft2), (std == std2));
	check("ft != std", (ft != ft2), (std != std2));
	check("ft >  std", (ft > ft2), (std > std2));
	check("ft <  std", (ft < ft2), (std < std2));
	check("ft >= std", (ft >= ft2), (std >= std2));
	check("ft <= std", (ft <= ft2), (std <= std2));

	test_vector_time_comparison();
}

void	test_vector(void)
{
	print_header("VECTOR TESTS", 1);
	
	test_name.clear();
	names.clear();
	errors.clear();
	time_perf.clear();

	test_vector_empty_constructor();
	test_vector_param_constructor();
	test_vector_two_param_constructor();
	test_vector_copy_constructor();
	test_vector_copy_range_constructor();
	test_vector_size_capacity_empty();
	test_vector_size_capacity_empty_random();
	test_vector_access();
	test_vector_resize();
	test_vector_reserve();
	test_vector_push_back();
	test_vector_pop_back();
	test_vector_erase_position();
	test_vector_erase_iter();
	test_vector_clear();
	test_vector_insert_position();
	test_vector_insert_position_value();
	test_vector_insert_iter();
	test_vector_assign();
	test_vector_assign_range();
	test_vector_assign_value();
	test_vector_reverse_iterator();
	test_vector_swap();
	test_vector_comparison();

	print_test_results();
}

