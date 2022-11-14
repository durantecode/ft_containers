/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 20:32:23 by ldurante          #+#    #+#             */
/*   Updated: 2022/11/14 18:33:24 by ldurante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <map>

namespace ft
{
	template <class Key, class T, class Compare = std::less<Key>,
			  class Alloc = std::allocator<std::pair<const Key, T> > >
	class map
	{
		public:
			typedef size_t								size_type;
			typedef Key									key_type;
			typedef T									mapped_type;
			typedef Compare								key_compare;
			
			typedef std::pair<const Key, T>				value_type;
			typedef std::ptrdiff_t						difference_type;
			
			typedef Alloc								allocator_type;
			typedef allocator_type::pointer				pointer;
			typedef allocator_type::const_pointer		const_pointer;
			typedef allocator_type::reference			reference;
			typedef allocator_type::const_reference		const_reference;
			
			class value_compare
			{
				friend class map;
				
				protected:
					Compare comp;
					value_compare (Compare c) : comp(c) {}
				
				public:
					typedef bool		result_type;
					typedef value_type	first_argument_type;
					typedef value_type	second_argument_type;
					bool operator() (const value_type& x, const value_type& y) const
					{
						return comp(x.first, y.first);
					}
			}

		protected:
			allocator_type	m_alloc;
			size_type		m_size;
			key_compare		m_compare;		

			/*************************************************/
			/*                 CONSTRUCTORS                  */
			/*************************************************/
	};
}
