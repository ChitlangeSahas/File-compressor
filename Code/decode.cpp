#include <stdio.h>
#include <iostream>
#include <string.h>
#include <vector>



void  split(std::string stringToBeSplitted, std::vector<std::string> &splittedString)
{	
	char delimeter = ' ';
    int startIndex = 0;
    int  endIndex = 0;
    while( (endIndex = stringToBeSplitted.find(delimeter, startIndex)) < stringToBeSplitted.size() )
    {
		std::string val = stringToBeSplitted.substr(startIndex, endIndex - startIndex);

		if (startIndex == endIndex)
		{
			splittedString.push_back(" ");
			startIndex += 2;
		}
		else
		{
			splittedString.push_back(val);
			startIndex = endIndex + 1;
		}

    }

    if(startIndex < stringToBeSplitted.size())
    {
       std::string val = stringToBeSplitted.substr(startIndex);
       splittedString.push_back(val);
    }
}

// Insertion sort for the string sorter.
std::string 	sort(std::string str)
{
	char key;
	int j;

	for (int i = 1; i < str.size(); ++i)
	{
		key = str[i];
		j = i - 1;

		while(j >= 0 && str[j] > key)
		{
			str[j + 1] = str[j];  
            j = j - 1;
		}
		str[j + 1] = key;
	}

	return str;
}

bool 	has(int arr[], int len, int value)
{
	for (int i = 0; i < len; ++i)
	{
		if (arr[i] == value)
		{
			return true;
		}
	}
	return false;
}

void 	decode(std::string encodedLine1, std::string encodedLine2)
{	
	std::vector<std::string> encoded_split_vector;  
	split(encodedLine2, encoded_split_vector);

	// std::cout << encodedLine2;

	for (int i = 0; i < encoded_split_vector.size(); ++i)
	{
		if (encoded_split_vector[i] == "")
		{
			encoded_split_vector[i] = ' ';
		}
	}

	int encoded_str_length = 0;
	int original_string_index = std::stoi(encodedLine1,nullptr,0);
	
	std::vector<std::string> last_chars;

	// calculate the string length
	for (int i = 0; i < encoded_split_vector.size(); i)
	{
		encoded_str_length += std::stoi(encoded_split_vector[i],nullptr,0);
		i = i + 2;
	}

	// get the last chars.
 	for (int i = 1; i < encoded_split_vector.size(); i)
	{
		for (int j = 0; j < std::stoi(encoded_split_vector[i-1], nullptr, 0); ++j)
		{
			last_chars.push_back(encoded_split_vector[i]);
		}
		i = i + 2;
	}

	std::string last = "";

	// append it into a string.
	for (int i = 0; i < last_chars.size(); ++i)
	{
		last += last_chars[i];
	}

	std::string initial_chars_sorted = sort(last);

	int next[encoded_str_length] ;
	for (int i = 0; i < encoded_str_length; ++i)
	{
		next[i] = -1;
	}

	for (int i = 0; i < encoded_str_length; ++i)
	{
		int pos = 0;

		while(has(next, encoded_str_length, last.find(initial_chars_sorted[i], pos)))
		{
			pos++;
		}

		next[i] = last.find(initial_chars_sorted[i], pos);
	}

	int x = next[original_string_index];
	for (int i = 0; i < encoded_str_length; i++)
	{	
		putchar( last[x] );
		x = next[x];
	}
	std::cout << "\n";
}

std::string	file_to_str()
{
    // FILE *file;
    std::string line;
    std::string file_string;

    while(getline(std::cin, line).good())
    {
    	file_string += (line + "\n");
    }   
    return file_string;
} 

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
int main(int argc, char const *argv[])
{
	std::string encoded_line1 = "";
	std::string encoded_line2 = "";

	std::string decoding_as_string = file_to_str();
	std::vector<std::string> lines = str_to_lines(decoding_as_string, "\n");

	for (int i = 0; i < lines.size() ; i)
	{
		int p = i;

		encoded_line2 = lines[p + 1];
		encoded_line1 = lines[p];

		decode(encoded_line1, encoded_line2);

		i = i + 2;
	}

	return 0;
}