#include<iostream>
#include<fstream>
#include<string>
#include <sstream>
#include <math.h>
#include <stdlib.h>
using namespace std;

int main()
{
    int result, k, val, n;

    FILE* fp;
    fp = fopen("input.txt", "r");
    fscanf(fp, "%d", &n);
    if((n > 1000) || (n < 0))
    {
        perror("ERROR: n is too large");
        exit(1);
        return 1;
    }
    int n2= n + 1;

    int board[n][n];				//cannot compile because n and n2 is not a constant value
    int VMile[n2][n2];

    for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			board[i][j] = NULL;		//empty array
		}
	}

	for (int i = 0; i < n2; i++)
	{
		for (int j = 0; j < n2; j++)
		{
			VMile[i][j] = 0;		//empty array
			//cout<<VMile[i][j] <<endl;
		}
	}

    for(int i=0; ;i++)
    {
        for(int j=0; ;j++)
        {

            if(fscanf(fp, "%d", &val) == -1)
            {
                goto end;
            }

             board[i][j] = val;
             //cout<<"["<<i<<"]["<<j<<"] "<<board[i][j]<<endl;

            if((k=fgetc(fp)) == '\n')
            {
                break;
            }

        }
    }
    end:

    int score = 0;

    for(int j = n-1; j>=0; j--)
    {
        VMile[n][j] = 0;				//dont think u need this since the array is already emptied above
        for(int i = n-1; i>=0; i--)
        {

            VMile[i][j] = board[i][j] + max(VMile[i+1][j], VMile[i][j+1]);//maximum possible score
            //cout<<"V: "<< VMile[i][j]<<endl;
            score = max(score, VMile[i][j]); //compare previous score and current score

        }
        //out<<"Score: "<< score<<endl;
    }
    cout<<"Highest score: "<<score<<endl;

    //print result to output file
    ofstream outfile;
    outfile.open("output.txt");
    outfile << score;

    outfile.close();

    return 0;
}
