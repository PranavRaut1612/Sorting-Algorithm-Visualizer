#include <iostream>
#include <chrono>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <thread>  // For sleep_for
#include <unistd.h> // For usleep
#include <windows.h>  // For Sleep()

using namespace std;
using namespace std::chrono;

void printArrayAsBars(int arr[], int n) {
    cout<<"Orignal Array : \n";
    for (int i = 0; i < n; i++) {
        cout << arr[i] << "\t";  // Print the element's value

        // Visual representation with blocks (grayscale)
        for (int j = 0; j < arr[i]; j++) {
            cout << "█";  // Represent each element as a block of '█'
        }
        cout << endl;
    }
    cout << endl;
}

// Function to print the array with visual cues
void printArrayForBubbleSort(int arr[], int n, int highlightIndex1 = -1, int highlightIndex2 = -1, bool swapped = false, int sortedBoundary = -1) {
    for (int i = 0; i < n; i++) {
        if (i == highlightIndex1 || i == highlightIndex2) {
            if (swapped) {
                cout << "\033[32m" << arr[i] << "\033[0m\t";  // Green for swapped
            } else {
                cout << "\033[31m" << arr[i] << "\033[0m\t";  // Red for comparison
            }
        } else if (i > sortedBoundary) {
            cout << "\033[34m" << arr[i] << "\033[0m\t";  // Blue for sorted
        } else {
            cout << arr[i] << "\t";  // Normal for unsorted elements
        }

        // Visual representation with blocks
        for (int j = 0; j < arr[i]; j++) {
            if (i == highlightIndex1 || i == highlightIndex2) {
                if (swapped) {
                    cout << "\033[32m" << "\033[1m" << "█" << "\033[0m";
                } else {
                    cout << "\033[31m" << "\033[1m" << "█" << "\033[0m";
                }
            } else if (i > sortedBoundary) {
                cout << "\033[34m" << "\033[1m" << "█" << "\033[0m";
            } else {
                cout << "\033[37m" << "█" << "\033[0m";
            }
        }
        cout << endl;
    }
    cout << endl;
}

// New function to print the array specifically for selection sort
void printArrayForSelectionSort(int arr[], int n, int highlightIndex1 = -1, int highlightIndex2 = -1, bool swapped = false, int sortedBoundary = -1) {
    for (int i = 0; i < n; i++) {
        if (i == highlightIndex1 || i == highlightIndex2) {
            if (swapped) {
                cout << "\033[32m" << arr[i] << "\033[0m\t";  // Green for swapped
            } else {
                cout << "\033[31m" << arr[i] << "\033[0m\t";  // Red for comparison
            }
        } else if (i <= sortedBoundary) {
            cout << "\033[34m" << arr[i] << "\033[0m\t";  // Blue for sorted elements
        } else {
            cout << arr[i] << "\t";  // Normal for unsorted elements
        }

        // Visual representation with blocks
        for (int j = 0; j < arr[i]; j++) {
            if (i == highlightIndex1 || i == highlightIndex2) {
                if (swapped) {
                    cout << "\033[32m" << "\033[1m" << "█" << "\033[0m";
                } else {
                    cout << "\033[31m" << "\033[1m" << "█" << "\033[0m";
                }
            } else if (i <= sortedBoundary) {
                cout << "\033[34m" << "\033[1m" << "█" << "\033[0m";
            } else {
                cout << "\033[37m" << "█" << "\033[0m";
            }
        }
        cout << endl;
    }
    cout << endl;
}

// New function to print the array specifically for insertion sort
void printArrayForInsertionSort(int arr[], int n, int highlightIndex1 = -1, int sortedBoundary = -1, bool shifted = false) {
    for (int i = 0; i < n; i++) {
        if (i == highlightIndex1) {
            if (shifted) {
                cout << "\033[32m" << arr[i] << "\033[0m\t";  // Green for shifted element
            } else {
                cout << "\033[31m" << arr[i] << "\033[0m\t";  // Red for comparison
            }
        } else if (i <= sortedBoundary) {
            cout << "\033[34m" << arr[i] << "\033[0m\t";  // Blue for sorted elements
        } else {
            cout << arr[i] << "\t";  // Normal for unsorted elements
        }

        // Visual representation with blocks
        for (int j = 0; j < arr[i]; j++) {
            if (i == highlightIndex1) {
                if (shifted) {
                    cout << "\033[32m" << "\033[1m" << "█" << "\033[0m";
                } else {
                    cout << "\033[31m" << "\033[1m" << "█" << "\033[0m";
                }
            } else if (i <= sortedBoundary) {
                cout << "\033[34m" << "\033[1m" << "█" << "\033[0m";
            } else {
                cout << "\033[37m" << "█" << "\033[0m";
            }
        }
        cout << endl;
    }
    cout << endl;
}

// Function to control the delay for visualization speed
void setVisualizationSpeed(int speed) {
    int delay_ms = (11 - speed) * 100;  // Speed 1 (slowest) -> 1000ms delay, Speed 10 (fastest) -> 100ms delay
    Sleep(delay_ms);  // Sleep for delay_ms milliseconds
}


// Bubble Sort with visualization
void bubbleSort(int arr[], int n, int speed, int &comparisonCount, int &swapCount, bool ascending = true) {
    for (int i = 0; i < n - 1; i++) {
        bool swapped = false;
        for (int j = 0; j < n - i - 1; j++) {
            comparisonCount++;
            printArrayForBubbleSort(arr, n, j, j + 1, false, n - i - 1);
            if ((ascending && arr[j] > arr[j + 1]) || (!ascending && arr[j] < arr[j + 1])) {
                swap(arr[j], arr[j + 1]);
                swapped = true;
                swapCount++;
                printArrayForBubbleSort(arr, n, j, j + 1, true, n - i - 1);
            }
            setVisualizationSpeed(speed);  // Visualization speed control
        }
        if (!swapped) break;
    }
}

// Selection Sort with visualization and correct sorted boundary highlighting
void selectionSort(int arr[], int n,int speed, int &comparisonCount, int &swapCount, bool ascending = true) {
    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < n; j++) {
            comparisonCount++;
            printArrayForSelectionSort(arr, n, minIndex, j, false, i - 1);  // Sorted boundary is i - 1
            if ((ascending && arr[j] < arr[minIndex]) || (!ascending && arr[j] > arr[minIndex])) {
                minIndex = j;
            }
        }
        if (minIndex != i) {
            swap(arr[i], arr[minIndex]);
            swapCount++;
            printArrayForSelectionSort(arr, n, i, minIndex, true, i);  // After swap, i is part of sorted array
        }
        setVisualizationSpeed(speed);  // Adjust as per your speed input
    }
}

// Insertion Sort with visualization
void insertionSort(int arr[], int n, int speed, int &comparisonCount, int &swapCount, bool ascending = true) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];  // The element to be placed in the sorted section
        int j = i - 1;     // Pointer for the sorted section
        bool shifted = false;

        // Move elements of arr[0..i-1] that are greater than key, to one position ahead
        while (j >= 0 && ((ascending && arr[j] > key) || (!ascending && arr[j] < key))) {
            comparisonCount++;
            arr[j + 1] = arr[j];  // Shift the larger element one position to the right
            shifted = true;
            printArrayForInsertionSort(arr, n, j + 1, i - 1, true);  // Highlight shifted element
            j--;  // Move to the next element in the sorted section
            setVisualizationSpeed(speed);  // Adjust speed for visualization
        }

        // Insert the key at its correct position
        arr[j + 1] = key;
        if (!shifted) {
            printArrayForInsertionSort(arr, n, i, i, false);  // If no shift occurred, highlight the key
        } else {
            printArrayForInsertionSort(arr, n, j + 1, i, false);  // After insertion, highlight key's final position
        }
        setVisualizationSpeed(speed);  // Adjust speed for visualization
    }
}

int main() {
    int n, choice, speed, sortOrder;
    char tryAnother;
    do {
        cout << "Enter the number of elements in the array (up to 100): ";
        cin >> n;
        if (n > 100) {
            cout << "Array size too large. Please enter a size up to 100.\n";
        }
    } while (n > 100);

    int arr[n], originalArr[n];
    cout << "\nChoose the type of input:\n";
    cout << "1. Manual input\n";
    cout << "2. Random input\n";
    cout << "Enter your choice: ";
    cin >> choice;

    if (choice == 1) {
        cout << "Enter the elements of the array:\n";
        for (int i = 0; i < n; i++) {
            cin >> arr[i];
            originalArr[i] = arr[i];  // Store original array for re-use
        }
    } else if (choice == 2) {
        srand(time(0));
        for (int i = 0; i < n; i++) {
            arr[i] = rand() % 100 + 1;
            originalArr[i] = arr[i];  // Store original array for re-use
        }
        cout << "Random array generated.\n";
    } else {
        cout << "Invalid choice! Exiting.\n";
        return 1;
    }

    do {
        // Restore the original array before each new sorting
        for (int i = 0; i < n; i++) {
            arr[i] = originalArr[i];
        }

        cout << "\nChoose the sorting algorithm:\n";
        cout << "1. Bubble Sort\n";
        cout << "2. Selection Sort\n";
        cout << "3. Insertion Sort\n";
        cout << "Enter your choice: ";
        cin >> choice;

        cout << "\nChoose sorting order:\n";
        cout << "1. Ascending\n";
        cout << "2. Descending\n";
        cout << "Enter your choice: ";
        cin >> sortOrder;
        bool ascending = (sortOrder == 1);

        cout << "\nChoose visualization speed (1-10, where 10 is fastest): ";
        cin >> speed;

        cout << "\nColor Legend:\n";
        cout << "\033[31mRed\033[0m - Elements being compared\n";
        cout << "\033[32mGreen\033[0m - Elements swapped\n";
        cout << "\033[34mBlue\033[0m - Sorted part of the array\n" << endl;

        printArrayAsBars(arr,n);
        int comparisonCount = 0;
        int swapCount = 0;

        auto start = high_resolution_clock::now();

        switch (choice) {
            case 1:
                bubbleSort(arr, n, speed, comparisonCount, swapCount, ascending);
                break;
            case 2:
                selectionSort(arr, n, speed, comparisonCount, swapCount, ascending);
                break;
            case 3:
                insertionSort(arr, n, speed, comparisonCount, swapCount, ascending);
                break;
            default:
                cout << "Invalid choice! Exiting.\n";
                return 1;
        }

        auto end = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(end - start).count() / 1000000.0;

        cout << "\nSorted Array:\n";
        printArrayForBubbleSort(arr, n);

        // Display performance metrics (comparisons, swaps, time)
        cout << "\n---------------------------------------------------\n";
        cout << "| Comparisons  | Swaps        | Time taken (s)    |\n";
        cout << "---------------------------------------------------\n";
        cout << "|" << setw(13) << comparisonCount+swapCount << " | " << setw(13) << swapCount << " | " << setw(17) << fixed << setprecision(6) << duration << " |\n";
        cout << "---------------------------------------------------\n";

        // Ask user if they want to try another sorting algorithm on the same array
        cout << "\nDo you want to try another sorting algorithm on the same array? (y/n): ";
        cin >> tryAnother;

    } while (tryAnother == 'y' || tryAnother == 'Y');

    cout << "Exiting the program.\n";
    return 0;
}
