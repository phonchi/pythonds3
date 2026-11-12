#include <iostream>
#include <vector>
using namespace std;

//function goes through list sorting adjacent values as it bubbles
//the largest value to the top.
vector<int> bubbleSort(vector<int> avector) { //the vector for bubble sort
  for (int passnum = avector.size()-1; passnum > 0; passnum -= 1) {
      for (int i = 0; i < passnum; i++) {
          if (avector[i] > avector[i+1]) {
              int temp = avector[i];
              avector[i] = avector[i+1];
              avector[i+1] = temp;
          }
      }
  }
  return avector;
}

vector<int> shortBubbleSort(vector<int> avector){ //the vector for bubble sort
    bool exchanges = true;
    int passnum = avector.size();
    //while vector size is greater than 0 and exchanges = true
    while (passnum > 0 && exchanges) {
        exchanges = false;
       //loops through vector, exchanging values until it reaches the end of vector.
        for(int i = 0; i < passnum; i++){
            if(avector[i] > avector[i+1]){
                exchanges = true;
                int temp = avector[i];
                avector[i] = avector[i+1];
                avector[i+1] = temp;
            }
        }
        //subtracts from the passnum variable so that the next passthrough is one less
        //than the previous, because the largest value has already 'bubbled' all the way up.
        passnum = passnum - 1;
    }
    return avector;
}


//function that sorts through values in vector through selection sort
vector<int> selectionSort(vector<int> avector) {
    for (int fillslot = (avector.size() - 1); fillslot >= 0; fillslot--) {
        int positionOfMax = 0;
        for (int location = 1; location < fillslot + 1; location++) {
            if (avector[location] > avector[positionOfMax]) {
                positionOfMax = location;
            }
        }

        int temp = avector[fillslot];
        avector[fillslot] = avector[positionOfMax];
        avector[positionOfMax] = temp;
    }
    return avector;
}


vector<int> insertionSort(vector<int> avector) {
    for (unsigned int index=1; index<avector.size(); index++) {

        int currentvalue = avector[index];
        int position = index;

        while (position>0 && avector[position-1]>currentvalue) {
            avector[position] = avector[position-1];
            position--;
        }

        avector[position] = currentvalue;
    }

    return avector;
}


// print the sorted vector
void printl(vector<int> avector) {
    for (unsigned int i=0; i<avector.size(); i++) {
        cout << avector[i] << " ";
    }
    cout << endl;
}
// function returns sorted subvector
vector<int> gapInsertionSort(vector<int> avector, int start, int gap) {
    for (unsigned int i = start + gap; i < avector.size(); i += gap) {
        int currentvalue = avector[i];
        int position = i;

        while (position >= gap && avector[position - gap] > currentvalue) {
            avector[position] = avector[position - gap];
            position -= gap;
        }
        avector[position] = currentvalue;
    }
    return avector;
}

//function shellsorts through the vector
vector<int> shellSort(vector<int> avector) {
    int subvectorcount = avector.size() / 2; //cuts vector by half
    while (subvectorcount > 0) {
        for (int startposition = 0; startposition < subvectorcount;
             startposition++) {
            avector = gapInsertionSort(avector, startposition, subvectorcount);/*
      runs avector through gapInsertionSort function
       */
        }
        cout << "After increments of size " << subvectorcount
             << " The vector is: " << endl;
        printl(avector);

        subvectorcount = subvectorcount / 2; //cuts vector in half
    }

    return avector;
}

//function sorts using mergesort.
vector<int> mergeSort(vector<int> avector) {
    cout<<"Splitting ";
    printl(avector);
    if (avector.size()>1) {
        int mid = avector.size()/2;
        //C++ Equivalent to using Python Slices
        vector<int> lefthalf(avector.begin(),avector.begin()+mid);
        vector<int> righthalf(avector.begin()+mid,avector.begin()+avector.size());

        lefthalf = mergeSort(lefthalf);
        righthalf = mergeSort(righthalf);

        unsigned i = 0;
        unsigned j = 0;
        unsigned k = 0;
        while (i < lefthalf.size() && j < righthalf.size()) {
            if (lefthalf[i] < righthalf[j]) {
                avector[k]=lefthalf[i];
                i++;
            } else {
                avector[k] = righthalf[j];
                j++;
            }
            k++;
        }

        while (i<lefthalf.size()) {
            avector[k] = lefthalf[i];
            i++;
            k++;
        }

        while (j<righthalf.size()) {
            avector[k]=righthalf[j];
            j++;
            k++;
        }

    }
    cout<<"Merging ";
    printl(avector);

    return avector;
}


//function partitions vector depending on pivot value
int partition(vector<int> &avector, int first, int last) {
  int pivotvalue = avector[first];

  int rightmark = last;
  int leftmark = first+1;

  bool done = false;

  while(not done){
    while(leftmark<=rightmark and avector[leftmark]<=pivotvalue){
      leftmark++;
    }
    while(rightmark>=leftmark and avector[rightmark]>=pivotvalue){
      rightmark--;
    }
    if(rightmark<leftmark){
      done = true;
    }
    else{
      swap(avector[rightmark], avector[leftmark]);
    }
  }

  swap(avector[rightmark], avector[first]);

  return rightmark;
}

//recursive function that quicksorts through a given vector
void quickSort(vector<int> &avector, int first, int last) {
  int splitpoint;

  if (first<last) {
    splitpoint = partition(avector,first,last);

    quickSort(avector,first,splitpoint);
    quickSort(avector,splitpoint+1,last);

  }
}

