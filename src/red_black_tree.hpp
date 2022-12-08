/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_black_tree.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 23:52:48 by ldurante          #+#    #+#             */
/*   Updated: 2022/12/08 20:36:17 by ldurante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <memory>
#include "pair.hpp"
#include "make_pair.hpp"
#include "swap.hpp"

#define _BLACK 0
#define _RED 1

namespace ft
{
	template <class value_type>
	struct Node
	{
		public:
			value_type		pair_data;
			Node			*parent;
			Node			*left;
			Node			*right;
			int				color;

			Node(): pair_data(), parent(NULL), left(NULL), right(NULL), color (_BLACK) {}
			Node(const value_type &pair_data): pair_data(pair_data), parent(NULL), left(NULL), right(NULL), color (_BLACK) {}
			Node(const Node &n): pair_data(n.pair_data), parent(n.parent), left(n.left), right(n.right), color (n.color) {}
			~Node() {}
			Node &operator = (const Node &n)
			{
				if (this != &n)
				{
					pair_data = n.pair_data;
					parent = n.parent;
					left = n.parent;
					right = n.parent;
					color = n.color;
				}
				return *this;
			}
	};

	template<class Value, class Key, class Mapped, class Alloc = std::allocator<Node<Value> > >
	class RBTree
	{
		public:

			typedef Value		value_type;
			typedef Key			key_type;
			typedef Mapped		mapped_type;
			typedef size_t		size_type;

			typedef Node<value_type>*		node_ptr;
			typedef typename Alloc::template rebind<Node<value_type> >::other	allocator_type;

		private:
			node_ptr		m_root;
			node_ptr		m_nullNode;
			size_type 		m_size;
			allocator_type	m_alloc;

				/*************************************************/
				/*                RBT CONSTRUCTORS               */
				/*************************************************/

		public:
			RBTree(const Alloc& alloc = allocator_type())
			{
				m_size = 0;
				m_alloc = alloc;
				m_nullNode = allocNode(value_type(), NULL);
				m_nullNode->color = _BLACK;
				m_root = m_nullNode;
			}

			RBTree(RBTree const &toCopy)
			{
				m_size = 0;
				m_nullNode = allocNode(value_type(), NULL);
				m_nullNode->color = _BLACK;
				m_root = m_nullNode;
				*this = toCopy;
			}

			~RBTree()
			{
				clear(m_root);
				m_alloc.destroy(m_nullNode);
				m_alloc.deallocate(m_nullNode, sizeof(Node<value_type>));	
			}

			RBTree &operator = (const RBTree &toCopy)
       		{				
				clear(m_root);
				copyTree(toCopy.m_root, toCopy);
				m_alloc	= toCopy.m_alloc;
				return *this;
			}

			/*************************************************/
			/*                ALLOC / DEALLOC                */
			/*************************************************/
		
		private:
			node_ptr	allocNode(value_type val, node_ptr parent)
			{
				node_ptr allocatedNode = m_alloc.allocate(sizeof(Node<value_type>));
				m_alloc.construct(allocatedNode, val);
				allocatedNode->parent = parent;
				allocatedNode->left = m_nullNode;
				allocatedNode->right = m_nullNode;
				allocatedNode->color = _RED;
				return allocatedNode;
			}

			void seekAndDestroy(node_ptr node)
			{
				if (node->parent)
				{
					if (node == node->parent->left)
						node->parent->left = m_nullNode;
					else if (node == node->parent->right)
						node->parent->right = m_nullNode;
				}
				else
					m_root = m_nullNode;
				m_alloc.destroy(node);
				m_alloc.deallocate(node, 1);
				m_size--;
			}

			/*************************************************/
			/*                    GETTERS                    */
			/*************************************************/
			
		public:
			node_ptr getRoot() const { return m_root; }
			node_ptr getNull() const { return m_nullNode; }
			size_t getSize() const { return m_size; }
			allocator_type getAlloc() const { return m_alloc; }

			node_ptr getMin(node_ptr node) const
			{
				while (node->left != m_nullNode)
					node = node->left;
				return node;
			}

			node_ptr getMax(node_ptr node) const
			{
				while (node->right != m_nullNode)
					node = node->right;
				return node;
			}

			/*************************************************/
			/*                SEARCH/CLEAR NODE              */
			/*************************************************/

			node_ptr searchTree(node_ptr node, key_type key) const
			{
				if (key == node->pair_data.first || node == m_nullNode)
					return node;
				if (key < node->pair_data.first)
					return searchTree(node->left, key);
				else return searchTree(node->right, key);
			}

			void clear(node_ptr node)
			{
				if (node != m_nullNode)
				{
					clear(node->left);
					clear(node->right);
					seekAndDestroy(node);
				}
			}

			/*************************************************/
			/*                  INSERT NODE                  */
			/*************************************************/

			node_ptr insertNode(value_type val)
			{
				if (!m_size)
				{
					m_root = allocNode(val, NULL);
					m_root->color = _BLACK;
					m_size++;
					return m_root;
				}
				else
				{
					node_ptr currentNode = m_root;
					node_ptr previousNode = m_root;
					while (currentNode != m_nullNode)
					{
						previousNode = currentNode;
						if (val.first == currentNode->pair_data.first)
								return currentNode;
						if  (val.first < currentNode->pair_data.first)
							currentNode = currentNode->left;
						else
							currentNode = currentNode->right;
					}
					if (val.first < previousNode->pair_data.first)
					{
						previousNode->left = allocNode(val, previousNode);
						currentNode = previousNode->left;
					}
					else
					{
						previousNode->right = allocNode(val, previousNode);
						currentNode = previousNode->right;
					}
					m_size++;
					if (!previousNode->parent)
						return currentNode;
					fixAfterInsert(currentNode);
					return currentNode;
				}
			}

			/*************************************************/
			/*                  DELETE NODE                  */
			/*************************************************/

			void	deleteNode(key_type key)
			{
				node_ptr tmp = searchTree(m_root, key);
				if (tmp == m_nullNode)
					return ;
				node_ptr A = tmp;
				int original_color = A->color;
				node_ptr B = NULL;
				if (tmp->left == m_nullNode) {
					B = tmp->right;
					transplantNode(tmp, tmp->right);
				}
				else if (tmp->right == m_nullNode) {
					B = tmp->left;
					transplantNode(tmp, tmp->left);
				}
				else
				{
					A = getMin(tmp->right);
					original_color = A->color;
					B = A->right;
					if (A->parent == tmp)
						B->parent = A;
					else
					{
						transplantNode(A, A->right);
						A->right = tmp->right;
						A->right->parent = A;
					}
					transplantNode(tmp, A);
					A->left = tmp->left;
					A->left->parent = A;
					A->color = tmp->color;
				}
				m_alloc.destroy(tmp);
				m_alloc.deallocate(tmp, 1);
				m_size--;
				if (original_color == _BLACK)
					fixAfterDelete(B);
			}

		private:
			/*************************************************/
			/*             FIXING DELETE/INSERT              */
			/*************************************************/

			void fixAfterDelete(node_ptr x)
			{
				while (x != m_root && x->color == _BLACK)
				{
					if (x == x->parent->left)
					{
						node_ptr w = x->parent->right;
						if (w->color == _RED)
						{
							w->color = _BLACK;
							x->parent->color = _RED;
							leftRotate (x->parent);
							w = x->parent->right;
						}
						if (w->left->color == _BLACK && w->right->color == _BLACK)
						{
							w->color = _RED;
							x = x->parent;
						} else
						{
							if (w->right->color == _BLACK)
							{
								w->left->color = _BLACK;
								w->color = _RED;
								rightRotate (w);
								w = x->parent->right;
							}
							w->color = x->parent->color;
							x->parent->color = _BLACK;
							w->right->color = _BLACK;
							leftRotate (x->parent);
							x = m_root;
						}
					}
					else
					{
						node_ptr w = x->parent->left;
						if (w->color == _RED)
						{
							w->color = _BLACK;
							x->parent->color = _RED;
							rightRotate (x->parent);
							w = x->parent->left;
						}
						if (w->right->color == _BLACK && w->left->color == _BLACK)
						{
							w->color = _RED;
							x = x->parent;
						} 
						else
						{
							if (w->left->color == _BLACK)
							{
								w->right->color = _BLACK;
								w->color = _RED;
								leftRotate (w);
								w = x->parent->left;
							}
							w->color = x->parent->color;
							x->parent->color = _BLACK;
							w->left->color = _BLACK;
							rightRotate (x->parent);
							x = m_root;
						}
					}
				}
				x->color = _BLACK;
				}

			void leftRotate(node_ptr n) 
			{
				node_ptr y = n->right;
				n->right = y->left;
				if (y->left != m_nullNode) 
					y->left->parent = n;
				y->parent = n->parent;
				if (n->parent == NULL) 
					this->m_root = y;
				else if (n == n->parent->left) 
					n->parent->left = y;
				else
					n->parent->right = y;
				y->left = n;
				n->parent = y;
			}

			void rightRotate(node_ptr n) 
			{
				node_ptr y = n->left;
				n->left = y->right;
				if (y->right != m_nullNode) 
					y->right->parent = n;
				y->parent = n->parent;
				if (n->parent == NULL) 
					this->m_root = y;
				else if (n == n->parent->right)
					n->parent->right = y;
				else
					n->parent->left = y;
				y->right = n;
				n->parent = y;
			}

			void transplantNode(node_ptr u, node_ptr v)
			{
				if (u->parent == NULL) 
					m_root = v;
				else if (u == u->parent->left)
					u->parent->left = v;
				else
					u->parent->right = v;
				v->parent = u->parent;
			}

			node_ptr fixAfterInsert(node_ptr k)
			{
				node_ptr u;
				while (k->parent->color == _RED) 
				{
					if (k->parent == k->parent->parent->right) 
					{
						u = k->parent->parent->left;
						if (u->color == _RED) 
						{
							u->color = _BLACK;
							k->parent->color = _BLACK;
							k->parent->parent->color = _RED;
							k = k->parent->parent;
						}
						else
						{
							if (k == k->parent->left) 
							{
								k = k->parent;
								rightRotate(k);
							}
							k->parent->color = _BLACK;
							k->parent->parent->color = _RED;
							leftRotate(k->parent->parent);
						}
					}
					else
					{
						u = k->parent->parent->right;
						if (u->color == _RED) 
						{
							u->color = _BLACK;
							k->parent->color = _BLACK;
							k->parent->parent->color = _RED;
							k = k->parent->parent;	
						}
						else
						{
							if (k == k->parent->right) 
							{
								k = k->parent;
								leftRotate(k);
							}
							k->parent->color = _BLACK;
							k->parent->parent->color = _RED;
							rightRotate(k->parent->parent);
						}
					}
					if (k == m_root) 
						break;
				}
				m_root->color = _BLACK;
				return (k);
			}

			/*************************************************/
			/*                 MISC FUNCTIONS                */
			/*************************************************/
		public:
			void swap(RBTree &tree)
			{
				ft::swap(m_root, tree.m_root);
				ft::swap(m_size, tree.m_size);
				ft::swap(m_nullNode, tree.m_nullNode);
				ft::swap(m_alloc, tree.m_alloc);
			}

		private:
			void copyTree(node_ptr node, const RBTree &tree)
			{
				if (node != tree.m_nullNode)
				{
					copyTree(node->left, tree);
					copyTree(node->right, tree);
					ft::pair<key_type, mapped_type> val(node->pair_data.first, node->pair_data.second);
					insertNode(val);
				}
			}
	};
}
