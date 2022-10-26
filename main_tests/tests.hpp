/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 18:42:34 by ldurante          #+#    #+#             */
/*   Updated: 2022/10/26 01:57:54 by ldurante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TESTS_HPP
# define TESTS_HPP

# include <vector>
# include <map>
# include <stack>
# include <iostream>
# include <iomanip>
# include "../vector.hpp"
# include "../map.hpp"
# include "../stack.hpp"

# define RESET "\033[0m"
# define RED "\x1B[0;31m"
# define GREEN "\033[0;32m"
# define YELLOW "\x1B[0;33m"
# define BLUE "\x1B[0;34m"
# define MAGENTA "\033[0;35m"
# define BOLD "\033[1m"

# define GOOD "✓"
# define FAIL "x"

void	test_vector(void);
void	test_map(void);
void	test_stack(void);

double 	timer_stop();
void   	timer_start();
void   	performance_result(double std, double ft);
void	print_test_name(long count);
void	comparision_result(int err_count, double comp_res);

void	test_vector_time_empty_constructor(long count);
void 	test_vector_time_param_constructor(long count);
void	test_vector_time_two_param_constructor(long count);
void 	test_vector_time_copy_constructor(long count);
void 	test_vector_time_copy_range_constructor(long count);
void	test_vector_time_size_capacity_empty(long count);
void	test_vector_time_size_capacity_random(long count);
void 	test_vector_time_access(long count);
void 	test_vector_time_reserve(long count);
void 	test_vector_time_resize(long count);
void 	test_vector_time_push_back(long count);
void 	test_vector_time_pop_back(long count);
void 	test_vector_time_erase_position(long count);
void 	test_vector_time_erase_iter(long count);
void 	test_vector_time_clear(long count);
void 	test_vector_time_insert_position(long count);
void 	test_vector_time_insert_pos_value(long count);
void 	test_vector_time_insert_iter(long count);
void 	test_vector_time_assign_value(long count);
void 	test_vector_time_assign_range(long count);
void 	test_vector_time_assignment(long count);
void 	test_vector_time_reverse_iter(long count);
void 	test_vector_time_swap(long count);
void 	test_vector_time_comparison(long count);

inline void print_header(std::string str, bool container)
{
	int margin = (40 - str.length()) / 2;
	int width = (margin * 2 + str.length()) + 2;
	if (container)
	{
		std::cout << BLUE;
		std::cout << std::string(width, '*') << std::endl;
		std::cout << "*" << RED << std::string(margin, ' ') << str << std::string(margin, ' ') << BLUE << "*" << std::endl;
		std::cout << std::string(width, '*') << std::endl << std::endl;
	}
	else
	{
		std::cout << MAGENTA;
		std::cout << std::string(width, '*') << std::endl;
		std::cout << "*" << YELLOW << std::string(margin, ' ') << str << std::string(margin, ' ') << MAGENTA << "*" << std::endl;
		std::cout << "*" << std::string(40, ' ') << "*" << std::endl;
		std::cout << RESET;
	}
}

template <typename T>
inline void check(std::string name, T a, T b)
{
	float margin = (42 - name.length() - 3) / 2;
	if (a == b)
		std::cout << MAGENTA << "*" << std::setw(margin + 3) << RESET << name << ": " << GREEN << GOOD << MAGENTA << std::setw(margin) << "*" << RESET << std::endl;
	else
		std::cout << MAGENTA << "*" << std::setw(margin + 3) << RESET << name << ": " << GREEN << FAIL << MAGENTA << std::setw(margin) << "*" << RESET << std::endl;
}

inline void check(std::string name, bool good)
{
	float margin = (42 - name.length() - 3) / 2;
	if (good)
		std::cout << MAGENTA << "*" << std::setw(margin + 3) << RESET << name << ": " << GREEN << GOOD << MAGENTA << std::setw(margin) << "*" << RESET << std::endl;
	else
		std::cout << MAGENTA << "*" << std::setw(margin + 3) << RESET << name << ": " << GREEN << FAIL << MAGENTA << std::setw(margin) << "*" << RESET << std::endl;
}

template <typename T>
bool operator==(ft::vector<T> &a, std::vector<T> &b)
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

// template <typename T, typename S>
// bool operator==(ft::map<T, S> &a, std::map<T, S> &b)
// {
// 	if (a.size() != b.size())
// 		return (false);
// 	if (a.empty() != b.empty())
// 		return (false);
// 	typename ft::Map<T, S>::iterator it = a.begin();
// 	typename std::map<T, S>::iterator it2 = b.begin();
// 	while (it != a.end())
// 	{
// 		if (it->first != it2->first || it->second != it2->second)
// 			return (false);
// 		++it;
// 		++it2;
// 	}
// 	return (true);
// }

#endif
