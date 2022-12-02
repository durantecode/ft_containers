/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_pair.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 23:19:30 by ldurante          #+#    #+#             */
/*   Updated: 2022/11/04 16:44:20 by ldurante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "pair.hpp"

/*
	Constructs a pair object with its first element set to x and its second element set to y.
	The template types can be implicitly deduced from the arguments passed to make_pair.
	pair objects can be constructed from other pair objects containing different types,
	if the respective types are implicitly convertible.
*/

namespace ft
{
	template <class T1,class T2>
	pair<T1,T2> make_pair (T1 x, T2 y)
	{
		return ( pair<T1,T2>(x,y) );
	}
}
