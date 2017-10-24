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

int Vankin(int board[2][2], int n)
{
	int score;
	int VMile[3][3];			 //create a new array for scoring
	
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
				score = gt(score, z);
			}
		}
	}

	int tempR = VMile[1][n+1];	//take the upper right element
	printf("%d\n", tempR);		//something wrong here, it return 0
	int tempB = VMile[n+1][1];	//take the bottom left element
	printf("%d\n", tempB);		// this one return -8912789
	for (int a = 1; a <= n - 1; a++)
	{
		if (tempR < VMile[a + 1][n + 1])	//compare the upper right element with the bottom element.
			tempR = VMile[a + 1][n + 1];	//if bigger, take the bigger one
	}

	for (int b = 1; b <= n - 1; b++)
	{
		if (tempB < VMile[n + 1][b + 1])	//compare the bottom left element with the right element
			tempB = VMile[n + 1][b + 1];	//if bigger, take the bigger one
	}

	if (tempB == tempR)			//if both score are the same, take one of them.
		score = tempB;			//else pick the highest one
	else if (tempB > tempR)
		score = tempB;
	else
		score = tempR;

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
