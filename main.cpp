/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 16:40:48 by ldurante          #+#    #+#             */
/*   Updated: 2022/10/13 18:08:55 by ldurante         ###   ########.fr       */
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

	// v.assign(3,45);
	std::cout << "size: " << v.size() << "   capacity: " << v.capacity() << std::endl;

	std::vector<int>::iterator it = v.begin();
	// std::vector<int>::iterator ite = v.end();
	v.insert(it, 50000);

	std::vector<int> vv(v.begin(), v.end());
	if (v > vv)
		std::cout << "OJETE\n";
	// std::cout << "size: " << vv.size() << "   capacity: " << vv.capacity() << std::endl;
	// vv.resize(5);
	// vv.assign(it, ite);
	// std::cout << "size: " << vv.size() << "   capacity: " << vv.capacity() << std::endl;
	printVector(v);
	// // v.resize(5, 9);
	// std::cout << "size: " << v.size() << "   capacity: " << v.capacity() << std::endl;




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

	ft::vector<int>::iterator iter = v1.begin();
	v1.insert(iter, 90000);
	// ft::vector<int>::iterator itend = v1.end();
	ft::vector<int> v2(v.begin(), 9000);
	// ft::vector<int> v2(v1.begin(), v.end());
	ft::vector<int> v3(23);
	v1.swap(v2);
		// std::cout << "IGUALITOOO\n";
	// v2.resize(10);
	// std::cout << "size: " << v2.size() << "   capacity: " << v2.capacity() << std::endl;
	// // v2.assign(iter, itend);
	// std::cout << "size: " << v2.size() << "   capacity: " << v2.capacity() << std::endl;
	std::cout << "------------" << std::endl;
	printMyVector(v1);
	printMyVector(v2);



	// atexit(leaks);

	return (0);
}
