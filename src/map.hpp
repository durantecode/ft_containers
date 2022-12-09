/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 20:32:23 by ldurante          #+#    #+#             */
/*   Updated: 2022/12/09 16:49:51 by ldurante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "equal.hpp"
#include "lexicographical_compare.hpp"
#include "map_iterator.hpp"

namespace ft
{
	template <class Key, class T, class Compare = std::less<Key>,
			  class Alloc = std::allocator<ft::pair<const Key, T> > >
	class map
	{
		public:
			typedef ft::map<Key, T, Compare>			Container;
			typedef size_t								size_type;
			typedef Key									key_type;
			typedef T									mapped_type;
			typedef Compare								key_compare;
			typedef Alloc								allocator_type;
			typedef ptrdiff_t							difference_type;
			
			typedef ft::pair<const Key, T>				value_type;
			typedef value_type*							pointer;
			typedef value_type&							reference;
			typedef const value_type*					const_pointer;
			typedef const value_type&					const_reference;
			typedef std::bidirectional_iterator_tag		iter_tag;

			typedef Node<value_type>*							node_ptr;
			typedef RBTree<value_type, Key, allocator_type>		rbtree;
			
			typedef ft::iterator<iter_tag, value_type, difference_type, pointer, reference>		map_iter;

			typedef ft::MapIterator<map_iter, rbtree>			iterator;
			typedef ft::ConstMapIterator<map_iter, rbtree>		const_iterator;
			typedef ft::ReverseMapIterator<iterator>			reverse_iterator;
			typedef ft::ReverseMapIterator<const_iterator>		const_reverse_iterator;
			
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

		private:
			allocator_type	m_alloc;
			size_type		m_size;
			Compare			m_compare;
			rbtree			m_tree;

			/*************************************************/
			/*               MAP CONSTRUCTORS                */
			/*************************************************/

		public:
		
			explicit map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) :
				m_alloc(alloc),
				m_size(0),
				m_compare(comp),
				m_tree(alloc)
				{}

			template <class InputIterator>
			map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) :
				m_alloc(alloc),
				m_size(0),
				m_compare(comp),
				m_tree(alloc)
			{
				this->insert(first, last);
			}

			map (const map &toCopy) :
				m_alloc(toCopy.m_alloc),
				m_size(toCopy.m_size),
				m_compare(toCopy.m_compare),
				m_tree(toCopy.m_tree)
				{}

			~map()
			{
				this->m_tree.clear(this->m_tree.getRoot());
			}

			map &operator = (const map &toCopy)
			{
				if (this != &toCopy)
				{
					m_alloc = toCopy.m_alloc;
					m_size = toCopy.m_size;
					m_compare = toCopy.m_compare;
					m_tree = toCopy.m_tree;
				}
				return (*this);
			}

			/*************************************************/
			/*                   ITERATORS                   */
			/*************************************************/

			iterator begin()
			{
				if (!this->size())
					return end();
				return (iterator(this->m_tree.getMin(this->m_tree.getRoot()), &this->m_tree));
			}
			const_iterator begin() const
			{
				if (!this->size())
					return end();
				return const_iterator(this->m_tree.getMin(this->m_tree.getRoot()), &this->m_tree);
			}
			iterator end()
			{
				return iterator(this->m_tree.getNull(), &this->m_tree);
			}
			const_iterator end() const
			{
				return const_iterator(this->m_tree.getNull(), &this->m_tree);
			}
			reverse_iterator rbegin()
			{
				if (!this->size())
					return rend();
				iterator it(this->m_tree.getMax(this->m_tree.getRoot()), &this->m_tree);
				return reverse_iterator(it);
			}
			const_reverse_iterator rbegin() const
			{
				if (!this->size())
					return end();
				const_iterator it(this->m_tree.getMax(this->m_tree.getRoot()), &this->m_tree);
				return const_reverse_iterator(it);
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
				if (!this->size())
					return (true);
				return (false);
			}

			size_type size() const { return (this->m_tree.getSize()); }
			size_type max_size() const
			{
				return (std::numeric_limits<size_type>::max() / (sizeof(ft::Node<value_type>)));
			}
			allocator_type get_allocator() const { return this->m_alloc; }
			

			/*************************************************/
			/*                ELEMENT ACCESS                 */
			/*************************************************/

			mapped_type& operator[] (const key_type& k)
			{
				return (insert(ft::make_pair(k, T())).first->second);
			}

			mapped_type& at (const key_type& k)
			{
				node_ptr tmp = this->m_tree.searchTree(this->m_tree.getRoot(), k);
				if (tmp->pair_data.first != k)
					throw std::out_of_range("key not found");
				return tmp->pair_data.second;
			}
			
			const mapped_type& at (const key_type& k) const
			{
				node_ptr tmp = this->m_tree.searchTree(this->m_tree.getRoot(), k);
				if (tmp->pair_data.first != k)
					throw std::out_of_range("key not found");
				return tmp->pair_data.second;
			}

			/*************************************************/
			/*                   MODIFIERS                   */
			/*************************************************/

			pair<iterator,bool> insert (const value_type& val)
			{
				size_type	prevSize(this->m_tree.getSize());
				node_ptr	insertedNode = this->m_tree.insertNode(val);
				size_type	postSize(this->m_tree.getSize());

				bool ret = (prevSize == postSize);
				
				return ft::make_pair<iterator, bool>(iterator(insertedNode, &this->m_tree), ret);
			}

			iterator insert (iterator position, const value_type& val)
			{
				(void)position;
				iterator tmp = this->find(val.first);
				if (tmp != this->end())
					return (tmp);
				node_ptr insertedNode = this->m_tree.insertNode(val);
				return (iterator(insertedNode, &this->m_tree));
			}

			template <class InputIterator>
			void insert (InputIterator first, InputIterator last)
			{
				while (first != last)
				{
					this->m_tree.insertNode(ft::make_pair(first->first, first->second));
					first++;
				}
			}
			
			void erase (iterator position)
			{
				iterator it = position;
				this->m_tree.deleteNode((*it).first);
			}
			
			size_type erase (const key_type& k)
			{
				size_type	prevSize(this->m_tree.getSize());
				this->m_tree.deleteNode(k);
				size_type	postSize(this->m_tree.getSize());

				return (prevSize == postSize);
			}

		    void erase (iterator first, iterator last)
			{
				iterator it;

				for (; first != last ;)
				{
					it = first++;;
					this->m_tree.deleteNode((*it).first);
				}
			}

			void swap (map &toSwap)
			{
				this->m_tree.swap(toSwap.m_tree);
			}

			void clear()
			{
				this->m_tree.clear(this->m_tree.getRoot());
			}

			/*************************************************/
			/*                   OBSERVERS                   */
			/*************************************************/

			key_compare key_comp() const { return (this->m_compare); }
			value_compare value_comp() const { return value_compare(key_compare()); }

			/*************************************************/
			/*                   OPERATIONS                  */
			/*************************************************/

			iterator find (const key_type& k)
			{
				if (!this->empty())
				{
					node_ptr tmp = this->m_tree.searchTree(this->m_tree.getRoot(), k);
					if (tmp)
						return (iterator(tmp, &this->m_tree));
				}
				return (this->end());
			}

			const_iterator find (const key_type& k) const
			{
				if (!this->empty())
				{
					node_ptr tmp = this->m_tree.searchTree(this->m_tree.getRoot(), k);
					if (tmp)
						return (const_iterator(tmp, &this->m_tree));
				}
				return (this->end());
			}

			size_type count (const key_type& k)
			{
				const_iterator it = this->find(k);
					if (it != this->end())
						return (1);
				return (0);
			}
			
			iterator lower_bound (const key_type& k)
			{
				iterator it = this->begin();
				iterator ite = this->end();
				while (it != ite)
				{
					if (this->m_compare(it->first, k) <= 0)
						return (it);
					++it;
				}
				return (ite);
			}
			
			const_iterator lower_bound (const key_type& k) const
			{
				const_iterator it = this->begin();
				const_iterator ite = this->end();
				while (it != ite)
				{
					if (this->m_compare(it->first, k) <= 0)
						return (it);
					++it;
				}
				return (ite);
			}

			iterator upper_bound (const key_type& k)
			{
				iterator it = this->begin();
				iterator ite = this->end();
				while (it != ite)
				{
					if (it->first != k && this->m_compare(it->first, k) <= 0)
						return (it);
					++it;
				}
				return (ite);
			}

			const_iterator upper_bound (const key_type& k) const
			{
				const_iterator it = this->begin();
				const_iterator ite = this->end();
				while (it != ite)
				{
					if (it->first != k && this->m_compare(it->first, k) <= 0)
						return (it);
					++it;
				}
				return (ite);
			}

			pair<iterator, iterator> equal_range (const key_type& k)
			{
				return (ft::make_pair(this->lower_bound(k), this->upper_bound(k)));
			}

			pair<const_iterator, const_iterator> equal_range (const key_type& k) const
			{
				return (ft::make_pair(this->lower_bound(k), this->upper_bound(k)));
			}
					
			friend bool operator == (const map &lhs, const map &rhs) { return lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin()); }
			friend bool operator != (const map &lhs, const map &rhs) { return !(lhs == rhs); }
			friend bool operator <  (const map &lhs, const map &rhs) { return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()); }
			friend bool operator <= (const map &lhs, const map &rhs) { return !(rhs < lhs); }
			friend bool operator >  (const map &lhs, const map &rhs) { return rhs < lhs; }
			friend bool operator >= (const map &lhs, const map &rhs) { return !(lhs < rhs); }
	};
}
