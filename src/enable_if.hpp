/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enable_if.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 23:07:25 by ldurante          #+#    #+#             */
/*   Updated: 2022/11/04 14:04:53 by ldurante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

/*	The type T is enabled as member type enable_if::type if Cond is true.
	Otherwise, enable_if::type is not defined.

	This is useful to hide signatures on compile time when a particular condition is not met,
	since in this case, the member enable_if::type will not be defined and attempting to compile
	using it should fail.
*/

namespace ft
{
	template<bool Cond, class T = void>
	struct enable_if {};

	template<class T>
	struct enable_if<true, T>
	{
		typedef T type;
	};
}
