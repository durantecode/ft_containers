/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_and_comparision.cpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 00:01:22 by ldurante          #+#    #+#             */
/*   Updated: 2022/10/31 02:43:59 by ldurante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.hpp"

std::clock_t   	start;
std::string		color;

void print_project_title(void)
{
	std::cout << std::endl << std::endl << YELLOW;
	std::cout << "        ███████╗████████╗      ██████╗ ██████╗ ███╗   ██╗████████╗ █████╗ ██╗███╗   ██╗███████╗██████╗ ███████╗" << std::endl;
	std::cout << "	██╔════╝╚══██╔══╝     ██╔════╝██╔═══██╗████╗  ██║╚══██╔══╝██╔══██╗██║████╗  ██║██╔════╝██╔══██╗██╔════╝" << std::endl;
	std::cout << "	█████╗     ██║        ██║     ██║   ██║██╔██╗ ██║   ██║   ███████║██║██╔██╗ ██║█████╗  ██████╔╝███████╗" << std::endl;
	std::cout << "	██╔══╝     ██║        ██║     ██║   ██║██║╚██╗██║   ██║   ██╔══██║██║██║╚██╗██║██╔══╝  ██╔══██╗╚════██║" << std::endl;
	std::cout << "	██║        ██║███████╗╚██████╗╚██████╔╝██║ ╚████║   ██║   ██║  ██║██║██║ ╚████║███████╗██║  ██║███████║" << std::endl;
	std::cout << "	╚═╝        ╚═╝╚══════╝ ╚═════╝ ╚═════╝ ╚═╝  ╚═══╝   ╚═╝   ╚═╝  ╚═╝╚═╝╚═╝  ╚═══╝╚══════╝╚═╝  ╚═╝╚══════╝" << std::endl;
	std::cout << RESET << std::endl << std::endl;                                                               
}

void print_header(std::string str, bool container)
{
	int margin = (40 - str.length()) / 2;
	int width = (margin * 2 + str.length()) + 2;
	if (container)
	{
		std::cout << BLUE;
		std::cout << std::string(width, '*') << std::endl;
		std::cout << "*" << RED << std::string(margin, ' ') << str << std::string(margin, ' ') << BLUE << "*" << std::endl;
		std::cout << std::string(width, '*') << std::endl << std::endl;
	}
	else
	{
		std::cout << MAGENTA;
		std::cout << std::string(width, '*') << std::endl;
		std::cout << "*" << YELLOW << std::string(margin, ' ') << str << std::string(margin, ' ') << MAGENTA << "*" << std::endl;
		std::cout << "*" << std::string(40, ' ') << "*" << std::endl;
		std::cout << RESET;
	}
}

void timer_start()
{
	start = std::clock();
}

double timer_stop()
{
	double	duration;
    duration = (std::clock() - start) / (double) CLOCKS_PER_SEC;
	start = 0;
	return duration;
}

void performance_result(double std, double ft)
{
	print_header("TIME PERFORMANCE", 0);
	
	std::string std_len = std::to_string(std);
	std::string ft_len = std::to_string(ft);
	if (std < ft)
	{
		std::cout << MAGENTA << "*" << std::setw(14) << RESET << "std time: " << GREEN << std_len << MAGENTA << std::setw(13) << "*" << RESET << std::endl;
		std::cout << MAGENTA << "*" << std::setw(14) << RESET << "ft  time: " << RED << ft_len << MAGENTA << std::setw(13) << "*" << RESET << std::endl;
	}
	else
	{
		std::cout << MAGENTA << "*" << std::setw(14) << RESET << "std time: " << RED << std_len << std::setw(19) << MAGENTA << "*" << RESET << std::endl;
		std::cout << MAGENTA << "*" << std::setw(14) << RESET << "ft  time: " << GREEN << ft_len << std::setw(19) << MAGENTA << "*" << RESET << std::endl;
	}
	
	double delta = std / ft;
    if (delta >= 1)
        color = GREEN;
    if (delta < 0.5)
        color = YELLOW;
    if (delta < 0.05)
        color = RED;
	std::string delta_str = std::to_string(delta);
	std::cout << MAGENTA << "*" << std::setw(7) << " " << RESET << "performance: "<< color << "x" << delta_str << MAGENTA << std::setw(20 - delta_str.length()) << "*" << RESET << std::endl;
}

void comparision_result(int err_count, double comp_res)
{
	print_header("FINAL RESULT", 0);

	std::string err_len = std::to_string(err_count);
	std::string comp_len = std::to_string(comp_res);
    std::string col = GREEN;
    if (err_count > 0)
        col = RED;
    std::cout << MAGENTA << "*" << RESET << " (std vs ft): " << col << err_len << " errors" << RESET;
	std::cout << " in " << color << comp_len << RESET << " sec" << MAGENTA << std::string(3 - err_len.length(), ' ');
	std::cout << "*" << std::endl << std::string(42, '*') << std::endl << RESET << "\n";
	std::cout << BLUE << std::string(42, '*') << std::endl << RESET << "\n";

}

void print_test_results(void)
{
	int i = 0;
	while (i < names.size())
	{
		std::string col = GREEN;
		std::string result = GOOD;
		std::cout << YELLOW << std::left << std::setw(25) << names[i];
		if (time_ft[i] <= time_std[i])
		{
			std::cout << RED << std::setw(12) << time_ft[i];
			std::cout << GREEN << std::setw(12) << time_std[i];
		}
		else
		{
			std::cout << GREEN << std::setw(12) << time_ft[i];
			std::cout << RED << std::setw(12) << time_std[i];
		}
		if (err_count)
			col = RED;
		std::cout << col << std::setw(6) << err_count;
		if (time_ft[i] < time_std[i] && !err_count)
			col = GREEN;
		if (errors[i])
		{
			result = FAIL;
			col = RED;
		}
		std::cout << col << std::setw(6) << result << std::endl;
		i++;
	}
	std::cout << RESET;
}