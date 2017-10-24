#include<iostream>
#include<fstream>
#include<string>
#include <sstream>
#include <math.h>
using namespace std;

int n;

int max(int a, int b)
{
	if (a == b)
		return a;
	else if (a > b)
		return a;
	else
		return b;
}

int Vankin(int *board)
{
	int score = 0;
	int* VMile = NULL;
	VMile = new int[(n + 1) * (n + 1)];//we will probably have to do this a different way
	for (int i = n; i >= 0; i--)
	{
		VMile[(i * n) + (n)] = 0;
	}
	for (int j = n-1; j >= 0; j--)
	{
		VMile[((n) * n) + j] = 0;
		for (int i = n-1; i >= 0; i--)
		{
			cout << board[((i * n) - 1) + j] << endl;

			//FIXED CALCULATION
			VMile[(i * n) + j] = board[(i * n) + j] + max(VMile[((i + 1) * n) + j], VMile[(i * n) + (j + 1)]);//maximum possible score
			//int z = VMile[(i * n) + j];
			//printf("%d", z);
			score = max(score, VMile[(i * n) + j]); //compare previous score and current score
		}
	}
	return score;
}

int main()
{
	int nread = 0, i = 1, j = 1, counter = 0, value = 0;
	int* board = NULL;
	board = new int[n * n];//we will probably have to do this a different way
	int result, x;

	ifstream File;
	File.open("input.txt");

	if (!File.is_open())
	{
		cout << "Couldn't open file" << endl;
		return 0;
	}

	while (File >> x)
	{


		if (nread == 0)
		{
			n = x;
			cout << "n is: " << n << endl;
			nread++;
		}
		else
		{
			//skip over any commas in input file
			if (File.peek() == ',')
				File.ignore();

			//calculate position of values on the game board
			j = (counter % n);
			i = (int)floor(counter / n);

			//store value in spot in board array
			board[(i * n) + j] = x;
			cout << "board[" << i << "][" << j << "]: " << board[(i * n) + j] << endl;
			counter++;
		}
	}


	result = Vankin(board);
	cout << "Highest score: " << result << endl;

	//print result to output file
	ofstream outfile;
	outfile.open("output.txt");
	outfile << result;
	File.close();

	return 0;
}
