#include <iostream>
#include <string>
#include <ctime>
#include <fstream>
#include <cstdlib>
using namespace std;

//n^2 algorithms
void selectionSort(string*, int);
void insertionSort(string*, int);

//n log n sorting algorithms
void quickSort(string*, int, int);
     int partition(string*, int, int, string&);
void mergeSort(string*, string*, int, int);

//print, testing
void printArray(string*, int);

//Command Line Arguments
//sorting[0] == executable
//sorting[1] == first argument(line count)
//soritng[2] == type of sort(SS,IS,QS,MS)
int main(int argArrSize, char* sorting[])
{
     if(argArrSize < 3)
     {
          cout << "This program expects 3 arguments (Executable, Line Count, and Type of Sort)" << endl;
          cout << "You provided only 2 arguments" << endl;
          return 1;
     }

     long int size = atoi(sorting[1]), arraySpot = 0;//character array argument to long integer
	string* strArray = new string[size];
	string* temp = new string[size];
	string word, algChoice = sorting[2]; //type of sort
     int third = size / 3;

     ifstream readFile;
     readFile.open("/home/win.thackerw/271/sort.dat");
	if(!readFile.is_open())
	{
		cout <<"File did not open!" << endl;
                exit(0);
        }

     cout << "STARTING FILE READ" << endl;
     readFile >> word;
     while((!readFile.eof()) && (arraySpot < size))
     {
          if(third == arraySpot || (third * 2) == arraySpot || (size - 1) == arraySpot)
               cout << "." << endl; //progress bar, helps convince me I'm not in infinite loop

          strArray[arraySpot] = word;
          arraySpot++;
          readFile >> word;
     }
     readFile.close();

     if(algChoice == "SS")//Insertion Sort
     {
          cout << "STARTING SELECTION SORT" << endl;
          selectionSort(strArray, size);
     }
     else if(algChoice == "QS")
     {
          cout << "STARTING QUICK SORT" << endl;
		quickSort(strArray, 0, size-1);
     }
     else if(algChoice == "IS")
     {
          cout << "STARTING INSERTION SORT" << endl;
          insertionSort(strArray,size);
     }
     else if(algChoice == "MS")
     {
          cout << "STARTING MERGE SORT" << endl;
          mergeSort(strArray, temp, 0, size-1);
     }

     //output results
     string fileName = algChoice + "_sorted.dat";
	ofstream outFile((fileName).c_str());
     cout << "STARTING WRITE TO FILE" << endl;
	for(int x = 0; x < size; x++)
	{
          if(third == x || (third * 2) == x || (size - 1) == x)
               cout << "." << endl;

		outFile << strArray[x] << endl;
	}

	outFile.close();
     cout << "FINISHED" << endl;
     return 0;
}

//n^2 sorting algorithms
void selectionSort(string* array, int size)
{
     for (int i = 0; i < size-1; i++)
     {
          int lowindex = i;           // Remember its index

          for (int j = size-1; j > i; j--)   // Find the least value
               if (array[j] <= array[lowindex])
                    lowindex = j;           // Put it in place

          swap(array[i], array[lowindex]);
     }
}

void insertionSort(string* array, int size)
{
     for (int i=1; i < size; i++)       // Insert i’th record
          for (int j = i; (j > 0) && (array[j]< array[j-1]); j--)
               swap(array[j], array[j-1]);
}

//n log n sorting algorithms
void quickSort(string* array, int low, int size)
{
	int pivotI = (low+size) / 2;

	swap(array[pivotI],array[size]);

	int newLow = partition(array, low-1, size, array[size]);
	swap(array[newLow],array[size]);

	if((newLow-low)>1)
		quickSort(array, low, newLow-1);
	if((size-newLow)>1)
		quickSort(array, newLow+1, size);

}
int partition(string* array, int low, int high, string &pivot)
{
	do{
		while(array[++low] < pivot);
		        while(high && (array[--high] > pivot));
		                swap(array[low], array[high]);

	}while(low < high);

	swap(array[low], array[high]);

	return low;
}

void mergeSort(string* array, string* temp, int lt, int rt)
{
	int I, j, k, mid = (lt+rt) / 2;
	if (lt == rt)
		return;

	mergeSort(array, temp, lt, mid);
	mergeSort(array, temp, mid+1, rt);

	for (I = lt; I <= mid; I++)
		temp[I] = array[I];

	for (j = 1; j <= rt-mid; j++)
		temp[rt-j+1] = array[j+mid];

	I = lt;
	j = rt;

	for (k = lt; k <= rt; k++)
	{
		if (temp[I] < temp[j])
			array[k] = temp[I++];

		else
			array[k] = temp[j--];
	}
}

void printArray(string* array, int size)
{
	for(int x = 0; x <= size-1; x++)
	{
		cout << array[x] << endl;
	}

}
