/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 20:33:18 by ldurante          #+#    #+#             */
/*   Updated: 2022/10/30 21:47:22 by ldurante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "vector.hpp"

namespace ft
{
	template <class T, class Container = ft::vector<T> >
	class stack
	{
		public:
			typedef Container	container_type;
			typedef T			value_type;
			typedef T&			reference;
			typedef const T&	const_reference;
			typedef size_t		size_type;


		protected:
			container_type c;

		public:
			explicit stack (const container_type& ctnr = container_type()) { c = ctnr; }
			stack(const stack &toCopy) { c = toCopy.c; };
			~stack() {}

			stack& operator = (const stack& toCopy)
			{
        		if (this != &toCopy)
            		c = toCopy.c;
        		return (*this);
    		}

			bool empty() const { return (this->c.empty()); }
			size_type size() const { return this->c.size(); }
			reference top() { return (this->c.back()); }
	   		const_reference top() const { return (this->c.back()); }
			void push (const value_type& val) { c.push_back(val); }
			void pop() { c.pop_back(); }

			friend bool operator == (const stack &lhs, const stack &rhs) { return lhs.c == rhs.c; };
			friend bool operator != (const stack &lhs, const stack &rhs) { return lhs.c != rhs.c; };
			friend bool operator <= (const stack &lhs, const stack &rhs) { return lhs.c <= rhs.c; };
			friend bool operator >= (const stack &lhs, const stack &rhs) { return lhs.c >= rhs.c; };
			friend bool operator < (const stack &lhs, const stack &rhs) { return lhs.c < rhs.c; };
			friend bool operator > (const stack &lhs, const stack &rhs) { return lhs.c > rhs.c; };
	};
}
