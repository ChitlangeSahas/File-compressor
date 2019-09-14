#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string.h>
#include <sstream>
#include <vector>

std::string INPUT_FILEPATH = "./sample input/banksy-cnn.txt";

/*
* split the incomin string into lines.
*/
std::vector<std::string> 	str_to_lines(std::string str, std::string delim)
{
    std::vector<std::string> tokens;
    size_t prev = 0, pos = 0;
    do
    {
        pos = str.find(delim, prev);
        if (pos == std::string::npos) pos = str.length();
        std::string token = str.substr(prev, pos-prev);
        if (!token.empty()) tokens.push_back(token);
        prev = pos + delim.length();
    }
    while (pos < str.length() && prev < str.length());
    return tokens;
}

/*
* converts the incoming file and outputs the contents 
* as a std::string 
*/
std::string 	file_to_str(std::string filePath)
{
	std::ifstream t(filePath);
	std::stringstream buffer;
	buffer << t.rdbuf();
	return buffer.str();	
} 

/*
* cyclic shift the string 
*/
std::vector<std::string>	cyclicShift(std::string line)
{
	char temp;
	int length = line.length();
	std::vector<std::string> shifted_line;

	for (int i = 0; i < length ; ++i)
	{
		temp = line[0];
		shifted_line.push_back(line) ;
		for (int i = 0; i < length; ++i)
		{
			if (i == (length-1)) 
			{
				line[i] = temp;
			}
			else
			{
				line[i] = line[i + 1];
			}
		}
	}
	return shifted_line;
}

/*
* sort the cyclic shifted array.
*/
std::vector<std::string> 	sortCyclicShiftedArray(std::vector<std::string> shiftedArray)
{
	std::string key;
	int j;

	for (int i = 1; i < shiftedArray.size(); ++i)
	{
		key = shiftedArray[i];
		j = i - 1;

		while(j >= 0 && shiftedArray[j] > key)
		{
			shiftedArray[j + 1] = shiftedArray[j];  
            j = j - 1;
		}
		shiftedArray[j + 1] = key;
	}

	return shiftedArray;
}

void 	encode(std::vector<std::string> sortedCyclicShiftedArray, int originalIndex)
{

	std::cout << originalIndex << "\n";
	int string_length = sortedCyclicShiftedArray[0].length();

	std::vector<char> terminal_characters;

	for (int i = 0; i < sortedCyclicShiftedArray.size(); ++i)
	 {
	 	//TODO
	 	terminal_characters.push_back(sortedCyclicShiftedArray[i][string_length - 1]);
	 }
	  
	 bool streak = false;
	 int count = 1;
	 for (int i = 0; i < terminal_characters.size() - 1; ++i)
	 {
	 	
	 	char current, next;
	 	current = terminal_characters[i];
	 	next = terminal_characters[i + 1];
	 	
	 	if (current == next)
	 	{
	 		count++;
	 		streak = true;
	 	}
	 	else
	 	{
	 		streak = false;
	 	}

	 	if (streak == false)
	 	{
	 		std::cout << count << current << " " ; 
	 		count = 1;
	 	}
	 }
	 std::cout << "\n";
}

int 	getOriginalStringIndex(std::vector<std::string> CyclicShiftedArray, std::vector<std::string> sortedCyclicShiftedArray)
{
	// the first string in the cyclic shifted array is the original string 
	// we loop through the sorted cyclic shifted array and see what index is the 
	// original string in the sorted cyclic shifted array.
	for (int i = 0; i < sortedCyclicShiftedArray.size(); ++i)
	{
		if (CyclicShiftedArray[0] == sortedCyclicShiftedArray[i])
		{
			return i;
		}
	}
	return -1;
}

/**/
int 	main() {
	std::string file_2_str = file_to_str(INPUT_FILEPATH); // file read as a string
	 
	std::vector<std::string>lines = str_to_lines(file_2_str, "\n");
	std::vector<std::string> lines_CyclicShifted, lines_CyclicShifted_sorted;

	for (int i = 0; i < lines.size(); ++i)
	{
	    lines_CyclicShifted = cyclicShift(lines[i]);

	    // std::cout << "cyclic shifting..." << std::endl;
	    // for (int i = 0; i < lines_CyclicShifted.size(); ++i)
	    // {
	    // 	std::cout << lines_CyclicShifted[i] << std::endl;
	    // }
	    
	    lines_CyclicShifted_sorted = sortCyclicShiftedArray(lines_CyclicShifted);

	    // std::cout << "sorted ..." << std::endl;
	    // for (int i = 0; i < lines_CyclicShifted_sorted.size(); ++i)
	    // {
	    // 	std::cout << lines_CyclicShifted_sorted[i] << std::endl;
	    // }
	    encode(lines_CyclicShifted_sorted, getOriginalStringIndex(lines_CyclicShifted, lines_CyclicShifted_sorted));
	}

	while(true){}
    return 0;
}