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
			UNKNOWN, PHONE_NUMBER, EMAIL_ADDRESS, IP_ADDRESS, END,
		} InfoType;

		enum CommandType {
			NONE, OPERATION, GET_DATA, GET_LOAD
		};

		struct operation {
			InfoType type;
			std::string file;
		};

		struct command {
			CommandType cmd;
			operation ope;
		};

		std::ostream &operator<<(std::ostream &os, InfoType it);
		std::ostream &operator<<(std::ostream &os, CommandType ct);
	}

	extern int const SUCCESS;
	extern int const FAILURE;

	int check_args(int argc, char const *argv[]);
	plazza::InfoType sToInfoType(std::string const &s);
	std::string infoTypeToS(plazza::InfoType it);
	plazza::CommandType sToCommandType(std::string const &s);
	std::string commandTypeToS(plazza::CommandType ct);

#endif //PLAZZA_PLAZZA_H
