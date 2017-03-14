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
        for(int i = 0; i < 3; i++)
        {
			std::cout << std::string(offset + 5, ' ');
			for (int j = 0; j <= _final.size(); j++)
			{
				if (i == 0)
					std::cout << j << " ";
				else if (i == 1)
					std::cout << _final[j] << " ";
				else
					std::cout << "- ";
			}
			if(i < 3)
				std::cout << std::endl;
        }

        for(int i = 0; i <= _initial.size(); i++)
        {
			if( i != 0)
				std::cout << std::endl;
			std::cout << std::setw(offset) << i << " " << _initial[i] << " | ";

            for(int j = 0; j <= _final.size(); j++)
            {
                std::cout << _table[i][j] << " ";
            }
        }
		std::cout << std::endl;
    }

	int currentPos = _table[_initial.size()][_final.size()];
	_e_map = "", _e_initial = "", _e_final = "";

	for (int i = _initial.size(); i > 0; )
	{
		for (int j = _final.size(); j > 0; )
		{
			std::cout << "DEBUG: " << currentPos << std::endl;;
			// Check if an insert was the best path
			if (currentPos > _table[i][j - 1])
			{
				currentPos = _table[i][j - 1];
				_e_initial += " ";
				_e_map += "i";
				_e_final += _final[_final.size()-j];
				j--;
			}
			// Check if a delete was the best path
			else if (currentPos > _table[i - 1][j])
			{
				currentPos = _table[i - 1][j];
				_e_initial += _initial[_initial.size()- i];
				_e_map += "d";
				_e_final += " ";
				i--;
			}
			// Check if a replace was the best choice
			else
			{
				if (currentPos == _table[i - 1][j - 1])
				{
					_e_map += " ";
				}
				else
				{
					_e_map += "r";	
				}
				currentPos = _table[i - 1][j - 1];
				_e_initial += _initial[_initial.size() - i];
				_e_final += _final[_final.size() - j];
				i--, j--;
				
			}
			
		}
	}

	std::cout << "From: " << _e_initial << std::endl;
	std::cout << " map: " << _e_map << std::endl;
	std::cout << "  To: " << _e_final << std::endl;

	
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
             * of the minimum operation and continue.
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