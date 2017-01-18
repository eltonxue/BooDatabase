#ifndef USERINTERFACE_HPP
#define USERINTERFACE_HPP

#include <string>
#include "HashMap.hpp"

class UserInterface
{
public:

	UserInterface();

	void start();


private:

	bool debug;
	bool programRunning;

	std::string command;
	std::string parameter1;
	std::string parameter2;
	std::string debugParameter;

	HashMap database;

	void ifCreate();

	void ifLogin() const;

	void ifRemove();

	void ifClear();

	void ifQuit();

	void ifDebug();

	void ifDebugBucket() const;

	void ifDebugLoad() const;

	void ifDebugMax() const;
};

#endif // USERINTERFACE_HPP