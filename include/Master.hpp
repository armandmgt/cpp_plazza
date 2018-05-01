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
	#include <unordered_map>

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
			std::list<std::string> _outputResult;
			std::unordered_map<plazza::InfoType, std::string> _shellInput;
		};
	};

#endif
