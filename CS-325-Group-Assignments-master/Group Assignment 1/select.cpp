#include<iostream>
#include<fstream>
#include<string>
#include <sstream>
using namespace std;

int binarySearch(int * values, int val, int beginning, int ending);
int findK(struct datFile*, int k);
void truncateK(struct datFile*, int k);
int largestArray(struct datFile*);
int binarySearch(int[], int, int);
void truncateL(struct datFile*, int newBeginning, int newEnd, int subtract);
int findKthSmallest(struct datFile*, int k);


struct datFile{
      int subArrays; //number of sub arrays, also known as 'm'
      int k; //kth smallest numbers
      int length; //described as n in assignment description
      string fileName;
      int* values; //should probably be dynamic
      int beginning;
      int ending; //last index of array, will change
      int middlePoint; //not exactly a middle point for every array. It's the 'm ' we marked on the paper
      int L;
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

//used to truncate when considering L's size
void truncateL(struct datFile* dats, int newBeginning, int newEnd, int subtract){
      for(int i = 0; i < dats[0].subArrays; i++){
            //cout << "DATS[0].K IS: " << dats[0].k << endl;
            //int difference = dats[i].ending  - dats[i].beginning - newEnd - newBeginning;
            int oldLength = dats[i].ending - dats[i].beginning;
            int newLength = newEnd - newBeginning;
            int difference = oldLength - newLength;
            dats[i].length = newLength;
            dats[i].beginning = newBeginning;
            dats[i].ending = newEnd;
            dats[i].length = dats[i].ending - dats[i].beginning + 1;
            //SOMETHING IS WRONG HERE WITH SUBTRACTING K. K SHOULD BE SUBTRACTED IF THE ELEMENTS IN THE LOWER HALF ARE BEING CUT OFF
            if(subtract == 1){
                  dats[0].k -= dats[i].L;

            }


            /*
            cou
            cout << "dats[i].ending " << dats[i].ending << "  - dats[i].beggining  " << dats[i].beginning << " +  newEnd " << newEnd << " - newBeginning " << newBeginning << endl;
            cout << "Difference is: " << difference << endl;
            for(int j = 0; j < dats[0].subArrays; j++){
                  if(i != j && subtract == 1){
                        cout << "Subtracting: " << difference << endl;
                        dats[j].k -= difference;
                  }
            }*/
      }
}
//for step 1, truncate if k> length
void truncateK(struct datFile* dats, int k){
      int n_subarrays = dats[0].subArrays;
      for(int i = 0; i < n_subarrays; i++){
            if(dats[i].length > k){
                  dats[i].ending = k - 1;
                  dats[i].length = dats[i].ending - dats[i].beginning;
            }

      }
}

int findKthSmallest(struct datFile* dats, int k){
      int smallest = dats[0].values[dats[0].beginning];
      for(int i = 1; i < k ; i++){
            if(dats[i].values[dats[i].beginning] < smallest){
                  smallest = dats[i].values[dats[i].beginning];
            }
      }

      for(int i = 0; i < k-1; i++){
            int wasFound = -1;

            for(int k = 0; k < dats[0].subArrays; k++){
                  if(dats[k].values[dats[k].beginning] > smallest && (wasFound == -1 || dats[k].values[dats[k].beginning] < dats[wasFound].values[dats[k].beginning])){
                        wasFound = k;
                  }
            }
            smallest = dats[wasFound].values[dats[wasFound].beginning];
      }

      return smallest;
}

int findK(struct datFile* dats, int k){
      if(k < dats[0].subArrays){
            for(int i = 0; i < dats[0].subArrays; i++){
                  for(int k = dats[i].beginning; k < dats[i].ending; k++){


                  }
            }

            return findKthSmallest(dats, k);
      }else{
            truncateK(dats, dats[0].k);
            int largestArr = largestArray(dats);

            int m = (dats[largestArr].ending) / 2 ; //m is the middle index

            //cout << "m is : " << m << endl;
            for(int i = 0; i < dats[0].subArrays; i++){ //loop for every array
                  //do binary search for each  except the one with m
                  if(i != largestArr){
                        //dats[i].middlePoint = binarySearch(dats, m, )
                        //cout << "going to find binary search " << endl;
                        dats[i].middlePoint = binarySearch(dats[i].values, dats[largestArr].values[m], dats[i].beginning, dats[i].ending);
                        //cout << binarySearch(dats[i].values, dats[largestArr].values[m], dats[i].beginning, dats[i].ending) << " <--- binary search " << endl;
                        //do binary search
                  }else{
                        dats[largestArr].middlePoint = m;
                  }

                  dats[i].L = dats[i].middlePoint - dats[i].beginning;
                  //cout << "Less than: " << dats[i].L << endl;



                  if(dats[i].k < dats[i].L){ //truncate off upper half. just use bottom half.
                        truncateL(dats, dats[i].beginning, dats[i].middlePoint, 1);

                  }else{//truncate off lower half, so just use top half
                        truncateL(dats, dats[i].middlePoint, dats[i].ending, 1);
                  }
                  return findK(dats, dats[0].k);
            }

      }


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
          binaryFile.open(dats[i].fileName.c_str(), ios::in | ios::out | ios::binary);
          for(int k = 0; k <  dats[i].length; k++){ //will loop through every element in the array for each dat file

                binaryFile.read(reinterpret_cast<char *>(buf), sizeof(int));
                unsigned int b4 = (buf[0] << 24) + (buf[1]) + (buf[2])+ (buf[3]);
                unsigned int b2 = (buf[0] << 8) + (buf[1]);
                y = b4 + b2;
                dats[i].values[k] = y;
          }
         binaryFile.close();

   }

    result = findK(dats, k);

    //store m n and k retrieved from input files
    m = arr[0];
    n = arr[1];
    k = arr[2];

    //print result of select() to output file
    ofstream outfile;
    outfile.open("output.txt");
    outfile << result;

    return 0;
}
