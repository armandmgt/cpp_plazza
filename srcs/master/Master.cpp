/*
** EPITECH PROJECT, 2018
** plazza
** File description:
** master
*/


#include <thread>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <wait.h>
#include "Slave.hpp"
#include "Master.hpp"

plazza::Master::Master(int threadLimit)
	: slaves({}), shell(), threadLimit(threadLimit), logFile()
{
	auto t = std::time(nullptr);
	auto tm = *std::localtime(&t);

	std::ostringstream oss;
	oss << std::put_time(&tm, "logfile-%d%m%Y-%H%M.log");
	logFile = std::ofstream(oss.str());
}

void plazza::Master::createProcess()
{
}

void plazza::Master::outputData(std::list<Data> data)
{
	for (auto const &e : data) {
		for (auto const &s : e.elems) {
			std::cout << e.type << " in "
			  << e.filename << ": " << s;
		}
	}
}

void plazza::Master::pollShell()
{
	auto const &input = shell.getCommands();


}

void plazza::Master::runMaster()
{
	Slave s(threadLimit);

	s.start();
	s.feedCommand(PHONE_NB, "file.txt");
	std::cout << "hello" << std::endl;
	int status = 0;
	wait(&status);
}
