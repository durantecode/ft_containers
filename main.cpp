/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 16:40:48 by ldurante          #+#    #+#             */
/*   Updated: 2022/10/06 00:55:27 by ldurante         ###   ########.fr       */
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

	std::vector<int> v;
	std::cout << "---- STL VECTOR ----\n" << std::endl;
	std::cout << "size: " << v.size() << "   capacity: " << v.capacity() << "\n";
	// try
	// {
	// 	std::cout << v.at(5445553) << std::endl;
	// }
	// catch(const std::exception& e)
	// {
	// 	std::cerr << e.what() << '\n';
	// }
	v.push_back(99);
	v.push_back(100);
	std::cout << "size: " << v.size() << "   capacity: " << v.capacity() << std::endl;
	// v.resize(100);
	std::cout << "size: " << v.size() << "   capacity: " << v.capacity() << std::endl;
	v.push_back(100);
	v.push_back(100);
	v.push_back(100);
	v.push_back(100);
	v.push_back(100);
	v.push_back(100);
	v.push_back(100);
	std::cout << "size: " << v.size() << "   capacity: " << v.capacity() << std::endl;
	// v.resize(150);
	std::cout << "size: " << v.size() << "   capacity: " << v.capacity() << std::endl;
	// v.resize(5, 9);
	std::cout << "size: " << v.size() << "   capacity: " << v.capacity() << std::endl;
	
	std::cout << "CLEAR VECTOR" << std::endl;
	v.clear();
	std::cout << "size: " << v.size() << "   capacity: " << v.capacity() << std::endl;
	// printVector(v);
	v.push_back(32);
	std::vector<int>::iterator iter = v.begin();
	std::vector<int>::iterator itend = v.end();
	while(iter != itend)
	{
		std::cout << "VECTORASSSSSO: " << *iter << std::endl;
		iter++;
	}
	std::cout << "size: " << v.size() << "   capacity: " << v.capacity() << std::endl;
	std::cout << v[5] << std::endl;



	ft::vector<int> v1;
	std::cout << "---- MY VECTOR ----\n" << std::endl;
	std::cout << "size: " << v1.size() << "    capacity: " << v1.capacity() << std::endl;
	// try
	// {
	// 	std::cout << v1.at(2) << std::endl;
	// }
	// catch(const std::exception& e)
	// {
	// 	std::cerr << e.what() << '\n';
	// }
	v1.push_back(99);
	v1.push_back(100);
	std::cout << "size: " << v1.size() << "   capacity: " << v1.capacity() << std::endl;
	// v1.resize(100);
	std::cout << "size: " << v1.size() << "   capacity: " << v1.capacity() << std::endl;
	v1.push_back(99);
	v1.push_back(32);
	v1.push_back(100);
	v1.push_back(654);
	v1.push_back(45);
	v1.push_back(4);
	v1.push_back(876);
	std::cout << "size: " << v1.size() << "   capacity: " << v1.capacity() << std::endl;
	// v1.resize(150);
	std::cout << "size: " << v1.size() << "   capacity: " << v1.capacity() << std::endl;
	// v1.resize(5, 9);
	std::cout << "size: " << v1.size() << "   capacity: " << v1.capacity() << std::endl;
	std::cout << "------------" << std::endl;
	// printMyVector(v1);

	ft::vector<int>::iterator it = v1.begin();
	ft::vector<int>::iterator ite = v1.end();
	// while(it != ite)
	// {
	// 	std::cout << "V: " << *it << std::endl;
	// 	it++;
	// }

	std::cout << "CLEAR VECTOR" << std::endl;
	// v1.clear();
	v1.pop_back();
	v1.pop_back();
	v1.pop_back();
	v1.pop_back();
	v1.pop_back();
	v1.pop_back();
	v1.pop_back();
	std::cout << "size: " << v1.size() << "   capacity: " << v1.capacity() << std::endl;
	v1.push_back(34);
	while(it != ite)
	{
		std::cout << "V: " << *it << std::endl;
		it++;
	}

	std::cout << v1[5] << std::endl;
	// atexit(leaks);

	return (0);
}
