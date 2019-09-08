#include <stdio.h>
#include <fstream>

using namespace std;
ifstream inFile;

void	openFile()
{
	inFile.open("C:\\temp\\datafile.txt");
}

int main(int argc, char const *argv[])
{
	openFile();
	return 0;
}