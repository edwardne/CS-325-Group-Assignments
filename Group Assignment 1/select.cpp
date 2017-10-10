#include<iostream>
#include<fstream>
#include<string>
#include <sstream>
#include <byteswap.h>

using namespace std;

int binarySearch(int * values, int val, int beginning, int ending);
int findK(struct datFile*, int k);
void truncate(struct datFile*, int k);
int largestArray(struct datFile*);
int binarySearch(int[], int, int);




struct datFile{
      int subArrays; //number of sub arrays, also known as 'm'
      int k; //kth smallest numbers
      int length; //described as n in assignment description
      string fileName;
      int* values; //should probably be dynamic
      int beginning;
      int ending; //last index of array, will change
      int middlePoint; //not exactly a middle point for every array. It's the 'm ' we marked on the paper
};

int binarySearch(int data[], int val, int beginning, int ending){
      int low = beginning;
      int high = ending;

      while(low < high){
            int mid = (low + high) / 2;
            if(data[mid] < val){
                  low = mid + 1;
            }else{
                  high = mid;
            }
      }

      return low;
}

//used for step 2, will return first largest array
int largestArray(struct datFile* dats){
      int n_subarrays = dats[0].subArrays;
      int largestArrayIndex = 0;
      int largestLength = 0;
      for(int i = 0; i < n_subarrays; i++){
            if(dats[i].length > largestLength){
                  largestArrayIndex = i;
            }
      }
      return largestArrayIndex;

}

//for step 1
void truncate(struct datFile* dats, int k){
      int n_subarrays = dats[0].subArrays;
      for(int i = 0; i < n_subarrays; i++){
            if(dats[i].length > k){
                  dats[i].ending = k;
                  dats[i].length = dats[i].ending - dats[i].beginning + 1;
            }
      }
}

int findK(struct datFile* dats, int k){
      truncate(dats, dats[0].k);
      int largestArr = largestArray(dats);
      cout << "Largest array is: " << largestArr << endl;
      int m = dats[largestArr].length / 2 + 1; //m is the middle index
      cout << "m is : " << m << endl;
      for(int i = 0; i < dats[0].subArrays; i++){
            //do binary search for each  except the one with m
            if(i != largestArr){
                  //dats[i].middlePoint = binarySearch(dats, m, )
                  dats[i].middlePoint = binarySearch(dats[i].values, m, dats[i].beginning, dats[i].ending);
                  //do binary search
            }else{
                  dats[largestArr].middlePoint = m;
            }
      }

      /*
      for(int i = 0; i < dats[0].subArrays; i++){
            for(int k = 0; k <  dats[i].length; k++){ //will loop through every element in the array for each dat file

                cout  << dats[i].values[k]<< endl; //<------UNCOMMENT THIS IF WANT TO SEE ARRAY
            }
      }*/

      //truncate(dats*, dats.k); //step 1, truncate if any have length > k
      return 0;
}


/*
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
}*/

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

    struct datFile* dats;
    dats = new datFile[arr[0]];
    //datFile dats[arr[0]]; //creates an array of size m (number of sub arrays)
    for(int i = 0; i < arr[0];  i++){ //loop through every .dat file
          dats[i].subArrays =arr[0];
          dats[i].k = arr[2];
          dats[i].length = arr[1];
          std::stringstream sstm;
          sstm << i+1 << ".dat";
          dats[i].fileName = sstm.str();
          dats[i].values = new int[dats[i].length];
          dats[i].beginning = 0;
          dats[i].ending = arr[1] -1;
          cout << "File name: " << dats[i].fileName << endl;
          binaryFile.open(dats[i].fileName.c_str(), ios::in | ios::out | ios::binary);
          for(int k = 0; k <  dats[i].length; k++){ //will loop through every element in the array for each dat file

                binaryFile.read(reinterpret_cast<char *>(buf), sizeof(int));
                unsigned int b4 = (buf[0] << 24) + (buf[1]) + (buf[2])+ (buf[3]);
                unsigned int b2 = (buf[0] << 8) + (buf[1]);
                y = b4 + b2;
                dats[i].values[k] = y;
              cout  << dats[i].values[k]<< endl; //<------UNCOMMENT THIS IF WANT TO SEE ARRAY
          }
         // binaryFile.close();

   }

   findK(dats, dats->k);

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
