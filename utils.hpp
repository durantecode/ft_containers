/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 19:27:33 by ldurante          #+#    #+#             */
/*   Updated: 2022/10/21 14:35:33 by ldurante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "vector_iterator.hpp"

namespace ft
{
	template <typename T>
	void	swap(T &a, T &b)
	{
		T tmp = a;
		a = b;
		b = tmp;
	}

	// // Iterator distance

	// // random access iterator optimization
	// template <typename RAIt>
	// typename iterator_traits<RAIt>::difference_type
	// distance(RAIt first, RAIt last)
	// {
	// 	return last - first;
	// }
}
