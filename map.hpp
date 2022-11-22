/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 20:32:23 by ldurante          #+#    #+#             */
/*   Updated: 2022/11/22 21:48:52 by ldurante         ###   ########.fr       */
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
			
			typedef ft::pair<const Key, T>				value_type;
			typedef ft::RBTree<value_type>				rbtree;
			typedef ft::Node<value_type>*				node_ptr;

			typedef ft::MapIterator<value_type>								iterator;
			typedef ft::MapIterator<const value_type>						const_iterator;
			typedef ft::ReverseMapIterator<iterator>						reverse_iterator;
			typedef ft::ReverseMapIterator<const_iterator>					const_reverse_iterator;
			typedef typename iterator_traits<iterator>::difference_type		difference_type;
			
			typedef Alloc										allocator_type;
			typedef typename allocator_type::pointer			pointer;
			typedef typename allocator_type::const_pointer		const_pointer;
			typedef typename allocator_type::reference			reference;
			typedef typename allocator_type::const_reference	const_reference;
					
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
				m_alloc(toCopy.alloc),
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
				return iterator(this->m_tree.minNode(this->m_tree.m_root), &this->m_tree);
			}
			const_iterator begin() const
			{
				return iterator(this->m_tree.minNode(this->m_tree.m_root), &this->m_tree);
			}
			iterator end()
			{
				return iterator(this->m_tree.m_nullNode, &this->m_tree);
			}
			const_iterator end() const
			{
				return iterator(this->m_tree.m_nullNode, &this->m_tree);
			}

			reverse_iterator rbegin()
			{
				return reverse_iterator(this->m_tree.maxNode(this->m_tree.m_root), &this->m_tree);
			}
			const_reverse_iterator rbegin() const
			{
				return const_reverse_iterator(this->m_tree.maxNode(this->m_tree.m_root), &this->m_tree);
			}
			reverse_iterator rend()
			{
				return reverse_iterator(NULL, &this->m_tree);
			}
			const_reverse_iterator rend() const
			{
				return const_reverse_iterator(NULL, &this->m_tree);
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
				// return (*(this->insert(value_type(k, mapped_type())).first)).second;
				iterator tmp = find(k);
				if (tmp != end())
				{
					// std::cout << "RETURN: " << tmp->first << std::endl;
					// std::cout << "OJETE" << std::endl;
					return tmp->second;
				}
				return (insert(ft::make_pair(k, mapped_type())).first->second);
			}

			mapped_type& at (const key_type& k)
			{
				iterator tmp = find(k);
				// std::cout << "RETURN: " << tmp->second << std::endl;
				if (tmp == end())
				{
					throw std::out_of_range("key not found");
				}
				return (insert(ft::make_pair(k, mapped_type())).first->second);
				// return tmp->second;
			}
			
			const mapped_type& at (const key_type& k) const
			{

			}

			/*************************************************/
			/*                   MODIFIERS                   */
			/*************************************************/

			pair<iterator,bool> insert (const value_type& val)
			{
				size_type	sizeBefore(this->m_tree.getSize());
				node_ptr	tmp = this->m_tree.insert(val);
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
				if (this->empty())
				{
					// std::cout << "END" << std::endl;
					return (this->end());
				}
				node_ptr tmp = this->m_tree.searchTree(ft::make_pair(k, mapped_type()));
				if (tmp->pair_data.first == k)
				{
					// std::cout << "TMP" << std::endl;
					return (iterator(tmp, &this->m_tree));
				}
				return (end());
			}

			const_iterator find (const key_type& k) const
			{

			}

			size_type count (const key_type& k) const
			{

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
