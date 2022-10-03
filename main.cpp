/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 16:40:48 by ldurante          #+#    #+#             */
/*   Updated: 2022/10/04 00:38:18 by ldurante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "vector.hpp"
#include <stdlib.h>

void leaks()
{
	system("leaks -q containers");
}

template <typename T>
void printVector(const std::vector<T> &vector)
{
	for(size_t i = 0; i < vector.size(); i++)
		std::cout << vector[i] << std::endl;
	
	std::cout << "------------\n\n";
}

template <typename T>
void printMyVector(const ft::vector<T> &vector)
{
	for(size_t i = 0; i < vector.size(); i++)
		std::cout << vector[i] << std::endl;
	
	std::cout << "------------\n\n";
}

int main(void)
{
	// std::allocator<int>		alloc;
	// int* a = alloc.allocate(10);
	// alloc.construct(a, 3);
	// std::cout << *a << '\n';
	
	// a[0] = 1;
	std::vector<int> v(3, 123);
	v.push_back(8);
	std::cout << "---- STL VECTOR ----" << std::endl;
	std::cout << "size: " << v.size() << "\n" << "capacity: " << v.capacity() << "\n\n";
	printVector(v);

	ft::vector<int> v1(5, 12);
	std::cout << "---- MY VECTOR ----" << std::endl;
	std::cout << "size: " << v1.size() << "\n" << "capacity: " << v1.capacity() << std::endl;
	std::cout << "------------" << std::endl;
	printMyVector(v1);

	atexit(leaks);

	return (0);
}
