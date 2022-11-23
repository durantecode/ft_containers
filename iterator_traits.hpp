/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator_traits.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 21:55:48 by ldurante          #+#    #+#             */
/*   Updated: 2022/11/23 22:11:16 by ldurante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

namespace ft
{
	template <class Iter>
    struct iterator_traits
	{
        typedef typename Iter::value_type           value_type;
        typedef typename Iter::difference_type      difference_type;
        typedef typename Iter::iterator_category    iterator_category;
        typedef typename Iter::pointer              pointer;
        typedef typename Iter::reference            reference;
    };

    template <class T>
    struct iterator_traits<T*>
	{
        typedef T									value_type;
        typedef ptrdiff_t                  			difference_type;
        typedef std::random_access_iterator_tag		iterator_category;
        typedef T*									pointer;
        typedef T&									reference;
    };
	template <class T>
	struct iterator_traits<const T*>
	{
		typedef T								    value_type;
		typedef std::ptrdiff_t					    difference_type;
		typedef std::random_access_iterator_tag	    iterator_category;
		typedef const T*						    pointer;
		typedef const T&						    reference;
	};
}
