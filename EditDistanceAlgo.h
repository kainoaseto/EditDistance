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

    void PrintResults(bool table);

    void Run();

private:
    // Utility triple comparison min
    int min(int x, int y, int z);

    std::string _initial;
    std::string _final;

    // The Edited versions of the above to show work
    std::string _e_initial;
    std::string _e_final;

    // DP cache table
    int _table[50][50];

};

#endif // __EDITDISTANCEALGO_H__
