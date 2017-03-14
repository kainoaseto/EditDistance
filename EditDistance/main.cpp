#include "pch.h"
#include "EditDistanceAlgo.h"

int main()
{
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
    
	dpAlgo.Run();
    dpAlgo.PrintResults(true);

    return 0;
}