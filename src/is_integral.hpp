/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_integral.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 23:10:52 by ldurante          #+#    #+#             */
/*   Updated: 2022/11/04 16:53:15 by ldurante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>

/*	Trait class that identifies whether T is an integral type.

	is_integral<int> inherits from true_type.
	is_integral<const char>::type is the type true_type.
	is_integral<long>::value is an integral constant expression that evaluates to true.
	is_integral<T>::value_type is the type bool.

*/

namespace ft
{
	template<typename> struct is_integral: public std::false_type {};
	template<> struct is_integral<bool>: public std::true_type {};
	template<> struct is_integral<char>: public std::true_type {};
	template<> struct is_integral<char32_t>: public std::true_type {};
	template<> struct is_integral<char16_t>: public std::true_type {};
	template<> struct is_integral<wchar_t>: public std::true_type {};
	template<> struct is_integral<signed char>: public std::true_type {};
	template<> struct is_integral<short int>: public std::true_type {};
	template<> struct is_integral<int>: public std::true_type {};
	template<> struct is_integral<long int>: public std::true_type {};
	template<> struct is_integral<unsigned char>: public std::true_type {};
	template<> struct is_integral<unsigned short int>: public std::true_type {};
	template<> struct is_integral<unsigned int>: public std::true_type {};
	template<> struct is_integral<unsigned long int>: public std::true_type {};
}
