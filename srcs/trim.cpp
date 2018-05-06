/*
** EPITECH PROJECT, 2018
** plazza
** File description:
** trim
*/

#include <string>
#include <algorithm>

static void ltrim(std::string &s)
{
	s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int ch) {
		return !std::isspace(ch);
	}));
}

static void rtrim(std::string &s)
{
	s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch) {
		return !std::isspace(ch);
	}).base(), s.end());
}

void trim(std::string &s)
{
	ltrim(s);
	rtrim(s);
}

