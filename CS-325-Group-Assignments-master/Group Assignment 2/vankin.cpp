#include <string>
#include <stdio.h>
#include <math.h>
using namespace std;


//max function
int max(int a, int b, int c)
{
	if ((a > b) && (a > c))
		return a;
	else if ((b > a) && (b > c))
		return b;
	else
		return c;
}

int gte(int a, int b)
{
	if (a == b)
		return a;
	else if(a > b)
		return a;
	else
		return b;
}

int Vankin(int board[2][2], int n)
{
	int score= 0;
	int VMile[3][3];			 //change this to suit n variables
	
	for (int i = 0; i <= n; i++)
	{
		for (int j = 0; j <= n; j++)
		{
			VMile[i][j] = 0;		//fill array with 0
		}
	}
	for (int i = 1; i <= n; i++)	//iterate for each column
	{
		for (int j = 1; j <= n; j++)	//iterate for each row
		{
			VMile[i][j] += max(board[i - 1][j - 1], (board[i - 1][j - 1] + VMile[i][j - 1]), (board[i - 1][j - 1] + VMile[i - 1][j]));
			//fill at index j,k the maximum value of the number itself, + top score, or + left score	
			if (i == n || j == n)
			{
				int z = VMile[i][j];
				//printf("%d\n", z);
				score = gte(score, z);
			}
		}
	}

	return score;
}

int main()
{
	int n = 2;
	int board[2][2] = { { 5,-2 },{ -3,1 } };
	int max = Vankin(board, n);
	printf("Highest score = %d", max);
	return 0;
}
