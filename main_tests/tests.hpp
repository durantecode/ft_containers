/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 18:42:34 by ldurante          #+#    #+#             */
/*   Updated: 2022/12/07 19:55:54 by ldurante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TESTS_HPP
# define TESTS_HPP

# include <vector>
# include <map>
# include <stack>
# include <iostream>
# include <iomanip>
# include <chrono>
# include <algorithm>
# include <type_traits>
# include <utility>

# include "../src/vector.hpp"
# include "../src/map.hpp"
# include "../src/stack.hpp"
# include "../src/enable_if.hpp"
# include "../src/lexicographical_compare.hpp"
# include "../src/is_integral.hpp"
# include "../src/equal.hpp"
# include "../src/pair.hpp"
# include "../src/make_pair.hpp"

# define RESET "\033[0m"
# define RED "\x1B[0;31m"
# define GREEN "\033[0;32m"
# define YELLOW "\x1B[0;33m"
# define BLUE "\x1B[0;34m"
# define MAGENTA "\033[0;35m"
# define GRAY "\x1b[90m"
# define BOLD "\033[1m"

# define GOOD "✓"
# define FAIL "x"

/* GLOBAL VARIABLES */

extern long	count;
extern long	err_count;
extern std::string test_name;
extern bool verbose;
extern std::vector<std::string> names;
extern std::vector<long> errors;
extern std::vector<double> time_perf;

/* MAIN FUNCTIONS */

template <class T>
static void print_map(T &map);

void	test_vector(void);
void	test_map(void);
void	test_stack(void);
void	test_utility(void);

/* PERFORMANCE AND COMPARISION FUNCTIONS */

double 		timer_stop();
void   		timer_start();
void   		performance_result(double std, double ft);
void		comparision_result(double comp_res);
std::string createString();

/* STACK FUNCTIONS */

void	test_stack_time_empty_constructor();
void	test_stack_time_copy_constructor();
void	test_stack_time_assignment();
void	test_stack_time_size_empty_top();
void	test_stack_time_push_pop();
void	test_stack_time_comparison();

/* VECTOR FUNCTIONS */

void	test_vector_time_empty_constructor();
void 	test_vector_time_param_constructor();
void	test_vector_time_two_param_constructor();
void 	test_vector_time_copy_constructor();
void 	test_vector_time_copy_range_constructor();
void	test_vector_time_size_capacity_empty();
void	test_vector_time_size_capacity_random();
void 	test_vector_time_access();
void 	test_vector_time_resize();
void 	test_vector_time_reserve();
void 	test_vector_time_push_back();
void 	test_vector_time_pop_back();
void 	test_vector_time_erase_position();
void 	test_vector_time_erase_iter();
void 	test_vector_time_clear();
void 	test_vector_time_insert_position();
void 	test_vector_time_insert_pos_value();
void 	test_vector_time_insert_iter();
void 	test_vector_time_assign();
void 	test_vector_time_assign_range();
void 	test_vector_time_assign_value();
void 	test_vector_time_iter();
void	test_vector_time_const_iter();
void 	test_vector_time_reverse_iter();
void	test_vector_time_const_reverse_iter();
void 	test_vector_time_swap();
void 	test_vector_time_comparison();

/* UTILIYY FUNCTIONS */

void 	test_enableif_integral();
void 	test_lexicographical_compare();
void 	test_lexicographical_compare_with_cmp();
void 	test_equal();
void 	test_equal_with_pred();
void 	test_pair_construction();
void 	test_pair_type_change();
void 	test_pair_make_pair();
void 	test_pair_comparisons();


/* MAP FUNCTIONS */

void 	test_map_time_empty_constructor();
void 	test_map_time_copy_constructor();
void 	test_map_time_range_constructor();
void 	test_map_time_size_empty_max();
void 	test_map_time_assignment_op();
void 	test_map_time_operator_at();
void 	test_map_time_insert_val();
void 	test_map_time_insert_pos();
void 	test_map_time_insert_range();
void 	test_map_time_erase_val();
void 	test_map_time_erase_pos(); 
void 	test_map_time_erase_range();
void 	test_map_time_swap(); 
void 	test_map_time_count_clear();
void 	test_map_time_find();
void 	test_map_time_lower_bound();
void 	test_map_time_upper_bound();
void 	test_map_time_equal_range();
void 	test_map_time_begin_end();
void 	test_map_time_rbegin_rend();
void 	test_map_time_comparison();

/* PRINTING FUNCTIONS */

void print_project_title(void);
void print_header(std::string str, bool container);
void print_test_results(void);

/* CHECK CONTAINERS FUNCTIONS */

template <typename T>
inline void check(std::string name, T a, T b)
{
	float margin = (42 - name.length() - 3) / 2;
	if (a == b)
	{
		if (verbose)
			std::cout << MAGENTA << "*" << std::setw(margin + 3) << RESET << name << ": " << GREEN << GOOD << MAGENTA << std::right << std::setw(margin) << "*" << RESET << std::endl;
	}
	else
	{
		if (verbose)
			std::cout << MAGENTA << "*" << std::setw(margin + 3) << RESET << name << ": " << RED << FAIL << MAGENTA << std::right << std::setw(margin) << "*" << RESET << std::endl;
		err_count++;
	}
}

inline void check(std::string name, bool good)
{
	float margin = (42 - name.length() - 3) / 2;
	if (good)
	{
		if (verbose)
			std::cout << MAGENTA << "*" << std::setw(margin + 3) << RESET << name << ": " << GREEN << GOOD << MAGENTA << std::right << std::setw(margin) << "*" << RESET << std::endl;
	}
	else
	{
		if (verbose)
			std::cout << MAGENTA << "*" << std::setw(margin + 3) << RESET << name << ": " << RED << FAIL << MAGENTA << std::right << std::setw(margin) << "*" << RESET << std::endl;
		err_count++;
	}
}

/* TEMPLATE TO CHECK STD VECTOR AGAINST FT VECTOR */

template <typename T>
bool operator == (ft::vector<T> &a, std::vector<T> &b)
{
	if (a.size() != b.size())
		return (false);
	if (a.empty() != b.empty())
		return (false);
	for (size_t i = 0; i < a.size(); i++)
	{
		if (a[i] != b[i])
			return (false);
	}
	return (true);
}

/* TEMPLATE TO CHECK STD MAP AGAINST FT MAP */

template <typename T, typename S>
bool operator == (ft::map<T, S> &a, std::map<T, S> &b)
{
	if (a.size() != b.size())
		return (false);
	if (a.empty() != b.empty())
		return (false);
	typename ft::map<T, S>::iterator it = a.begin();
	typename ft::map<T, S>::iterator ite = a.end();
	typename std::map<T, S>::iterator it2 = b.begin();
	while (it != ite)
	{
		if (it->first != it2->first || it->second != it2->second)
			return (false);
		++it;
		++it2;
	}
	return (true);
}

template <class InputIterator1, class InputIterator2>
bool my_equal (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2)
{
	while (first1 != last1)
	{
		if (first1->first != first2->first)
			return false;
		if (first1->second != first2->second)
			return false;
		++first1;
		++first2;
	}
	return true;
}

template <class InputIterator1, class InputIterator2>
bool iter_compare (InputIterator1 &first1, InputIterator2 &first2)
{
	if (first1.first != first2.first)
		return false;
	if (first1.second != first2.second)
		return false;
	return true;
}

#endif
