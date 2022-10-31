/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 20:33:48 by ldurante          #+#    #+#             */
/*   Updated: 2022/10/30 23:30:03 by ldurante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

/* 	THERE'S SOME STD FUNCTIONS LIKE "DISTANCE" AND "ENABLE_IF"
	REMEMBER TO CHANGE THEM FOR YOUR OWN IMPLEMENTED VERSIONS"
*/

#include <memory>
#include <stdexcept>
#include "utils.hpp"
#include "vector_iterator.hpp"

namespace ft
{
	template <typename T, typename Alloc = std::allocator<T> >
	class vector
	{
		public:
			typedef size_t		size_type;
			typedef T			value_type;
			typedef Alloc		allocator_type;

			typedef T*			pointer;
			typedef const T*	const_pointer;
			typedef T&			reference;
			typedef const T&	const_reference;

			typedef ft::VectorIterator<T>						iterator;
			typedef ft::VectorIterator<const T> 				const_iterator;
			typedef ft::ReverseVectorIterator<iterator> 		reverse_iterator;
			typedef ft::ReverseVectorIterator<const_iterator>	const_reverse_iterator;

		protected:
			allocator_type	m_alloc;
			size_type		m_size;
			size_type		m_capacity;
			pointer			m_data;


			/*************************************************/
			/*                 CONSTRUCTORS                  */
			/*************************************************/
		
		public:

			explicit vector (const allocator_type& alloc = allocator_type()) :
				m_alloc(alloc),
				m_size(0),
				m_capacity(0),
				m_data(0)
				{}

			explicit vector(size_type n, const value_type &val = value_type(), const allocator_type &alloc = allocator_type()) :
				m_alloc(alloc),
				m_size(0),
				m_capacity(0),
				m_data(0)
			{
				this->assign(n, val);
			}

			template <class InputIterator>
			vector(InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(),
				typename std::enable_if<!std::is_integral<InputIterator>::value, void>::type* = 0) :
				m_alloc(alloc),
				m_size(0),
				m_capacity(1),
				m_data(m_alloc.allocate(m_capacity))
			{
				this->assign(first, last);
			}

			vector(vector const &toCopy) :
				m_alloc(toCopy.get_allocator()),
				m_size(toCopy.m_size),
				m_capacity(toCopy.m_capacity),
				m_data(m_alloc.allocate(toCopy.m_capacity))
			{
				for (size_type i = 0; i < toCopy.m_size; i++)
					this->m_alloc.construct(&this->m_data[i], toCopy.m_data[i]);
			}

			~vector()
			{
				this->clear();
				this->m_alloc.deallocate(this->m_data, this->m_capacity);
			}

			vector& operator = (const vector& toCopy)
			{
				// std::cout << "OJETE" << std::endl;
				if (this != &toCopy)
					this->assign(toCopy.begin(), toCopy.end());
					// return *this;
				// this->clear();
				// this->m_alloc = toCopy.get_allocator();
				// this->m_alloc.deallocate(this->m_data, this->m_capacity);
				// this->m_capacity = toCopy.m_capacity;
				// this->m_size = toCopy.m_size;
				// this->m_data = m_alloc.allocate(this->m_capacity);
				// for (size_type i = 0; i < this->m_size; ++i)
				// 	this->m_alloc.construct(&this->m_data[i], toCopy.m_data[i]);
				return *this;
			}


			/*************************************************/
			/*                  ITERATORS                    */
			/*************************************************/

		public:

			iterator begin() { return iterator(&m_data[0]);	}
			const_iterator begin() const { return const_iterator(&m_data[0]); }
			iterator end() { return iterator(&m_data[m_size]); }
			const_iterator end() const { return const_iterator(&m_data[m_size]); }

			reverse_iterator rbegin() { return reverse_iterator(end()); }
			const_reverse_iterator rbegin() const { return const_reverse_iterator(end()); }
			reverse_iterator rend() { return reverse_iterator(begin()); }
			const_reverse_iterator rend() const { return const_reverse_iterator(begin()); }


			/*************************************************/
			/*                   CAPACITY                    */
			/*************************************************/

		public:

			size_type size() const { return this->m_size; }
			size_type max_size() const { return this->m_alloc.max_size(); }
			size_type capacity() const { return this->m_capacity; }
			allocator_type get_allocator() const { return this->m_alloc; }
			
			bool empty() const
			{
				if (!this->m_size)
					return (true);
				return (false);
			}

			void resize (size_type n, value_type val = value_type())
			{
				if (n < this->m_size)
				{
					while (this->m_size != n)
						pop_back();
				}
				else
				{
					if (this->m_capacity * 2 < n)
						reserve(n);
					while (this->m_size != n)
						push_back(val);
				}
			}

			void reserve (size_type n)
			{
				if (n < this->m_capacity)
					return ;
				if (n > max_size())
					throw std::length_error("allocator<T>::allocate(size_t n) 'n' exceeds maximum supported size");
				pointer newBlock;
				newBlock = this->m_alloc.allocate(n);
				for (size_type i = 0; i < this->m_size; i++)
				{
					m_alloc.construct(&newBlock[i], m_data[i]);
					m_alloc.destroy(&m_data[i]);
				}
				if (this->m_capacity)
					m_alloc.deallocate(this->m_data, this->m_capacity);
				this->m_capacity = n;
				this->m_data = newBlock;
			}

			/*************************************************/
			/*               ELEMENT ACCESS                  */
			/*************************************************/
			
		public:

			reference operator [] (size_type n) { return m_data[n]; }
			const_reference operator [] (size_type n) const { return m_data[n]; }
			
			reference at(size_type n)
			{
				if (n >= this->m_size)
					throw std::out_of_range("vector");
				return (this->m_data[n]);
			}
			const_reference at(size_type n) const
			{
				if (n >= this->m_size)
					throw std::out_of_range("vector");
				return (this->m_data[n]);
			}
			
			reference front() { return (this->m_data[0]);	}
			const_reference front() const { return (this->m_data[0]); }
			
			reference back() { return (this->m_data[m_size - 1]); }
			const_reference back() const { return (this->m_data[m_size - 1]); }
			
			pointer data() { return (this->m_data); }
			const_pointer data() const { return (this->m_data); }

			/*************************************************/
			/*                  MODIFIERS                    */
			/*************************************************/

		public:

			template <class InputIterator>
			void assign (InputIterator first, InputIterator last,
			typename std::enable_if<!std::is_integral<InputIterator>::value>::type* = 0)
			{
				size_type n = std::distance(first, last);

				clear();
				if (n > this->m_capacity)
					reserve(n);
				for (size_type i = 0; i < n; i++)
				{
					this->m_alloc.construct(&this->m_data[i], *first);
					first++;
				}
				this->m_size = n;
			}

			void assign (size_type n, const value_type& val)
			{
				clear();
				if (n > this->m_capacity)
					reserve(n);
				for (size_type i = 0; i < n; i++)
					this->m_alloc.construct(&this->m_data[i], val);
				this->m_size = n;
			}

			iterator insert (iterator position, const value_type& value)
			{
				size_type i = position - this->begin();
				if (this->m_capacity < this->m_size + 1)
					this->reserve(this->m_size + 1);
				size_type j = this->m_size;
				while (j > i)
				{
					this->m_alloc.construct(&this->m_data[j], this->m_data[j - 1]);
					this->m_alloc.destroy(&this->m_data[j - 1]);
					j--;
				}
				this->m_alloc.construct(&this->m_data[i], value);
				this->m_size++;
				position = &this->m_data[i];
				return (position);
			}

			void insert (iterator position, size_type n, const value_type& val)
			{
				while (n--)
					position = insert(position, val);
			}

			template <class InputIterator>
			void insert (iterator position, InputIterator first, InputIterator last, typename std::enable_if<!std::is_integral<InputIterator>::value>::type* = 0)
			{
				while (first != last)
				{
					position = insert(position, *first) + 1;
					++first;
				}
			}

			void push_back (const value_type& val)
			{
				if (this->m_size == this->m_capacity)
				{
					if (!this->m_capacity)
						reserve(1);
					else
						reserve(this->m_capacity * 2);
				}	
				this->m_alloc.construct(&this->m_data[this->m_size], val);
				this->m_size++;
			}

			void pop_back()
			{
				this->m_alloc.destroy(&this->m_data[this->m_size - 1]);
				this->m_size--;
			}

			void clear()
			{
				for (size_type i = 0; i < this->m_size; i++)
					this->m_alloc.destroy(m_data + i);
				this->m_size = 0;
			}

			iterator erase(iterator position)
			{
				size_type	pos = position - begin();
				pointer		tmp = &this->m_data[pos];

				this->m_alloc.destroy(tmp);
				m_size--;
				while (pos < this->m_size)
				{
					*tmp = *(tmp + 1);
					tmp++;
					pos++;
				}
				return position;
			}

			iterator erase(iterator first, iterator last)
			{
				size_type	n	 = std::distance(first, begin());
				pointer 	tmp  = &this->m_data[n];
				size_type	diff = std::distance(first, last);

				size_type i = 0;
				while (n + diff < this->m_size)
				{
					if (i < diff)
						this->m_alloc.destroy(tmp);
					if (n + diff < this->m_size)
						*tmp = *(tmp + diff);
					i++;
					n++;
					tmp++;
				}
				this->m_size -= diff;
				return first;
			}


			void swap(vector &other)
			{
				ft::swap(this->m_alloc, other.m_alloc);
				ft::swap(this->m_data, other.m_data);
				ft::swap(this->m_size, other.m_size);
				ft::swap(this->m_capacity, other.m_capacity);
			}
	};

	/*************************************************/
	/*        NON-MEMBER FUNCTIONS OVERLOADS         */
	/*************************************************/
	
	template <class T, class Alloc>
	void swap (vector<T,Alloc>& x, vector<T,Alloc>& y)
	{
		x.swap(y);
	}

	template <class T, class Alloc>
	bool operator == (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		if (lhs.size() != rhs.size())
			return (false);
		size_t i = 0;
		while (i < lhs.size())
		{
			if (lhs[i] != rhs[i])
				return (false);
			i++;
		}
		return (true);
	}

	template <class T, class Alloc>
	bool operator != (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return (!(lhs == rhs));
	}

	template <class T, class Alloc>
	bool operator < (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		size_t		i;
		size_t		n;

		i = 0;
		if (lhs.size() > rhs.size())
			n = rhs.size();
		else
			n = lhs.size();
		while (i < n)
		{
			if (lhs.at(i) != rhs.at(i))
				return (lhs.at(i) < rhs.at(i));
			i++;
		}
		return (lhs.size() < rhs.size());
	}

	template <class T, class Alloc>
	bool operator <= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return (!(rhs < lhs));
	}

	template <class T, class Alloc>
	bool operator > (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return (rhs < lhs);
	}

	template <class T, class Alloc>
	bool operator >= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return (!(lhs < rhs));
	}

}
