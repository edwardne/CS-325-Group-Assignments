#include<iostream>
#include<fstream>
#include<string>

using namespace std;

int select(int m, int n, int k)
{
    int result= 1000;//just a placeholder to test file output

    //Read the array from binary file.
    //Put them into m arrays consisting of n elements
    //Use Merge function in MergeSort to Merge all m arrays
    //Find k with for loop

    return result;
}

int main()
{
    int num = 0;
    int arr[100];
    int x, m, n, k, result;
    int sum = 0;

    ifstream File;
    File.open("input.txt");

    if(!File.is_open())
    {
        cout<<"Couldn't open file"<<endl;
        return 0;
    }

    while(File>>x)
    {
        arr[num] = x;
        if(num>2)
        {
            cout << "Bad input file\n";
        }
        num++;

        //skip over commas in input file
        if (File.peek() == ',')
            File.ignore();
    }

    if(num<2)
        {
            cout << "Bad input file\n";
        }

    File.close();

    //store m n and k retrieved from input files
    m = arr[0];
    n = arr[1];
    k = arr[2];

    cout << "m is: " << arr[0] << "\n";
    cout << "n is: " << arr[1] << "\n";
    cout << "k is: " << arr[2] << "\n";

    result = select(m,n,k);
    cout << k << "th smallest element is: " << result;

    //print result of select() to output file
    ofstream outfile;
    outfile.open("output.txt");
    outfile << result;

    return 0;
}
