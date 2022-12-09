/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_iterator.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 20:44:06 by ldurante          #+#    #+#             */
/*   Updated: 2022/12/09 12:58:43 by ldurante         ###   ########.fr       */
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

					node_ptr	m_iterNode;
					rbtree*		m_iterTree;
			
					MapIterator(): m_iterNode(NULL), m_iterTree(NULL) {}
					MapIterator(const MapIterator& toCopy): m_iterNode(toCopy.m_iterNode), m_iterTree(toCopy.m_iterTree) {}
					MapIterator(node_ptr node, rbtree *tree): m_iterNode(node), m_iterTree(tree) {}
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

					node_ptr			m_iterNode;
					const rbtree*		m_iterTree;
			
					ConstMapIterator(): m_iterNode(NULL), m_iterTree(NULL) {}
					ConstMapIterator(const MapIterator<Iter,Tree> &toCopy): m_iterNode(toCopy.m_iterNode), m_iterTree(toCopy.m_iterTree) {}
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
			
			template <class Iter, class Tree>
			class ReverseMapIterator
			{
				public:
					typedef typename Iter::value_type			value_type;
					typedef typename Iter::pointer				pointer;
					typedef typename Iter::reference			reference;
					typedef typename Iter::difference_type		difference_type;
					typedef typename Iter::iterator_category	iterator_category;
					
					typedef Node<value_type>*					node_ptr;
					typedef Tree								rbtree;

					node_ptr	m_iterNode;
					rbtree*		m_iterTree;
			
					ReverseMapIterator(): m_iterNode(NULL), m_iterTree(NULL) {}
					ReverseMapIterator(const ReverseMapIterator& toCopy): m_iterNode(toCopy.m_iterNode), m_iterTree(toCopy.m_iterTree) {}
					ReverseMapIterator(node_ptr node, rbtree *tree): m_iterNode(node), m_iterTree(tree) {}
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
							ReverseMapIterator tmp(*this);
							m_iterNode = m_iterTree->nextNode(m_iterNode);
							return tmp;
					}
			};

				/*************************************************/
				/*           CONST REVERSE MAP ITERATOR          */
				/*************************************************/

			template <class Iter, class Tree>
			class ConstReverseMapIterator
			{	
				public:
					typedef typename Iter::value_type			value_type;
					typedef typename Iter::pointer				pointer;
					typedef typename Iter::reference			reference;
					typedef typename Iter::difference_type		difference_type;
					typedef typename Iter::iterator_category	iterator_category;
					
					typedef Node<value_type>*					node_ptr;
					typedef Tree								rbtree;
					
					node_ptr			m_iterNode;
					const rbtree*		m_iterTree;
			
					ConstReverseMapIterator(): m_iterNode(NULL), m_iterTree(NULL) {}
					ConstReverseMapIterator(const ReverseMapIterator<Iter,Tree> &toCopy): m_iterNode(toCopy.m_iterNode), m_iterTree(toCopy.m_iterTree) {}
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
							ConstReverseMapIterator tmp(*this);
							m_iterNode = m_iterTree->nextNode(m_iterNode);
							return tmp;
					}
			};
}
