/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_tests.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 19:02:51 by ldurante          #+#    #+#             */
/*   Updated: 2022/12/07 21:10:40 by ldurante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.hpp"
#include <map>
#include <utility>

template <class T>
static void print_map(T &map)
{
	typename T::iterator it = map.begin();
	std::cout << " --- Map of size " << map.size() << " ---" << std::endl;
	while (it != map.end())
	{
		std::cout << it->first << ": " << it->second << std::endl;
		++it;
	}
	std::cout << " --- " << std::endl;
}

static void test_map_constructors(void)
{
	//empty
	test_name = "EMPTY CONSTRUCTOR TEST";
	err_count = 0;
	names.push_back(test_name);
	if (verbose)
		print_header(test_name, 0);

	std::pair<int, int> a[] = {std::make_pair(0, 1), std::make_pair(1, 0), std::make_pair(2, 1)};
	ft::pair<int, int> b[] = {ft::make_pair(0, 1), ft::make_pair(1, 0), ft::make_pair(2, 1)};
	ft::map<int, int> m1;
	std::map<int, int> m2;
	check("(default) m1 == m2 ", (m1 == m2));
	test_map_time_empty_constructor();

	//range
	test_name = "RANGE CONSTRUCTOR TEST";
	err_count = 0;
	names.push_back(test_name);
	if (verbose)
		print_header(test_name, 0);

	ft::map<int, int> m3(b, b + 3);
	std::map<int, int> m4(a, a + 3);
	check("(range) m3 == m4 ", (m3 == m4));
	test_map_time_range_constructor();

	//copy
	test_name = "COPY CONSTRUCTOR TEST ";
	err_count = 0;
	names.push_back(test_name);
	if (verbose)
		print_header(test_name, 0);

	ft::map<int, int> m5(m3);
	std::map<int, int> m6(m4);
	check("(copy) m5 == m6", (m5 == m6));
	ft::map<int, int> m7;
	std::map<int, int> m8;
	m7[0] = 1;
	m7[1] = 2;
	m7[2] = 3;
	m8[0] = 1;
	m8[1] = 2;
	m8[2] = 3;
	check("(copy) m7 == m8", (m7 == m8));
	ft::map<int, int> m9;
	std::map<int, int> m10;
	m9 = m7;
	m10 = m8;
	check("(copy) m9 == m10 ", (m9 == m10));

	test_map_time_copy_constructor();	
}

static void test_map_max_size(void)
{
	test_name = "SIZE/EMPTY TEST ";
	err_count = 0;
	names.push_back(test_name);

	if (verbose)
		print_header(test_name, 0);

	ft::map<int, int> m1;
	std::map<int, int> m2;
	check("m1.max_size() == m2.max_size() ", m1.max_size(), m2.max_size());
 	ft::map<std::string, int> m3;
	std::map<std::string, int> m4;
	check("m3.empty() == m4.empty() ", m3.empty(), m4.empty());
	for (size_t i = 0; i < 50; ++i)
	{
		std::string fill = createString();
		int  fill_n = 42 % 99;
		m3.insert(ft::make_pair(fill, fill_n));
		m4.insert(std::make_pair(fill, fill_n));
	}
	check("m3.empty() == m4.empty() ", m3.size(), m4.size());

	test_map_time_size_empty_max();
}

static void test_map_access(void)
{
	test_name = "ACCESS OP TEST";
	err_count = 0;
	names.push_back(test_name);

	if (verbose)
		print_header(test_name, 0);

	ft::map<std::string, int> m1;
	std::map<std::string, int> m2;
	m1["a"] = 1;
	m1["b"] = 0;
	m1["c"] = 42;
	m1["d"] = -5;
	m1["d"] = 11;
	m1["test"] = 100;
	m2["a"] = 1;
	m2["b"] = 0;
	m2["c"] = 42;
	m2["d"] = -5;
	m2["d"] = 11;
	m2["test"] = 100;
	check("m1 == m2 ", m1 == m2);
	check("m1['a'] == m2['a'] ", m1["a"], m2["a"]);
	check("m1['d'] == m2['d'] ", m1["d"], m2["d"]);
	check("m1['test'] == m2['test'] ", m1["test"], m2["test"]);
	check("m1['z'] == m2['z'] ", m1["z"], m2["z"]);

	test_map_time_assignment_op();

	//at
	test_name = "ACCESS AT TEST";
	err_count = 0;
	names.push_back(test_name);

	if (verbose)
		print_header(test_name, 0);

	check("m1 == m2 ", m1 == m2);
	check("m1['a'] == m2['a'] ", m1["a"], m2["a"]);
	check("m1['d'] == m2['d'] ", m1["d"], m2["d"]);
	check("m1['test'] == m2['test'] ", m1["test"], m2["test"]);
	check("m1['z'] == m2['z'] ", m1["z"], m2["z"]);

	test_map_time_operator_at();
}

static void test_map_insert(void)
{
	//insert val
	test_name = "INSERT VAL TEST ";
	err_count = 0;
	names.push_back(test_name);

	if (verbose)
		print_header(test_name, 0);

	std::pair<int, int> a[] = {std::make_pair(0, 1), std::make_pair(1, 0), std::make_pair(2, 1)};
	ft::pair<int, int> b[] = {ft::make_pair(0, 1), ft::make_pair(1, 0), ft::make_pair(2, 1)};
	ft::map<int, int> m1(b, b + 3);
	std::map<int, int> m2(a, a + 3);
	check("m1 == m2 ", m1 == m2);
	m1.insert(ft::make_pair(5, 0));
	m2.insert(std::make_pair(5, 0));
	m1.insert(ft::make_pair(10, 54));
	m2.insert(std::make_pair(10, 54));
	check("m1 == m2 ", m1 == m2);

	test_map_time_insert_val();

	//insert pos, val
	test_name = "INSERT POS, VAL TEST";
	err_count = 0;
	names.push_back(test_name);

	if (verbose)
		print_header(test_name, 0);

	m1.insert(++m1.begin(), ft::make_pair(5, 5));
	m2.insert(++m2.begin(), std::make_pair(5, 5));
	check("m1 == m2 ", m1 == m2);

	test_map_time_insert_val();

	//insert range
	test_name = "INSERT RANGE TEST ";
	err_count = 0;
	names.push_back(test_name);
	
	if (verbose)
		print_header(test_name, 0);

	ft::map<int, int> m3(b, b + 3);
	std::map<int, int> m4(a, a + 3);
	ft::map<int, int> m5;
	std::map<int, int> m6;
	m3.insert(m3.begin(), ft::make_pair(5, 5));
	m4.insert(m4.begin(), std::make_pair(5, 5));
	check("m3 == m4 ", m3 == m4);
	m3.insert(ft::make_pair(5, 0));
	m4.insert(std::make_pair(5, 0));
	m3.insert(ft::make_pair(10, 54));
	m4.insert(std::make_pair(10, 54));
	m5.insert(m3.begin(), m3.end());
	m6.insert(m4.begin(), m4.end());
	check("m5 == m6 ", m3 == m4);

	test_map_time_insert_range();
}

static void test_map_erase(void)
{
	//erase val
	test_name = "ERASE VAL TEST";
	err_count = 0;
	names.push_back(test_name);
	
	if (verbose)
		print_header(test_name, 0);

	ft::map<std::string, int> m1;
	std::map<std::string, int> m2;
	m1["test"] = 1;
	m1["a"] = 2;
	m1["b"] = 3;
	m1["c"] = 4;
	m1["d"] = 6;
	m1["e"] = 8;
	m2["test"] = 1;
	m2["a"] = 2;
	m2["b"] = 3;
	m2["c"] = 4;
	m2["d"] = 6;
	m2["e"] = 8;
	check("m1 == m2 ", m1 == m2);
	m1.erase("a");
	m2.erase("a");
	check("m1 == m2 ", m1 == m2);
	
	test_map_time_erase_val();

	//erase pos
	test_name = "ERASE POS TEST";
	err_count = 0;
	names.push_back(test_name);	
	if (verbose)
		print_header(test_name, 0);
	
	m1.erase(++m1.begin());
	m2.erase(++m2.begin());
	check("m1 == m2 ", m1 == m2);
	
	test_map_time_erase_pos();
	
	//erase range
	test_name = "ERASE RANGE TEST";
	err_count = 0;
	names.push_back(test_name);
	if (verbose)
		print_header(test_name, 0);
	
	m1.erase(++m1.begin(), --m1.end());
	m2.erase(++m2.begin(), --m2.end());
	check("m1 == m2 ", m1 == m2);

	test_map_time_erase_range();
}

static void test_map_swap(void)
{
	test_name = "SWAP TEST ";
	err_count = 0;
	names.push_back(test_name);
	
	if (verbose)
		print_header(test_name, 0);

	ft::map<std::string, int> m1;
	std::map<std::string, int> m2;
	ft::map<std::string, int> m3;
	std::map<std::string, int> m4;
	m1["a"] = 1;
	m1["b"] = 2;
	m1["c"] = 3;
	m2["a"] = 1;
	m2["b"] = 2;
	m2["c"] = 3;
	m3["a"] = 42;
	m3["b"] = 21;
	m4["a"] = 42;
	m4["b"] = 21;
	m1.swap(m3);
	m2.swap(m4);
	check("m1 == m2 ", m1 == m2);
	check("m3 == m4 ", m3 == m4);

	test_map_time_swap();
}

static void test_map_count(void)
{
	ft::map<std::string, int> m1;
	std::map<std::string, int> m2;
	m1["a"] = 1;
	m1["b"] = 42;
	m1["b"] = 21;
	m2["a"] = 1;
	m2["b"] = 42;
	m2["b"] = 21;
	check("m1.count('a') == m2.count('a') ", m1.count("a"), m2.count("a"));
	check("m1.count('b') == m2.count('b') ", m1.count("b"), m2.count("b"));
	check("m1.count('z') == m2.count('z') ", m1.count("z"), m2.count("z"));

	test_map_time_count_clear();
}

static void test_map_clear(void)
{
	test_name = "COUNT / CLEAR TEST";
	err_count = 0;
	names.push_back(test_name);
	
	if (verbose)
		print_header(test_name, 0);
	ft::map<std::string, int> m1;
	std::map<std::string, int> m2;

	m1["a"] = 1;
	m1["b"] = 42;
	m2["a"] = 1;
	m2["b"] = 42;
	m1.clear();
	m2.clear();
	check("m1 == m2 ", m1 == m2);

	test_map_count();
}

static void test_map_find(void)
{
	test_name = "FIND TEST ";
	err_count = 0;
	names.push_back(test_name);
	
	if (verbose)
		print_header(test_name, 0);

	ft::map<std::string, int> m1;
	std::map<std::string, int> m2;
	m1["a"] = 1;
	m1["b"] = 42;
	m2["a"] = 1;
	m2["b"] = 42;
	check("m1.find('a') == m2.find('a') ", m1.find("a")->second, m2.find("a")->second);
	check("m1.find('z') == m2.find('z') ", m1.find("a")->second, m2.find("a")->second);

	test_map_time_find();
}

static void test_map_bounds()
{
	test_name = "LOWER BOUND TEST";
	err_count = 0;
	names.push_back(test_name);
	
	if (verbose)
		print_header(test_name, 0);

	ft::map<std::string, int> m1;
	std::map<std::string, int> m2;
	m1["a"] = 1;
	m1["b"] = 42;
	m1["c"] = 42;
	m1["d"] = 42;
	m2["a"] = 1;
	m2["b"] = 42;
	m2["c"] = 42;
	m2["d"] = 42;
	check("m1.lower_bound() == m2.lower_bound() ", m1.lower_bound("a")->first, m2.lower_bound("a")->first);
	check("m1.lower_bound() == m2.lower_bound() ", m1.lower_bound("c")->first, m2.lower_bound("c")->first);
	test_map_time_lower_bound();
	
	test_name = "UPPER BOUND TEST";
	err_count = 0;
	names.push_back(test_name);
	if (verbose)
		print_header(test_name, 0);
	check("m1.upper_bound() == m2.upper_bound() ", m1.upper_bound("a")->first, m2.upper_bound("a")->first);
	check("m1.upper_bound() == m2.upper_bound() ", m1.upper_bound("c")->first, m2.upper_bound("c")->first);
	test_map_time_upper_bound();
}

static void test_map_range(void)
{
	test_name = "EQUAL RANGE TEST";
	err_count = 0;
	names.push_back(test_name);

	if (verbose)
		print_header(test_name, 0);

	ft::map<std::string, int> m1;
	std::map<std::string, int> m2;
	m1["a"] = 1;
	m1["b"] = 42;
	m1["c"] = 42;
	m1["d"] = 42;
	m2["a"] = 1;
	m2["b"] = 42;
	m2["c"] = 42;
	m2["d"] = 42;
	ft::pair<ft::map<std::string, int>::iterator, ft::map<std::string, int>::iterator> a = m1.equal_range("a");
	std::pair<std::map<std::string, int>::iterator, std::map<std::string, int>::iterator> b = m2.equal_range("a");
	check("a.first->first == b.first->first ", a.first->first, b.first->first);
	check("a.first->second == b.first->second ", a.first->second, b.first->second);
	check("a.second->first == b.second->first ", a.second->first, b.second->first);
	check("a.second->second == b.second->second ", a.second->second, b.second->second);

	test_map_time_equal_range();
}

static void test_map_iterators(void)
{
	test_name = "ITERATORS TEST";
	err_count = 0;
	names.push_back(test_name);

	if (verbose)
		print_header(test_name, 0);

	test_map_time_begin_end();
}

static void test_map_reverse_iterators(void)
{
	test_name = "REVERSE ITERATORS TEST";
	err_count = 0;
	names.push_back(test_name);

	if (verbose)
		print_header(test_name, 0);

	test_map_time_rbegin_rend();
}

static void test_map_comparision(void)
{
	test_name = "COMPARISION TEST";
	err_count = 0;
	names.push_back(test_name);
	
	if (verbose)
		print_header(test_name, 0);

	ft::map<std::string, int> m1;
	std::map<std::string, int> m2;
	m1["a"] = 1;
	m1["b"] = 42;
	m1["c"] = 42;
	m1["d"] = 42;
	m2["a"] = 1;
	m2["b"] = 42;
	m2["c"] = 42;
	m2["d"] = 42;
	ft::map<std::string, int> m3;
	std::map<std::string, int> m4;
	m3 = m1;
	m4 = m2;
	check("m1 == m2 ", (m1 == m3), (m2 == m4));
	check("m1 != m2 ", (m1 != m3), (m2 != m4));
	check("m1 > m2", (m1 > m3), (m2 > m4));
	check("m1 < m2", (m1 < m3), (m2 < m4));
	check("m1 >= m2 ", (m1 >= m3), (m2 >= m4));
	check("m1 <= m2 ", (m1 <= m3), (m2 <= m4));
	m1["e"] = 1;
	m2["e"] = 1;
	check("m1 == m2 ", (m1 == m3), (m2 == m4));
	check("m1 != m2 ", (m1 != m3), (m2 != m4));
	check("m1 > m2", (m1 > m3), (m2 > m4));
	check("m1 < m2", (m1 < m3), (m2 < m4));
	check("m1 >= m2 ", (m1 >= m3), (m2 >= m4));
	check("m1 <= m2 ", (m1 <= m3), (m2 <= m4));
	m3["e"] = 3;
	m4["e"] = 3;
	check("m1 == m2 ", (m1 == m3), (m2 == m4));
	check("m1 != m2 ", (m1 != m3), (m2 != m4));
	check("m1 > m2", (m1 > m3), (m2 > m4));
	check("m1 < m2", (m1 < m3), (m2 < m4));
	check("m1 >= m2 ", (m1 >= m3), (m2 >= m4));
	check("m1 <= m2 ", (m1 <= m3), (m2 <= m4));

	test_map_time_comparison();
}

void test_map(void)
{
	print_header("MAP TESTS", 1);

	test_name.clear();
	names.clear();
	errors.clear();
	time_perf.clear();
	
	test_map_constructors();
	test_map_max_size();
	test_map_access();
	test_map_insert();
	test_map_erase();
	test_map_swap();
	test_map_clear();
	test_map_find();
	test_map_bounds();
	test_map_iterators();
	test_map_reverse_iterators();
	test_map_range();
	test_map_comparision();

	print_test_results();
}
