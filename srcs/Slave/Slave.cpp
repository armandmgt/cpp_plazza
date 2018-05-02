/*
** EPITECH PROJECT, 2018
** plazza
** File description:
** Slave
*/

#include <thread>
#include <mutex>
#include "Slave.hpp"

plazza::Slave::Slave(unsigned int &threadLimit) : _threadLimit(threadLimit), _pool(), _buffer()
{
}

plazza::Slave::~Slave()
{
	_buffer.erase();
	_pool.erase();
}

bool feedCommand(InfoType, std::string &file)
{
	return true;
}

list<plazza::Load> plazza::Slave::getLoad()
{
	return _load[0];
}

list<plazza::Data> plazza::Slave::getData()
{

	return _pool[0].getData();
}

