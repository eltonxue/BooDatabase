#include <iostream>
#include <string>
#include <sstream>
#include "UserInterface.hpp"

UserInterface::UserInterface()
	:debug{false}, programRunning{true}
{
}

void UserInterface::start()
{

	while (programRunning)
	{
		std::string inputLine;
		getline(std::cin, inputLine);

		std::istringstream iss(inputLine);

		command = "";
		parameter1 = "";
		parameter2 = ""; 
		debugParameter = "";

		iss >> command;
		iss >> parameter1;
		iss >> parameter2;
		iss >> debugParameter;

		if (command == "CREATE")
		{
			ifCreate();
		}
		else if (command == "LOGIN")
		{
			ifLogin();
		}
		else if (command == "REMOVE")
		{
			ifRemove();
		}
		else if (command == "CLEAR")
		{
			ifClear();
		}
		else if (command == "QUIT")
		{
			ifQuit();
		}
		else if (command == "DEBUG")
		{
			ifDebug();
		}
		else if (debug and command == "BUCKET")
		{
			ifDebugBucket();
		}
		else if (debug and command == "LOAD")
		{
			ifDebugLoad();
		}
		else if (debug and command == "MAX")
		{
			ifDebugMax();
		}
		else
		{
			std::cout << "INVALID" << std::endl;
		}

		/*
		std::cout << std::endl << "-------DEBUG HELPER INFORMATION-------" << std::endl;
		std::cout << "Command: " << command << std::endl;
		std::cout << "Parameter #1: " << parameter1 << std::endl;
		std::cout << "Parameter #2: " << parameter2 << std::endl;
		std::cout << "Debug Parameter: " << debugParameter << std::endl << std::endl;
		*/
	}
}

void UserInterface::ifCreate()
{
	if (parameter1 == "" or parameter2 == "" or debugParameter != "")
	{
		std::cout << "INVALID" << std::endl;
	}
	else if (database.contains(parameter1))
	{
		std::cout << "EXISTS" << std::endl;
	}
	else
	{
		database.add(parameter1, parameter2);
		std::cout << "CREATED" << std::endl;
	}
}

void UserInterface::ifLogin() const
{
	if (debug and parameter1 == "COUNT" and parameter2 == "" and debugParameter == "")
	{
		std::cout << database.size() << std::endl;
	}
	else if (parameter1 == "" or parameter2 == "" or debugParameter != "")
	{
		std::cout << "INVALID" << std::endl;
	}

	else if (database.contains(parameter1) and database.value(parameter1) == parameter2)
	{
		std::cout << "SUCCEEDED" << std::endl;
	}
	else 
	{
		std::cout << "FAILED" << std::endl;
	}
}

void UserInterface::ifRemove()
{
	if (parameter1 == "" or parameter2 != "" or debugParameter != "")
	{
		std::cout << "INVALID" << std::endl;
	}
	else if (not database.contains(parameter1))
	{
		std::cout << "NONEXISTENT" << std::endl;
	}
	else
	{
		database.remove(parameter1);
		std::cout << "REMOVED" << std::endl;
	}
}

void UserInterface::ifClear()
{
	if (parameter1 != "" or parameter2 != "" or debugParameter != "")
	{
		std::cout << "INVALID" << std::endl;
	}
	else
	{
		database.clearMainBuckets();
		database.setNewBuckets();
		std::cout << "CLEARED" << std::endl;
	}
}

void UserInterface::ifQuit()
{
	if (parameter1 != "" or parameter2 != "" or debugParameter != "")
	{
		std::cout << "INVALID" << std::endl;
	}
	else
	{
		programRunning = false;
		std::cout << "GOODBYE" << std::endl;
	}
}

void UserInterface::ifDebug()
{
	if (parameter1 == "ON" and parameter2 == "" and debugParameter == "")
	{
		if (debug)
		{
			std::cout << "ON ALREADY" << std::endl;
		}
		else
		{
			debug = true;
			std::cout << "ON NOW" << std::endl;
		}
	}
	else if (parameter1 == "OFF" and parameter2 == "" and debugParameter == "")
	{
		if (not debug)
		{
			std::cout << "OFF ALREADY" << std::endl;
		}
		else
		{
			debug = false;
			std::cout << "OFF NOW" << std::endl;
		}
	}
	else
	{
		std::cout << "INVALID" << std::endl;
	}
}

void UserInterface::ifDebugBucket() const
{
	if (parameter1 == "COUNT" and parameter2 == "" and debugParameter == "")
	{
		std::cout << database.bucketCount() << std::endl;
	}
	else
	{
		std::cout << "INVALID" << std::endl;
	}
}

void UserInterface::ifDebugLoad() const
{
	if (parameter1 == "FACTOR" and parameter2 == "" and debugParameter == "")
	{
		std::cout << database.loadFactor() << std::endl;
	}
	else
	{
		std::cout << "INVALID" << std::endl;
	}
}

void UserInterface::ifDebugMax() const
{
	if (parameter1 == "BUCKET" and parameter2 == "SIZE" and debugParameter == "")
	{
		std::cout << database.maxBucketSize() << std::endl;
	}
	else
	{
		std::cout << "INVALID" << std::endl;
	}
}