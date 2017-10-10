#include<iostream>
#include<fstream>
#include<string>
#include <sstream>
#include <byteswap.h>

using namespace std;


struct datFile{
      int subArrays; //number of sub arrays, also known as 'm'
      int k; //kth smallest numbers
      int length; //described as n in assignment description
      string fileName;
      int* values; //should probably be dynamic
};



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

    //Reading binary file. Note: use console command "xxd 1.dat" toread values of dat file onconsole
    //the block of code simply prints the first 10 numbers, will need to generalize it
    ifstream binaryFile;
    int y;
    unsigned char buf[4];

    datFile dats[arr[0]]; //creates an array of size m (number of sub arrays)
    for(int i = 0; i < arr[0];  i++){ //loop through every .dat file
          dats[i].subArrays =arr[0];
          dats[i].k = arr[2];
          dats[i].length = arr[1];
          std::stringstream sstm;
          sstm << i+1 << ".dat";
          dats[i].fileName = sstm.str();
          dats[i].values = new int[dats[i].length];
          cout << "File name: " << dats[i].fileName << endl;
          binaryFile.open(dats[i].fileName.c_str(), ios::in | ios::out | ios::binary);
          for(int k = 0; k <  dats[i].length; k++){ //will loop through every element in the array for each dat file

                binaryFile.read(reinterpret_cast<char *>(buf), sizeof(int));
                unsigned int b4 = (buf[0] << 24) + (buf[1]) + (buf[2])+ (buf[3]);
                unsigned int b2 = (buf[0] << 8) + (buf[1]);
                y = b4 + b2;
                dats[i].values[k] = y;
               //cout  << dats[i].values[k]<< endl; //<------UNCOMMENT THIS IF WANT TO SEE ARRAY
          }
          binaryFile.close();

   }

    //store m n and k retrieved from input files
    m = arr[0];
    n = arr[1];
    k = arr[2];

    cout << "m is: " << arr[0] << "\n";
    cout << "n is: " << arr[1] << "\n";
    cout << "k is: " << arr[2] << "\n";

    result = select(m,n,k);
    cout << k << "th smallest element is: " << result << endl;

    //print result of select() to output file
    ofstream outfile;
    outfile.open("output.txt");
    outfile << result;

    return 0;
}
