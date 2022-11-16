/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 20:32:23 by ldurante          #+#    #+#             */
/*   Updated: 2022/11/16 21:18:17 by ldurante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "red_black_tree.hpp"
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
			typedef std::ptrdiff_t						difference_type;
			typedef ft::RBTree<value_type>				rbtree;

			typedef ft::MapIterator<rbtree, value_type>			iterator;
			typedef ft::MapIterator<rbtree, const value_type>	const_iterator;
			typedef ft::ReverseMapIterator<iterator>			reverse_iterator;
			typedef ft::ReverseMapIterator<const_iterator>		const_reverse_iterator;
			
			typedef Alloc										allocator_type;
			typedef typename allocator_type::pointer			pointer;
			typedef typename allocator_type::const_pointer		const_pointer;
			typedef typename allocator_type::reference			reference;
			typedef typename allocator_type::const_reference	const_reference;
			
			typedef typename Alloc::template rebind<rbtree>::other		allocator_node;
			
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
			allocator_node	m_alloc;
			size_type		m_size;
			key_compare		m_compare;
			rbtree			*m_tree;		

			/*************************************************/
			/*                 CONSTRUCTORS                  */
			/*************************************************/

		public:
		
			explicit map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) :
				m_alloc(alloc),
				m_size(0),
				m_compare(comp)
				{
					this->m_tree = this->m_alloc.allocate(sizeof(rbtree));
					this->m_alloc.construct(m_tree, rbtree());
				}

			template <class InputIterator>
			map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
			{
				
			}

			map (const map &toCopy) :
				m_alloc(toCopy.alloc),
				m_size(toCopy.m_size),
				m_compare(toCopy.m_compare),
				m_tree(toCopy.m_tree)
			{
				
			}

			~map()
			{

			}

			map &operator = (const map &toCopy)
			{
				
			}

			/*************************************************/
			/*                   ITERATORS                   */
			/*************************************************/

			iterator begin()
			{ 
				rbtree *tmp;
				tmp->m_root = this->m_tree->minimum(this->m_tree->m_root);
				return iterator(*tmp);
			}
			// const_iterator begin() const
			// {
			// 	this->m_tree->m_root = this->m_tree->minimum(this->m_tree->m_root);
			// 	return iterator(*this->m_tree);
			// }
			iterator end()
			{
				rbtree *tmp;
				tmp->m_root = this->m_tree->maximum(this->m_tree->m_root);
				return iterator(*tmp);
			}
			// const_iterator end() const
			// {
			// 	this->m_tree->m_root = this->m_tree->maximum(this->m_tree->m_root);
			// 	return iterator(*this->m_tree);
			// }

			/*************************************************/
			/*                   CAPACITY                    */
			/*************************************************/

			bool empty() const
			{

			}

			size_type size() const
			{
				return (this->m_size);
			}

			size_type max_size() const
			{

			}

			/*************************************************/
			/*                ELEMENT ACCESS                 */
			/*************************************************/

			mapped_type& operator[] (const key_type& k)
			{

			}

			mapped_type& at (const key_type& k)
			{

			}
			
			const mapped_type& at (const key_type& k) const
			{

			}

			/*************************************************/
			/*                   MODIFIERS                   */
			/*************************************************/

			pair<iterator,bool> insert (const value_type& val)
			{
				this->m_tree->insert(val);
				this->m_size++;
				return (ft::make_pair(iterator(*m_tree), true));
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
