/*
** EPITECH PROJECT, 2018
** plazzaui
** File description:
** utils
*/
#ifndef PLAZZAUI_UTILS_HPP
#define PLAZZAUI_UTILS_HPP

#include <string>

class Filesystem {
public:
	static bool isDirectory(std::string const &name);
	static std::string getFilename(std::string const &path);
};

#endif //PLAZZAUI_UTILS_HPP
