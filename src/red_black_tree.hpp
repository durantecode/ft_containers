/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_black_tree.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 23:52:48 by ldurante          #+#    #+#             */
/*   Updated: 2022/12/09 13:34:36 by ldurante         ###   ########.fr       */
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

	template<class Value, class Key, class Alloc = std::allocator<Node<Value> > >
	class RBTree
	{
		public:

			typedef Value		value_type;
			typedef Key			key_type;
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
			/*             PREVIOUS / NEXT NODE              */
			/*************************************************/

			node_ptr nextNode(node_ptr node)
			{
				if (node == m_nullNode)
					return node;
				else if (node == getMax(m_root))
					return m_nullNode;
				else if (!node)
					return getMin(m_root);
				else if (node->right != m_nullNode)
					return getMin(node->right);
				else
				{
					node_ptr next = node->parent;
					while (next && node == next->right)
					{
						node = next;
						next = next->parent;
					}
					return next;
				}
			}

			node_ptr nextNode(node_ptr node) const
			{
				if (node == m_nullNode)
					return node;
				else if (node == getMax(m_root))
					return m_nullNode;
				else if (!node)
					return getMin(m_root);
				else if (node->right != m_nullNode)
					return getMin(node->right);
				else
				{
					node_ptr next = node->parent;
					while (next && node == next->right)
					{
						node = next;
						next = next->parent;
					}
					return next;
				}
			}

			node_ptr prevNode(node_ptr node)
			{
				if (!node)
					return node;
				else if (node == m_nullNode)
					return getMax(m_root);
				else if (node == getMin(m_root))
					return nullptr;
				else if (node->left != m_nullNode)
					return getMax(node->left);
				else
				{
					node_ptr prev = node->parent;
					while (prev && node == prev->left)
					{
						node = prev;
						prev = prev->parent;
					}
					return prev;
				}
			}

			node_ptr prevNode(node_ptr node) const
			{
				if (!node)
					return node;
				if (node == m_nullNode)
					return getMax(m_root);
				else if (node == getMin(m_root))
					return nullptr;
				else if (node->left != m_nullNode)
					return getMax(node->left);
				else
				{
					node_ptr prev = node->parent;
					while (prev && node == prev->left)
					{
						node = prev;
						prev = prev->parent;
					}
					return prev;
				}
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
				node_ptr x = tmp;
				node_ptr y = NULL;
				int original_color = x->color;
				if (tmp->left == m_nullNode) {
					y = tmp->right;
					transplantNode(tmp, tmp->right);
				}
				else if (tmp->right == m_nullNode) {
					y = tmp->left;
					transplantNode(tmp, tmp->left);
				}
				else
				{
					x = getMin(tmp->right);
					original_color = x->color;
					y = x->right;
					if (x->parent == tmp)
						y->parent = x;
					else
					{
						transplantNode(x, x->right);
						x->right = tmp->right;
						x->right->parent = x;
					}
					transplantNode(tmp, x);
					x->left = tmp->left;
					x->left->parent = x;
					x->color = tmp->color;
				}
				m_alloc.destroy(tmp);
				m_alloc.deallocate(tmp, sizeof(Node<value_type>));
				m_size--;
				if (original_color == _BLACK)
					fixAfterDelete(y);
			}

		private:
			/*************************************************/
			/*             FIXING DELETE/INSERT              */
			/*************************************************/

			void fixAfterDelete(node_ptr node)
			{
				while (node != m_root && node->color == _BLACK)
				{
					if (node == node->parent->left)
					{
						node_ptr x = node->parent->right;
						if (x->color == _RED)
						{
							x->color = _BLACK;
							node->parent->color = _RED;
							leftRotate (node->parent);
							x = node->parent->right;
						}
						if (x->left->color == _BLACK && x->right->color == _BLACK)
						{
							x->color = _RED;
							node = node->parent;
						} else
						{
							if (x->right->color == _BLACK)
							{
								x->left->color = _BLACK;
								x->color = _RED;
								rightRotate (x);
								x = node->parent->right;
							}
							x->color = node->parent->color;
							node->parent->color = _BLACK;
							x->right->color = _BLACK;
							leftRotate (node->parent);
							node = m_root;
						}
					}
					else
					{
						node_ptr x = node->parent->left;
						if (x->color == _RED)
						{
							x->color = _BLACK;
							node->parent->color = _RED;
							rightRotate (node->parent);
							x = node->parent->left;
						}
						if (x->right->color == _BLACK && x->left->color == _BLACK)
						{
							x->color = _RED;
							node = node->parent;
						} 
						else
						{
							if (x->left->color == _BLACK)
							{
								x->right->color = _BLACK;
								x->color = _RED;
								leftRotate (x);
								x = node->parent->left;
							}
							x->color = node->parent->color;
							node->parent->color = _BLACK;
							x->left->color = _BLACK;
							rightRotate (node->parent);
							node = m_root;
						}
					}
				}
				node->color = _BLACK;
				}

			void leftRotate(node_ptr node) 
			{
				node_ptr y = node->right;
				node->right = y->left;
				if (y->left != m_nullNode) 
					y->left->parent = node;
				y->parent = node->parent;
				if (node->parent == NULL) 
					this->m_root = y;
				else if (node == node->parent->left) 
					node->parent->left = y;
				else
					node->parent->right = y;
				y->left = node;
				node->parent = y;
			}

			void rightRotate(node_ptr node) 
			{
				node_ptr y = node->left;
				node->left = y->right;
				if (y->right != m_nullNode) 
					y->right->parent = node;
				y->parent = node->parent;
				if (node->parent == NULL) 
					this->m_root = y;
				else if (node == node->parent->right)
					node->parent->right = y;
				else
					node->parent->left = y;
				y->right = node;
				node->parent = y;
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

			node_ptr fixAfterInsert(node_ptr node)
			{
				node_ptr uncle;
				while (node->parent->color == _RED) 
				{
					if (node->parent == node->parent->parent->right) 
					{
						uncle = node->parent->parent->left;
						if (uncle->color == _RED) 
						{
							uncle->color = _BLACK;
							node->parent->color = _BLACK;
							node->parent->parent->color = _RED;
							node = node->parent->parent;
						}
						else
						{
							if (node == node->parent->left) 
							{
								node = node->parent;
								rightRotate(node);
							}
							node->parent->color = _BLACK;
							node->parent->parent->color = _RED;
							leftRotate(node->parent->parent);
						}
					}
					else
					{
						uncle = node->parent->parent->right;
						if (uncle->color == _RED) 
						{
							uncle->color = _BLACK;
							node->parent->color = _BLACK;
							node->parent->parent->color = _RED;
							node = node->parent->parent;	
						}
						else
						{
							if (node == node->parent->right) 
							{
								node = node->parent;
								leftRotate(node);
							}
							node->parent->color = _BLACK;
							node->parent->parent->color = _RED;
							rightRotate(node->parent->parent);
						}
					}
					if (node == m_root) 
						break;
				}
				m_root->color = _BLACK;
				return (node);
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
					insertNode(ft::make_pair(node->pair_data.first, node->pair_data.second));
				}
			}
	};
}
