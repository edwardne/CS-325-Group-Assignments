#include<iostream>
#include<fstream>
#include<string>
#include <sstream>
using namespace std;

struct datFile{
      int subArrays; //number of sub arrays, also known as 'm'
      int k; //kth smallest numbers
      int length; //described as n in assignment description
      string fileName;
      int values []; //should probably be dynamic
};

//merging two sorted arrays into one sorted arrays
void merge(int arr1[], int arr2[], int arr3[]){
  int x = sizeof(arr1)/sizeof(arr1[0]);
  int y = sizeof(arr2)/sizeof(arr2[0]);
  int i = 0, j = 0, k = 0;

  //traverse both arrays
  while(i < x && j < y){
    if(arr1[i] < arr2[j])           //Check if the current element in the first array
      arr3[k++] = arr1[i++];        //is smaller than the current element in second array
    else                            //Store which one is smaller
      arr3[k++] = arr2[j++];
  }

  while(i < x)
    arr3[k++] = arr1[i++];

  while(j < y)
    arr3[k++] = arr2[j++];
}

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
    binaryFile.open("1.dat", ios::in | ios::out | ios::binary);
    unsigned int c;
    unsigned char y;

    for(int i = 0; i < 10; i++){
          binaryFile.read(reinterpret_cast<char *>(&y), 1);
          cout << (int)y << endl;
    }
    datFile dats[arr[0]]; //creates an array of size m (number of sub arrays)
    for(int i = 0; i < arr[0];  i++){
          dats[i].subArrays =arr[0];
          dats[i].k = arr[2];
          dats[i].length = arr[1];

          std::stringstream sstm;
          sstm << i+1 << ".dat";
          dats[i].fileName = sstm.str();
        //dats[i].fileName=  itoa(i) + ".dat";

          cout << "File name: " << dats[i].fileName << endl;
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
