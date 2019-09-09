#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string.h>
#include <sstream>
#include <vector>
std::string INPUT_FILEPATH = "./sample input/banksy-cnn.txt";

/*
* split the strings into lines.
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

std::vector<std::string>	cyclicShift(std::string line)
{
	char temp;
	int length = line.length();
	std::vector<std::string> shifted_lines;

	for (int i = 0; i < length ; ++i)
	{
		temp = line[0];
		shifted_lines.push_back(line) ;
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
		// std::cout << line << std::endl;
	}
	return shifted_lines;
}

int 	main() {
	std::string file_2_str = file_to_str(INPUT_FILEPATH); // file read as a string
	 
	std::vector<std::string>lines = str_to_lines(file_2_str, "\n");
	std::vector<std::string> lines_CyclicShifted;
	lines_CyclicShifted = cyclicShift(lines[9]);
    
    for (int i = 0; i < lines_CyclicShifted.size(); ++i)
    {
    	std::cout << lines_CyclicShifted[i] << std::endl;
    }
    
    return 0;
}