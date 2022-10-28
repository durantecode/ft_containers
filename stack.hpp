/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 20:33:18 by ldurante          #+#    #+#             */
/*   Updated: 2022/10/28 21:13:00 by ldurante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "vector.hpp"

namespace ft
{
	template <class T, class Container = vector<T> >
	class stack
	{
		public:
			typedef Container									container_type;
			typedef typename container_type::value_type			value_type;
			typedef typename container_type::reference			reference;
			typedef typename container_type::const_reference	const_reference;
			typedef typename container_type::size_type			size_type;


		protected:
			container_type c;

		public:
			explicit stack (const container_type& ctnr = container_type())
			{
				
			}

			stack(const stack& toCopy)
			{

			}

			~stack()
			{
				
			}

			stack& operator = (const stack& toCopy)
			{
				return *this;
			}

			bool empty() const
			{
				return (this->c.empty());
			}
    		
			size_type size() const
			{
				return this->c.size();
			}
    		
			reference top()
			{
				return (this->c.back());
			}

    		const_reference top() const
			{
				return (this->c.back());
			}

			void push (const value_type& val)
			{

			}

			void pop()
			{
				
			}

	};
}
