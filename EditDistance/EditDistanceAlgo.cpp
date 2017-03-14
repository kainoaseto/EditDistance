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
        /*
			To be fair this is TERRIBLE in performance but for our small use case
            this will get a dynamic offset for us. A lookup table would be best
		*/
        int offset = static_cast<int>(std::to_string(_initial.size()).size());

		/*
			Prints out the formatted table
		*/
        for(int i = 0; i < 3; i++)
        {
			std::cout << std::string(offset + 5, ' ');
			for (int j = 0; j <= _final.size(); j++)
			{
				if (i == 0)
					std::cout << std::setw(offset) << j << " ";
				else if (i == 1)
					std::cout << std::setw(offset) << _final[j] << " ";
				else
					std::cout << std::setw(offset) << "- ";
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
                std::cout << std::setw(offset) <<  _table[i][j] << " ";
            }
        }
		std::cout << std::endl;
    }

	int currentPos = _table[_initial.size()][_final.size()];
	
	for (int i = _initial.size(); i > 0; )
	{
		for (int j = _final.size(); j > 0 && i > 0; )
		{
			// Check if an insert was the best path
			if (currentPos > _table[i][j - 1])
			{
				currentPos = _table[i][j - 1];
				update_edits(' ', 'i', _final[j-1]);
				j--;
			}
			// Check if a delete was the best path
			else if (currentPos > _table[i - 1][j])
			{
				currentPos = _table[i - 1][j];
				update_edits(_initial[i-1], 'd', ' ');
				i--;
			}
			// Check if it was a replace or equal character that got us here
			// If you put this check above the delete check then you should have a tindall table
			else
			{
				if (currentPos == _table[i - 1][j - 1])
					_e_map.push(' ');
				else
					_e_map.push('r');	

				currentPos = _table[i - 1][j - 1];
				_e_initial.push(_initial[i-1]);
				_e_final.push(_final[j-1]);
				i--, j--;
				
			}
		}
	}

	std::cout << "From: ";
	stack_print(_e_initial);
	std::cout << std::endl;
	std::cout << " map: ";
	stack_print(_e_map);
	std::cout << "    : (i)insertions, (d)eletions, (r)eplacements" << std::endl;
	std::cout << "  To: ";
	stack_print(_e_final);
	std::cout << std::endl;

	std::cout << "Minimum edits required to change initial to final: " << _table[_initial.size()][_final.size()] << std::endl;


	
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

void EditDistanceAlgo::update_edits(char cinitial, char cmap, char cfinal)
{
	_e_initial.push(cinitial);
	_e_map.push(cmap);
	_e_final.push(cfinal);
}

void EditDistanceAlgo::stack_print(std::stack<char> cstack)
{
	while (!cstack.empty())
	{
		std::cout << cstack.top();
		cstack.pop();
	}
}