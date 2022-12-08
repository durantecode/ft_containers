/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 18:19:43 by ldurante          #+#    #+#             */
/*   Updated: 2022/12/07 21:17:09 by ldurante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.hpp"

long count;
long err_count;
bool verbose;
std::string test_name;
std::vector<std::string> names;
std::vector<long> errors;
std::vector<double> time_perf;

int main(int argc, char **argv)
{
	std::string test;
	std::string verb;
	verbose = false;
	count = 10000;

	if (argc < 2 || argc > 3)
	{
		std::cout << "usage: ./containers [container] [-verbose]" << std::endl;
		return (1);
	}
	else
	{
		test = std::string(argv[1]);
		if (argv[2])
		{
			verb = std::string(argv[2]);
			if (verb == "-verbose")
				verbose = true;
			else
			{
				std::cout << "No option called " << verb << std::endl;
				std::cout << "usage: ./containers [container] [-verbose]" << std::endl;
				return (1);
			}
		}	
	}
	print_project_title();
	if (test == "vector")
		test_vector();
	else if (test == "stack")
		test_stack();
	else if (test == "utils")
		test_utility();
	else if (test == "map")
		test_map();
	else if (test == "all")
	{
		test_stack();
		test_utility();
		test_map();
		test_vector();
	}
	else
		std::cout << "No test for " << test << std::endl;
	return (0);
}
