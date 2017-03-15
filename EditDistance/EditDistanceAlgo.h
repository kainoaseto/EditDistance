//
// Created by Kainoa Seto on 3/13/17.
//

#ifndef __EDITDISTANCEALGO_H__
#define __EDITDISTANCEALGO_H__

#include "pch.h"

class EditDistanceAlgo
{
public:
    EditDistanceAlgo(std::string initial, std::string final);
    ~EditDistanceAlgo() {};

	// Print table and backtrace through it to find the shortest path and results
    void PrintResults(bool table);

	// Fill the DP table
    void Run();

	int Recursive(std::string initial, std::string final, int initialSz, int finalSz);

private:
	void update_edits(char cinitial, char cmap, char cfinal);
	void stack_print(std::stack<char> cstack);
    // Utility triple min comparison
    int min(int x, int y, int z);

    std::string _initial;
    std::string _final;

    // The Edited versions of the above to show work
    std::stack<char> _e_initial;
    std::stack<char> _e_final;
	std::stack<char> _e_map;

    // DP cache table
    int _table[50][50];

	int _dp_str_compares;
	int _recur_str_compares;

};

#endif // __EDITDISTANCEALGO_H__
