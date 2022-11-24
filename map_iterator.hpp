/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_iterator.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 21:58:48 by ldurante          #+#    #+#             */
/*   Updated: 2022/11/24 21:15:14 by ldurante         ###   ########.fr       */
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
	
	template <class T, class Pointer, class Reference>
	class MapIterator
	{
		public:
			typedef MapIterator<T, T*, T&>				iterator;
			typedef MapIterator<T, const T*, const T&>	const_iterator;
			typedef MapIterator<T, Pointer, Reference>	iter_type;
			typedef size_t		size_type;
			typedef ptrdiff_t	difference_type;
			typedef T			value_type;
			typedef Pointer		pointer;
			typedef Reference	reference;
			typedef std::bidirectional_iterator_tag				iterator_category;

			typedef ft::RBTree<value_type>*				rbtree_ptr;
			typedef ft::Node<value_type>*				node_ptr;
			typedef ft::RBTree<const value_type>		const_tree;
			typedef ft::Node<const value_type>       	const_node;

		// private:
			node_ptr 		m_currentNode;
			rbtree_ptr		m_tree;
		
		public:
			MapIterator() : m_currentNode(0), m_tree(0) {}
			MapIterator(node_ptr ptr) : m_currentNode(ptr) {}
			MapIterator(node_ptr ptr, rbtree_ptr tree) : m_currentNode(ptr), m_tree(tree) {}
			MapIterator(iterator const &toCopy) : m_currentNode(const_cast<node_ptr>(toCopy.m_currentNode)), m_tree(const_cast<rbtree_ptr>(toCopy.m_tree)) {}
			~MapIterator() {}
			iter_type &operator = (const_iterator const &toCopy)
			{
				this->m_currentNode = toCopy.m_currentNode;
				this->m_tree = toCopy.m_tree;
				return (*this);
			}

			reference operator * () { return (this->m_currentNode->pair_data); }
			pointer operator -> () { return (&this->m_currentNode->pair_data); }

			MapIterator& operator ++ ()
			{
				this->m_currentNode = this->m_tree->nextNode(this->m_currentNode);
				return (*this);
			}
			MapIterator operator ++ (int)
			{
				MapIterator it(*this);
				this->m_currentNode = this->m_tree->nextNode(this->m_currentNode);
				return it;
			}
			MapIterator& operator -- ()
			{
				this->m_currentNode = this->m_tree->prevNode(this->m_currentNode);
				return (*this);
			}
			MapIterator operator -- (int)
			{
				MapIterator it(*this);
				this->m_currentNode = this->m_tree->prevNode(this->m_currentNode);
				return it;
			}
			bool operator == (const MapIterator &it) const { return (this->m_currentNode == it.m_currentNode); }
			bool operator != (const MapIterator &it) const { return (this->m_currentNode != it.m_currentNode); }
			bool operator > (const MapIterator &it) const { return (this->m_currentNode > it.m_currentNode); }
			bool operator >= (const MapIterator &it) const { return (this->m_currentNode >= it.m_currentNode); }
			bool operator < (const MapIterator &it) const { return (this->m_currentNode < it.m_currentNode); }
			bool operator <= (const MapIterator &it) const { return (this->m_currentNode <= it.m_currentNode); }
	};

			/*************************************************/
			/*              REVERSE_MAP_ITERATOR             */
			/*************************************************/
	template <class T>
	class ReverseMapIterator
	{
		public:
			typedef T												iterator_type;
			typedef typename iterator_traits<T>::iterator_category	iterator_category;
			typedef typename iterator_traits<T>::value_type			value_type;
			typedef typename iterator_traits<T>::difference_type	difference_type;
			typedef typename iterator_traits<T>::pointer			pointer;
			typedef typename iterator_traits<T>::reference			reference;

		protected:
			iterator_type	m_iter;
		
		public:
			ReverseMapIterator() : m_iter() {}
			ReverseMapIterator(const iterator_type &it) : m_iter(it) {}
			ReverseMapIterator(const ReverseMapIterator &toCopy) : m_iter(toCopy.base()) {}
			template <typename I>
			ReverseMapIterator(const ReverseMapIterator<I> &toCopy) : m_iter(toCopy.base()) {}
			~ReverseMapIterator() {}
			ReverseMapIterator &operator = (ReverseMapIterator const &toCopy)
			{
				iterator_type::operator=(toCopy);
				// this->m_iter = toCopy.base();
				return (*this);
			}

			iterator_type base() const { return this->m_iter; }
			reference operator * () { return (*this->m_iter); }
			pointer operator -> () { return (&operator*()); }

			ReverseMapIterator& operator ++ ()
			{
				this->m_iter++;
				return (*this);
			}
			ReverseMapIterator operator ++ (int)
			{
				ReverseMapIterator it(*this);
				this->m_iter++;
				return it;
			}
			ReverseMapIterator& operator -- ()
			{
				this->m_iter--;
				return (*this);
			}
			ReverseMapIterator operator -- (int)
			{
				ReverseMapIterator it(*this);
				this->m_iter--;
				return it;
			}
			bool operator == (const ReverseMapIterator &it) const { return (this->m_iter == it.m_iter); }
			bool operator != (const ReverseMapIterator &it) const { return (this->m_iter != it.m_iter); }
			bool operator > (const ReverseMapIterator &it) const { return (this->m_iter > it.m_iter); }
			bool operator >= (const ReverseMapIterator &it) const { return (this->m_iter >= it.m_iter); }
			bool operator < (const ReverseMapIterator &it) const { return (this->m_iter < it.m_iter); }
			bool operator <= (const ReverseMapIterator &it) const { return (this->m_iter <= it.m_iter); }
	};
}
