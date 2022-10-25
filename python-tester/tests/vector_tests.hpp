#ifndef _VECTOR_TESTS_
#define _VECTOR_TESTS_

#include <iostream>
#include "test_utils.hpp"
#include <vector>

void test_vector_empty_ctor(long count);
void test_vector_param_ctor(long count);
void test_vector_time_two_param_constructor(long count);
void test_vector_time_size_capacity_empty(long count);
void test_vector_time_size_capacity_random(long count);
void test_vector_time_reserve(long count);
void test_vector_time_resize(long count);
void test_vector_time_push_back(long count);
void test_vector_time_pop_back(long count);
void test_vector_time_erase_position(long count);
void test_vector_time_erase_iter(long count);
void test_vector_time_clear(long count);
void test_vector_time_reverse_iter(long count);
void test_vector_time_swap(long count);
void test_vector_time_insert_position(long count);
void test_vector_time_insert_pos_value(long count);
void test_vector_time_insert_iter(long count);
void test_vector_time_comparison(long count);
void test_vector_time_assign_value(long count);
void test_vector_time_assign_range(long count);
void test_vector_time_assignment(long count);
void test_vector_time_copy_constructor(long count);
void test_vector_time_copy_range_constructor(long count);
void test_vector_time_access(long count);

#endif
