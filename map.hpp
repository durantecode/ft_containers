/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 20:32:23 by ldurante          #+#    #+#             */
/*   Updated: 2022/11/14 15:33:31 by ldurante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <map>

namespace ft
{
	template <class Key, class T, class Compare = std::less<Key>,
			  class Allocator = std::allocator<std::pair<const Key, T> > >
	class map
	{
		public:
			typedef size_t						size_type;
			typedef Key							key_type;
			typedef T							mapped_type;
			
			typedef std::pair<const Key, T>		value_type;
			typedef std::ptrdiff_t				difference_type;
			
			typedef Allocator					allocator_type;
			typedef Allocator*					pointer;
			typedef const Allocator*			const_pointer;
			
			typedef value_type&					reference;
			typedef const value_type&			const_reference;
	};
}
