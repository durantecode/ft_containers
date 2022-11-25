/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 20:32:23 by ldurante          #+#    #+#             */
/*   Updated: 2022/11/25 16:41:07 by ldurante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "red_black_tree.hpp"
// #include "map_iterator.hpp"
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

			typedef ft::RBTree<value_type, allocator_type>		rbtree;
			typedef ft::Node<value_type>*						node_ptr;

			// typedef ft::bidirectionnal_iterator<rbtree, value_type>					iterator;
			// typedef ft::const_bidirectionnal_iterator<rbtree, value_type, iterator>		const_iterator;
			// typedef ft::ReverseMapIterator<iterator>								reverse_iterator;
			// typedef ft::ReverseMapIterator<const_iterator>							const_reverse_iterator;
			// typedef typename iterator_traits<iterator>::difference_type				difference_type;
			typedef ptrdiff_t				difference_type;
			
					
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
			key_compare		m_compare;
			rbtree			m_tree;

	public:
	class map_iter : public ft::iterator<ft::random_access_iterator_tag, T, difference_type, pointer, reference>
		{
		public:
			node_ptr	NodePtr;
			rbtree*		Tree;
	
			map_iter(): NodePtr(nullptr), Tree(nullptr) {}
			map_iter(const map_iter& cpy): NodePtr(cpy.NodePtr), Tree(cpy.Tree) {}
			map_iter(node_ptr ptr, rbtree* rbt): NodePtr(ptr), Tree(rbt) {}
			map_iter& operator=(const map_iter& rhs) {
				NodePtr = rhs.NodePtr;
				Tree	= rhs.Tree;
				return *this;
			}
			~map_iter(){}
			
		reference	operator*() const {return (*NodePtr).pair_data;}
		pointer		operator->() const {return &(operator*());}

		bool		operator== (const map_iter& rhs) const {return NodePtr == rhs.NodePtr;}
		bool		operator!= (const map_iter& rhs) const {return NodePtr != rhs.NodePtr;}
		map_iter&	operator++ () {
				NodePtr = Tree->nextNode(NodePtr);
				return *this;
			}
		map_iter	operator++ (int dummy) {
				(void)dummy;
				map_iter tmp(*this);
				NodePtr = Tree->nextNode(NodePtr);
				return tmp;
			}
		map_iter&	operator-- () {
				NodePtr = Tree->prevNode(NodePtr);
				return *this;
			}
		map_iter	operator-- (int dummy) {
				(void)dummy;
				map_iter tmp(*this);
				NodePtr = Tree->prevNode(NodePtr);
				return tmp;
			}
		map_iter&	operator+ (size_type offset) {
			for (size_type n = 0; n < offset; n++)
				operator++();
			return *this;
			}
		map_iter&	operator- (size_type offset) {
			for (size_type n = 0; n < offset; n++)
				operator--();
			return *this;
			}
		};

		class const_map_iter : public ft::iterator<ft::random_access_iterator_tag, T, difference_type, pointer, reference>
		{	
		public:	
			node_ptr			NodePtr;
			const rbtree*		Tree;
	
			const_map_iter(): NodePtr(nullptr), Tree(nullptr) {}
			const_map_iter(const map_iter& cpy): NodePtr(cpy.NodePtr), Tree(cpy.Tree) {}
			const_map_iter(const const_map_iter& cpy): NodePtr(cpy.NodePtr), Tree(cpy.Tree) {}
			const_map_iter(const node_ptr& ptr, rbtree* rbt): NodePtr(ptr), Tree(rbt) {}
			const_map_iter(const node_ptr& ptr, const rbtree* rbt): NodePtr(ptr), Tree(rbt) {}
			const_map_iter& operator=(const const_map_iter& rhs) {
				NodePtr = rhs.NodePtr;
				Tree	= rhs.Tree;
				return *this;
			}
			~const_map_iter(){}
			
		reference	operator*()  const {return (*NodePtr).pair_data;}
		pointer		operator->() const {return &(operator*());}

		bool		operator== (const const_map_iter& rhs) const {return NodePtr == rhs.NodePtr;}
		bool		operator!= (const const_map_iter& rhs) const {return NodePtr != rhs.NodePtr;}
		const_map_iter&	operator++ () {
				NodePtr = Tree->nextNode(NodePtr);
				return *this;
			}
		const_map_iter	operator++ (int dummy) {
				(void)dummy;
				const_map_iter tmp(*this);
				NodePtr = Tree->nextNode(NodePtr);
				return tmp;
			}
		const_map_iter&	operator-- () {
				NodePtr = Tree->prevNode(NodePtr);
				return *this;
			}
		const_map_iter	operator-- (int dummy) {
				(void)dummy;
				const_map_iter tmp(*this);
				NodePtr = Tree->prevNode(NodePtr);
				return tmp;
			}
		const_map_iter&	operator+ (size_type offset) {
			for (size_type n = 0; n < offset; n++)
				operator++();
			return *this;
			}
		const_map_iter&	operator- (size_type offset) {
			for (size_type n = 0; n < offset; n++)
				operator--();
			return *this;
			}
		};

		typedef map_iter				iterator;	
		typedef const_map_iter			const_iterator;

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

			// reverse_iterator rbegin()
			// {
			// 	return reverse_iterator(iterator(this->m_tree.getMax(this->m_tree.m_root), &this->m_tree));
			// }
			// const_reverse_iterator rbegin() const
			// {
			// 	return const_reverse_iterator(const_iterator(this->m_tree.getMax(this->m_tree.m_root), &this->m_tree));
			// }
			// reverse_iterator rend()
			// {
			// 	return reverse_iterator(iterator(NULL, &this->m_tree));
			// }
			// const_reverse_iterator rend() const
			// {
			// 	return const_reverse_iterator(const_iterator(NULL, &this->m_tree));
			// }

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
				// // node_ptr tmp = this->m_tree.searchTree(this->m_tree.m_root, ft::make_pair(k, T()));
				// // if (tmp->pair_data.first == k)
				// // 	return tmp->pair_data.second;
				return (insert(ft::make_pair(k, T())).first->second);
				// iterator tmp = find(k);
				// if (tmp != end())
				// 	return tmp->second;
				// ft:pair ft::make_pair(k, T());
				// std::cout << "K: " << k << std::endl;
				// std::cout << "VAL: " << T().first->second << std::endl;
				// node_ptr found = this->m_tree.searchTree(this->m_tree.m_root, ft::make_pair(k, T()));
				// if (found)
				// 	return (found->pair_data.second);
				// // ++this->m_size;
				// return (this->m_tree.insertNode(ft::make_pair(k, T()))->pair_data.second);
			}

			mapped_type& at (const key_type& k)
			{
				node_ptr tmp = this->m_tree.searchTree(this->m_tree.m_root, ft::make_pair(k, T()));
				if (tmp->pair_data.first != k)
					throw std::out_of_range("key not found");
				return tmp->pair_data.second;
			}
			
			const mapped_type& at (const key_type& k) const
			{
				node_ptr tmp = this->m_tree.searchTree(this->m_tree.m_root, ft::make_pair(k, T()));
				if (tmp->pair_data.first != k)
					throw std::out_of_range("key not found");
				return tmp->pair_data.second;
			}

			/*************************************************/
			/*                   MODIFIERS                   */
			/*************************************************/

			pair<iterator,bool> insert (const value_type& val)
			{
				std::cout << "VALLL: " << val.first << std::endl;
				// std::cout << "VALLL SECOND: " << val.second << std::endl;
				size_type	sizeBefore(this->m_tree.getSize());
				node_ptr	tmp = this->m_tree.insertNode(val);
				std::cout << "TMP FIRST: " << tmp->pair_data.first << std::endl;
				std::cout << "TMP SECOND: " << tmp->pair_data.second << std::endl;
				if (this->m_tree.getSize() != sizeBefore)
				{
					std::cout << "MUST INSERT: " << tmp->pair_data.first << std::endl;
					return ft::make_pair<iterator, bool>(iterator(tmp, &this->m_tree), true);
				}
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

			size_type count (const key_type& k) const
			{
				const_iterator it = find(k);
					if (it == end())
						return (1);
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
