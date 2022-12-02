/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 20:32:23 by ldurante          #+#    #+#             */
/*   Updated: 2022/12/02 01:14:07 by ldurante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "red_black_tree.hpp"
#include "equal.hpp"
#include "lexicographical_compare.hpp"
#include "iterator_traits.hpp"

namespace ft
{
	template <class Key, class T, class Compare = std::less<Key>,
			  class Alloc = std::allocator<std::pair<const Key, T> > >
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
			typedef std::random_access_iterator_tag		iter_tag;

			typedef Node<value_type>*								node_ptr;
			typedef RBTree<value_type, Key, T, allocator_type>		rbtree;
			
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

		public:

				/*************************************************/
				/*                  MAP ITERATOR                 */
				/*************************************************/

			class MapIterator : public ft::iterator<iter_tag, T, difference_type, pointer, reference>
			{
				public:
					node_ptr	m_iterNode;
					rbtree*		m_iterTree;
			
					MapIterator(): m_iterNode(NULL), m_iterTree(NULL) {}
					MapIterator(const MapIterator& toCopy): m_iterNode(toCopy.m_iterNode), m_iterTree(toCopy.m_iterTree) {}
					MapIterator(node_ptr node, rbtree* tree): m_iterNode(node), m_iterTree(tree) {}
					MapIterator& operator=(const MapIterator& toCopy)
					{
						m_iterNode = toCopy.m_iterNode;
						m_iterTree	= toCopy.m_iterTree;
						return *this;
					}
					~MapIterator() {}
					
					node_ptr 	getBase() const { return (m_iterNode); }
					reference	operator * () const { return (*m_iterNode).pair_data; }
					pointer		operator -> () const { return &(operator*()); }
					bool		operator == (const MapIterator& toCopy) const { return (m_iterNode == toCopy.m_iterNode); }
					bool		operator != (const MapIterator& toCopy) const { return (m_iterNode != toCopy.m_iterNode); }
			
					MapIterator&	operator++ ()
					{
							m_iterNode = m_iterTree->nextNode(m_iterNode);
							return *this;
					}
					MapIterator	operator++ (int)
					{
							MapIterator tmp(*this);
							m_iterNode = m_iterTree->nextNode(m_iterNode);
							return tmp;
					}
					MapIterator&	operator-- ()
					{
							m_iterNode = m_iterTree->prevNode(m_iterNode);
							return *this;
					}
					MapIterator	operator-- (int)
					{
							MapIterator tmp(*this);
							m_iterNode = m_iterTree->prevNode(m_iterNode);
							return tmp;
					}
			};

				/*************************************************/
				/*               CONST MAP ITERATOR              */
				/*************************************************/

			class ConstMapIterator : public ft::iterator<iter_tag, T, difference_type, pointer, reference>
			{	
				public:	
					node_ptr			m_iterNode;
					const rbtree*		m_iterTree;
			
					ConstMapIterator(): m_iterNode(NULL), m_iterTree(NULL) {}
					ConstMapIterator(const MapIterator &toCopy): m_iterNode(toCopy.m_iterNode), m_iterTree(toCopy.m_iterTree) {}
					ConstMapIterator(const ConstMapIterator &toCopy): m_iterNode(toCopy.m_iterNode), m_iterTree(toCopy.m_iterTree) {}
					ConstMapIterator(const node_ptr &node, rbtree *tree): m_iterNode(node), m_iterTree(tree) {}
					ConstMapIterator(const node_ptr &node, const rbtree *tree): m_iterNode(node), m_iterTree(tree) {}
					ConstMapIterator& operator=(const ConstMapIterator &toCopy)
					{
						m_iterNode = toCopy.m_iterNode;
						m_iterTree	= toCopy.m_iterTree;
						return *this;
					}
					~ConstMapIterator() {}
					
					node_ptr 	getBase() const { return (m_iterNode); }
					reference	operator * () const {return (*m_iterNode).pair_data; }
					pointer		operator -> () const {return &(operator*()); }
					bool		operator == (const ConstMapIterator& it) const { return (m_iterNode == it.m_iterNode); }
					bool		operator != (const ConstMapIterator& it) const { return (m_iterNode != it.m_iterNode); }

					ConstMapIterator&	operator++ ()
					{
							m_iterNode = m_iterTree->nextNode(m_iterNode);
							return *this;
					}
					ConstMapIterator	operator++ (int)
					{
							ConstMapIterator tmp(*this);
							m_iterNode = m_iterTree->nextNode(m_iterNode);
							return tmp;
					}
					ConstMapIterator&	operator-- ()
					{
							m_iterNode = m_iterTree->prevNode(m_iterNode);
							return *this;
					}
					ConstMapIterator	operator-- (int)
					{
							ConstMapIterator tmp(*this);
							m_iterNode = m_iterTree->prevNode(m_iterNode);
							return tmp;
					}
			};

				/*************************************************/
				/*             REVERSE MAP ITERATOR              */
				/*************************************************/

			class ReverseMapIterator : public ft::iterator<iter_tag, T, difference_type, pointer, reference>
			{
				public:
					node_ptr	m_iterNode;
					rbtree*		m_iterTree;
			
					ReverseMapIterator(): m_iterNode(NULL), m_iterTree(NULL) {}
					ReverseMapIterator(const ReverseMapIterator& toCopy): m_iterNode(toCopy.m_iterNode), m_iterTree(toCopy.m_iterTree) {}
					ReverseMapIterator(node_ptr node, rbtree* tree): m_iterNode(node), m_iterTree(tree) {}
					ReverseMapIterator& operator=(const ReverseMapIterator& toCopy)
					{
						m_iterNode = toCopy.m_iterNode;
						m_iterTree	= toCopy.m_iterTree;
						return *this;
					}
					~ReverseMapIterator() {}
					
					node_ptr 	getBase() const { return (m_iterNode); }
					reference	operator * () const { return (*m_iterNode).pair_data; }
					pointer		operator -> () const { return &(operator*()); }
					bool		operator == (const ReverseMapIterator& toCopy) const { return (m_iterNode == toCopy.m_iterNode); }
					bool		operator != (const ReverseMapIterator& toCopy) const { return (m_iterNode != toCopy.m_iterNode); }
			
					ReverseMapIterator&	operator++ ()
					{
							m_iterNode = m_iterTree->prevNode(m_iterNode);
							return *this;
					}
					ReverseMapIterator	operator++ (int)
					{
							ReverseMapIterator tmp(*this);
							m_iterNode = m_iterTree->prevNode(m_iterNode);
							return tmp;
					}
					ReverseMapIterator&	operator-- ()
					{
							m_iterNode = m_iterTree->nextNode(m_iterNode);
							return *this;
					}
					ReverseMapIterator	operator-- (int)
					{
							MapIterator tmp(*this);
							m_iterNode = m_iterTree->nextNode(m_iterNode);
							return tmp;
					}
			};

				/*************************************************/
				/*           CONST REVERSE MAP ITERATOR          */
				/*************************************************/

			class ConstReverseMapIterator : public ft::iterator<iter_tag, T, difference_type, pointer, reference>
			{	
				public:	
					node_ptr			m_iterNode;
					const rbtree*		m_iterTree;
			
					ConstReverseMapIterator(): m_iterNode(NULL), m_iterTree(NULL) {}
					ConstReverseMapIterator(const ReverseMapIterator &toCopy): m_iterNode(toCopy.m_iterNode), m_iterTree(toCopy.m_iterTree) {}
					ConstReverseMapIterator(const ConstReverseMapIterator &toCopy): m_iterNode(toCopy.m_iterNode), m_iterTree(toCopy.m_iterTree) {}
					ConstReverseMapIterator(const node_ptr &node, rbtree *tree): m_iterNode(node), m_iterTree(tree) {}
					ConstReverseMapIterator(const node_ptr &node, const rbtree *tree): m_iterNode(node), m_iterTree(tree) {}
					ConstReverseMapIterator& operator=(const ConstReverseMapIterator &toCopy)
					{
						m_iterNode = toCopy.m_iterNode;
						m_iterTree	= toCopy.m_iterTree;
						return *this;
					}
					~ConstReverseMapIterator() {}
					
					node_ptr 	getBase() const { return (m_iterNode); }
					reference	operator * () const {return (*m_iterNode).pair_data; }
					pointer		operator -> () const {return &(operator*()); }
					bool		operator == (const ConstReverseMapIterator& it) const { return (m_iterNode == it.m_iterNode); }
					bool		operator != (const ConstReverseMapIterator& it) const { return (m_iterNode != it.m_iterNode); }

					ConstReverseMapIterator&	operator++ ()
					{
							m_iterNode = m_iterTree->prevNode(m_iterNode);
							return *this;
					}
					ConstReverseMapIterator	operator++ (int)
					{
							ConstReverseMapIterator tmp(*this);
							m_iterNode = m_iterTree->prevNode(m_iterNode);
							return tmp;
					}
					ConstReverseMapIterator&	operator-- ()
					{
							m_iterNode = m_iterTree->nextNode(m_iterNode);
							return *this;
					}
					ConstReverseMapIterator	operator-- (int)
					{
							ConstMapIterator tmp(*this);
							m_iterNode = m_iterTree->nextNode(m_iterNode);
							return tmp;
					}
			};

			typedef	MapIterator					iterator;
			typedef ConstMapIterator			const_iterator;
			typedef ReverseMapIterator			reverse_iterator;
			typedef ConstReverseMapIterator		const_reverse_iterator;

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
			{

			}

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
				return reverse_iterator(this->m_tree.getMax(this->m_tree.getRoot()), &this->m_tree);
			}
			const_reverse_iterator rbegin() const
			{
				if (!this->size())
					return end();
				return const_reverse_iterator(this->m_tree.getMax(this->m_tree.getRoot()), &this->m_tree);
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
			friend bool operator >  (const map &lhs, const map &rhs) { return rhs < lhs; }
			friend bool operator >= (const map &lhs, const map &rhs) { return !(lhs < rhs); }
			friend bool operator <= (const map &lhs, const map &rhs) { return !(rhs < lhs); }
	};
}
