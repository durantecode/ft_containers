/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator_traits.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 21:55:48 by ldurante          #+#    #+#             */
/*   Updated: 2022/11/22 13:19:51 by ldurante         ###   ########.fr       */
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
        typedef typename Iter::const_pointer		const_pointer;
        typedef typename Iter::const_reference		const_reference;
    };

    template <class T>
    struct iterator_traits<T*>
	{
        typedef T									value_type;
        typedef ptrdiff_t                  			difference_type;
        typedef std::random_access_iterator_tag		iterator_category;
        typedef T*									pointer;
        typedef T&									reference;
        typedef const T*							const_pointer;
        typedef const T&							const_reference;
    };
}
