/*
** EPITECH PROJECT, 2018
** plazzaui
** File description:
** utils
*/

#include <sys/stat.h>
#include <sys/types.h>
#include <iostream>
#include "../include/Utils.hpp"

std::string Filesystem::getFilename(std::string const &path)
{
	std::string filename;
	size_t pos;

	pos = path.find_last_of('/');
	filename = path.substr(pos + 1);
	return filename;
}

bool Filesystem::isDirectory(std::string const &name)
{
	struct stat sb{};

	if (stat(name.c_str(), &sb) == -1)
		return false;
	return (sb.st_mode & static_cast<unsigned int>(S_IFMT)) == S_IFDIR;
}


