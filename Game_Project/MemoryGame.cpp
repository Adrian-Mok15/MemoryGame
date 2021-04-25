#include "MemoryGame.hpp"
#include <cstdlib> //srand, rand
#include <ctime>
#include <iomanip> //setw
#include <iostream> //std
using namespace std;

int* randomize(int numSpaces); //function to randomize layout
void swap(int* arr, int i, int j);
void displaySeparateLine(int numSpaces);

//TODO: implement by students
MemoryGame::MemoryGame() //default constructor,
{
    srand(time(NULL)); //TODO: uncomment this line to see
        //different layouts of numbers in different runnings.
        //time(NULL) is the current running time.
        //use the current running time to grow random sequence
        //Since running time differs,
        //the random sequence looks different
        //at different running time.
    srand(1); //TODO: add this before submitting to gradescope,
        //or autograde script cannot handle random input.
    numPairs = 3;
    numSpaces = 2*numPairs + 2;
    int* data = new int[numPairs];
    for(int i = 0; i<numPairs; ++i){
        data[i] = rand()%1000;
    }
    values = new string[numSpaces];
    int* arr = randomize(numSpaces);

    for(int i = 0; i<numSpaces; ++i){
        if(i<numPairs*2){
            values[arr[i]] = to_string(data[i/2]);
            values[arr[i+1]] = to_string(data[i/2]);
        }
        else values[arr[i]] = "";
    }
    delete[] data;
    data = nullptr;
    delete[] arr;
    arr = nullptr;
}

//TODO: implement by students
MemoryGame::~MemoryGame()
{

}

MemoryGame::MemoryGame(int n){
    srand(time(NULL)); //TODO: uncomment this line to see
        //different layouts of numbers in different runnings.
        //time(NULL) is the current running time.
        //use the current running time to grow random sequence
        //Since running time differs,
        //the random sequence looks different
        //at different running time.
    srand(1); //TODO: add this before submitting to gradescope,
        //or autograde script cannot handle random input.
    numPairs = n;
    numSpaces = 2*n + 2;
    int* data = new int[numPairs];
    for(int i = 0; i<numPairs; ++i){
        data[i] = rand()%1000;
    }
    values = new string[numSpaces];
    int* arr = randomize(numSpaces);

    for(int i = 0; i<numSpaces; ++i){
        if(i<numPairs*2){
            values[arr[i]] = to_string(data[i/2]);
            values[arr[i+1]] = to_string(data[i/2]);
        }
        else values[arr[i]] = "";
    }
    delete[] data;
    data = nullptr;
    delete[] arr;
    arr = nullptr;
}

MemoryGame::MemoryGame(int n, int m){
    srand(time(NULL)); //TODO: uncomment this line to see
        //different layouts of numbers in different runnings.
        //time(NULL) is the current running time.
        //use the current running time to grow random sequence
        //Since running time differs,
        //the random sequence looks different
        //at different running time.
    srand(1); //TODO: add this before submitting to gradescope,
        //or autograde script cannot handle random input.
    numPairs = n;
    numSpaces = m;
    int* data = new int[numPairs];
    for(int i = 0; i<numPairs; ++i){
        data[i] = rand()%1000;
    }
    values = new string[numSpaces];
    int* arr = randomize(numSpaces);

    for(int i = 0; i<numSpaces; ++i){
        if(i<numPairs*2){
            values[arr[i]] = to_string(data[i/2]);
            values[arr[i+1]] = to_string(data[i/2]);
        }
        else values[arr[i]] = "";
    }
    delete[] data;
    data = nullptr;
    delete[] arr;
    arr = nullptr;
}

int* randomize(int size)
{
    int *arr = new int[size];
    for(int i = 0; i< size; ++i){
        arr[i] = i;
    }
    int index;
    for(int i = size; i>0; --i){
        index = rand()%size;
        swap(arr, index, size-1);
        size--;
    }
    return arr;

}

void swap(int *arr, int i, int j)
{
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}

//Display -----+ for numSpaces times.
//Add an extra + when for the first block (when index i is 0).
//So suppose numSpaces is 8, we get
//+-----+-----+-----+-----+-----+-----+-----+-----+
//followed by a new line.
void displaySeparateLine(int numSpaces)
{
    for (int i = 0; i < numSpaces; i++)
    {
        if (i == 0)
           cout << "+";
        cout << "-----+";
    }
    cout << endl;
}

//TODO: implement by students
//display the items in values array where bShown is true.
void MemoryGame::display(bool* bShown)
{
    std::cout << " ";
    for(int i = 0; i< numSpaces; ++i){
        std::cout << setw(3) << i;
        std::cout << setw(3) << " ";
    }
    std::cout << endl;
    displaySeparateLine(numSpaces);
    std::cout << "|";
    for(int i = 0; i < numSpaces; ++i) {
        if(bShown[i] == true){
            std::cout << setw(5) << values[i];
        }
        else cout << setw(5) << "";
        std::cout << "|";
    }
    std::cout << "\n";
    displaySeparateLine(numSpaces);

}

//TODO: implement by students
//rules for a round
//(1) pick a number, flip it
//(2) pick a second number, if the number is the same as
//    previous pick, display the second number,
//    otherwise, unflip the previous pick.
//(3) Finish until every pair are chosen correctly.
void MemoryGame::play()
{
    bool* bShown = new bool[numSpaces];
    for(int i =0; i<numSpaces; ++i){
        bShown[i] = false;
    }
    display(bShown);
    int index;
    int first;
    int numFlips = 0;
    int pairsFound = 0;

    while(pairsFound < numPairs){
        std::cout << "Pick a cell to flip: ";
        std::cin >> index;
        while(index < 0 || index >= numSpaces || bShown[index] == true){
            if(index < 0|| index>= numSpaces){
                std::cout << "index needs to be in range [0, " << numSpaces << "]" << "\n";
            }
            else{
                std::cout << "The cell indexed at " << index << " is shown." << "\n";
            }
            cout << "Re-enter an index: ";
            cin >> index;
        }
        if(numFlips % 2 == 0){
            bShown[index] = true;
            first = index;
        }
        else{
            if(values[first] == values[index] && values[first] != ""){
                bShown[index] = true;
                pairsFound++;
            }
            else{
                bShown[index] = true;
                display(bShown);
                bShown[index] = false;
                bShown[first] = false;
            }
        }
        display(bShown);
        numFlips++;
    }
    std::cout << "Congratulations! Take " << numFlips << " steps to find all matched pairs." << "\n";

    delete [] bShown;
    bShown = nullptr;
}
