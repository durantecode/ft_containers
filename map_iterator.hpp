/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_iterator.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 21:58:48 by ldurante          #+#    #+#             */
/*   Updated: 2022/11/18 15:31:31 by ldurante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "iterator_traits.hpp"
#include "red_black_tree.hpp"

namespace ft
{
			/*************************************************/
			/*                  MAP_ITERATOR                 */
			/*************************************************/
	
	template <class T>
	class MapIterator
	{
		public:
			typedef T									value_type;
			typedef T&									reference;
			typedef ft::Node<value_type>*				node;
			typedef ft::RBTree<value_type>*				rbtree;
			typedef std::random_access_iterator_tag		iterator_category;
			typedef std::ptrdiff_t						difference_type;


		protected:
			node 	m_currentNode;
			rbtree	m_tree;
		
		public:
			MapIterator() : m_currentNode(0) {}
			MapIterator(node ptr, rbtree tree) : m_currentNode(ptr), m_tree(tree) {}
			MapIterator(MapIterator const &toCopy) : m_currentNode(toCopy.m_currentNode) {}
			~MapIterator() {}
			MapIterator &operator = (MapIterator const &toCopy)
			{
				this->m_currentNode = toCopy.m_currentNode;
				return (*this);
			}

			value_type &operator * () { return (this->m_currentNode->pair_data); }
			// const_reference operator * () const { return (this->m_currentNode->pair_data); }
			value_type *operator -> () { return (&this->m_currentNode->pair_data); }
			// const_node operator -> () const { return (&this->m_currentNode->pair_data); }

			MapIterator& operator ++ ()
			{
				this->m_currentNode = this->m_tree->successor(this->m_currentNode);
				if (!this->m_currentNode)
					this->m_currentNode = this->m_tree->m_root;
				return (*this);
			}
			// MapIterator operator ++ (int)
			// {
			// 	MapIterator it(*this);
			// 	this->m_currentNode->m_root = this->m_currentNode->successor(this->m_currentNode->m_root);
			// 	return it;
			// }
			// MapIterator& operator -- ()
			// {
			// 	this->m_currentNode->m_root = this->m_currentNode->predecessor(this->m_currentNode->m_root);
			// 	return *this;
			// }
			// MapIterator operator -- (int)
			// {
			// 	MapIterator it(*this);
			// 	this->m_currentNode->m_root = this->m_currentNode->predecessor(this->m_currentNode->m_root);
			// 	return it;
			// }
			bool operator == (const MapIterator &it) const { return (this->m_currentNode == it.m_currentNode); }
			bool operator != (const MapIterator &it) const { return (this->m_currentNode != it.m_currentNode); }
			// bool operator > (const MapIterator &it) const { return (this->m_currentNode->m_root > it.m_currentNode->m_root); }
			// bool operator >= (const MapIterator &it) const { return (this->m_currentNode->m_root >= it.m_currentNode->m_root); }
			// bool operator < (const MapIterator &it) const { return (this->m_currentNode->m_root < it.m_currentNode->m_root); }
			// bool operator <= (const MapIterator &it) const { return (this->m_currentNode->m_root <= it.m_currentNode->m_root); }

	};

			/*************************************************/
			/*              REVERSE_MAP_ITERATOR             */
			/*************************************************/
	
	template <class T>
	class ReverseMapIterator
	{
		
	};
}
