/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_and_comparision.cpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 00:01:22 by ldurante          #+#    #+#             */
/*   Updated: 2022/11/03 23:42:45 by ldurante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.hpp"

std::clock_t   	start;
std::string		color;

void print_project_title(void)
{
	std::cout << std::endl << std::endl << YELLOW;
	std::cout << "███████╗████████╗      ██████╗ ██████╗ ███╗   ██╗████████╗ █████╗ ██╗███╗   ██╗███████╗██████╗ ███████╗" << std::endl;
	std::cout << "██╔════╝╚══██╔══╝     ██╔════╝██╔═══██╗████╗  ██║╚══██╔══╝██╔══██╗██║████╗  ██║██╔════╝██╔══██╗██╔════╝" << std::endl;
	std::cout << "█████╗     ██║        ██║     ██║   ██║██╔██╗ ██║   ██║   ███████║██║██╔██╗ ██║█████╗  ██████╔╝███████╗" << std::endl;
	std::cout << "██╔══╝     ██║        ██║     ██║   ██║██║╚██╗██║   ██║   ██╔══██║██║██║╚██╗██║██╔══╝  ██╔══██╗╚════██║" << std::endl;
	std::cout << "██║        ██║███████╗╚██████╗╚██████╔╝██║ ╚████║   ██║   ██║  ██║██║██║ ╚████║███████╗██║  ██║███████║" << std::endl;
	std::cout << "╚═╝        ╚═╝╚══════╝ ╚═════╝ ╚═════╝ ╚═╝  ╚═══╝   ╚═╝   ╚═╝  ╚═╝╚═╝╚═╝  ╚═══╝╚══════╝╚═╝  ╚═╝╚══════╝" << std::endl;
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
		std::cout << RESET;
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

std::string getNewId()
{
    const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";
    std::string tmp_s;
    int len = 20;
    tmp_s.reserve(len);
    for (int i = 0; i < len; ++i)
        tmp_s += alphanum[rand() % (sizeof(alphanum) - 1)];
    return tmp_s;
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
	
	double delta = 0;
	color = GREEN;
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
	
	if (std == 0)
	{
		delta = ft;	
		if (delta <= 1)
			color = GREEN;
		if (delta > 0.5)
			color = YELLOW;
		if (delta > 0.05)
			color = RED;
	}
	else
	{
		delta = std / ft;
		if (delta >= 1)
			color = GREEN;
		if (delta < 0.5)
			color = YELLOW;
		if (delta < 0.05)
			color = RED;
	}
	if (std == ft)
	{
		delta = 0;
		color = RESET;
	}
	std::string delta_str = std::to_string(delta);
	std::cout << MAGENTA << "*" << std::setw(7) << " " << RESET << "performance: "<< color << "x" << delta_str << MAGENTA << std::right << std::setw(20 - delta_str.length()) << "*" << RESET << std::endl;
}

void comparision_result(double comp_res)
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
	std::string col = GREEN;
	std::string result = GOOD;
	long test_passed = 0;

	std::cout << std::left << GRAY << BOLD;
	std::cout << std::setw(40) << "TEST NAME" << std::setw(20) << "PERFORMANCE";
	std::cout << std::setw(16) << "ERRORS" << std::setw(16) << "RESULT" << std::endl;
	std::cout << std::string(90, '-') << RESET << std::endl;
	for(size_t i = 0; i < names.size(); i++)
	{
		col = GREEN;
		result = GOOD;
		std::cout << BOLD << RESET << std::left << std::setw(42) << names[i];
		if (time_perf[i] >= 1 || time_perf[i] == 0)
			col = GREEN;
		else if (time_perf[i] < 0.5 && time_perf[i] > 0.05)
			col = YELLOW;
		else if (time_perf[i] < 0.05)
			col = RED;
		std::cout << col << "x" << std::setw(19) << time_perf[i];
		col = GREEN;
		if (errors[i])
		{
			col = RED;
			result = FAIL;
			test_passed++;
		}
		std::cout << col << std::setw(16) << errors[i];
		std::cout << col << std::setw(6) << result << std::endl;
	}
	std::cout << GRAY << std::string(90, '-') << std::endl;
	col = GREEN;
	if (test_passed)
		col = RED;
	std::cout << "TESTS PASSED:   " << col << names.size() - test_passed << "/" << names.size() << std::endl << std::endl;
	std::cout << RESET;
}
