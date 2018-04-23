/*
** EPITECH PROJECT, 2018
** plazza
** File description:
** SplitableMap
*/

#ifndef PLAZZA_SPLITMAP_HPP
	#define PLAZZA_SPLITMAP_HPP

	#include <map>
	#include <unordered_map>
	#include <vector>

	template<typename Container>
	std::vector<Container> split(
		Container const &map, std::size_t size)
	{
		std::size_t listId = 0;
		std::vector<Container> v({});

		for (auto it = map.begin(); it != map.end(); it++) {
			if (std::distance(map.begin(), it) % size == 0) {
				v.emplace_back();
				if (it != map.begin())
					listId += 1;
			}
			v.at(listId).emplace(it->first, it->second);
		}
		return v;
	}

//	template<typename K, typename V>
//	std::vector<std::unordered_map<K, V>> split<std::unordered_map<K, V>>(
//		std::unordered_map<K, V> const &map, std::size_t size);
//
//	template<typename K, typename V>
//	std::vector<std::map<K, V>> split<std::map<K, V>>(
//		std::map<K, V> const &map, std::size_t size);

#endif //PLAZZA_SPLITMAP_HPP
