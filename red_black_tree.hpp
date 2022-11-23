/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_black_tree.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 23:52:48 by ldurante          #+#    #+#             */
/*   Updated: 2022/11/24 00:45:41 by ldurante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <memory>
#include "pair.hpp"
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

			Node(): pair_data(), parent(NULL), left(NULL), right(NULL), color (0) {}
			Node(const value_type &pair_data): pair_data(pair_data), parent(NULL), left(NULL), right(NULL), color (0) {}
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

	template <typename value_type, typename Alloc = std::allocator<value_type> >
	class RBTree
	{
		public:
			typedef Node<value_type>*	node_ptr;
			typedef typename Alloc::template rebind<Node<value_type> >::other		allocator_type;

			node_ptr		m_root;
			node_ptr		m_nullNode;
			allocator_type	m_alloc;
			size_t			m_size;
	
			/*************************************************/
			/*                RBT CONSTRUCTORS               */
			/*************************************************/

		public:
			RBTree(const Alloc& alloc = allocator_type())
			{
				m_size = 0;
				m_alloc = alloc;
				m_nullNode = allocNode(nullptr, value_type());
				m_nullNode->color = _BLACK;
				m_nullNode->left = NULL;
				m_nullNode->right = NULL;
				m_root = m_nullNode;
			}

			RBTree(RBTree const &toCopy) :
				m_root(toCopy.m_root),
				m_nullNode(toCopy.m_nullNode),
				m_alloc(toCopy.m_alloc),
				m_size(toCopy.m_size)
				{}

			~RBTree()
			{
				clear(m_root);
				m_alloc.destroy(m_nullNode);
				m_alloc.deallocate(m_nullNode, 1);	
			}

			RBTree &operator = (const RBTree &toCopy)
       		{				
				if (this != &toCopy)
				{
					m_root = toCopy.m_root;
					m_nullNode = toCopy.m_nullNode;
					m_alloc = toCopy.m_alloc;
					m_size = toCopy.m_size;
				}
          		return *this;
			}

		private:
			/*************************************************/
			/*                ALLOC / DEALLOC                */
			/*************************************************/

			node_ptr allocNode(node_ptr node, const value_type &key = value_type())
			{
				node_ptr allocatedNode;
				allocatedNode = m_alloc.allocate(1);
				m_alloc.construct(allocatedNode, key);
				allocatedNode->parent = node;
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
			}

		public:
			/*************************************************/
			/*                    GETTERS                    */
			/*************************************************/

			node_ptr getRoot() { return this->m_root; }			
			size_t getSize() const { return this->m_size; }

			node_ptr getMin(node_ptr node)
			{
				while (node->left != m_nullNode) 
					node = node->left;
				return node;
			}

			node_ptr getMax(node_ptr node)
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

			node_ptr prevNode(node_ptr node)
			{
				if (!node)
					return node;
				else if (node == m_nullNode)
					return getMax(m_root);
				else if (node == getMin(m_root))
					return nullptr;
				else if (node->left != m_nullNode)
					return getMin(node->left);
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

			node_ptr searchTree(node_ptr node, value_type key) const
			{
				if (node == m_nullNode || key.first == node->pair_data.first) 
					return node;
				if (key < node->pair_data) 
					return searchTree(node->left, key);
				return searchTree(node->right, key);
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
			
			node_ptr insertNode(const value_type &key) 
			{
				if (!m_size)
				{
					m_root = allocNode(NULL, key);
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
						if (key.first == currentNode->pair_data.first)
								return currentNode;
						if  (key.first < currentNode->pair_data.first)
							currentNode = currentNode->left;
						else
							currentNode = currentNode->right;
					}
					if (key.first < previousNode->pair_data.first)
					{
						previousNode->left = allocNode(previousNode, key);
						currentNode = previousNode->left;
					}
					else
					{
						previousNode->right = allocNode(previousNode, key);
						currentNode = previousNode->right;
					}
					m_size++;
					if (!previousNode->parent)
						return currentNode;
					return (fixAfterInsert(currentNode));
				}
			}

			/*************************************************/
			/*                  DELETE NODE                  */
			/*************************************************/

			void deleteNode(node_ptr node, value_type key) 
			{
				node_ptr z = m_nullNode;
				node_ptr x, y;
				while (node != m_nullNode)
				{
					if (node->pair_data.first == key.first) 
						z = node;
					if (node->pair_data.first <= key.first) 
						node = node->right;
					else
						node = node->left;
				}
				if (z == m_nullNode) 
					return;
				y = z;
				int y_original_color = y->color;
				if (z->left == m_nullNode) 
				{
					x = z->right;
					transplantNode(z, z->right);
				}
				else if (z->right == m_nullNode) 
				{
					x = z->left;
					transplantNode(z, z->left);
				}
				else
				{
					y = getMin(z->right);
					y_original_color = y->color;
					x = y->right;
					if (y->parent == z) 
						x->parent = y;
					else
					{
						transplantNode(y, y->right);
						y->right = z->right;
						y->right->parent = y;
					}

					transplantNode(z, y);
					y->left = z->left;
					y->left->parent = y;
					y->color = z->color;
				}
				m_alloc.destroy(z);
				m_alloc.deallocate(z, 1);
				if (y_original_color == _BLACK)
					fixAfterDelete(x);
			}

		private:
			/*************************************************/
			/*             FIXING DELETE/INSERT              */
			/*************************************************/

			void fixAfterDelete(node_ptr x) 
			{
				node_ptr s;
				while (x != m_root && x->color == _BLACK) 
				{
					if (x == x->parent->left) 
					{
						s = x->parent->right;
						if (s->color == _RED) 
						{
							s->color = _BLACK;
							x->parent->color = _RED;
							leftRotate(x->parent);
							s = x->parent->right;
						}

						if (s->left->color == _BLACK && s->right->color == _BLACK) 
						{
							s->color = _RED;
							x = x->parent;
						}
						else
						{
							if (s->right->color == _BLACK) 
							{
								s->left->color = _BLACK;
								s->color = _RED;
								rightRotate(s);
								s = x->parent->right;
							} 
							s->color = x->parent->color;
							x->parent->color = _BLACK;
							s->right->color = _BLACK;
							leftRotate(x->parent);
							x = m_root;
						}
					}
					else
					{
						s = x->parent->left;
						if (s->color == _RED) 
						{
							s->color = _BLACK;
							x->parent->color = _RED;
							rightRotate(x->parent);
							s = x->parent->left;
						}

						if (s->right->color == _BLACK && s->right->color == _BLACK) 
						{
							s->color = _RED;
							x = x->parent;
						}
						else
						{
							if (s->left->color == _BLACK) 
							{
								s->right->color = _BLACK;
								s->color = _RED;
								leftRotate(s);
								s = x->parent->left;
							}
							s->color = x->parent->color;
							x->parent->color = _BLACK;
							s->left->color = _BLACK;
							rightRotate(x->parent);
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
	};
}
