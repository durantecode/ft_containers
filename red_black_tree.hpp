/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_black_tree.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 23:52:48 by ldurante          #+#    #+#             */
/*   Updated: 2022/11/25 18:09:50 by ldurante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <memory>
#include "pair.hpp"
#include "make_pair.hpp"
#define _BLACK 0
#define _RED 1

namespace ft
{
	template <typename value_type>
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

	template<class Container, class Alloc = std::allocator<Node<typename Container::value_type> > >
	class RBTree
	{
		public:

			typedef typename Container::value_type			value_type;
			typedef typename Container::key_type			key_type;
			typedef typename Container::mapped_type			mapped_type;
			typedef typename Container::size_type			size_type;

			typedef Node<value_type>*						node_ptr;
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

			/*************************************************/
			/*                ALLOC / DEALLOC                */
			/*************************************************/
		
		private:
			node_ptr	allocNode(value_type val, node_ptr parent)
			{
				node_ptr allocatedNode = m_alloc.allocate(1);
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

			node_ptr getMin(node_ptr start) const
			{
				while (start->left != m_nullNode)
					start = start->left;
				return start;
			}

			node_ptr getMax(node_ptr start) const
			{
				while (start->right != m_nullNode)
					start = start->right;
				return start;
			}

			/*************************************************/
			/*             PREVIOUS / NEXT NODE              */
			/*************************************************/

			node_ptr nextNode(node_ptr start)
			{
				if (start == m_nullNode)
					return start;
				else if (start == getMax(m_root))
					return m_nullNode;
				else if (!start)
					return getMin(m_root);
				else if (start->right != m_nullNode)
					return getMin(start->right);
				else
				{
					node_ptr rval = start->parent;
					while (rval && start == rval->right)
					{
						start = rval;
						rval = rval->parent;
					}
					return rval;
				}
			}

			node_ptr nextNode(node_ptr start) const
			{
				if (start == m_nullNode)
					return start;
				else if (start == getMax(m_root))
					return m_nullNode;
				else if (!start)
					return getMin(m_root);
				else if (start->right != m_nullNode)
					return getMin(start->right);
				else
				{
					node_ptr rval = start->parent;
					while (rval && start == rval->right)
					{
						start = rval;
						rval = rval->parent;
					}
					return rval;
				}
			}

			node_ptr prevNode(node_ptr start)
			{
				if (!start)
					return start;
				else if (start == m_nullNode)
					return getMax(m_root);
				else if (start == getMin(m_root))
					return nullptr;
				else if (start->left != m_nullNode)
					return getMax(start->left);
				else
				{
					node_ptr rval = start->parent;
					while (rval && start == rval->left)
					{
						start = rval;
						rval = rval->parent;
					}
					return rval;
				}
			}

			node_ptr prevNode(node_ptr start) const
			{
				if (!start)
					return start;
				if (start == m_nullNode)
					return getMax(m_root);
				else if (start == getMin(m_root))
					return nullptr;
				else if (start->left != m_nullNode)
					return getMax(start->left);
				else
				{
					node_ptr rval = start->parent;
					while (rval && start == rval->left)
					{
						start = rval;
						rval = rval->parent;
					}
					return rval;
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
					m_root = allocNode(val, nullptr);
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

			/*************************************************/
			/*                 MISC FUNCTIONS                */
			/*************************************************/

			void copy(node_ptr node, const RBTree &tree)
			{
				if (node != tree.m_nullNode)
				{
					copy(node->left, tree);
					copy(node->right, tree);
					insert(ft::make_pair<key_type, mapped_type>(node->pair_data.first, node->pair_data.second));
				}
			}

			void swap(RBTree &tree)
			{
				node_ptr				tmpm_root  = tree.m_root;
				size_type 				tmpm_size  = tree.m_size;
				node_ptr				tmpm_nullNode  = tree.m_nullNode;
				allocator_type			tmpm_alloc = tree.m_alloc;

				tree.m_root  = m_root;
				tree.m_size  = m_size;
				tree.m_nullNode  = m_nullNode;
				tree.m_alloc = m_alloc;

				m_root = tmpm_root;
				m_size = tmpm_size;
				m_nullNode = tmpm_nullNode;
				m_alloc = tmpm_alloc;
			}

			bool is_end(node_ptr A) {
				if (A->left && A->left == m_nullNode && A->right && A->right == m_nullNode)
					return true;
				return false;
			}

			bool one_child(node_ptr A) {
				return ((A->left && A->left != m_nullNode) + (A->right && A->right != m_nullNode)) == 1;
			}
	};
}
