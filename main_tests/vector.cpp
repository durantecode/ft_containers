/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 18:41:53 by ldurante          #+#    #+#             */
/*   Updated: 2022/10/28 21:52:58 by ldurante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.hpp"

long count = 50;

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
	print_header("EMPTY CONSTRUCTOR TEST", 0);

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

	test_vector_time_empty_constructor(count);
}

static void test_vector_param_constructor(void)
{
	print_header("ONE PARAM CONSTRUCTION TEST ", 0);

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

	test_vector_time_param_constructor(count);
}

static void test_vector_two_param_constructor(void)
{
	print_header("TWO PARAM CONSTRUCTION TEST ", 0);

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

	test_vector_time_two_param_constructor(count);
}

static void test_vector_copy_constructor(void)
{
	print_header("COPY CONSTRUCTOR TEST ", 0);

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

	test_vector_time_copy_constructor(count);
}

static void test_vector_copy_range_constructor(void)
{
	print_header("COPY RANGE CONSTRUCTOR TEST ", 0);

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

	test_vector_time_copy_range_constructor(count);
}

static void test_vector_size_capacity_empty(void)
{
	print_header("SIZE, CAPACITY, EMPTY TEST", 0);

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

	test_vector_time_size_capacity_empty(count);
}

static void test_vector_size_capacity_empty_random(void)
{
	print_header("SIZE, CAPACITY, EMPTY RANDOM TEST ", 0);

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

	test_vector_time_size_capacity_random(count);
}

static void test_vector_access(void)
{
	print_header("ACCESS - [] operator, at() TEST ", 0);
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
	test_vector_time_access(count);
}

static void test_vector_resize(void)
{
	print_header("RESIZE TEST ", 0);

	ft::vector<std::string> ft;
	std::vector<std::string> std;
	ft.resize(10, "test");
	std.resize(10, "test");
	check("ft == std", (ft == std));
	ft.resize(2, "42");
	std.resize(2, "42");
	check("ft == std", (ft == std));

	test_vector_time_resize(count);
}

static void test_vector_reserve(void)
{
	print_header("RESERVE TEST", 0);

	ft::vector<std::string> ft;
	std::vector<std::string> std;
	ft.reserve(10);
	std.reserve(10);
	check("ft == std", (ft == std));
	ft.reserve(123213);
	std.reserve(123213);
	check("ft == std", (ft == std));

	test_vector_time_reserve(count);
}

static void test_vector_push_back(void)
{
	print_header("PUSH BACK TEST", 0);

	ft::vector<int> ft;
	std::vector<int> std;
	ft.push_back(1);
	ft.push_back(2);
	ft.push_back(42);
	std.push_back(1);
	std.push_back(2);
	std.push_back(42);
	check("ft == std", ft == std);

	test_vector_time_push_back(count);
}

static void test_vector_pop_back(void)
{
	print_header("POP BACK TEST ", 0);

    const int M = std::numeric_limits<int>::max();
	
    std::vector<int> std(count, M);
	ft::vector<int> ft(count, M);
	for (int i = 0; i < count; ++i)
		std.pop_back();
	for (int i = 0; i < count; ++i)
		ft.pop_back();
	check("ft == std", ft == std);

	test_vector_time_pop_back(count);
}

static void test_vector_erase_position(void)
{
	print_header("ERASE POSITION TEST ", 0);
	
	std::string test[] = {"Hey", "what's", "up", "?"};
	ft::vector<std::string> ft;
	std::vector<std::string> std;
	ft.assign(test, test + 4);
	std.assign(test, test + 4);
	check("ft == std", ft == std);
	ft.erase(ft.begin() + 2);
	std.erase(std.begin() + 2);
	check("ft == std", ft == std);

	test_vector_time_erase_position(count);
}

static void test_vector_erase_iter(void)
{
	print_header("ERASE ITER TEST ", 0);
	
    const int M = std::numeric_limits<int>::max();
    std::vector<int> std(count, M);
	ft::vector<int> ft(count, M);
	for (int i = 0; i < count; ++i)
		std.erase(std.begin(), std.begin() + 1);
	for (int i = 0; i < count; ++i)
		ft.erase(ft.begin(), ft.begin() + 1);
	check("ft == std", ft == std);

	test_vector_time_erase_iter(count);
}

static void test_vector_clear(void)
{
	print_header("CLEAR TEST", 0);
	
	std::string test[] = {"Hey", "what's", "up", "?"};
	ft::vector<std::string> ft;
	std::vector<std::string> std;
	ft.assign(test, test + 4);
	std.assign(test, test + 4);
	check("ft == std", ft == std);
	ft.clear();
	std.clear();
	check("ft == std", ft == std);

	test_vector_time_clear(count);
}


static void test_vector_insert_position(void)
{
	print_header("INSERT POSITION TEST", 0);

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

	test_vector_time_insert_position(count);
}

static void test_vector_insert_position_value(void)
{
	print_header("INSERT POSITION VALUE TEST", 0);
	
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

	test_vector_time_insert_pos_value(count);
}

static void test_vector_insert_iter(void)
{
	print_header("INSERT ITER TEST", 0);

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

	test_vector_time_insert_iter(count);
}

static void test_vector_assign(void)
{
	print_header("ASSIGNMENT OP TEST", 0);

	std::string test[] = {"Hey", "what's", "up", "?"};
	ft::vector<std::string> ft;
	std::vector<std::string> std;
	ft.assign(test, test + 4);
	std.assign(test, test + 4);
	check("ft == std", ft == std);
	ft.assign(10, "?");
	std.assign(10, "?");
	check("ft == std", ft == std);

	test_vector_time_assign(count);
}

static void test_vector_assign_range(void)
{
	print_header("ASSIGN RANGE TEST ", 0);
	std::string test[] = {"Hey", "what's", "up", "?"};
	ft::vector<std::string> ft;
	std::vector<std::string> std;
	ft.assign(test, test + 4);
	std.assign(test, test + 4);
	check("ft == std", ft == std);
	ft.assign(10, "?");
	std.assign(10, "?");
	check("ft == std", ft == std);

	test_vector_time_assign_range(count);
}

static void test_vector_assign_value(void)
{
	print_header("ASSIGN VALUE TEST ", 0);
	std::string test[] = {"Hey", "what's", "up", "?"};
	ft::vector<std::string> ft;
	std::vector<std::string> std;
	ft.assign(test, test + 4);
	std.assign(test, test + 4);
	check("ft == std", ft == std);
	ft.assign(10, "?");
	std.assign(10, "?");
	check("ft == std", ft == std);

	test_vector_time_assign_value(count);
}

static void test_vector_reverse_iterator(void)
{
	print_header("REVERSE ITERATOR TEST ", 0);

	test_vector_time_reverse_iter(count);
}

static void test_vector_swap(void)
{
	print_header("SWAP TEST ", 0);

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

	test_vector_time_swap(count);
}

static void test_vector_comparison(void)
{
	print_header("COMPARISON OP TEST", 0);

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

	test_vector_time_comparison(count);
}

// static void front_back(void)
// {
// 	print_header("Front / Back", 0);
// 	ft::vector<int> ft;
// 	std::vector<int> std;
// 	ft.push_back(1);
// 	ft.push_back(2);
// 	ft.push_back(3);
// 	std.push_back(1);
// 	std.push_back(2);
// 	std.push_back(3);
// 	check("ft.front() == std.front()", ft.front(), std.front());
// 	check("ft.back() == std.back()", ft.front(), std.front());
// }

void	test_vector(void)
{
	print_header("VECTOR TESTS", 1);

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

}

