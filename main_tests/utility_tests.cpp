/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility_tests.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 21:24:15 by ldurante          #+#    #+#             */
/*   Updated: 2022/11/04 17:12:52 by ldurante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.hpp"

/* templates needed only for utility tests */

template <class T>
typename std::enable_if<std::is_integral<T>::value, bool>::type
is_odd (T i) { return bool(i % 2); }

template <class T>
typename ft::enable_if<ft::is_integral<T>::value, bool>::type
is_odd_ft (T i) { return bool(i % 2); }

static bool ft_comp (const std::string& s1, const std::string& s2)
{
    return s1 < s2;
}

static bool ft_is_first_greater(int& x, int& y)
{
    return x > y;
}

void test_enableif_integral()
{
	test_name = "ENABLE_IF / IS INTEGRAL TEST";
	err_count = 0;
	names.push_back(test_name);

	if (verbose)
		print_header(test_name, 0);

	//std test
	timer_start();
	for (int i = 0; i < count; ++i)
		is_odd(i);
	double std_res = timer_stop();

	//ft test
	timer_start();
	for (int i = 0; i < count; ++i)
		is_odd_ft(i);
	double ft_res = timer_stop();

	// results
	if (verbose)
	{
		performance_result(std_res, ft_res);
		comparision_result(ft_res);
	}
	if (std_res != 0)
		time_perf.push_back(std_res / ft_res);
	else	
		time_perf.push_back(0);
	errors.push_back(err_count);
}

void test_equal_with_pred()
{
	test_name = "EQUAL TEST WITH PRED";
	err_count = 0;
	names.push_back(test_name);

	if (verbose)
		print_header(test_name, 0);

	//init
	std::vector<int> v1;
	v1.push_back(42);
	v1.push_back(21);
	v1.push_back(4);
	v1.push_back(10);
	v1.push_back(12);
	v1.push_back(55);
	v1.push_back(25);
	v1.push_back(21);
	v1.push_back(42);
	std::vector<int> v2(v1.begin(), v1.end());

	//output test
	timer_start();
	for (int i = 0; i < count / 10; ++i)
	{
		std::random_shuffle(v1.begin(), v1.end());
		std::random_shuffle(v2.begin(), v2.end());
		bool std_res = std::equal(v1.begin(), v1.end(),
                                  v2.begin(), ft_is_first_greater);
		bool ft_res = ft::equal(v1.begin(), v1.end(),
                                v2.begin(), ft_is_first_greater);
		if (std_res != ft_res)
			++err_count;
	}
	double comp_res = timer_stop();

	//std test
	timer_start();
	for (int i = 0; i < count; ++i)
	{
		std::equal(v1.begin(), v1.end(),
                   v2.begin(), ft_is_first_greater);
	}
	double std_res = timer_stop();
	
	//ft test 
	timer_start();
	for (int i = 0; i < count; ++i)
	{
		ft::equal(v1.begin(), v1.end(),
                  v2.begin(), ft_is_first_greater);
	}
	double ft_res = timer_stop();

	// results
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

void test_equal()
{
	test_name = "EQUAL TEST";
	err_count = 0;
	names.push_back(test_name);

	if (verbose)
		print_header(test_name, 0);

	//init
	std::vector<int> v1;
	v1.push_back(42);
	v1.push_back(21);
	v1.push_back(4);
	v1.push_back(10);
	v1.push_back(12);
	v1.push_back(55);
	v1.push_back(25);
	v1.push_back(21);
	v1.push_back(42);
	std::vector<int> v2 (v1.begin(), v1.end());

	//output test
	timer_start();
	for (int i = 0; i < count / 10; ++i)
	{
		std::random_shuffle(v1.begin(), v1.end());
		std::random_shuffle(v2.begin(), v2.end());
		bool std_res = std::equal(v1.begin(), v1.end(),
                                  v2.begin());
		bool ft_res = ft::equal(v1.begin(), v1.end(),
                                v2.begin());
		if (std_res != ft_res)
			++err_count;
	}
	double comp_res = timer_stop();

	//std test
	timer_start();
	for (int i = 0; i < count; ++i)
	{
		std::equal(v1.begin(), v1.end(),
                   v2.begin());
	}
	double std_res = timer_stop();
	
	//ft test 
	timer_start();
	for (int i = 0; i < count; ++i)
	{
		ft::equal(v1.begin(), v1.end(),
                  v2.begin());
	}
	double ft_res = timer_stop();

	// results
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

void test_lexicographical_compare()
{
	test_name = "LEXIOGRAPHICAL COMPARE TEST ";
	err_count = 0;
	names.push_back(test_name);

	if (verbose)
		print_header(test_name, 0);

	//init
	std::vector<char> v1;
	v1.push_back('a');
	v1.push_back('b');
	v1.push_back('c');
	v1.push_back('d');
	v1.push_back('e');
	v1.push_back('f');
	v1.push_back('g');
	v1.push_back('h');
	v1.push_back('i');
	std::vector<char> v2 (v1.begin(), v1.end());

	//output test
	timer_start();
	for (int i = 0; i < count / 10; ++i)
	{
		std::random_shuffle(v1.begin(), v1.end());
		std::random_shuffle(v2.begin(), v2.end());
		bool std_res = std::lexicographical_compare(v1.begin(), v1.end(),
                                    				v2.begin(), v2.end());
		bool ft_res = ft::lexicographical_compare(v1.begin(), v1.end(),
                                    			  v2.begin(), v2.end());
		if (std_res != ft_res)
			++err_count;
	}
	double comp_res = timer_stop();

	//std test
	timer_start();
	for (int i = 0; i < count; ++i)
	{
		std::lexicographical_compare(v1.begin(), v1.end(),
                                    v2.begin(), v2.end());
	}
	double std_res = timer_stop();
	
	//ft test 
	timer_start();
	for (int i = 0; i < count; ++i)
	{
		ft::lexicographical_compare(v1.begin(), v1.end(),
                                    v2.begin(), v2.end());
	}
	double ft_res = timer_stop();

	// results
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

void test_lexicographical_compare_with_cmp()
{
	test_name = "LEXIOGRAPHICAL COMPARE W/ COMP";
	err_count = 0;
	names.push_back(test_name);

	if (verbose)
		print_header(test_name, 0);

	//init
	std::vector<std::string> v1;
	v1.push_back("This");
	v1.push_back("Is");
	v1.push_back("A");
	v1.push_back("Bunch");
	v1.push_back("Of");
	v1.push_back("Test");
	v1.push_back("Strings");
	v1.push_back("To");
	v1.push_back("Compare");
	std::vector<std::string> v2 (v1.begin(), v1.end());

	//output test
	timer_start();
	for (int i = 0; i < count / 10; ++i)
	{
		std::random_shuffle(v1.begin(), v1.end());
		std::random_shuffle(v2.begin(), v2.end());
		bool std_res = std::lexicographical_compare(v1.begin(), v1.end(),
                                    				v2.begin(), v2.end(), ft_comp);
		bool ft_res = ft::lexicographical_compare(v1.begin(), v1.end(),
                                    			  v2.begin(), v2.end(), ft_comp);
		if (std_res != ft_res)
			++err_count;
	}
	double comp_res = timer_stop();

	//std test
	timer_start();
	for (int i = 0; i < count; ++i)
	{
		std::lexicographical_compare(v1.begin(), v1.end(),
                                    v2.begin(), v2.end(), ft_comp);
	}
	double std_res = timer_stop();
	
	//ft test 
	timer_start();
	for (int i = 0; i < count; ++i)
	{
		ft::lexicographical_compare(v1.begin(), v1.end(),
                                    v2.begin(), v2.end(), ft_comp);
	}
	double ft_res = timer_stop();

	// results
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

void test_pair_construction()
{
	test_name = "PAIR CONSTRUCTION TEST";
	err_count = 0;
	names.push_back(test_name);

	if (verbose)
		print_header(test_name, 0);

	//std test
	timer_start();
	for (int i = 0; i < count; ++i)
	{
		std::pair<int, int> p1(42, 42);
		std::pair<int, int> p2;
		p2 = p1;
	}
	double std_res = timer_stop();

	//ft test
	timer_start();
	for (int i = 0; i < count; ++i)
	{
		ft::pair<int, int> p1(42, 42);
		ft::pair<int, int> p2;
		p2 = p1;
	}
	double ft_res = timer_stop();

	// results
	if (verbose)
	{
		performance_result(std_res, ft_res);
		comparision_result(ft_res);
	}
	if (std_res != 0)
		time_perf.push_back(std_res / ft_res);
	else	
		time_perf.push_back(0);
	errors.push_back(err_count);
}

void test_pair_type_change()
{
	test_name = "PAIR TYPE CHANGE TEST ";
	err_count = 0;
	names.push_back(test_name);

	if (verbose)
		print_header(test_name, 0);

	//std test
	timer_start();
	for (int i = 0; i < count; ++i)
	{
		std::pair<char, int> p1('s', 42);
		std::pair<int, double> p2;
		p2 = p1;
	}
	double std_res = timer_stop();

	//ft test
	timer_start();
	for (int i = 0; i < count; ++i)
	{
		ft::pair<char, int> p1('s', 42);
		ft::pair<int, double> p2;
		p2 = p1;
	}
	double ft_res = timer_stop();

	// results
	if (verbose)
	{
		performance_result(std_res, ft_res);
		comparision_result(ft_res);
	}
	if (std_res != 0)
		time_perf.push_back(std_res / ft_res);
	else	
		time_perf.push_back(0);
	errors.push_back(err_count);
}

void test_pair_make_pair()
{
	test_name = "PAIR MAKE PAIR TEST ";
	err_count = 0;
	names.push_back(test_name);

	if (verbose)
		print_header(test_name, 0);

	//std test
	timer_start();
	for (int i = 0; i < count; ++i)
	{
		std::pair<char, int> p1 = std::make_pair ('c', 42);
		(void) p1;
	}
	double std_res = timer_stop();

	//ft test
	timer_start();
	for (int i = 0; i < count; ++i)
	{
		ft::pair<char, int> p1 = ft::make_pair ('c', 42);
		(void) p1;
	}
	double ft_res = timer_stop();

	// results
	if (verbose)
	{
		performance_result(std_res, ft_res);
		comparision_result(ft_res);
	}
	if (std_res != 0)
		time_perf.push_back(std_res / ft_res);
	else	
		time_perf.push_back(0);
	errors.push_back(err_count);
}

void test_pair_comparisons()
{
	test_name = "PAIR COMPARISONS TEST ";
	err_count = 0;
	names.push_back(test_name);

	if (verbose)
		print_header(test_name, 0);

	//std test
	timer_start();
	for (int i = 0; i < count; ++i)
	{
		std::pair<char, int> p1 = std::make_pair ('c', 42);
		std::pair<char, int> p2 = std::make_pair ('c', 21);
		bool res;
		res = (p1 == p2);
		res = (p1 != p2);
		res = (p1 < p2);
		res = (p1 <= p2);
		res = (p1 > p2);
		res = (p1 >= p2);
		(void) res;
	}
	double std_res = timer_stop();

	//ft test
	timer_start();
	for (int i = 0; i < count; ++i)
	{
		ft::pair<char, int> p1 = ft::make_pair ('c', 42);
		ft::pair<char, int> p2 = ft::make_pair ('c', 21);
		bool res;
		res = (p1 == p2);
		res = (p1 != p2);
		res = (p1 < p2);
		res = (p1 <= p2);
		res = (p1 > p2);
		res = (p1 >= p2);
		(void) res;
	}
	double ft_res = timer_stop();

	// results
	if (verbose)
	{
		performance_result(std_res, ft_res);
		comparision_result(ft_res);
	}
	if (std_res != 0)
		time_perf.push_back(std_res / ft_res);
	else	
		time_perf.push_back(0);
	errors.push_back(err_count);
}

void test_utility(void)
{
	print_header("UTILITY TESTS", 1);

	test_name.clear();
	names.clear();
	errors.clear();
	time_perf.clear();

 	test_enableif_integral();
 	test_lexicographical_compare();
 	test_lexicographical_compare_with_cmp();
 	test_equal();
 	test_equal_with_pred();
 	test_pair_construction();
 	test_pair_type_change();
 	test_pair_make_pair();
 	test_pair_comparisons();

	print_test_results();
}
