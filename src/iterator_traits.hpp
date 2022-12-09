/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator_traits.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 21:55:48 by ldurante          #+#    #+#             */
/*   Updated: 2022/12/09 13:00:41 by ldurante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

namespace ft
{
	template <class Category, class T, class Distance = ptrdiff_t, class Pointer = T*, class Reference = T&>
	struct iterator
	{
		typedef T			value_type;
		typedef Pointer		pointer;
		typedef Reference	reference;
		typedef Distance	difference_type;
		typedef Category	iterator_category; 
	};

	template <class Iter>
    struct iterator_traits
	{
        typedef typename Iter::value_type           value_type;
        typedef typename Iter::pointer              pointer;
        typedef typename Iter::reference            reference;
        typedef typename Iter::difference_type      difference_type;
        typedef typename Iter::iterator_category    iterator_category;
    };

    template <class T>
    struct iterator_traits<T*>
	{
        typedef T									value_type;
        typedef T*									pointer;
        typedef T&									reference;
        typedef std::ptrdiff_t             			difference_type;
        typedef std::random_access_iterator_tag		iterator_category;
    };
	template <class T>
	struct iterator_traits<const T*>
	{
		typedef T								    value_type;
		typedef const T*						    pointer;
		typedef const T&						    reference;
		typedef std::ptrdiff_t					    difference_type;
		typedef std::random_access_iterator_tag	    iterator_category;
	};

	template<class InputIterator>
	typename ft::iterator_traits<InputIterator>::difference_type
	distance (InputIterator first, InputIterator last)
	{
		typename ft::iterator_traits<InputIterator>::difference_type i = 0;
		while (first != last)
		{
			i++;
			first++;
		}
		return (i);
	}
}
