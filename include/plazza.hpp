/*
** EPITECH PROJECT, 2018
** plazza
** File description:
** plazza
*/

#ifndef PLAZZA_PLAZZA_H
	#define PLAZZA_PLAZZA_H

	typedef enum Information {
		PHONE_NB, EMAIL_ADDR, IP_ADDR
	} InfoType;

	extern int const SUCCESS;
	extern int const FAILURE;

	int check_args(int argc, char const *argv[]);

#endif //PLAZZA_PLAZZA_H
