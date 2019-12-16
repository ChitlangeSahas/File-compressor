#include <stdio.h>
#include <iostream>
#include <string.h>
#include <vector>


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
std::string	file_to_str()
{
    std::string line;
    std::string file_string;

    while(getline(std::cin, line).good())
    {
    	file_string += (line + "\n");
    }    
    return file_string;
} 

/*
* cyclic shift the string 
*/
std::vector<std::string>	cyclicShift(std::string line)
{
	char temp;			// a temporary variable to hold character.
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

void printArray(std::vector<std::string> arr)
{
	for (int i = 0; i < arr.size(); ++i)
	{
		std::cout << arr[i] << "\n";
	}
}

// =================================== 
void	 merge(std::vector<std::string> *arr, int l, int m, int r) 
{ 
    int i, j, k; 
    int n1 = m - l + 1; 
    int n2 =  r - m; 
  
    /* create temp arrays */
    std::vector<std::string> L, R; 

    /* Copy data to temp arrays L[] and R[] */
    for (i = 0; i < n1; i++)
        L.push_back(arr->at(l + i)); 
    for (j = 0; j < n2; j++) 
        R.push_back(arr->at(m + j + 1)); 

    /* Merge the temp arrays back into arr[l..r]*/
    i = 0; // Initial index of first subarray 
    j = 0; // Initial index of second subarray 
    k = l; // Initial index of merged subarray 
    while (i < n1 && j < n2) 
    { 
        if (L[i] <= R[j]) 
        { 
            arr->at(k) = L[i]; 
            i++; 
        } 
        else
        { 
            arr->at(k) = R[j]; 
            j++; 
        } 
        k++; 
    } 
        while (i < n1) 
    { 
        arr->at(k) = L[i]; 
        i++; 
        k++; 
    } 
  
    /* Copy the remaining elements of R[], if there 
       are any */
    while (j < n2) 
    { 
        arr->at(k) = R[j]; 
        j++; 
        k++; 
    } 
} 
  
/* l is for left index and r is right index of the 
   sub-array of arr to be sorted */
std::vector<std::string> 	sortCyclicShiftedArray_mergeSort(std::vector<std::string> *arr, int l, int r) 
{ 
	std::vector<std::string> sorted_arr;
    if (l < r) 
    { 
        // Same as (l+r)/2, but avoids overflow for 
        // large l and h 
        int m = (l+r)/2;

        sortCyclicShiftedArray_mergeSort(arr, l, m); 
        sortCyclicShiftedArray_mergeSort(arr, m+1, r); 
        merge(arr, l, m, r);

    }
    for (int i = 0; i < arr->size(); ++i)
    {
    	sorted_arr.push_back(arr->at(i));
    }
    return sorted_arr;
} 

/*
* sort the cyclic shifted array using insertion sort.
*/
std::vector<std::string> 	sortCyclicShiftedArray_InsertionSort(std::vector<std::string> shiftedArray)
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

/*
* Encodes the string and prints the encodings to stdout.http://www.cplusplus.com 
*/
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
	 for (int i = 0; i < terminal_characters.size(); ++i)
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
	 		std::cout << count << " " << current << " "; 
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
int 	main(int argc, char *argv[]) 
{
	std::string file_2_str = file_to_str(); // file read as a string
	std::vector<std::string>lines = str_to_lines(file_2_str, "\n");
	std::vector<std::string> lines_CyclicShifted, lines_CyclicShifted_sorted, lines_CyclicShifted_forMS;

	for (int i = 0; i < lines.size(); ++i)
	{
	    lines_CyclicShifted = cyclicShift(lines[i]);
	    lines_CyclicShifted_forMS = lines_CyclicShifted; // need a copy for Merge sort // DIRTY FIX
	    
	    // insertion or merge sort?
	    if (std::string(argv[1]) == "insertion")
	    {
	    	lines_CyclicShifted_sorted = sortCyclicShiftedArray_InsertionSort(lines_CyclicShifted);
	    }
	    else if (std::string(argv[1]) == "merge")
	    {
	    	lines_CyclicShifted_sorted = sortCyclicShiftedArray_mergeSort(&lines_CyclicShifted, 0, lines_CyclicShifted.size() - 1);
	    }
	    encode(lines_CyclicShifted_sorted, getOriginalStringIndex(lines_CyclicShifted_forMS, lines_CyclicShifted_sorted));
	}
    return 0;
}