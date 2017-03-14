//
// Created by Kainoa Seto on 3/13/17.
//

#include "EditDistanceAlgo.h"

EditDistanceAlgo::EditDistanceAlgo(std::string initial, std::string final)
{
    _initial = initial;
    _final = final;
}

void EditDistanceAlgo::PrintResults(bool table)
{
    if(table)
    {
        // To be fair this is TERRIBLE in performance but for our small use case
        // this will get a dynamic offset for us. A lookup table would be best
        int offset = static_cast<int>(std::to_string(_initial.size()).size());
        for(int i = 0; i <= _final.size(); i++)
        {
            if(i % _final.size() == 0 )
                std::cout << std::string(offset+5, ' K');

            if(i <= _final.size())
                std::cout << i << " ";
            else
                std::cout << _final[i % _final.size()] << " ";

            if(i % _final.size()+1 == 0 && i != 0)
                std::cout << std::endl;
        }

        for(int i = 0; i <= _initial.size(); i++)
        {
            std::cout << std::endl << std::setw(offset) << i << " " << _initial[i] << " | ";

            for(int j = 0; j <= _final.size(); j++)
            {
                std::cout << _table[i][j] << " ";
            }
        }
    }
}

void EditDistanceAlgo::Run()
{
    for(int i = 0; i <= _initial.size(); i++)
    {
        for(int j = 0; j <= _final.size(); j++)
        {
            // Check if first string is empty, if it is then insert all
            if(i == 0)
                _table[i][j] = j; // j# of inserts (entire length of _final)

                // Check if second string is empty, if it is then insert all
            else if(j == 0)
                _table[i][j] = i; // i# of inserts (entire length of _initial)

            /*
             * If the last characters were the same then just use the same count
             * from before without incrementing
             */
            else if(_initial[i-1] == _final[j-1])
                _table[i][j] = _table[i-1][j-1];

            /*
             * If they aren't the same or empty then add one op to the total
             * of the mimum operation and continue.
             */
            else {
                _table[i][j] = 1 + min(
                        _table[i][j-1],  // Insert
                        _table[i-1][j],  // Delete
                        _table[i-1][j-1] // Replace
                );
            }

        }


    }

}

int EditDistanceAlgo::min(int x, int y, int z)
{
    return std::min(std::min(x, y), z);
}