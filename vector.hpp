/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 20:33:48 by ldurante          #+#    #+#             */
/*   Updated: 2022/10/06 19:50:35 by ldurante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

#include <memory>
#include <stdexcept>
#include "utils.hpp"
#include <vector>

/*
	NOTES:

	std::allocator<int> a1;   // default allocator for ints
	int* a = a1.allocate(1);  // space for one int
	a1.construct(a, 7);       // construct the int
	std::cout << a[0] << '\n';
	a1.deallocate(a, 1);      // deallocate space for one int

*/
namespace ft
{
	template<typename T>
	class VectorIterator
	{
		public:
			typedef T				value_type;
			typedef T*				pointer;
			typedef const T*		const_pointer;
			typedef T&				reference;
			typedef const T&		const_reference;
			typedef std::ptrdiff_t	difference_type;

		protected:
			pointer m_ptr;
		
		public:
			VectorIterator() : m_ptr(nullptr) {}
			VectorIterator(pointer ptr) : m_ptr(ptr) {}
			VectorIterator(VectorIterator const &toCopy) : m_ptr(toCopy.m_ptr) {}
			~VectorIterator() {}
			VectorIterator &operator = (VectorIterator const &toCopy)
			{
				this->m_ptr = toCopy.m_ptr;
				return (*this);
			}

			VectorIterator& operator ++ ()
			{
				this->m_ptr++;
				return (*this);
			}
			VectorIterator operator ++ (int)
			{
				VectorIterator it(*this);
				++(*this);
				return it;
			}
			VectorIterator &operator += (int val)
			{
				this->m_ptr += val;
				return (*this);
			}
			VectorIterator operator + (int val) const
			{
				VectorIterator it(*this);
				return (it += val);
			}
			VectorIterator& operator -- ()
			{
				this->m_ptr--;
				return *this;
			}
			VectorIterator operator -- (int)
			{
				VectorIterator it(*this);
				--(*this);
				return it;
			}
			VectorIterator &operator -= (int val)
			{
				this->m_ptr -= val;
				return (*this);
			}
			VectorIterator operator - (int val) const
			{
				VectorIterator it(*this);
				return (it -= val);
			}
			reference operator * ()
			{
				return (*this->m_ptr);
			}
			const_reference operator * () const
			{
				return (*this->m_ptr);
			}
			pointer operator -> ()
			{
				return (this->m_ptr);
			}
			const_pointer operator -> () const
			{
				return (this->m_ptr);
			}
			reference operator [] (int val)
			{
				return (*(this->m_ptr + val));
			}
			const_reference operator [] (int val) const
			{
				return (*(this->m_ptr + val));
			}
			bool operator == (const VectorIterator &it) const
			{
				return (m_ptr == it.m_ptr);
			}
			bool operator != (const VectorIterator &it) const
			{
				return (m_ptr != it.m_ptr);
			}
			bool operator > (const VectorIterator &it) const
			{
				return (m_ptr > it.m_ptr);
			}
			bool operator >= (const VectorIterator &it) const
			{
				return (m_ptr >= it.m_ptr);
			}
			bool operator < (const VectorIterator &it) const
			{
				return (m_ptr < it.m_ptr);
			}
			bool operator <= (const VectorIterator &it) const
			{
				return (m_ptr <= it.m_ptr);
			}
	};


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

			typedef VectorIterator<T>				iterator;
			typedef VectorIterator<const T> 		const_iterator;
			typedef VectorIterator<iterator> 		reverse_iterator;
			typedef VectorIterator<const_iterator>	const_reverse_iterator;

		protected:
			allocator_type	m_alloc;
			size_type		m_size;
			size_type		m_capacity;
			pointer			m_data;


			/*************************************************/
			/*                 CONSTRUCTORS                  */
			/*************************************************/
		
		public:

			explicit vector(const allocator_type &alloc = allocator_type())
			{
				this->m_alloc = alloc;
				this->m_data = m_alloc.allocate(0);
				this->m_size = 0;
				this->m_capacity = 0;
			}

			explicit vector(size_type n, const value_type &val = value_type(), const allocator_type &alloc = allocator_type())
			{
				this->m_alloc = alloc;
				this->m_size = n;
				this->m_capacity = n;
				this->m_data = this->m_alloc.allocate(this->m_capacity);
				if (val)
				{
					for (size_t i = 0; i < m_size; i++)
						this->m_alloc.construct(&this->m_data[i], val);
				}
			}

			vector (iterator first, iterator last, const allocator_type& alloc = allocator_type())
			{
				this->m_data = nullptr;
				this->m_size = 0;
				this->m_capacity = 0;
				this->m_alloc = alloc;
				this->assign(first, last);
			}

			vector(vector const &toCopy)
			{
				this->m_alloc = toCopy.m_alloc;
				this->m_data = this->m_alloc.allocate(toCopy.m_capacity);
				for (size_type i = 0; i < toCopy.m_size; i++)
					this->m_alloc.construct(&this->m_data[i], toCopy.m_data[i]);
				this->m_size = toCopy.m_size;
				this->m_capacity = toCopy.m_capacity;
			}

			~vector()
			{
				clear();
				m_alloc.deallocate(m_data, m_capacity);
			}

			/* OPERATOR ASSIGNMENT */

			vector& operator = (const vector& toCopy)
			{
				if (this != &toCopy)
					this->assign(toCopy.begin(), toCopy.end());
				return (*this);
			}


			/*************************************************/
			/*                  ITERATORS                    */
			/*************************************************/

		public:

			iterator begin() { return iterator(m_data);	}
			const_iterator begin() const { return const_iterator(m_data); }
			iterator end() { return iterator(m_data + m_size); }
			const_iterator end() const { return const_iterator(m_data + m_size); }

			reverse_iterator rbegin() { return reverse_iterator(m_data + (m_size - 1)); }
			const_reverse_iterator rbegin() const { return const_reverse_iterator(m_data + (m_size - 1)); }
			reverse_iterator rend() { return reverse_iterator(m_data - 1); }
			const_reverse_iterator rend() const { return const_reverse_iterator(m_data - 1); }


			/*************************************************/
			/*                   CAPACITY                    */
			/*************************************************/

		public:

			size_type size() const { return this->m_size; }
			size_type max_size() const { return this->m_alloc.max_size(); }
			size_type capacity() const { return this->m_capacity; }
			
			bool empty() const
			{
				if (!m_size)
					return (true);
				return (false);
			}

			void resize (size_type n, value_type val = value_type())
			{
				while (n < m_size)
					pop_back();
				if (n > m_capacity)
				{
					m_capacity = n;
					reserve(m_capacity);
				}
				while (n > m_size)
				{
					m_alloc.construct(&m_data[m_size], val);
					m_size++;
				}
			}
			
			void reserve (size_type n)
			{
				if (n < m_capacity)
					return ;
				if (n > max_size())
					throw std::length_error("allocator<T>::allocate(size_t n) 'n' exceeds maximum supported size");
				pointer newBlock;
				newBlock = m_alloc.allocate(n);
				for (size_type i = 0; i < m_size; i++)
				{
					m_alloc.construct(&newBlock[i], m_data[i]);
					m_alloc.destroy(&m_data[i]);
				}
				m_alloc.deallocate(m_data, m_capacity);
				m_data = newBlock;
				m_capacity = n;
			}

			/*************************************************/
			/*               ELEMENT ACCESS                  */
			/*************************************************/
			
		public:

			reference operator [] (size_type n) { return m_data[n]; }
			const_reference operator [] (size_type n) const { return m_data[n]; }
			
			reference at(size_type n)
			{
				if (n >= m_size)
					throw std::out_of_range("vector");
				return (m_data[n]);
			}
			const_reference at(size_type n) const
			{
				if (n >= m_size)
					throw std::out_of_range("vector");
				return (m_data[n]);
			}
			
			reference front() { return (m_data[0]);	}
			const_reference front() const { return (m_data[0]); }
			
			reference back() { return (m_data[m_size - 1]); }
			const_reference back() const { return (m_data[m_size - 1]); }
			
			pointer data() { return (m_data); }
			const_pointer data() const { return (m_data); }

			/*************************************************/
			/*                  MODIFIERS                    */
			/*************************************************/

		public:

			void assign (iterator first, iterator last)
			{
				this->clear();
				iterator tmp = first;
				size_type distance = 0;
				while (tmp != last)
				{
					distance++;
					tmp++;
				}
				if (distance > m_capacity)
					this->reserve(distance);
				for (size_type i = 0; i < distance; i++)
					this->m_alloc.construct(this->m_data + i, *first++);
				this->m_size = distance;
			}

			void assign (size_type n, const value_type& val)
			{
				this->clear();
				if (n > m_capacity)
					this->reserve(n);
				for (size_type i = 0; i < n; i++)
					this->m_alloc.construct(&this->m_data[i], val);
				this->m_size = n;
			}

			iterator insert (iterator position, const value_type& val)
			{
				size_type i = 0;
				size_type j = this->m_size - 1;
				iterator it = this->begin();
				while (it + i != position && i < this->m_size)
					i++;
				if (this->m_size < this->m_capacity + 1)
					this->reserve(this->m_capacity + 1);
				while (j > i)
				{
					this->m_alloc.construct(&this->m_data[j], this->m_data[j - 1]);
					j--;
				}
				this->m_alloc.construct(&this->m_data[i], val);
				this->m_capacity++;
				iterator newIter(&this->m_data[i]);
				return (newIter);

			}

			void insert (iterator position, size_type n, const value_type& val)
			{
				while (n--)
					position = insert(position, val);
			}

			void insert (iterator position, iterator first, iterator last)
			{
				while (first != last)
				{
					position = insert(position, *first) + 1;
					++first;
				}
			}

			void push_back (const value_type& val)
			{
				if (m_size == m_capacity)
				{
					if (!m_capacity)
						m_capacity++;
					m_capacity *= 2;
					reserve(m_capacity);
				}	
				m_alloc.construct(&m_data[m_size], val);
				m_size++;
			}

			void pop_back()
			{
				m_alloc.destroy(&back());
				m_size--;
			}

			void clear()
			{
				for (size_type i = 0; i < m_size; i++)
					m_alloc.destroy(&m_data[i]);
				m_size = 0;
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


#endif
