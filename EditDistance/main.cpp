/*
	Kainoa Seto
	Edit Distance Algorithm
	Recursive and Dynamic Programming approaches called on two strings inputted
	by the user.
	3-14-17
	Main.cpp
*/

#include "pch.h"
#include "EditDistanceAlgo.h"

int main(int argc, char* argv[])
{
	bool printTable = false;
	std::string initial, final;

	std::cout << "===================================================================================================" << std::endl;
    std::cout << "This program computes the minimum edit distance between two strings and the operations" << std::endl
		<< "that change the intial string into the final string using a Dynamic Progarmming Memoization table" << std::endl;
	std::cout << "===================================================================================================" << std::endl;

	std::cout << "Enter the initial string: ";
	getline(std::cin, initial);
    std::cout << "Enter the final string: ";
	getline(std::cin, final);

    EditDistanceAlgo dpAlgo(initial, final);
	if (argc > 1)
	{
		if (std::string(argv[1]) == "table")
			printTable = true;
	}

	dpAlgo.Run();
    dpAlgo.PrintResults(printTable);

    return 0;
}