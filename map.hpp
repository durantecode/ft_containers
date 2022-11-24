/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 20:32:23 by ldurante          #+#    #+#             */
/*   Updated: 2022/11/25 00:50:13 by ldurante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

// #include "red_black_tree.hpp"
#include "map_iterator.hpp"
#include "make_pair.hpp"

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
			typedef Alloc								allocator_type;
			
			typedef ft::pair<const Key, T>				value_type;
			typedef value_type*							pointer;
			typedef value_type&							reference;
			typedef const value_type*					const_pointer;
			typedef const value_type&					const_reference;

			typedef ft::RBTree<value_type>				rbtree;
			typedef ft::Node<value_type>*				node_ptr;

			typedef ft::MapIterator<value_type, pointer, reference>					iterator;
			typedef ft::MapIterator<value_type, const_pointer, const_reference>		const_iterator;
			typedef ft::ReverseMapIterator<iterator>								reverse_iterator;
			typedef ft::ReverseMapIterator<const_iterator>							const_reverse_iterator;
			typedef typename iterator_traits<iterator>::difference_type				difference_type;
			
					
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
			};

		protected:
			allocator_type	m_alloc;
			size_type		m_size;
			key_compare		m_compare;
			rbtree			m_tree;

			/*************************************************/
			/*                 CONSTRUCTORS                  */
			/*************************************************/

		public:
		
			explicit map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) :
				m_alloc(alloc),
				m_size(0),
				m_compare(comp),
				m_tree(alloc)
				{}

			template <class InputIterator>
			map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
			{
				
			}

			map (const map &toCopy) :
				m_alloc(toCopy.m_alloc),
				m_size(toCopy.m_size),
				m_compare(toCopy.m_compare),
				m_tree(toCopy.m_tree)
			{}

			~map()
			{
				this->m_tree.clear(this->m_tree.m_root);
			}

			map &operator = (const map &toCopy)
			{
				if (*this != &toCopy)
				{
					
					this->m_alloc = toCopy.m_alloc;
					this->m_compare = toCopy.m_compare;
					this->m_size = toCopy.m_size;
					this->m_tree = toCopy.m_tree;
				}
			}

			/*************************************************/
			/*                   ITERATORS                   */
			/*************************************************/

			iterator begin()
			{ 
				return iterator(this->m_tree.getMin(this->m_tree.m_root), &this->m_tree);
			}
			const_iterator begin() const
			{
				return const_iterator(this->m_tree.getMin(this->m_tree.m_root), &this->m_tree);
			}
			iterator end()
			{
				return iterator(this->m_tree.m_nullNode, &this->m_tree);
			}
			const_iterator end() const
			{
				return const_iterator(this->m_tree.m_nullNode, &this->m_tree);
			}

			reverse_iterator rbegin()
			{
				return reverse_iterator(iterator(this->m_tree.getMax(this->m_tree.m_root), &this->m_tree));
			}
			const_reverse_iterator rbegin() const
			{
				return const_reverse_iterator(const_iterator(this->m_tree.getMax(this->m_tree.m_root), &this->m_tree));
			}
			reverse_iterator rend()
			{
				return reverse_iterator(iterator(NULL, &this->m_tree));
			}
			const_reverse_iterator rend() const
			{
				return const_reverse_iterator(const_iterator(NULL, &this->m_tree));
			}

			/*************************************************/
			/*                   CAPACITY                    */
			/*************************************************/

			bool empty() const
			{
				if (!this->m_size)
					return (true);
				return (false);
			}

			size_type size() const { return (this->m_tree.getSize()); }
			size_type max_size() const { return (this->m_alloc.max_size()); }
			allocator_type get_allocator() const { return this->m_alloc; }
			

			/*************************************************/
			/*                ELEMENT ACCESS                 */
			/*************************************************/

			mapped_type& operator[] (const key_type& k)
			{
				iterator tmp = find(k);
				if (tmp != end())
					return tmp->second;
				return (insertNode(ft::make_pair(k, mapped_type())).first->second);
			}

			mapped_type& at (const key_type& k)
			{
				iterator tmp = find(k);
				if (tmp == end())
					throw std::out_of_range("key not found");
				return tmp->second;
			}
			
			const mapped_type& at (const key_type& k) const
			{
				const_iterator tmp = find(k);
				if (tmp == end())
					throw std::out_of_range("key not found");
				return tmp->second;
			}

			/*************************************************/
			/*                   MODIFIERS                   */
			/*************************************************/

			pair<iterator,bool> insert (const value_type& val)
			{
				size_type	sizeBefore(this->m_tree.getSize());
				node_ptr	tmp = this->m_tree.insertNode(val);
				if (this->m_tree.getSize() != sizeBefore)
					return ft::make_pair<iterator, bool>(iterator(tmp, &this->m_tree), true);
				return ft::make_pair<iterator, bool>(iterator(tmp, &this->m_tree), false);
			}

			iterator insert (iterator position, const value_type& val)
			{

			}

			template <class InputIterator>
			void insert (InputIterator first, InputIterator last)
			{

			}
			
			void erase (iterator position)
			{

			}
			
			size_type erase (const key_type& k)
			{

			}

		    void erase (iterator first, iterator last)
			{

			}

			void swap (map& x)
			{

			}

			void clear()
			{
				this->m_tree.clear(this->m_tree.m_root);
			}

			/*************************************************/
			/*                   OBSERVERS                   */
			/*************************************************/

			key_compare key_comp() const
			{

			}

			value_compare value_comp() const
			{

			}

			/*************************************************/
			/*                   OPERATIONS                  */
			/*************************************************/

			iterator find (const key_type& k)
			{
				if (!empty())
				{
					node_ptr tmp = this->m_tree.searchTree(this->m_tree.m_root, ft::make_pair(k, T()));
					if (tmp)
						return (iterator(tmp, &this->m_tree));
				}
				return (end());
			}

			const_iterator find (const key_type& k) const
			{
				if (!empty())
				{
					node_ptr tmp = this->m_tree.searchTree(this->m_tree.m_root, ft::make_pair(k, T()));
					if (tmp)
						return (const_iterator(tmp, &this->m_tree));
				}
				return (end());
			}

			size_type count (const key_type& k)
			{
				const_iterator it = this->begin();
				// while (it != end())
				// {
				// 	if (it->first == k)
				// 		return (1);
				// 	++it;
				// }
				return (0);
			}
			
			iterator lower_bound (const key_type& k)
			{
				
			}
			
			const_iterator lower_bound (const key_type& k) const
			{

			}

			iterator upper_bound (const key_type& k)
			{

			}

			const_iterator upper_bound (const key_type& k) const
			{
				
			}

			pair<const_iterator, const_iterator> equal_range (const key_type& k) const
			{

			}
			
			pair<iterator, iterator> equal_range (const key_type& k)
			{

			}
	};
}
