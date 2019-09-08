#include <stdio.h>
#include <fstream>
#include <iostream>

std::ifstream inFile("input_file.txt");


int main(int argc, char const *argv[])
{
	if(!inFile) 
	{
		std::cout << "Cannot open input file.\n";
		return 1;
	}

	char str[255];

	// read line by line
	while(inFile)
	{
		inFile.getline(str, 255);  // delim defaults to '\n'
	    std::cout << str << std::endl;
	}

	inFile.close();

	return 0;
}