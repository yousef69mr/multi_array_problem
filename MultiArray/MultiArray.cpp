// MultiArray.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "MultiArray.h"

using namespace std;

int main()
{
    // Example usage
    MultiArray<int> myArrays(2, { "numbers", "grades" }, { 3, 5 });

    myArrays.loadFromFile("numbers", "numbers.txt");
    myArrays.loadFromFile("grades", "grades.txt");

    cout << "Original Arrays:\n" << myArrays;
    
    cout << "###############\n";
    int* subArray = myArrays.subArray("grades", 1, 3);
    cout << "Subarray of 'grades' from index 1 to 3: ";
    printArray(subArray,3);
    cout << "###############\n";
    myArrays.reverse("grades");
    cout << "Reversed 'grades' array:\n" << myArrays;
    cout << "###############\n";
    myArrays.sort("grades");
    cout << "Sorted 'grades' array:\n" << myArrays;
    cout << "###############\n";
    cout << "Is 40 present in any array? " << (myArrays.search(40) ? "Yes" : "No") << endl;
    cout << "###############\n";
    cout << "Value at index 2 of 'grades': " << myArrays("grades", 2) << endl;
    cout << "###############\n";
    
    MultiArray<int> splitArrays = myArrays.split("grades");
    cout << "Arrays after splitting 'grades':\n" << splitArrays;
    cout << "###############\n";
    
    int* mergedArray = myArrays.merge();
    cout << "Merged array of all arrays: ";
    printArray(mergedArray,8);
    cout << "###############\n";
    myArrays.applyToArray("numbers", [](int& x) { x += 10; });
    cout << "Arrays after applying function 'x += 10' to 'numbers':\n" << myArrays;
    cout << "###############\n";
    MultiArray<int> squaredArrays = square(myArrays);
    cout << "Arrays after squaring 'numbers':\n" << squaredArrays;
    cout << "###############\n";


    delete[] subArray;
    delete[] mergedArray;

    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
