/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distance.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 23:23:11 by ldurante          #+#    #+#             */
/*   Updated: 2022/12/20 23:23:42 by ldurante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "iterator_traits.hpp"

namespace ft
{
	template<class InputIterator>
	typename ft::iterator_traits<InputIterator>::difference_type
	distance (InputIterator first, InputIterator last)
	{
		typename ft::iterator_traits<InputIterator>::difference_type i = 0;
		while (first != last)
		{
			i++;
			first++;
		}
		return (i);
	}
}
