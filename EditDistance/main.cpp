#include "pch.h"
#include "EditDistanceAlgo.h"

int main()
{
    std::string initial, final;


    std::cout << "Computes minimum edit distance between two strings and the operations to change them" << std::endl;
    //std::cout << "Enter the initial string: ";
    //std::cin >> initial;
    //std::cout << std::endl << "Enter the final string: ";
    //std::cin >> final;

    initial = "Saturday", final = "Sunday";

    EditDistanceAlgo dpAlgo(initial, final);
    dpAlgo.Run();
    dpAlgo.PrintResults(true);

    return 0;
}