/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_iterator.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 21:58:48 by ldurante          #+#    #+#             */
/*   Updated: 2022/11/16 21:24:26 by ldurante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "iterator_traits.hpp"

namespace ft
{
			/*************************************************/
			/*                  MAP_ITERATOR                 */
			/*************************************************/
	
	template <class Tree, class T>
	class MapIterator
	{
		public:
			typedef Tree								value_type;
			typedef std::random_access_iterator_tag		iterator_category;
			typedef std::ptrdiff_t						difference_type;
			typedef T*									pointer;
			typedef const T*							const_pointer;
			typedef T&									reference;
			typedef const T&							const_reference;

		protected:
			value_type m_node;
		
		public:
			MapIterator() : m_node() {}
			MapIterator(value_type node) : m_node(node) {}
			MapIterator(MapIterator const &toCopy) : m_node(toCopy.m_node) {}
			~MapIterator() {}
			MapIterator &operator = (MapIterator const &toCopy)
			{
				this->m_node = toCopy.m_node;
				return (*this);
			}

			MapIterator& operator ++ ()
			{
				this->m_node.m_root = this->m_node.successor(this->m_node.m_root);
				return (*this);
			}
			MapIterator operator ++ (int)
			{
				MapIterator it(*this);
				this->m_node.m_root = this->m_node.successor(this->m_node.m_root);
				return it;
			}
			MapIterator& operator -- ()
			{
				this->m_node.m_root = this->m_node.predecessor(this->m_node.m_root);
				return *this;
			}
			MapIterator operator -- (int)
			{
				MapIterator it(*this);
				this->m_node.m_root = this->m_node.predecessor(this->m_node.m_root);
				return it;
			}
			reference operator * () { return (this->m_node.m_root->pair_data); }
			const_reference operator * () const { return (this->m_node.m_root->pair_data); }
			pointer operator -> () { return (&this->m_node.m_root->pair_data); }
			const_pointer operator -> () const { return (&this->m_node.m_root->pair_data); }
			bool operator == (const MapIterator &it) const { return (this->m_node.m_root == it.m_node.m_root); }
			bool operator != (const MapIterator &it) const { return (this->m_node.m_root != it.m_node.m_root); }
			bool operator > (const MapIterator &it) const { return (this->m_node.m_root > it.m_node.m_root); }
			bool operator >= (const MapIterator &it) const { return (this->m_node.m_root >= it.m_node.m_root); }
			bool operator < (const MapIterator &it) const { return (this->m_node.m_root < it.m_node.m_root); }
			bool operator <= (const MapIterator &it) const { return (this->m_node.m_root <= it.m_node.m_root); }

	};

			/*************************************************/
			/*              REVERSE_MAP_ITERATOR             */
			/*************************************************/
	
	template <class T>
	class ReverseMapIterator
	{
		
	};
}
