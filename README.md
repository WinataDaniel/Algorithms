# Algorithms
Scenario - Your superiors at the company "Data Fuse Inc." are enthusiastic about your skills! Since the processing speed of the enormous amounts of data has to be optimized, you have been asked to develop a framework for measuring runtimes. With the help of this program you are to investigate the execution time of different sorting algorithms in dependence of a problem size n and evaluate them. Since exact time measurements are not trivial in C/C++, you do not need to implement this yourself. Instead you should use OpenMP to measure the times (advantage: consistent and easy to use). In the second part of the task a simple hash table is to be implemented.

## Task 1
### 1.1
Complete the sorting algorithm library consisting of the header file sorting.h and implement the following algorithms in the associated cpp file sorting.cpp and in its own namespace sorting:
* Heapsort
* Mergesort
* Natural Mergesort - The difference between the original mergesort and the natural mergesort is the first step of the recursive division into different sublists. **The original mergesort** subdivides the entire set of numbers until partial lists of size 1 are generated and then reassembles them recursively while 2 adjacent subsequences are mixed and thus sorted. The natural mergesort does not divide the entire set of numbers into sublists of size 1, but recognizes already presorted subsequences (so-called runs) and divides the sublists into these runs. As soon as this is done, the natural mergesort iteratively sets the sublists iteratively in a similar way as the normal mergesort. In Figs. 1 and 2 shows the difference between these two methods for the same set of numbers can be seen.
![ads_p4_01](https://user-images.githubusercontent.com/115429300/196440350-13186648-c390-4f37-8ca0-b058bca3c6fa.png)
* Quicksort - Implement the quicksort method with the partition algorithm.
* Hybrid Quicksort - Evaluate the cross over point from which n0 Insertion Sort sorts faster than quicksort. Then use Insertion Sort for all subsequences that have less than n0 elements and Quicksort for all subsequences that have equal or more elements than n0.
* Shellsort
  1. Shellsort with Hibbard sequence *(Hi = 2Hi−1 + 1)*
  2. Shellsort with distance sequence *(Hi = 3Hi−1 + 1)*
 
 ### 1.2
 Create or complete the main program. In the main program the sorting algorithms are to be measured with a corresponding problem size n and the results of the time measurements are to be written into text files.
 
 ### 1.3
 
