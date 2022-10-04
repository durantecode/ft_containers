/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 20:33:48 by ldurante          #+#    #+#             */
/*   Updated: 2022/10/04 21:38:11 by ldurante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

#include <memory>
#include <stdexcept>
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

		protected:
			allocator_type	m_alloc;
			size_type		m_size;
			size_type		m_capacity;
			pointer			m_data;

		public:

			/*
				= allocator_type() just tells the compiler that it is an optional argument.
				If the user don't provide any other allocator_type object to the constructor
				of the vector, the default constructor of the Allocator/allocator_type will be used
				to create an object to be passed there instead.
				it´s an alias for std::allocator<T>()
			*/

			vector(const allocator_type &alloc = allocator_type())
			{
				//	Constructs an empty container, with no elements.
				
				std::cout << "Empty constructor called\n";
				m_alloc = alloc;
				m_data = m_alloc.allocate(0);
				m_size = 0;
				m_capacity = 0;
			}

			vector(size_type n, const value_type &val = value_type(), const allocator_type &alloc = allocator_type())
			{
				// Constructs a container with n elements. Each element is a copy of val.

				std::cout << "Fill constructor called\n";

				m_alloc = alloc;
				m_size = n;
				m_capacity = n;
				m_data = m_alloc.allocate(m_capacity);
				if (val)
				{
					for (size_t i = 0; i < m_size; i++)
						m_alloc.construct(&m_data[i], val);
				}
			}

			vector(vector const &toCopy)
			{
				// Constructs a container with a copy of each of the elements in x, in the same order.
				
				std::cout << "Copy constructor called\n";

				*this = toCopy;
			}

			~vector()
			{
				std::cout << "Destructor called\n";

				m_alloc.deallocate(m_data, m_capacity);
			}

			/* OPERATOR ASSIGNMENT */

			// vector& operator = (const vector& toCopy)
			// {

			// }



			/* CAPACITY: */

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
				while (n > m_size)
					push_back(val);
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

			/* ELEMENTS ACCESS */
			
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


			/* MODIFIERS */

			void push_back (const value_type& val)
			{
				if (m_size == m_capacity)
				{
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
	};
}

#endif
