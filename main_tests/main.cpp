/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 18:19:43 by ldurante          #+#    #+#             */
/*   Updated: 2022/10/22 01:19:33 by ldurante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.hpp"

int main(int argc, char **argv)
{
	std::string choice;
	if (argc != 2)
	{
		std::cout << "No test given, testing vector." << std::endl;
		choice = "vector";
	}
	else
		choice = std::string(argv[1]);
	if (choice == "vector")
		test_vector();
	// else if (choice == "map")
	// 	test_map();
	// else if (choice == "stack")
	// 	test_stack();
	// else if (choice == "all")
	// {
	// 	test_vector();
	// 	test_map();
	// 	test_stack();
	// }
	else
		std::cout << "No test for " << choice << std::endl;

	return (0);
}
