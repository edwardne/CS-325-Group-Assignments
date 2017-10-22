#include<iostream>
#include<fstream>
#include<string>
#include <sstream>
#include <math.h>
using namespace std;

int n;

int Vankin(int board[100][100])
{
    int score = 0;
    int VMile[100][100];
    for(int i = n+1; i>=1; i--)
    {
        VMile[i][n+1] = 0;
    }
    for(int j = n; j>=1; j--)
    {
        VMile[n+1][j] = 0;
        for(int i=n; i>=1; i--)
        {
            //I know this part isn't fully correct yet
            VMile[i][j] = board[i][j] + max(board[i+1][j], board[i][j+1]);//maximum possible score
            //VMile[i,j] = A[i,j] + max{VMile[i+1, j], VMile[i, j+1]}

            score = max(score, VMile[i][j]); //compare previous score and current score
        }
    }
    return score;
}

int main()
{
    int nread = 0, i = 1, j = 1, counter =0;
    int board[100][100];//we will probably have to do this a different way
    int result, x;

    ifstream File;
    File.open("input.txt");

    if(!File.is_open())
    {
        cout<<"Couldn't open file"<<endl;
        return 0;
    }

    while(File>>x)
    {


        if(nread==0)
        {
            n = x;
            cout<< "n is: "<<n<<endl;
            nread++;
        }
        else
        {
            //skip over any commas in input file
            if (File.peek() == ',')
            File.ignore();

            //calculate position of values on the game board
            j = (counter % n);
            i = floor(counter/n);

            //store value in spot in board array
            board[i][j] = x;
            cout<<"board["<<i<<"]["<<j<<"]: "<<board[i][j]<<endl;
            counter++;
        }
    }

    File.close();

    result = Vankin(board);
    cout<<"Highest score: "<<result<<endl;

    //print result to output file
    ofstream outfile;
    outfile.open("output.txt");
    outfile << result;

    return 0;
}
