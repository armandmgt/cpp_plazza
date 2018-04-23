/*
** EPITECH PROJECT, 2018
** plazza
** File description:
** test_SplitableMap
*/

#include <criterion/criterion.h>
#include <iostream>
#include "container/SplitMap.hpp"

Test(split_map, empty_map)
{
	std::map<int, int> m({});
	auto msize = split(m, 3).size();
	cr_assert_eq(msize, 0);
}

Test(split_map, nine_elems)
{
	std::map<int, int> m({
		     {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5},
		     {6, 6}, {7, 7}, {8, 8}, {9, 9}
	});

	auto v = split(m, 3);
	cr_assert_eq(v.size(), 3);
	for (std::size_t i = 0; i < v.size(); i += 1) {
		cr_assert_eq(v.at(i).size(), 3);
	}
}

Test(split_map, ten_elems)
{
	std::map<int, int> m({
			     {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5},
			     {6, 6}, {7, 7}, {8, 8}, {9, 9}, {10, 10}
			     });

	auto v = split(m, 3);
	cr_assert_eq(v.size(), 4);
	for (std::size_t i = 0; i < v.size() - 1; i += 1) {
		cr_assert_eq(v.at(i).size(), 3);
	}
	cr_assert_eq(v.back().size(), 1);
}
