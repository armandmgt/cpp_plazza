/*
** EPITECH PROJECT, 2018
** plazza
** File description:
** Master
*/

#ifndef PLAZZA_MASTER_HPP
	#define PLAZZA_MASTER_HPP

	#include <string>
	#include <list>

	namespace plazza {

		typedef enum Information {
			PHONE_NB, EMAIL_ADDR, IP_ADDR
		} 		InfoType;

		class Master {
		public:
			Master();
			~Master();

			void outputFileDataResult();
			void createProcesses();

		private:
			std::list<std::string> outputResult;

		};
	};

#endif
