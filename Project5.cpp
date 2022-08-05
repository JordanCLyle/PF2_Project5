// Project5_PF2_Project.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
using namespace std;
#include <stdlib.h>

//------------------------------------------------------------------
// Read input file to initialize data array
//------------------------------------------------------------------
void read_data(string name, int data[], int& count, int& range)
{
    // Open input file
    ifstream din;
    din.open(name.c_str());
    if (din.fail())
        cout << "Error: could not open input file\n";

    // Read the data
    range = 0;
    din >> count;
    for (int i = 0; i < count; i++)
    {
        din >> data[i];
        if (data[i] > range)
            range = data[i];
    }

    // Close the file
    din.close();
    range++;
}

//------------------------------------------------------------------
// Write data array to output file
//------------------------------------------------------------------
void write_data(string name, int data[], int count)
{
    // Open output file
    ofstream dout;
    dout.open(name.c_str());
    if (dout.fail())
        cout << "Error: could not open output file\n";

    // Write the data
    for (int i = 0; i < count; i++)
    {
        if (i % 20 == 0)
            dout << endl;
        dout << data[i] << " ";
    }

    // Close the file 
    dout.close();
}

//------------------------------------------------------------------
// Initialize data array with random values
//------------------------------------------------------------------
void create_random_data(int data[], int count, int range)
{
    srand((unsigned)time(NULL));
    // Put random data values into array
    for (int index = 0; index < count; index++)
        data[index] = rand() % range;
    write_data("unsorted.txt", data, count);
}

//------------------------------------------------------------------
// Initialize data array with mostly sorted values
//------------------------------------------------------------------
void create_mostly_sorted_data(int data[], int count, int swaps)
{
    // Put sorted data values into array
    for (int index = 0; index < count; index++)
        data[index] = index;

    // Shuffle data by swapping random pairs of values
    for (int index = 0; index < swaps; index++)
    {
        int pos1 = rand() % count;
        int pos2 = rand() % count;
        int temp = data[pos1];
        data[pos1] = data[pos2];
        data[pos2] = temp;
    }
    write_data("unsorted.txt", data, count);
}
void merge_sort2(int data[], int copy[], int low, int high)
{
    // Check terminating condition
    int range = high - low + 1;
    if (range > 1)
    {
        // Divide the array and sort both halves
        int mid = (low + high) / 2;
        merge_sort2(data, copy, low, mid);
        merge_sort2(data, copy, mid + 1, high);

        // Initialize array indices
        int index1 = low;
        int index2 = mid + 1;
        int index = 0;

        // Merge largest data elements into copy array
        while (index1 <= mid && index2 <= high)
        {
            if (data[index1] < data[index2])
                copy[index++] = data[index2++];
            else
                copy[index++] = data[index1++];
        }

        // Copy any remaining entries from the first half
        while (index1 <= mid)
            copy[index++] = data[index1++];

        // Copy any remaining entries from the second half
        while (index2 <= high)
            copy[index++] = data[index2++];

        // Copy data back from the temporary array
        for (index = 0; index < range; index++)
            data[low + index] = copy[index];
    }
}
void merge_sort3(int data[], int copy[], int low, int high)
{
    // Check terminating condition
    int range = high - low + 1;
    int midpoint1 = low + (high - low) / 3;
    int midpoint2 = low + ((high - low) / 3) * 2 + 1;
    if (range > 1)
    {
        // Divide the array and sort both halves
        // Initialize array indices
        int index1 = low;
        int index2 = midpoint1 + 1;
        int index3 = midpoint2 + 1;
        int index = 0;

        merge_sort3(data, copy, low, midpoint1);
        merge_sort3(data, copy, index2, midpoint2);
        merge_sort3(data, copy, index3, high);


        // Merge largest data elements into copy array
        while (index1 <= midpoint1 && index2 <= midpoint2 && index3 <= high) // Run until one array runs out of elements
        {
            if (data[index1] < data[index2])
            { 
                if (data[index3] < data[index2])
                {
                    copy[index++] = data[index2++]; // data[index2] is largest, add index2 to copy
                }
                else // If index3 > index2
                {
                    copy[index++] = data[index3++]; // data[index3] is largest, add index2 to copy
                }
            }
            else if (data[index1] < data[index3])
            {
                copy[index++] = data[index3++]; // data[index3] is largest, add index3 to copy
            }
            else // data[index1] > data[index2] and data[index1] > data[index3]
            {
                copy[index++] = data[index1++]; // data[index1] is largest, add index1 to copy
            }
        }
        while (index1 <= midpoint1 && index2 <= midpoint2) // If data[index3] runs out first
        {
            if (data[index1] < data[index2])
            {
                copy[index++] = data[index2++];
            }
            else
            {
                copy[index++] = data[index1++];
            }
        }
        while (index2 <= midpoint2 && index3 <= high) // If data[index1] runs out first
        {
            if (data[index2] < data[index3])
            {
                copy[index++] = data[index3++];
            }
            else
            {
                copy[index++] = data[index2++];
            }
        }
        while (index1 <= midpoint1 && index3 <= high) // If data[index2] runs out first
        {
            if (data[index1] < data[index3])
            {
                copy[index++] = data[index3++];
            }
            else
            {
                copy[index++] = data[index1++];
            }
        }
        //Compare index1 to index2
        // Compare index1 to index 3
        // Compare index2 to index 3
        // Copy any remaining entries from the first half
        while (index1 <= midpoint1)
            copy[index++] = data[index1++];
        while (index2 <= midpoint2)
            copy[index++] = data[index2++];
        // Copy any remaining entries from the second half
        while (index3 <= high)
            copy[index++] = data[index3++];

        // Copy data back from the temporary array
        for (index = 0; index < range; index++)
            data[low + index] = copy[index];
    }
}

void merge_sort(int data[], int low, int high)
{

    // Check terminating condition
    int range = high - low + 1;
    if (range > 1)
    {
        // Allocate memory and call merge_sort3
        int* copy = new int[range];
        cout << endl;
        int menu = 0;
        while (menu == 0)
        {
            // Print input data menu
            cout << "Select initial data:\n"
                << "  r - random data\n"
                << "  m - mostly sorted data\n"
                << "  s - sorted data\n"
                << "  e - exit\n";
            char choice;
            cin >> choice;

            // Create input data
            if (choice == 'r')
            {
                create_random_data(data, high, range);
            }
            else if (choice == 'm')
            {
                create_mostly_sorted_data(data, high, high / 10);
            }
            else if (choice == 's')
            {
                create_mostly_sorted_data(data, high, 0);
            }
            else
            {
                menu = 1;
            }
            if (menu == 0)
            {
                cout << "Select sorting method:\n"
                    << "2 - Classic Merge Sort\n"
                    << "3 - 3-Way Merge Sort\n"
                    << "4 - Exit\n";
                int numberChoice;
                cin >> numberChoice;
                if (numberChoice == 2) // Conditional to initiate classic merge sort
                {
                    // Get start time
                    clock_t time1 = clock(); //Start timer
                    merge_sort2(data, copy, low, high);
                    cout << endl << endl;
                    clock_t time2 = clock(); //End timer
                    double run_time = (time2 - time1) / (double)CLOCKS_PER_SEC;
                    cout << "Run time: " << run_time << " seconds\n";
                    //                for (int i = 0; i < range - 1; i++)
                    //                {
                    //                    cout << data[i] << " ";
                    //                }
                    //                cout << endl;
                    write_data("sorted.txt", data, high);
                }
                else if (numberChoice == 3) // Conditional to initiate 3-way merge sort
                {
                    // Get start time
                    clock_t time1 = clock(); // Start timer
                    merge_sort3(data, copy, low, high);
                    // Get end time
                    cout << endl << endl;
                    clock_t time2 = clock(); //End timer
                    double run_time = (time2 - time1) / (double)CLOCKS_PER_SEC;
                    cout << "Run time: " << run_time << " seconds\n";
                    //               for (int i = 0; i < range - 1; i++)
                    //               {
                    //                   cout << data[i] << " ";
                    //               }
                    //               cout << endl;
                    write_data("sorted.txt", data, high);
                }
                else
                {
                    menu = 1;
                }
            }
        }
            delete[]copy;
    }
}
int main()
{
    const int MAX_COUNT = 99999;
    const int MAX_RANGE = 99999;
    int data[MAX_COUNT];
    int count;
    int range;
    cout << "ENTER COUNT: ";
    cin >> count;
    cout << "ENTER RANGE: ";
    cin >> range;
    if (count > MAX_COUNT) // If user input greater than max, revert to max
    {
        count = MAX_COUNT;
    }
    else if (count < 1) // If user input negative or zero, revert to one.
    {
        count = 1;
    }
    if (range > MAX_RANGE) // If user input greater than max, revert to max
    {
        range = MAX_RANGE;
    }
    else if (range < 1) // If user input negative or zero, revert to one.
    {
        range = 1;
    }
    merge_sort(data, 0, count);
}
