/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_iterator.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 20:44:06 by ldurante          #+#    #+#             */
/*   Updated: 2022/12/09 17:04:10 by ldurante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "iterator_traits.hpp"
#include "red_black_tree.hpp"

namespace ft
{
		/*************************************************/
		/*                  MAP ITERATOR                 */
		/*************************************************/

	template <class Iter, class Tree>
	class MapIterator
	{
		public:
			typedef typename Iter::value_type			value_type;
			typedef typename Iter::pointer				pointer;
			typedef typename Iter::reference			reference;
			typedef typename Iter::difference_type		difference_type;
			typedef typename Iter::iterator_category	iterator_category;
			
			typedef Node<value_type>*					node_ptr;
			typedef Tree								rbtree;

		private:
			node_ptr	m_iterNode;
			rbtree*		m_iterTree;
	
		public:
			MapIterator(): m_iterNode(NULL), m_iterTree(NULL) {}
			MapIterator(const MapIterator &toCopy): m_iterNode(toCopy.getBase()), m_iterTree(toCopy.getTree()) {}
			MapIterator(node_ptr node, rbtree *tree): m_iterNode(node), m_iterTree(tree) {}
			MapIterator& operator=(const MapIterator &toCopy)
			{
				m_iterNode = toCopy.getBase();
				m_iterTree	= toCopy.getTree();
				return *this;
			}
			~MapIterator() {}
			
			node_ptr 	getBase() const { return (m_iterNode); }
			rbtree* 	getTree() const { return (m_iterTree); }
			reference	operator * () const { return (*m_iterNode).pair_data; }
			pointer		operator -> () const { return &(operator*()); }
			bool		operator == (const MapIterator &it) const { return (m_iterNode == it.getBase()); }
			bool		operator != (const MapIterator &it) const { return (m_iterNode != it.getBase()); }
	
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

	template <class Iter, class Tree>
	class ConstMapIterator
	{	
		public:
			typedef typename Iter::value_type			value_type;
			typedef typename Iter::pointer				pointer;
			typedef typename Iter::reference			reference;
			typedef typename Iter::difference_type		difference_type;
			typedef typename Iter::iterator_category	iterator_category;
			
			typedef Node<value_type>*					node_ptr;
			typedef Tree								rbtree;

		private:
			node_ptr			m_iterNode;
			const rbtree*		m_iterTree;
	
		public:
			ConstMapIterator(): m_iterNode(NULL), m_iterTree(NULL) {}
			ConstMapIterator(const MapIterator<Iter,Tree> &toCopy): m_iterNode(toCopy.getBase()), m_iterTree(toCopy.getTree()) {}
			ConstMapIterator(const ConstMapIterator &toCopy): m_iterNode(toCopy.getBase()), m_iterTree(toCopy.getTree()) {}
			ConstMapIterator(const node_ptr &node, rbtree *tree): m_iterNode(node), m_iterTree(tree) {}
			ConstMapIterator(const node_ptr &node, const rbtree *tree): m_iterNode(node), m_iterTree(tree) {}
			ConstMapIterator& operator=(const ConstMapIterator &toCopy)
			{
				m_iterNode = toCopy.getBase();
				m_iterTree	= toCopy.getTree();
				return *this;
			}
			~ConstMapIterator() {}
			
			node_ptr 		getBase() const { return (m_iterNode); }
			const rbtree* 	getTree() const { return (m_iterTree); }
			reference		operator * () const {return (*m_iterNode).pair_data; }
			pointer			operator -> () const {return &(operator*()); }
			bool			operator == (const ConstMapIterator& it) const { return (m_iterNode == it.getBase()); }
			bool			operator != (const ConstMapIterator& it) const { return (m_iterNode != it.getBase()); }

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
	
	template <class T>
	class ReverseMapIterator
	{
		public:
			typedef T												iterator_type;
			typedef typename iterator_traits<T>::value_type			value_type;
			typedef typename iterator_traits<T>::pointer			pointer;
			typedef typename iterator_traits<T>::reference			reference;
			typedef typename iterator_traits<T>::difference_type	difference_type;
			typedef typename iterator_traits<T>::iterator_category	iterator_category;
			
		private:
			iterator_type m_iter;
	
		public:
			ReverseMapIterator(): m_iter() {}
			ReverseMapIterator(iterator_type it): m_iter(it) {}
			~ReverseMapIterator() {}

			template <class Iter>
			ReverseMapIterator(const ReverseMapIterator<Iter> &toCopy): m_iter(toCopy.getBase()) {}
			
			template <class Iter>
			ReverseMapIterator& operator=(const ReverseMapIterator<Iter> &toCopy)
			{
				m_iter = toCopy.getBase();
				return *this;
			}
			
			iterator_type	getBase() const { return (m_iter); }
			reference		operator * () const { return (*m_iter); }
			pointer			operator -> () const { return &(operator*()); }
			bool			operator == (const ReverseMapIterator &it) const { return (m_iter == it.getBase()); }
			bool			operator != (const ReverseMapIterator &it) const { return (m_iter != it.getBase()); }
	
			ReverseMapIterator&	operator++ ()
			{
					--m_iter;
					return *this;
			}
			ReverseMapIterator	operator++ (int)
			{
					ReverseMapIterator tmp(*this);
					--m_iter;
					return tmp;
			}
			ReverseMapIterator&	operator-- ()
			{
					++m_iter;
					return *this;
			}
			ReverseMapIterator	operator-- (int)
			{
					ReverseMapIterator tmp(*this);
					++m_iter;
					return tmp;
			}
	};
}
