/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_time_tests.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 20:14:13 by ldurante          #+#    #+#             */
/*   Updated: 2022/12/01 22:19:07 by ldurante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.hpp"

void test_map_time_empty_constructor()
{
	//std test
	timer_start();
	for (int i = 0; i < count; ++i)
		std::map<std::string, int> p1;
	double std_res = timer_stop();

	//ft test
	timer_start();
	for (int i = 0; i < count; ++i)
		ft::map<std::string, int> p2;
	double ft_res = timer_stop();
	
	// results
	if (verbose)
	{
		performance_result(std_res, ft_res);
		comparision_result(0);
	}
	if (std_res != 0)
		time_perf.push_back(std_res / ft_res);
	else	
		time_perf.push_back(0);
	errors.push_back(err_count);
}

void test_map_time_insert_val()
{
	//init
    const size_t N = 42;
    const int M = std::numeric_limits<int>::max();    
	srand(time(NULL));
	{
		//output test
		timer_start();
		std::map<std::string, int> v1;
		ft::map<std::string, int> v2;
		for (size_t i = 0; i < N * N; ++i)
		{
			std::string fill = getNewId();
            int val = rand() % M;
			v1.insert(std::make_pair<std::string, int>(fill, val));
			v2.insert(ft::make_pair<std::string, int>(fill, val));
			if (!my_equal(v1.begin(),v1.end(),v2.begin()))
				++err_count;
		}
	}
	double comp_res = timer_stop();

	//std test
	std::map<std::string, int> v1;
	timer_start();
	for (int i = 0; i < count; ++i)
	{
        std::string fill = getNewId();
		v1.insert(std::make_pair<std::string, int>(fill, N));
	}
	double std_res = timer_stop();
	
	//ft test 
	ft::map<std::string, int> v2;
	timer_start();
	for (int i = 0; i < count; ++i)
	{
        std::string fill = getNewId();
		v2.insert(ft::make_pair<std::string, int>(fill, N));
	}
	double ft_res = timer_stop();
	
	// results
	if (verbose)
	{
		performance_result(std_res, ft_res);
		comparision_result(comp_res);
	}
	if (std_res != 0)
		time_perf.push_back(std_res / ft_res);
	else	
		time_perf.push_back(0);
	errors.push_back(err_count);
}

void test_map_time_size_empty_max()
{
	//init
    const size_t N = 42;
    const int M = 99;
	srand(time(NULL));
	{ 
		//output test
		timer_start();
		for (int i = 0; i < count / 3; ++i)
		{
			size_t num = rand() % N;
			std::map<std::string, int> v1;
			ft::map<std::string, int> v2;
			for (size_t i = 0; i < num; ++i)
			{
				std::string fill = getNewId();
				int  fill_n = rand() % M;
				v1.insert(std::make_pair<std::string, int>(fill, fill_n));
				v2.insert(ft::make_pair<std::string, int>(fill, fill_n));
			}
			int std_res = v1.size();
			int ft_res = v2.size();
			if (std_res != ft_res)
				++err_count;
			std_res = v1.max_size();
			ft_res = v2.max_size();
			if (std_res != ft_res)
				++err_count;
			bool std_res_b = v1.empty();
			bool ft_res_b = v2.empty();
			if (std_res_b != ft_res_b)
				++err_count;
		}
	}

	double comp_res = timer_stop();
	//std test
	std::map<std::string, int> v1;
	timer_start();
	for (int i = 0; i < count * 100; ++i)
	{
		v1.size();
		v1.max_size();
		v1.empty();
	}
	double std_res = timer_stop();
	
	//ft test 
	ft::map<std::string, int> v2;
	timer_start();
	for (int i = 0; i < count * 100; ++i)
	{
		v2.size();
		v2.max_size();
		v2.empty();
	}
	double ft_res = timer_stop();
	
	// results
	if (verbose)
	{
		performance_result(std_res, ft_res);
		comparision_result(comp_res);
	}
	if (std_res != 0)
		time_perf.push_back(std_res / ft_res);
	else	
		time_perf.push_back(0);
	errors.push_back(err_count);
}

void test_map_time_copy_constructor()
{
	//init
    const size_t N = 42;
    const int M = std::numeric_limits<int>::max();
	srand(time(NULL));
	{
		//output test
		timer_start();
		for (int i = 0; i < count / 3; ++i)
		{
			size_t num = rand() % N;
			std::map<std::string, int> v1;
			ft::map<std::string, int> v2;
			for (size_t i = 0; i < num; ++i)
			{
				std::string fill = getNewId();
				int  fill_n = rand() % M;
				v1.insert(std::make_pair<std::string, int>(fill, fill_n));
				v2.insert(ft::make_pair<std::string, int>(fill, fill_n));
			}
			std::map<std::string, int> v1_r(v1);
			ft::map<std::string, int> v2_r(v2);
			int std_res = v1_r.size();
			int ft_res = v2_r.size();
			if (std_res != ft_res)
			{ 
				++err_count;
				std::cout << "std size: " << std_res << " ft size : " << ft_res << std::endl;
			}
			if (!my_equal(v1_r.begin(),v1_r.end(),v2_r.begin()))
				++err_count;
		}
	}

	double comp_res = timer_stop();
	//std test
    size_t num = rand() % N;
	std::map<std::string, int> v1;
    for (size_t i = 0; i < num; ++i)
	{
	    std::string fill = getNewId();
        v1.insert(std::make_pair<std::string, int>(fill, N));
    }
	timer_start();
	for (int i = 0; i < count; ++i)
	    std::map<std::string, int> v1_r(v1);
	double std_res = timer_stop();
	
	//ft test
	ft::map<std::string, int> v2;
    for (size_t i = 0; i < num; ++i)
	{
	    std::string fill = getNewId();
        v2.insert(ft::make_pair<std::string, int>(fill, N));
    }
	timer_start();
	for (int i = 0; i < count; ++i)
		ft::map<std::string, int> v2_r(v2);
	double ft_res = timer_stop();
	
	// results
	if (verbose)
	{
		performance_result(std_res, ft_res);
		comparision_result(comp_res);
	}
	if (std_res != 0)
		time_perf.push_back(std_res / ft_res);
	else	
		time_perf.push_back(0);
	errors.push_back(err_count);
}

void test_map_time_begin_end()
{
	//init
    const size_t N = 42;
    const int M = std::numeric_limits<int>::max();
	srand(time(NULL));
	{
		//output test
		timer_start();
		for (int i = 0; i < count / 3; ++i)
		{
			size_t num = rand() % N;
			std::map<std::string, int> v1;
			ft::map<std::string, int> v2;
			for (size_t i = 0; i < num; ++i)
			{
				std::string fill = getNewId();
				int  fill_n = rand() % M;
				v1.insert(std::make_pair<std::string, int>(fill, fill_n));
				v2.insert(ft::make_pair<std::string, int>(fill, fill_n));
			}
			int std_res = v1.size();
			int ft_res = v2.size();
			if (std_res != ft_res)
				++err_count;
			if (!num) continue;
			std::map<std::string, int>::iterator it = v1.begin();
			ft::map<std::string, int>::iterator it_ft = v2.begin();
			if (!iter_compare(*it, *it_ft))
				++err_count;
			std::map<std::string, int>::const_iterator c_it = v1.begin();
			ft::map<std::string, int>::const_iterator c_it_ft = v2.begin();
			if (!iter_compare(*c_it, *c_it_ft))
				++err_count;
			std::map<std::string, int>::iterator eit = v1.end();
			ft::map<std::string, int>::iterator eit_ft = v2.end();
			--eit;
			--eit_ft;
			if (!iter_compare(*(eit), *(eit_ft)))
				++err_count;
			std::map<std::string, int>::const_iterator c_eit = v1.end();
			ft::map<std::string, int>::const_iterator c_eit_ft = v2.end();
			if (!iter_compare(*(--c_eit), *--(c_eit_ft)))
				++err_count;
		}
	}

	double comp_res = timer_stop();
	//std test
    size_t num = rand() % N;
	std::map<std::string, int> v1;
    for (size_t i = 0; i < num; ++i)
	{
	    std::string fill = getNewId();
        v1.insert(std::make_pair<std::string, int>(fill, N));
    }
	timer_start();
	for (int i = 0; i < count; ++i)
	{
	    v1.begin();
        v1.end();
	}
	double std_res = timer_stop();
	
	//ft test
	ft::map<std::string, int> v2;
    for (size_t i = 0; i < num; ++i)
	{
	    std::string fill = getNewId();
        v2.insert(ft::make_pair<std::string, int>(fill, N));
    }
	timer_start();
	for (int i = 0; i < count; ++i)
	{
		v2.begin();
        v2.end();
	}
	double ft_res = timer_stop();
	
	// results
	if (verbose)
	{
		performance_result(std_res, ft_res);
		comparision_result(comp_res);
	}
	if (std_res != 0)
		time_perf.push_back(std_res / ft_res);
	else	
		time_perf.push_back(0);
	errors.push_back(err_count);
}

void test_map_time_rbegin_rend()
{
	//init
    const size_t N = 42;
    const int M = std::numeric_limits<int>::max();
	srand(time(NULL));
	{
		//output test
		timer_start();
		for (int i = 0; i < count / 3; ++i)
		{
			size_t num = rand() % N;
			std::map<std::string, int> v1;
			ft::map<std::string, int> v2;
			for (size_t i = 0; i < num; ++i)
			{
				std::string fill = getNewId();
				int  fill_n = rand() % M;
				v1.insert(std::make_pair<std::string, int>(fill, fill_n));
				v2.insert(ft::make_pair<std::string, int>(fill, fill_n));
			}
			int std_res = v1.size();
			int ft_res = v2.size();
			if (std_res != ft_res)
				++err_count;
			if (!num) continue;
			std::map<std::string, int>::reverse_iterator it = v1.rbegin();
			ft::map<std::string, int>::reverse_iterator it_ft = v2.rbegin();
			if (!iter_compare(*it, *it_ft))
				++err_count;
			std::map<std::string, int>::const_reverse_iterator c_it = v1.rbegin();
			ft::map<std::string, int>::const_reverse_iterator c_it_ft = v2.rbegin();
			if (!iter_compare(*c_it, *c_it_ft))
				++err_count;
			std::map<std::string, int>::reverse_iterator eit = v1.rend();
			ft::map<std::string, int>::reverse_iterator eit_ft = v2.rend();
			if (!iter_compare(*(--eit), *(--eit_ft)))
				++err_count;
			std::map<std::string, int>::const_reverse_iterator c_eit = v1.rend();
			ft::map<std::string, int>::const_reverse_iterator c_eit_ft = v2.rend();
			if (!iter_compare(*(--c_eit), *--(c_eit_ft)))
				++err_count;
		}
	}

	double comp_res = timer_stop();
	//std test
    size_t num = rand() % N;
	std::map<std::string, int> v1;
    for (size_t i = 0; i < num; ++i)
	{
	    std::string fill = getNewId();
        v1.insert(std::make_pair<std::string, int>(fill, N));
    }
	timer_start();
	for (int i = 0; i < count; ++i)
	{
	    v1.rbegin();
        v1.rend();
	}
	double std_res = timer_stop();
	
	//ft test
	ft::map<std::string, int> v2;
    for (size_t i = 0; i < num; ++i)
	{
	    std::string fill = getNewId();
        v2.insert(ft::make_pair<std::string, int>(fill, N));
    }
	timer_start();
	for (int i = 0; i < count; ++i)
	{
		v2.rbegin();
        v2.rend();
	}
	double ft_res = timer_stop();
	
	// results
	if (verbose)
	{
		performance_result(std_res, ft_res);
		comparision_result(comp_res);
	}
	if (std_res != 0)
		time_perf.push_back(std_res / ft_res);
	else	
		time_perf.push_back(0);
	errors.push_back(err_count);
}

void test_map_time_operator_at()
{
	//init
    const size_t N = 42;
    const int M = std::numeric_limits<int>::max();
	srand(time(NULL));
	{
		//output test
		timer_start();
		for (int i = 0; i < count / 3; ++i)
		{
			size_t num = rand() % N;
			std::map<std::string, int> v1;
			ft::map<std::string, int> v2;
			for (size_t i = 0; i < num; ++i)
			{
				std::string fill = getNewId();
				int  fill_n = rand() % M;
				v1.insert(std::make_pair<std::string, int>(fill, fill_n));
				v2.insert(ft::make_pair<std::string, int>(fill, fill_n));
			}
			std::string ref = getNewId();
			if (v1[ref] != v2[ref])
				++err_count;
			if (v1.size() != v2.size())
				++err_count;
			if (v1.at(ref) != v2.at(ref))
				++err_count;
		}
	}

	double comp_res = timer_stop();
	//std test
    size_t num = rand() % N;
	std::map<std::string, int> v1;
    std::string fill_s;
    for (size_t i = 0; i < num; ++i)
	{
	    fill_s = getNewId();
        v1.insert(std::make_pair<std::string, int>(fill_s, N));
    }
	timer_start();
	for (int i = 0; i < count; ++i)
	{
        v1[fill_s];
        v1.at(fill_s);
	}
	double std_res = timer_stop();
	
	//ft test
	ft::map<std::string, int> v2;
    for (size_t i = 0; i < num; ++i)
	{
	    fill_s = getNewId();
        v2.insert(ft::make_pair<std::string, int>(fill_s, N));
    }
	timer_start();
	for (int i = 0; i < count; ++i)
	{
        v2[fill_s];
        v2.at(fill_s);
	}
	double ft_res = timer_stop();
	
	// results
	if (verbose)
	{
		performance_result(std_res, ft_res);
		comparision_result(comp_res);
	}
	if (std_res != 0)
		time_perf.push_back(std_res / ft_res);
	else	
		time_perf.push_back(0);
	errors.push_back(err_count);
}

void test_map_time_assignment_op()
{
	//init
    const size_t N = 42;
    const int M = std::numeric_limits<int>::max();
	srand(time(NULL));
	{
		//output test
		timer_start();
		for (int i = 0; i < count / 3; ++i)
		{
			size_t num = rand() % N;
			std::map<std::string, int> v1;
			ft::map<std::string, int> v2;
			for (size_t i = 0; i < num; ++i)
			{
				std::string fill = getNewId();
				int  fill_n = rand() % M;
				v1.insert(std::make_pair<std::string, int>(fill, fill_n));
				v2.insert(ft::make_pair<std::string, int>(fill, fill_n));
			}
			std::map<std::string, int> v1_r;
			ft::map<std::string, int> v2_r;
			v1_r = v1;
			v2_r = v2;
			int std_res = v1_r.size();
			int ft_res = v2_r.size();
			if (std_res != ft_res)
				++err_count;
			if (!my_equal(v1_r.begin(),v1_r.end(),v2_r.begin()))
				++err_count;
		}
	}

	double comp_res = timer_stop();
	//std test
    size_t num = rand() % N;
	std::map<std::string, int> v1;
    for (size_t i = 0; i < num; ++i)
	{
	    std::string fill = getNewId();
        v1.insert(std::make_pair<std::string, int>(fill, N));
    }
    std::map<std::string, int> v1_r;
	timer_start();
	for (int i = 0; i < count; ++i)
        v1_r = v1;
	double std_res = timer_stop();
	
	//ft test
	ft::map<std::string, int> v2;
    for (size_t i = 0; i < num; ++i)
	{
	    std::string fill = getNewId();
        v2.insert(ft::make_pair<std::string, int>(fill, N));
    }
	ft::map<std::string, int> v2_r;
	timer_start();
	for (int i = 0; i < count; ++i)
        v2_r = v2;
	double ft_res = timer_stop();
	
	// results
	if (verbose)
	{
		performance_result(std_res, ft_res);
		comparision_result(comp_res);
	}
	if (std_res != 0)
		time_perf.push_back(std_res / ft_res);
	else	
		time_perf.push_back(0);
	errors.push_back(err_count);
}

void test_map_time_range_constructor()
{
	//init
    const size_t N = 42;
    const int M = std::numeric_limits<int>::max();
	srand(time(NULL));
	{
		//output test
		timer_start();
		for (int i = 0; i < count / 3; ++i)
		{
			size_t num = rand() % N;
			std::map<std::string, int> v1;
			ft::map<std::string, int> v2;
			for (size_t i = 0; i < num; ++i)
			{
				std::string fill = getNewId();
				int  fill_n = rand() % M;
				v1.insert(std::make_pair<std::string, int>(fill, fill_n));
				v2.insert(ft::make_pair<std::string, int>(fill, fill_n));
			}
			std::map<std::string, int> v1_r(v1.begin(), v1.end());
			ft::map<std::string, int> v2_r(v2.begin(), v2.end());
			int std_res = v1_r.size();
			int ft_res = v2_r.size();
			if (std_res != ft_res)
				++err_count;
			if (!my_equal(v1_r.begin(),v1_r.end(),v2_r.begin()))
				++err_count;
		}
	}

	double comp_res = timer_stop();
	//std test
    size_t num = rand() % N;
	std::map<std::string, int> v1;
    for (size_t i = 0; i < num; ++i)
	{
	    std::string fill = getNewId();
        v1.insert(std::make_pair<std::string, int>(fill, N));
    }
	timer_start();
	for (int i = 0; i < count; ++i)
		std::map<std::string, int> v1_r(v1.begin(), v1.end());
	double std_res = timer_stop();
	
	//ft test
	ft::map<std::string, int> v2;
    for (size_t i = 0; i < num; ++i)
	{
	    std::string fill = getNewId();
        v2.insert(ft::make_pair<std::string, int>(fill, N));
    }
	timer_start();
	for (int i = 0; i < count; ++i)
		ft::map<std::string, int> v2_r(v2.begin(), v2.end());
	double ft_res = timer_stop();
	
	// results
	if (verbose)
	{
		performance_result(std_res, ft_res);
		comparision_result(comp_res);
	}
	if (std_res != 0)
		time_perf.push_back(std_res / ft_res);
	else	
		time_perf.push_back(0);
	errors.push_back(err_count);
}

void test_map_time_comparison()
{
	//init
    const size_t N = 42;
    const int M = std::numeric_limits<int>::max();
	srand(time(NULL));
	{
		//output test
		timer_start();
		for (int i = 0; i < count / 3; ++i)
		{
			size_t num = rand() % N;
			std::map<std::string, int> v1;
			std::map<std::string, int> v1_r;
			ft::map<std::string, int> v2;
			ft::map<std::string, int> v2_r;
			for (size_t i = 0; i < num; ++i)
			{
				std::string fill = getNewId();
				int  fill_n = rand() % M;
				v1.insert(std::make_pair<std::string, int>(fill, fill_n));
				v1_r.insert(std::make_pair<std::string, int>(fill, fill_n));
				v2.insert(ft::make_pair<std::string, int>(fill, fill_n));
				v2_r.insert(ft::make_pair<std::string, int>(fill, fill_n));
			}
			if ((v1 == v1_r) != (v2 == v2_r))
				++err_count;
			if ((v1 < v1_r) != (v2 < v2_r))
				++err_count;
			if ((v1 != v1_r) != ( v2 != v2_r))
				++err_count;
			if ((v1 > v1_r) != (v2 > v2_r))
				++err_count;
			if ((v1 <= v1_r) != (v2 <= v2_r))
				++err_count;
			if ((v1 >= v1_r) != (v2 >= v2_r))
				++err_count;
		}
	}
	double comp_res = timer_stop();

	if (verbose)
	{
		performance_result(0, 0);
		comparision_result(comp_res);
	}
	time_perf.push_back(0);
	errors.push_back(err_count);
}

void test_map_time_find()
{
	//init
    const size_t N = 42;
    const int M = std::numeric_limits<int>::max();
	srand(time(NULL));
	{
		//output test
		timer_start();
		for (int i = 0; i < count / 3; ++i)
		{
			size_t num = rand() % N;
			std::map<std::string, int> v1;
			ft::map<std::string, int> v2;
			std::string save_to_find;
			for (size_t i = 0; i < num; ++i)
			{
				std::string fill = getNewId();
				int  fill_n = rand() % M;
				v1.insert(std::make_pair<std::string, int>(fill, fill_n));
				v2.insert(ft::make_pair<std::string, int>(fill, fill_n));
				save_to_find = fill;
			}
			std::string ref = getNewId();
			ptrdiff_t d1 = std::distance(v1.begin(), v1.find(ref));
			ptrdiff_t d2 = ft::distance(v2.begin(), v2.find(ref));
			if (d1 != d2)
				++err_count;
			d1 = std::distance(v1.begin(), v1.find(save_to_find));
			d2 = ft::distance(v2.begin(), v2.find(save_to_find));
			if (d1 != d2)
			{
				++err_count;
				//  std::cout << "distance std : " << d1 << std::endl;
				//  std::cout << "distance ft : " << d2 << std::endl;
			}
		}
	}
	double comp_res = timer_stop();

	//std test
    size_t num = rand() % N;
	std::map<std::string, int> v1;
    std::string fill_s;
    for (size_t i = 0; i < num; ++i)
	{
	    fill_s = getNewId();
        v1.insert(std::make_pair<std::string, int>(fill_s, N));
    }
	timer_start();
	for (int i = 0; i < count; ++i)
		v1.find(fill_s);
	double std_res = timer_stop();
	
	//ft test
	ft::map<std::string, int> v2;
    for (size_t i = 0; i < num; ++i)
	{
	    fill_s = getNewId();
        v2.insert(ft::make_pair<std::string, int>(fill_s, N));
    }
	timer_start();
	for (int i = 0; i < count; ++i)
		v2.find(fill_s);
	double ft_res = timer_stop();
	
	// results
	if (verbose)
	{
		performance_result(std_res, ft_res);
		comparision_result(comp_res);
	}
	if (std_res != 0)
		time_perf.push_back(std_res / ft_res);
	else	
		time_perf.push_back(0);
	errors.push_back(err_count);
}

void test_map_time_swap()
{
	//init
    const size_t N = 42;
    const int M = std::numeric_limits<int>::max();
	srand(time(NULL));
	{
		//output test
		timer_start();
		for (int i = 0; i < count / 6; ++i)
		{
			size_t num = N;
			std::map<std::string, int> v1;
			ft::map<std::string, int> v2;
			for (size_t i = 0; i < num; ++i)
			{
				std::string fill = getNewId();
				int  fill_n = rand() % M;
				v1.insert(std::make_pair<std::string, int>(fill, fill_n));
				v2.insert(ft::make_pair<std::string, int>(fill, fill_n));
			}
			std::map<std::string, int> v1_r(v1);
			ft::map<std::string, int> v2_r(v2);
			v1.swap(v1_r);
			v2.swap(v2_r);
			if (v1.size() != v1_r.size())
				++err_count;
			if (!my_equal(v1_r.begin(),v1_r.end(),v2_r.begin()))
				++err_count;
			if (!my_equal(v1.begin(),v1.end(),v2.begin()))
				++err_count;
		}
	}
	double comp_res = timer_stop();

	//std test
    size_t num = rand() % N;
	std::map<std::string, int> v1;
	std::map<std::string, int> v1_r;
    for (size_t i = 0; i < num; ++i)
	{
	    std::string fill = getNewId();
        v1.insert(std::make_pair<std::string, int>(fill, N));
        v1_r.insert(std::make_pair<std::string, int>(fill, N));
    }
	timer_start();
	for (int i = 0; i < count; ++i)
		v1.swap(v1_r);
	double std_res = timer_stop();
	
	//ft test
	ft::map<std::string, int> v2;
	ft::map<std::string, int> v2_r;
    for (size_t i = 0; i < num; ++i)
	{
	    std::string fill = getNewId();
        v2.insert(ft::make_pair<std::string, int>(fill, N));
        v2_r.insert(ft::make_pair<std::string, int>(fill, N));
    }
	timer_start();
	for (int i = 0; i < count; ++i)
		v2.swap(v2_r);
	double ft_res = timer_stop();
	
	// results
	if (verbose)
	{
		performance_result(std_res, ft_res);
		comparision_result(comp_res);
	}
	if (std_res != 0)
		time_perf.push_back(std_res / ft_res);
	else	
		time_perf.push_back(0);
	errors.push_back(err_count);
}

void test_map_time_count_clear()
{
	//init
    const size_t N = 42;
    const int M = std::numeric_limits<int>::max();
	srand(time(NULL));
	{
		//output test
		timer_start();
		for (int i = 0; i < count / 3; ++i)
		{
			size_t num = rand() % N;
			std::map<std::string, int> v1;
			ft::map<std::string, int> v2;
			std::string save_to_find;
			for (size_t i = 0; i < num; ++i)
			{
				std::string fill = getNewId();
				int  fill_n = rand() % M;
				v1.insert(std::make_pair<std::string, int>(fill, fill_n));
				v2.insert(ft::make_pair<std::string, int>(fill, fill_n));
				save_to_find = fill;
			}
			std::string ref = getNewId();
			size_t d1 = v1.count(ref);
			size_t d2 = v2.count(ref);
			if (d1 != d2)
				++err_count;
			d1 = v1.count(save_to_find);
			d2 = v2.count(save_to_find);
			if (d1 != d2)
				++err_count;
			v1.clear();
			v2.clear();
			d1 = v1.count(save_to_find);
			d2 = v2.count(save_to_find);
			if (d1 != d2)
				++err_count;
		}
	}
	double comp_res = timer_stop();

	//std test
    size_t num = rand() % N;
	std::map<std::string, int> v1;
    std::string fill_s;
    for (size_t i = 0; i < num; ++i)
	{
	    fill_s = getNewId();
        v1.insert(std::make_pair<std::string, int>(fill_s, N));
    }
	timer_start();
	for (int i = 0; i < count; ++i)
	{
		v1.count(fill_s);
		v1.clear();
	}
	double std_res = timer_stop();
	
	//ft test
	ft::map<std::string, int> v2;
    for (size_t i = 0; i < num; ++i)
	{
	    fill_s = getNewId();
        v2.insert(ft::make_pair<std::string, int>(fill_s, N));
    }
	timer_start();
	for (int i = 0; i < count; ++i)
	{
		v2.count(fill_s);
		v2.clear();
	}
	double ft_res = timer_stop();
	
	// results
	if (verbose)
	{
		performance_result(std_res, ft_res);
		comparision_result(comp_res);
	}
	if (std_res != 0)
		time_perf.push_back(std_res / ft_res);
	else	
		time_perf.push_back(0);
	errors.push_back(err_count);
}

void test_map_insert_pos(long count)
{
	//init
    const size_t N = 42;
    const int M = std::numeric_limits<int>::max();    
	srand(time(NULL));
	{
		//output test
		timer_start();
		long err_count = 0;
		std::map<std::string, int> v1;
		std::map<std::string, int> v1_r;
		ft::map<std::string, int> v2;
		ft::map<std::string, int> v2_r;
		for (size_t i = 0; i < N * 10; ++i)
		{
			std::string fill = getNewId();
			int val = rand() % M;
			std::pair<std::string, int> p1(fill, val);
			ft::pair<std::string, int> p2(fill, val);
			v1.insert(p1);
			v2.insert(p2);
			v1_r.insert(v1.begin(), p1);
			v2_r.insert(v2.begin(), p2);
			if (!my_equal(v1_r.begin(),v1_r.end(),v2_r.begin()))
				++err_count;
		}
	}
	double comp_res = timer_stop();

	//std test
	std::map<std::string, int> v1;
	std::map<std::string, int> v1_r;
	std::pair<std::string, int> p1;
	for (int i = 0; i < count; ++i)
	{
        std::string fill = getNewId();
		p1.first = fill;
		p1.second = N;
		v1.insert(p1);
	}
	timer_start();
	v1_r.insert(v1.begin(), p1);
	double std_res = timer_stop();
	
	//ft test 
	ft::map<std::string, int> v2;
	ft::map<std::string, int> v2_r;
	ft::pair<std::string, int> p2;
	for (int i = 0; i < count; ++i)
	{
        std::string fill = getNewId();
		p2.first = fill;
		p2.second = N;
		v2.insert(p2);
	}
	timer_start();
	v2_r.insert(v2.begin(), p2);
	double ft_res = timer_stop();

	// results
	if (verbose)
	{
		performance_result(std_res, ft_res);
		comparision_result(comp_res);
	}
	if (std_res != 0)
		time_perf.push_back(std_res / ft_res);
	else	
		time_perf.push_back(0);
	errors.push_back(err_count);
}

void test_map_time_insert_range()
{
	//init
    const size_t N = 42;
    const int M = std::numeric_limits<int>::max();    
	srand(time(NULL));
	{
		//output test
		timer_start();
		std::map<std::string, int> v1;
		std::map<std::string, int> v1_r;
		ft::map<std::string, int> v2;
		ft::map<std::string, int> v2_r;
		for (size_t i = 0; i < N * 10; ++i)
		{
			std::string fill = getNewId();
			int val = rand() % M;
			v1.insert(std::make_pair<std::string, int>(fill, val));
			v2.insert(ft::make_pair<std::string, int>(fill, val));
			v1_r.insert(v1.begin(), v1.end());
			v2_r.insert(v2.begin(), v2.end());
			if (!my_equal(v1_r.begin(),v1_r.end(),v2_r.begin()))
				++err_count;
		}
	}
	double comp_res = timer_stop();

	//std test
	std::map<std::string, int> v1;
	std::map<std::string, int> v1_r;
	for (int i = 0; i < count; ++i)
	{
        std::string fill = getNewId();
		v1.insert(std::make_pair<std::string, int>(fill, N));
	}
	timer_start();
	v1_r.insert(v1.begin(), v1.end());
	double std_res = timer_stop();
	
	//ft test 
	ft::map<std::string, int> v2;
	ft::map<std::string, int> v2_r;
	for (int i = 0; i < count; ++i)
	{
        std::string fill = getNewId();
		v2.insert(ft::make_pair<std::string, int>(fill, N));
	}
	timer_start();
	v2_r.insert(v2.begin(), v2.end());
	double ft_res = timer_stop();
	
	// results
	if (verbose)
	{
		performance_result(std_res, ft_res);
		comparision_result(comp_res);
	}
	if (std_res != 0)
		time_perf.push_back(std_res / ft_res);
	else	
		time_perf.push_back(0);
	errors.push_back(err_count);
}

void test_map_time_erase_range()
{
	//init
    const size_t N = 42;
    const int M = std::numeric_limits<int>::max();
	srand(time(NULL));
	{
		//output test
		timer_start();
		for (int i = 0; i < count / 3; ++i)
		{
			size_t num = rand() % N;
			std::map<std::string, int> v1;
			ft::map<std::string, int> v2;
			for (size_t i = 0; i < num; ++i)
			{
				std::string fill = getNewId();
				int  fill_n = rand() % M;
				v1.insert(std::make_pair<std::string, int>(fill, fill_n));
				v2.insert(ft::make_pair<std::string, int>(fill, fill_n));
			}
			if (v1.size() != v2.size()) 
				++err_count;
			v1.erase(v1.begin(), v1.end());
			v2.erase(v2.begin(), v2.end());
			if(v1.empty() != v2.empty())
				++err_count;
			if (v1.size() != v2.size())
				++err_count;
		}
	}
	double comp_res = timer_stop();

	//std test
    size_t num = rand() % N;
	std::map<std::string, int> v1;
    for (size_t i = 0; i < num; ++i)
	{
	    std::string fill = getNewId();
        v1.insert(std::make_pair<std::string, int>(fill, N));
    }
	timer_start();
	for (int i = 0; i < count; ++i)
		v1.erase(v1.begin(), v1.end());
	double std_res = timer_stop();
	
	//ft test
	ft::map<std::string, int> v2;
    for (size_t i = 0; i < num; ++i)
	{
	    std::string fill = getNewId();
        v2.insert(ft::make_pair<std::string, int>(fill, N));
    }
	timer_start();
	for (int i = 0; i < count; ++i)
		v2.erase(v2.begin(), v2.end());
	double ft_res = timer_stop();
	
	// results
	if (verbose)
	{
		performance_result(std_res, ft_res);
		comparision_result(comp_res);
	}
	if (std_res != 0)
		time_perf.push_back(std_res / ft_res);
	else	
		time_perf.push_back(0);
	errors.push_back(err_count);
}

void test_map_time_erase_pos()
{
	//init
    const size_t N = 42;
    const int M = std::numeric_limits<int>::max();
	srand(time(NULL));
	{
		//output test
		timer_start();
		for (int i = 0; i < count / 3; ++i)
		{
			size_t num = rand() % N + 1;
			std::map<std::string, int> v1;
			ft::map<std::string, int> v2;
			for (size_t i = 0; i < num; ++i)
			{
				std::string fill = getNewId();
				int  fill_n = rand() % M;
				v1.insert(std::make_pair<std::string, int>(fill, fill_n));
				v2.insert(ft::make_pair<std::string, int>(fill, fill_n));
			}
			if (v1.size() != v2.size())
				++err_count;
			v1.erase(v1.begin());
			v2.erase(v2.begin());
			if(v1.empty() != v2.empty())
				++err_count;
			if (v1.size() != v2.size())
				++err_count;
			if (!my_equal(v1.begin(),v1.end(),v2.begin()))
				++err_count;
		}
	}
	double comp_res = timer_stop();

	//std test
    size_t num = count;
	std::map<std::string, int> v1;
    for (size_t i = 0; i < num; ++i)
	{
	    std::string fill = getNewId();
        v1.insert(std::make_pair<std::string, int>(fill, N));
    }
	timer_start();
	for (size_t i = 0; i < num; ++i)
		v1.erase(v1.begin());
	double std_res = timer_stop();
	
	//ft test
	ft::map<std::string, int> v2;
    for (size_t i = 0; i < num; ++i)
	{
	    std::string fill = getNewId();
        v2.insert(ft::make_pair<std::string, int>(fill, N));
    }
	timer_start();
	for (size_t i = 0; i < num; ++i)
		v2.erase(v2.begin());
	double ft_res = timer_stop();
	
	// results
	if (verbose)
	{
		performance_result(std_res, ft_res);
		comparision_result(comp_res);
	}
	if (std_res != 0)
		time_perf.push_back(std_res / ft_res);
	else	
		time_perf.push_back(0);
	errors.push_back(err_count);
}

void test_map_time_erase_val()
{
	//init
    const size_t N = 42;
    const int M = std::numeric_limits<int>::max();
	srand(time(NULL));
	{
		//output test
		timer_start();
		for (int i = 0; i < count / 3; ++i)
		{
			size_t num = rand() % N;
			std::map<std::string, int> v1;	    
			ft::map<std::string, int> v2;
			std::vector<std::string> save;
			for (size_t i = 0; i < num; ++i)
			{
				std::string fill = getNewId();
				save.push_back(fill);
				int  fill_n = rand() % M;
				v1.insert(std::make_pair<std::string, int>(fill, fill_n));
				v2.insert(ft::make_pair<std::string, int>(fill, fill_n));
			}
			if (v1.size() != v2.size()) 
				++err_count;
			for (size_t i = 0; i < save.size(); ++i)
			{
				v1.erase(save[i]);
				v2.erase(save[i]);
			}
			if(v1.empty() != v2.empty())
				++err_count;
			if (v1.size() != v2.size())
				++err_count;
		}
	}
	double comp_res = timer_stop();

	//std test
    size_t num = count;
	std::map<std::string, int> v1;
	std::vector<std::string> save;
    for (size_t i = 0; i < num; ++i)
	{
	    std::string fill = getNewId();
		save.push_back(fill);
        v1.insert(std::make_pair<std::string, int>(fill, N));
    }
	timer_start();
	for (size_t i = 0; i < save.size(); ++i)
		v1.erase(save[i]);
	double std_res = timer_stop();
	
	//ft test
	ft::map<std::string, int> v2;
	save.clear();
    for (size_t i = 0; i < num; ++i)
	{
	    std::string fill = getNewId();
		save.push_back(fill);
        v2.insert(ft::make_pair<std::string, int>(fill, N));
    }
	timer_start();
	for (size_t i = 0; i < save.size(); ++i)
		v2.erase(save[i]);
	double ft_res = timer_stop();
	
	// results
	if (verbose)
	{
		performance_result(std_res, ft_res);
		comparision_result(comp_res);
	}
	if (std_res != 0)
		time_perf.push_back(std_res / ft_res);
	else	
		time_perf.push_back(0);
	errors.push_back(err_count);
}

void test_map_time_upper_bound()
{
	//init
    const size_t N = 42;
    const int M = std::numeric_limits<int>::max();
	srand(time(NULL));
	{
		//output test
		timer_start();
		for (int i = 0; i < count / 3; ++i)
		{
			size_t num = rand() % N;
			std::map<std::string, int> v1;
			ft::map<std::string, int> v2;
			for (size_t i = 0; i < num; ++i)
			{
				std::string fill = getNewId();
				int  fill_n = rand() % M;
				v1.insert(std::make_pair<std::string, int>(fill, fill_n));
				v2.insert(ft::make_pair<std::string, int>(fill, fill_n));
			}
			int std_res = v1.size();
			int ft_res = v2.size();
			if (std_res != ft_res)
				++err_count;
			if (!num) continue;
			std::string bound = getNewId();
			std::map<std::string, int>::iterator it = v1.upper_bound(bound);
			ft::map<std::string, int>::iterator it_ft = v2.upper_bound(bound);
			if (it == v1.end() || it_ft == v2.end())
				continue;
			if (!iter_compare(*it, *it_ft))
				++err_count;
		}
	}
	double comp_res = timer_stop();

	//std test
    size_t num = rand() % N;
	std::map<std::string, int> v1;
    for (size_t i = 0; i < num; ++i)
	{
	    std::string fill = getNewId();
        v1.insert(std::make_pair<std::string, int>(fill, N));
    }
	std::string bound = getNewId();
	timer_start();
	for (int i = 0; i < count; ++i)
		v1.upper_bound(bound);
	double std_res = timer_stop();
	
	//ft test
	ft::map<std::string, int> v2;
    for (size_t i = 0; i < num; ++i)
	{
	    std::string fill = getNewId();
        v2.insert(ft::make_pair<std::string, int>(fill, N));
    }
	timer_start();
	for (int i = 0; i < count; ++i)
		v2.upper_bound(bound);
	double ft_res = timer_stop();
	
	// results
	if (verbose)
	{
		performance_result(std_res, ft_res);
		comparision_result(comp_res);
	}
	if (std_res != 0)
		time_perf.push_back(std_res / ft_res);
	else	
		time_perf.push_back(0);
	errors.push_back(err_count);
}

void test_map_time_lower_bound()
{
	//init
    const size_t N = 42;
    const int M = std::numeric_limits<int>::max();
	srand(time(NULL));
	{
		//output test
		timer_start();
		for (int i = 0; i < count / 3; ++i)
		{
			size_t num = rand() % N;
			std::map<std::string, int> v1;
			ft::map<std::string, int> v2;
			for (size_t i = 0; i < num; ++i)
			{
				std::string fill = getNewId();
				int  fill_n = rand() % M;
				v1.insert(std::make_pair<std::string, int>(fill, fill_n));
				v2.insert(ft::make_pair<std::string, int>(fill, fill_n));
			}
			int std_res = v1.size();
			int ft_res = v2.size();
			if (std_res != ft_res)
				++err_count;
			if (!num)
				continue;
			std::string bound = getNewId();
			std::map<std::string, int>::iterator it = v1.lower_bound(bound);
			ft::map<std::string, int>::iterator it_ft = v2.lower_bound(bound);
			if (it == v1.end() || it_ft == v2.end())
				continue;
			if (!iter_compare(*it, *it_ft))
				++err_count;
		}
	}
	double comp_res = timer_stop();

	//std test
    size_t num = rand() % N;
	std::map<std::string, int> v1;
    for (size_t i = 0; i < num; ++i)
	{
	    std::string fill = getNewId();
        v1.insert(std::make_pair<std::string, int>(fill, N));
    }
	std::string bound = getNewId();
	timer_start();
	for (int i = 0; i < count; ++i)
		v1.lower_bound(bound);
	double std_res = timer_stop();
	
	//ft test
	ft::map<std::string, int> v2;
    for (size_t i = 0; i < num; ++i)
	{
	    std::string fill = getNewId();
        v2.insert(ft::make_pair<std::string, int>(fill, N));
    }
	timer_start();
	for (int i = 0; i < count; ++i)
		v2.lower_bound(bound);
	double ft_res = timer_stop();
	
	// results
	if (verbose)
	{
		performance_result(std_res, ft_res);
		comparision_result(comp_res);
	}
	if (std_res != 0)
		time_perf.push_back(std_res / ft_res);
	else	
		time_perf.push_back(0);
	errors.push_back(err_count);
}

void test_map_time_equal_range()
{
	//init
    const size_t N = 42;
    const int M = std::numeric_limits<int>::max();
	srand(time(NULL));
	{
		//output test
		timer_start();
		for (int i = 0; i < count / 3; ++i)
		{
			size_t num = rand() % N;
			std::map<std::string, int> v1;
			ft::map<std::string, int> v2;
			for (size_t i = 0; i < num; ++i)
			{
				std::string fill = getNewId();
				int  fill_n = rand() % M;
				v1.insert(std::make_pair<std::string, int>(fill, fill_n));
				v2.insert(ft::make_pair<std::string, int>(fill, fill_n));
			}
			int std_res = v1.size();
			int ft_res = v2.size();
			if (std_res != ft_res)
				++err_count;
			if (!num)
				continue;
			std::string bound = getNewId();
			std::pair<std::map<std::string, int>::iterator, 
			std::map<std::string, int>::iterator> it = v1.equal_range(bound);
			ft::pair<ft::map<std::string, int>::iterator, 
			ft::map<std::string, int>::iterator> it_ft = v2.equal_range(bound);
			if (it.first == v1.end() || it_ft.first == v2.end())
				continue;
			if (!iter_compare(*it.first, *it_ft.first))
				++err_count;
		}
	}
	double comp_res = timer_stop();

	//std test
    size_t num = rand() % N;
	std::map<std::string, int> v1;
    for (size_t i = 0; i < num; ++i)
	{
	    std::string fill = getNewId();
        v1.insert(std::make_pair<std::string, int>(fill, N));
    }
	std::string bound = getNewId();
	timer_start();
	for (int i = 0; i < count; ++i)
		v1.equal_range(bound);
	double std_res = timer_stop();
	
	//ft test
	ft::map<std::string, int> v2;
    for (size_t i = 0; i < num; ++i)
	{
	    std::string fill = getNewId();
        v2.insert(ft::make_pair<std::string, int>(fill, N));
    }
	timer_start();
	for (int i = 0; i < count; ++i)
		v2.equal_range(bound);
	double ft_res = timer_stop();
	
	// results
	if (verbose)
	{
		performance_result(std_res, ft_res);
		comparision_result(comp_res);
	}
	if (std_res != 0)
		time_perf.push_back(std_res / ft_res);
	else	
		time_perf.push_back(0);
	errors.push_back(err_count);
}
