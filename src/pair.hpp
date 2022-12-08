/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pair.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 23:17:41 by ldurante          #+#    #+#             */
/*   Updated: 2022/12/08 23:33:10 by ldurante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

/*
	This class couples together a pair of values, which may be of different types (T1 and T2).
	The individual values can be accessed through its public members first and second.
*/

namespace ft
{
	template <class T1, class T2>
	struct pair
	{
		public:
			typedef T1	first_type;
			typedef T2	second_type;

			first_type	first;
			second_type	second;

			pair() : first(), second() {}

			template<class U, class V>
			pair (const pair<U, V> &pr) : first(pr.first), second(pr.second) {}

			pair (const first_type &a, const second_type &b) : first(a), second(b) {}

			pair &operator = (const pair &pr)
			{
				first = pr.first;
				second = pr.second;
				return *this;
			}

			void swap (pair& pr)
			{
  				std::swap(first, pr.first);
				std::swap(second, pr.second);
			}

			friend bool operator == (const pair &lhs, const pair &rhs) { return lhs.first == rhs.first && lhs.second == rhs.second; }
			friend bool operator != (const pair &lhs, const pair &rhs) { return !(lhs == rhs); }
			friend bool operator <  (const pair &lhs, const pair &rhs) { return lhs.first < rhs.first || (!(rhs.first < lhs.first) && lhs.second < rhs.second); }
			friend bool operator <= (const pair &lhs, const pair &rhs) { return !(rhs < lhs); }
			friend bool operator >  (const pair &lhs, const pair &rhs) { return rhs < lhs; }
			friend bool operator >= (const pair &lhs, const pair &rhs) { return !(lhs < rhs); }
	};
}
