/*
** EPITECH PROJECT, 2018
** plazza
** File description:
** test_search
*/

#include <criterion/criterion.h>
#include <iostream>
#include "Search.hpp"

Test(Search, Search_email)
{
	std::list<std::string> toCompare = {"thomas.burgaud@epitech.eu",
					    "quesandra.lundh@epitech.eu",
					    "armandmegrot@gmail.com"};
	std::string fileName("../../tests/hiden_data");
	plazza::Search addr(plazza::EMAIL_ADDR, fileName);
	addr.parseFileData();
	auto weGet = addr.getData();
	cr_expect(toCompare == weGet.elems,
		  "Testing the research of email in hiden data");
}

Test(Search, Search_ipAddress)
{
	std::list<std::string> toCompare = {"192.168.1.0",
					    "192.168.1.1",
					    "192.168.1.2"};
	std::string fileName("../../tests/hiden_data");
	plazza::Search addr(plazza::IP_ADDR, fileName);
	addr.parseFileData();
	auto weGet = addr.getData();
	cr_expect(toCompare == weGet.elems,
		  "Testing the research of ip address in hiden_data");
}

Test(Search, Search_phoneNumber)
{
	std::list<std::string> toCompare = {"0684252849",
					    "06 84 25 28 49"};
	std::string fileName("../../tests/hiden_data");
	plazza::Search addr(plazza::PHONE_NB, fileName);
	addr.parseFileData();
	auto weGet = addr.getData();
	cr_expect(toCompare == weGet.elems,
		  "Testing the research of phone number in hiden data");
}
