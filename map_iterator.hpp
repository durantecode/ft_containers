/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_iterator.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 21:58:48 by ldurante          #+#    #+#             */
/*   Updated: 2022/11/22 20:50:38 by ldurante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "iterator_traits.hpp"
#include "red_black_tree.hpp"

namespace ft
{
			/*************************************************/
			/*                  MAP_ITERATOR                 */
			/*************************************************/
	
	template <class T>
	class MapIterator
	{
		public:
			typedef T									value_type;
			typedef T*									pointer;
			typedef T&									reference;
			typedef const T*							const_pointer;
			typedef const T&							const_reference;
			typedef ft::RBTree<value_type>*				rbtree_ptr;
			typedef ft::Node<value_type>*				node_ptr;
			typedef std::bidirectional_iterator_tag		iterator_category;
			typedef std::ptrdiff_t						difference_type;
			typedef size_t								size_type;

		private:
			node_ptr 		m_currentNode;
			rbtree_ptr		m_tree;
		
		public:
			MapIterator() : m_currentNode(0) {}
			MapIterator(node_ptr ptr, rbtree_ptr tree) : m_currentNode(ptr), m_tree(tree) {}
			MapIterator(MapIterator const &toCopy) : m_currentNode(toCopy.m_currentNode) {}
			~MapIterator() {}
			MapIterator &operator = (MapIterator const &toCopy)
			{
				this->m_currentNode = toCopy.m_currentNode;
				return (*this);
			}

			reference operator * () { return (this->m_currentNode->pair_data); }
			const_reference operator * () const { return (this->m_currentNode->pair_data); }
			pointer operator -> () { return (&this->m_currentNode->pair_data); }
			const_pointer operator -> () const { return (&this->m_currentNode->pair_data); }

			MapIterator& operator ++ ()
			{
				this->m_currentNode = nextNode(this->m_currentNode);
				return (*this);
			}
			MapIterator operator ++ (int)
			{
				MapIterator it(*this);
				this->m_currentNode = nextNode(this->m_currentNode);
				return it;
			}
			MapIterator& operator -- ()
			{
				this->m_currentNode = prevNode(this->m_currentNode);
				return (*this);
			}
			MapIterator operator -- (int)
			{
				MapIterator it(*this);
				this->m_currentNode = prevNode(this->m_currentNode);
				return it;
			}
			// MapIterator& operator + (size_type offset)
			// {
			// 	for (size_type n = 0; n < offset; n++)
			// 		operator++();
			// 	return *this;
			// }
			// MapIterator&	operator- (size_type offset)
			// {
			// 	for (size_type n = 0; n < offset; n++)
			// 		operator--();
			// 	return *this;
			// }
			bool operator == (const MapIterator &it) const { return (this->m_currentNode == it.m_currentNode); }
			bool operator != (const MapIterator &it) const { return (this->m_currentNode != it.m_currentNode); }
			bool operator > (const MapIterator &it) const { return (this->m_currentNode > it.m_currentNode); }
			bool operator >= (const MapIterator &it) const { return (this->m_currentNode >= it.m_currentNode); }
			bool operator < (const MapIterator &it) const { return (this->m_currentNode < it.m_currentNode); }
			bool operator <= (const MapIterator &it) const { return (this->m_currentNode <= it.m_currentNode); }

		private:
			node_ptr getFirst(node_ptr node) 
			{
				while (node->left->left) 
					node = node->left;
				return node;
			}

			node_ptr getLast(node_ptr node) 
			{
				while (node->right->right) 
					node = node->right;
				return node;
			}

			node_ptr nextNode(node_ptr node)
			{
				if (node == this->m_tree->m_nullNode)
					return node;
				else if (node == getLast(this->m_tree->m_root))
					return this->m_tree->m_nullNode;
				else if (!node)
					return getFirst(this->m_tree->m_root);
				else if (node->right != this->m_tree->m_nullNode)
					return getFirst(node->right);
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
				else if (node == this->m_tree->m_nullNode)
					return getLast(this->m_tree->m_root);
				else if (node == getFirst(this->m_tree->m_root))
					return nullptr;
				else if (node->left != this->m_tree->m_nullNode)
					return getFirst(node->left);
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
	};

			/*************************************************/
			/*              REVERSE_MAP_ITERATOR             */
			/*************************************************/
	
	template <class T>
	class ReverseMapIterator
	{
		public:
			typedef T												iterator_type;
			typedef typename iterator_traits<T>::iterator_category	iterator_category;
			typedef typename iterator_traits<T>::value_type			value_type;
			typedef typename iterator_traits<T>::difference_type	difference_type;
			typedef typename iterator_traits<T>::pointer			pointer;
			typedef typename iterator_traits<T>::reference			reference;
			typedef typename iterator_traits<T>::const_pointer		const_pointer;
			typedef typename iterator_traits<T>::const_reference	const_reference;

			typedef ft::RBTree<value_type>*		rbtree_ptr;
			typedef ft::Node<value_type>*		node_ptr;

		private:
			node_ptr 		m_currentNode;
			rbtree_ptr		m_tree;
		
		public:
			ReverseMapIterator() : m_currentNode(0) {}
			ReverseMapIterator(node_ptr ptr, rbtree_ptr tree) : m_currentNode(ptr), m_tree(tree) {}
			ReverseMapIterator(ReverseMapIterator const &toCopy) : m_currentNode(toCopy.m_currentNode), m_tree(toCopy.m_tree) {}
			~ReverseMapIterator() {}
			ReverseMapIterator &operator = (ReverseMapIterator const &toCopy)
			{
				this->m_currentNode = toCopy.m_currentNode;
				this->m_currentNode = toCopy.m_tree;
				return (*this);
			}

			reference operator * () { return (this->m_currentNode->pair_data); }
			const_reference operator * () const { return (this->m_currentNode->pair_data); }
			pointer operator -> () { return (&this->m_currentNode->pair_data); }
			const_pointer operator -> () const { return (&this->m_currentNode->pair_data); }

			ReverseMapIterator& operator ++ ()
			{
				this->m_currentNode = prevNode(this->m_currentNode);
				return (*this);
			}
			ReverseMapIterator operator ++ (int)
			{
				ReverseMapIterator it(*this);
				this->m_currentNode = prevNode(this->m_currentNode);
				return it;
			}
			ReverseMapIterator& operator -- ()
			{
				this->m_currentNode = nextNode(this->m_currentNode);
				return (*this);
			}
			ReverseMapIterator operator -- (int)
			{
				ReverseMapIterator it(*this);
				this->m_currentNode = nextNode(this->m_currentNode);
				return it;
			}
			bool operator == (const ReverseMapIterator &it) const { return (this->m_currentNode == it.m_currentNode); }
			bool operator != (const ReverseMapIterator &it) const { return (this->m_currentNode != it.m_currentNode); }
			bool operator > (const ReverseMapIterator &it) const { return (this->m_currentNode > it.m_currentNode); }
			bool operator >= (const ReverseMapIterator &it) const { return (this->m_currentNode >= it.m_currentNode); }
			bool operator < (const ReverseMapIterator &it) const { return (this->m_currentNode < it.m_currentNode); }
			bool operator <= (const ReverseMapIterator &it) const { return (this->m_currentNode <= it.m_currentNode); }
	
		private:

			node_ptr getFirst(node_ptr node) 
			{
				while (node->left->left) 
					node = node->left;
				return node;
			}

			node_ptr getLast(node_ptr node) 
			{
				while (node->right->right) 
					node = node->right;
				return node;
			}

			node_ptr nextNode(node_ptr node)
			{
				if (node == this->m_tree->m_nullNode)
					return node;
				else if (node == getLast(this->m_tree->m_root))
					return this->m_tree->m_nullNode;
				else if (!node)
					return getFirst(this->m_tree->m_root);
				else if (node->right != this->m_tree->m_nullNode)
					return getFirst(node->right);
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
				else if (node == this->m_tree->m_nullNode)
					return getLast(this->m_tree->m_root);
				else if (node == getFirst(this->m_tree->m_root))
					return nullptr;
				else if (node->left != this->m_tree->m_nullNode)
					return getFirst(node->left);
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
	};
}
