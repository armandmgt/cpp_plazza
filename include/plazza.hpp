/*
** EPITECH PROJECT, 2018
** plazza
** File description:
** plazza
*/

#ifndef PLAZZA_PLAZZA_H
	#define PLAZZA_PLAZZA_H

	namespace plazza {
		/**
		 * @brief information type to search for
		 * @enum PHONE_NUMBER searches for a phone number
		 * @enum EMAIL_ADDR searches for an email address
		 * @enum IP_ADDR searches for an ip address
		 */
		typedef enum Information {
			UNKNOWN, PHONE_NB, EMAIL_ADDR, IP_ADDR
		} InfoType;
	}

	extern int const SUCCESS;
	extern int const FAILURE;

	int check_args(int argc, char const *argv[]);
	plazza::InfoType sToInfoType(std::string const &s);
	std::string infoTypeToS(plazza::InfoType it);

#endif //PLAZZA_PLAZZA_H
