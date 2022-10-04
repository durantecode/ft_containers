/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 16:40:48 by ldurante          #+#    #+#             */
/*   Updated: 2022/10/04 21:38:12 by ldurante         ###   ########.fr       */
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

	std::vector<int> v(5, 123);
	std::cout << "---- STL VECTOR ----" << std::endl;
	std::cout << "size: " << v.size() << "\n" << "capacity: " << v.capacity() << "\n";
	try
	{
		std::cout << v.at(5445553) << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	v.push_back(99);
	v.push_back(100);
	v.pop_back();
	v.pop_back();
	v.pop_back();
	v.pop_back();
	v.resize(30);
	std::cout << "size: " << v.size() << "\n" << "capacity: " << v.capacity() << "\n\n";
	// printVector(v);




	ft::vector<int> v1(5, 123);
	std::cout << "---- MY VECTOR ----" << std::endl;
	std::cout << "size: " << v1.size() << "\n" << "capacity: " << v1.capacity() << std::endl;
	try
	{
		std::cout << v1.at(2) << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	v1.push_back(99);
	v1.push_back(100);
	v1.pop_back();
	v1.pop_back();
	v1.pop_back();
	v1.pop_back();
	v1.resize(30);
	std::cout << "size: " << v1.size() << "\n" << "capacity: " << v1.capacity() << std::endl;
	std::cout << "------------" << std::endl;
	// printMyVector(v1);

	// atexit(leaks);

	return (0);
}
