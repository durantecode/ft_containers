/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 18:19:43 by ldurante          #+#    #+#             */
/*   Updated: 2022/10/28 21:17:37 by ldurante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.hpp"

int main(int argc, char **argv)
{
	std::string test;
	if (argc != 2)
	{
		std::cout << "No test given. usage: ./containers [container]\n" << std::endl;
		return (1);
	}
	else
		test = std::string(argv[1]);
	if (test == "vector")
		test_vector();
	else if (test == "stack")
		test_stack();
	// else if (test == "map")
	// 	test_map();
	// else if (test == "all")
	// {
	// 	test_vector();
	// 	test_map();
	// 	test_stack();
	// }
	else
		std::cout << "No test for " << test << std::endl;
	return (0);
}
