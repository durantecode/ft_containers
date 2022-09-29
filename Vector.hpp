/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 20:33:48 by ldurante          #+#    #+#             */
/*   Updated: 2022/09/30 00:48:34 by ldurante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

#include <memory>
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
			typedef size_t	size_type;
			typedef T		value_type;
			typedef Alloc	allocator_type;

			// typedef typename allocator_type::pointer			pointer;
			// typedef typename allocator_type::const_pointer		const_pointer;
			// typedef typename allocator_type::reference			reference;
			// typedef typename allocator_type::const_reference	const_reference;

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
				m_alloc = alloc;
				m_data = m_alloc.allocate(0);
				m_size = 0;
				m_capacity = 0;
			}
			vector(size_type n, const value_type &val = value_type(), const allocator_type &alloc = allocator_type())
			{
				m_alloc = alloc;
				m_data = m_alloc.allocate(n);
				m_size = 0;
				m_capacity = 0;
				val = 0;
			}

			// vector(vector const &toCopy);
			~vector() {}

			size_type size() const { return this->m_size; }
			size_type capacity() const { return this->m_capacity; }
	};
}

#endif
