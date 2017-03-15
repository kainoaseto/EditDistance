/*
	Kainoa Seto
	Edit Distance Algorithm
	Recursive and Dynamic Programming approaches called on two strings inputted
	by the user.
	3-14-17
	EditDistanceAlgo.cpp
*/

#include "EditDistanceAlgo.h"

EditDistanceAlgo::EditDistanceAlgo(std::string initial, std::string final)
{
    _initial = initial;
    _final = final;
	_dp_str_compares = 0;
	_recur_str_compares = 0;
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
			Prints out the top three columns of the formatted table which is
			the number of columns, then the letters in the string and a 
			horizontal seperation line.
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
					std::cout << std::setw(offset) << "-" << " ";
			}
			if(i < 3)
				std::cout << std::endl;
        }
		
		// Prints out the table with the left row identifiers with a seperation line.
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

	// Initialize current position to the bottom right of the grid
	int currentPos = _table[_initial.size()][_final.size()];
	
	for (int i = _initial.size(), j = _final.size(); j > 0 || i > 0; )
	{
		/*
			Our first choice is always to replace out of the three options
			so this is at the top. As long as we can go diagnol and the
			operation is less than our current we can do a replace.
		*/
		if ((i > 0 && j > 0) && (currentPos > _table[i - 1][j - 1]))
		{
			currentPos = _table[i - 1][j - 1];
			update_edits(_initial[i - 1], 'r', _final[j - 1]);
			i--, j--;
		}
		/*
			If we can go left and it is better than our current position
			then an insert operation is the best choice.
		*/
		else if ((j > 0) && (currentPos > _table[i][j - 1]))
		{
			currentPos = _table[i][j - 1];
			update_edits(' ', 'i', _final[j-1]);
			j--;
		}
		/*
			As long as we can go up and it is better than our current position
			then a delete operation is the best choice.
		*/
		else if ((i > 0) && (currentPos > _table[i - 1][j]))
		{
			currentPos = _table[i - 1][j];
			update_edits(_initial[i-1], 'd', ' ');
			i--;
		}
		/*
			If we can go diagnol, nothing else matches, and our currentPos
			is equal to the diagnol then we will navigate up the diagnol since
			no change was made.
		*/
		else if((i > 0 && j > 0) && (currentPos == _table[i - 1][j - 1]))
		{
			currentPos = _table[i - 1][j - 1];
			update_edits(_initial[i - 1], ' ', _final[j - 1]);
			i--, j--;
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

	std::cout << "Minimum edits required to change initial to final via DP: " << _table[_initial.size()][_final.size()] << std::endl;
	std::cout << "Minimum character comparisons to change via DP: " << _dp_str_compares << std::endl;
	std::cout << std::endl;

	int recursiveCount = Recursive(_initial, _final, _initial.size(), _final.size());
	std::cout << "Minimum edits required to change initial to final via Recursion: " << recursiveCount << std::endl;
	std::cout << "Minimum character comparisons to change via Recursion: " << _recur_str_compares << std::endl;
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
			else if (_initial[i - 1] == _final[j - 1])
			{
				_table[i][j] = _table[i - 1][j - 1];
				++_dp_str_compares;
			}
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
				++_dp_str_compares;
            }
        }
    }
}

/*
	Calculate the min edit distance via Recursive calls
*/
int EditDistanceAlgo::Recursive(std::string initial, std::string final, int initialSz, int finalSz)
{
	// If initialSz is 0 then we have reached the end or the string is empty so everything needs to be inserted.
	if (initialSz == 0) return finalSz;
	// If finalSz is 0 then we have reached the end of the string is empty so everything need to be removed from the first string.
	if (finalSz == 0) return initialSz;

	// If the characters are the same then continue on without increasing the count
	_recur_str_compares++;
	if (initial[initialSz - 1] == final[finalSz - 1])
		return Recursive(initial, final, initialSz - 1, finalSz - 1);

	// Recurse through the strings and count up the shortest path from operations
	return 1 + min(
		Recursive(initial, final, initialSz, finalSz - 1),		// Insert
		Recursive(initial, final, initialSz - 1, finalSz),		// Remove
		Recursive(initial, final, initialSz - 1, finalSz - 1)	// Replace
	);
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