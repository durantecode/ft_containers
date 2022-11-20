/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_black_tree.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 23:52:48 by ldurante          #+#    #+#             */
/*   Updated: 2022/11/20 01:18:44 by ldurante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "pair.hpp"
#define _BLACK 0
#define _RED 1

// class to represent a node in the tree
namespace ft
{
	template <class value_type>
	struct Node
	{
		public:
			value_type		pair_data; 	// holds the key
			Node			*parent; 	// pointer to the parent
			Node			*left; 		// pointer to left child
			Node			*right; 	// pointer to right child
			int				color;		// 1 -> Red, 0 -> Black

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

	// class RBTree implements the operations in Red Black Tree
	template <class value_type>
	class RBTree
	{
		private:
			typedef Node<value_type>*	node_ptr;

		public:
			node_ptr m_root;
			node_ptr m_nullNode;
	
			RBTree() 
			{
				m_nullNode = new Node<value_type>;
				m_nullNode->color = _BLACK;
				m_nullNode->left = NULL;
				m_nullNode->right = NULL;
				m_root = m_nullNode;
			}

			RBTree(RBTree const &toCopy) :
				m_root(toCopy.m_root),
				m_nullNode(toCopy.m_nullNode)
				{}

			~RBTree() {}

			RBTree &operator = (const RBTree &toCopy)
       		{				
				if (this != &toCopy)
				{
					m_root = toCopy.m_root;
					m_nullNode = toCopy.m_nullNode;
				}
          		return *this;
			}

			// search the tree for the key k
			// and return the corresponding node
			node_ptr searchTree(value_type key) 
			{
				return searchTreeAux(this->m_root, key);
			}

			// find the node with the minNode key
			node_ptr minNode(node_ptr node) 
			{
				while (node->left != m_nullNode) 
					node = node->left;
				return node;
			}

			// find the node with the maxNode key
			node_ptr maxNode(node_ptr node) 
			{
				while (node->right != m_nullNode) 
					node = node->right;
				return node;
			}

			// rotate left at node n
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

			// rotate right at node n
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

			// insert the key to the tree in its appropriate position
			// and fix the tree
			node_ptr insert(const value_type &key) 
			{
				// Ordinary Binary Search Insertion
				node_ptr node = new Node<value_type>(key);
				node->parent = new Node<value_type>();
				node->left = m_nullNode;
				node->right = m_nullNode;
				node->color = _RED; // new node must be red

				node_ptr y = NULL;
				node_ptr x = this->m_root;

				while (x != m_nullNode) 
				{
					y = x;
					if (node->pair_data < x->pair_data) 
						x = x->left;
					else
						x = x->right;
				}

				// y is parent of x
				node->parent = y;
				if (y == NULL) 
					m_root = node;
				else if (node->pair_data < y->pair_data) 
					y->left = node;
				else
					y->right = node;

				// if new node is a m_root node, simply return
				if (node->parent == NULL)
				{
					node->color = _BLACK;
					return node;
				}

				// if the grandparent is null, simply return
				if (node->parent->parent == NULL) 
					return node;

				// Fix the tree
				return (fixAfterInsert(node));
			}

			node_ptr getRoot()
			{
				return this->m_root;
			}

			// delete the node from the tree
			void deleteNode(value_type key)
			{
				deleteNodeAux(this->m_root, key);
			}

			node_ptr searchTreeAux(node_ptr node, value_type key) 
			{
				if (node == m_nullNode || key == node->pair_data) 
					return node;
				if (key < node->pair_data) 
					return searchTreeAux(node->left, key);
				return searchTreeAux(node->right, key);
			}

			// fix the rb tree modified by the delete operation
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
							// case 3.1
							s->color = _BLACK;
							x->parent->color = _RED;
							leftRotate(x->parent);
							s = x->parent->right;
						}

						if (s->left->color == _BLACK && s->right->color == _BLACK) 
						{
							// case 3.2
							s->color = _RED;
							x = x->parent;
						}
						else
						{
							if (s->right->color == _BLACK) 
							{
								// case 3.3
								s->left->color = _BLACK;
								s->color = _RED;
								rightRotate(s);
								s = x->parent->right;
							} 

							// case 3.4
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
							// case 3.1
							s->color = _BLACK;
							x->parent->color = _RED;
							rightRotate(x->parent);
							s = x->parent->left;
						}

						if (s->right->color == _BLACK && s->right->color == _BLACK) 
						{
							// case 3.2
							s->color = _RED;
							x = x->parent;
						}
						else
						{
							if (s->left->color == _BLACK) 
							{
								// case 3.3
								s->right->color = _BLACK;
								s->color = _RED;
								leftRotate(s);
								s = x->parent->left;
							} 

							// case 3.4
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

			void rbTransplant(node_ptr u, node_ptr v)
			{
				if (u->parent == NULL) 
					m_root = v;
				else if (u == u->parent->left)
					u->parent->left = v;
				else
					u->parent->right = v;
				v->parent = u->parent;
			}

			void deleteNodeAux(node_ptr node, value_type key) 
			{
				// find the node containing key
				node_ptr z = m_nullNode;
				node_ptr x, y;
				while (node != m_nullNode)
				{
					if (node->pair_data == key) 
						z = node;
					if (node->pair_data <= key) 
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
					rbTransplant(z, z->right);
				}
				else if (z->right == m_nullNode) 
				{
					x = z->left;
					rbTransplant(z, z->left);
				}
				else
				{
					y = minNode(z->right);
					y_original_color = y->color;
					x = y->right;
					if (y->parent == z) 
						x->parent = y;
					else
					{
						rbTransplant(y, y->right);
						y->right = z->right;
						y->right->parent = y;
					}

					rbTransplant(z, y);
					y->left = z->left;
					y->left->parent = y;
					y->color = z->color;
				}
				delete z;
				if (y_original_color == _BLACK)
					fixAfterDelete(x);
			}
			
			// fix the red-black tree
			node_ptr fixAfterInsert(node_ptr k)
			{
				node_ptr u;
				while (k->parent->color == _RED) 
				{
					if (k->parent == k->parent->parent->right) 
					{
						u = k->parent->parent->left; // uncle
						if (u->color == _RED) 
						{
							// case 3.1
							u->color = _BLACK;
							k->parent->color = _BLACK;
							k->parent->parent->color = _RED;
							k = k->parent->parent;
						}
						else
						{
							if (k == k->parent->left) 
							{
								// case 3.2.2
								k = k->parent;
								rightRotate(k);
							}
							// case 3.2.1
							k->parent->color = _BLACK;
							k->parent->parent->color = _RED;
							leftRotate(k->parent->parent);
						}
					}
					else
					{
						u = k->parent->parent->right; // uncle

						if (u->color == _RED) 
						{
							// mirror case 3.1
							u->color = _BLACK;
							k->parent->color = _BLACK;
							k->parent->parent->color = _RED;
							k = k->parent->parent;	
						}
						else
						{
							if (k == k->parent->right) 
							{
								// mirror case 3.2.2
								k = k->parent;
								leftRotate(k);
							}
							// mirror case 3.2.1
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
