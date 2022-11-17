/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_black_tree.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 23:52:48 by ldurante          #+#    #+#             */
/*   Updated: 2022/11/18 00:28:31 by ldurante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "pair.hpp"
#define _BLACK 0
#define _RED 1

// class to represent a node in the tree
namespace ft
{
	template <class T>
	class Node
	{
		public:
			T		pair_data; 	// holds the key
			Node	*parent; 	// pointer to the parent
			Node	*left; 		// pointer to left child
			Node	*right; 	// pointer to right child
			int		color;		// 1 -> Red, 0 -> Black

			Node(): pair_data(), parent(nullptr), left(nullptr), right(nullptr), color (0) {}
			Node(const T &pair_data): pair_data(pair_data), parent(nullptr), left(nullptr), right(nullptr), color (0) {}
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
			typedef Node<value_type>		*NodePtr;

		public:
			NodePtr m_root;
			NodePtr TNULL;
	
			RBTree() 
			{
				TNULL = new Node<value_type>;
				TNULL->color = _BLACK;
				TNULL->left = nullptr;
				TNULL->right = nullptr;
				m_root = TNULL;
			}

			RBTree(RBTree const &toCopy) :
				m_root(toCopy.m_root),
				TNULL(toCopy.TNULL)
				{}

			~RBTree() {}

			RBTree &operator = (const RBTree &toCopy)
       		{

				if (this != &toCopy)
				{
					m_root = toCopy.m_root;
					TNULL = toCopy.TNULL;
				}
          		return *this;
			}

			// search the tree for the key k
			// and return the corresponding node
			NodePtr searchTree(value_type key) 
			{
				return searchTreeAux(this->m_root, key);
			}

			// find the node with the minimum key
			NodePtr minimum(NodePtr node) 
			{
				while (node->left != TNULL) 
					node = node->left;
				return node;
			}

			// find the node with the maximum key
			NodePtr maximum(NodePtr node) 
			{
				while (node->right != TNULL) 
					node = node->right;
				return node;
			}

			// find the successor of a given node
			NodePtr successor(NodePtr x) 
			{
				// if the right subtree is not null,
				// the successor is the leftmost node in the
				// right subtree
				if (x->right != TNULL) 
					return minimum(x->right);
				// else it is the lowest ancestor of x whose
				// left child is also an ancestor of x.
				NodePtr y = x->parent;
				while (y != TNULL && x == y->right) 
				{
					x = y;
					y = y->parent;
				}
				return y;
			}

			// find the predecessor of a given node
			NodePtr predecessor(NodePtr x) 
			{
				// if the left subtree is not null,
				// the predecessor is the rightmost node in the 
				// left subtree
				if (x->left != TNULL) 
					return maximum(x->left);

				NodePtr y = x->parent;
				while (y != TNULL && x == y->left) 
				{
					x = y;
					y = y->parent;
				}
				return y;
			}

			// rotate left at node x
			void leftRotate(NodePtr x) 
			{
				NodePtr y = x->right;
				x->right = y->left;
				if (y->left != TNULL) 
					y->left->parent = x;
				y->parent = x->parent;
				if (x->parent == nullptr) 
					this->m_root = y;
				else if (x == x->parent->left) 
					x->parent->left = y;
				else
					x->parent->right = y;
				y->left = x;
				x->parent = y;
			}

			// rotate right at node x
			void rightRotate(NodePtr x) 
			{
				NodePtr y = x->left;
				x->left = y->right;
				if (y->right != TNULL) 
					y->right->parent = x;
				y->parent = x->parent;
				if (x->parent == nullptr) 
					this->m_root = y;
				else if (x == x->parent->right)
					x->parent->right = y;
				else
					x->parent->left = y;
				y->right = x;
				x->parent = y;
			}

			// insert the key to the tree in its appropriate position
			// and fix the tree
			NodePtr insert(const value_type &key) 
			{
				// Ordinary Binary Search Insertion
				NodePtr node = new Node<value_type>(key);
				node->parent = new Node<value_type>();
				node->left = TNULL;
				node->right = TNULL;
				node->color = _RED; // new node must be red

				NodePtr y = nullptr;
				NodePtr x = this->m_root;

				while (x != TNULL) 
				{
					y = x;
					if (node->pair_data < x->pair_data) 
						x = x->left;
					else
						x = x->right;
				}

				// y is parent of x
				node->parent = y;
				if (y == nullptr) 
					m_root = node;
				else if (node->pair_data < y->pair_data) 
					y->left = node;
				else
					y->right = node;

				// if new node is a m_root node, simply return
				if (node->parent == nullptr)
				{
					node->color = _BLACK;
					return node;
				}

				// if the grandparent is null, simply return
				if (node->parent->parent == nullptr) 
					return node;

				// Fix the tree
				return (fixAfterInsert(node));
			}

			NodePtr getRoot()
			{
				return this->m_root;
			}

			NodePtr getEnd()
			{
				NodePtr tmp = m_root;
				while (tmp->right != TNULL) 
				{
					tmp = tmp->right;
				}
				return tmp->right;
			}

			// delete the node from the tree
			void deleteNode(value_type key)
			{
				deleteNodeAux(this->m_root, key);
			}

			NodePtr searchTreeAux(NodePtr node, value_type key) 
			{
				if (node == TNULL || key == node->pair_data) 
					return node;
				if (key < node->pair_data) 
					return searchTreeAux(node->left, key);
				return searchTreeAux(node->right, key);
			}

			// fix the rb tree modified by the delete operation
			void fixAfterDelete(NodePtr x) 
			{
				NodePtr s;
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

			void rbTransplant(NodePtr u, NodePtr v)
			{
				if (u->parent == nullptr) 
					m_root = v;
				else if (u == u->parent->left)
					u->parent->left = v;
				else
					u->parent->right = v;
				v->parent = u->parent;
			}

			void deleteNodeAux(NodePtr node, value_type key) 
			{
				// find the node containing key
				NodePtr z = TNULL;
				NodePtr x, y;
				while (node != TNULL)
				{
					if (node->pair_data == key) 
						z = node;
					if (node->pair_data <= key) 
						node = node->right;
					else
						node = node->left;
				}

				if (z == TNULL) 
				{
					std::cout<<"Couldn't find key in the tree"<<std::endl;
					return;
				} 

				y = z;
				int y_original_color = y->color;
				if (z->left == TNULL) 
				{
					x = z->right;
					rbTransplant(z, z->right);
				}
				else if (z->right == TNULL) 
				{
					x = z->left;
					rbTransplant(z, z->left);
				}
				else
				{
					y = minimum(z->right);
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
			NodePtr fixAfterInsert(NodePtr k)
			{
				NodePtr u;
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
