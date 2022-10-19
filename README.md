# Algorithms

## Table of contents
- [Scenario](#scenario)
- [Task 1](#task-1)
- [Task 2](#task-2)

## Scenario
Your superiors at the company "Data Fuse Inc." are enthusiastic about your skills! Since the processing speed of the enormous amounts of data has to be optimized, you have been asked to develop a framework for measuring runtimes. With the help of this program you are to investigate the execution time of different sorting algorithms in dependence of a problem size n and evaluate them. Since exact time measurements are not trivial in C/C++, you do not need to implement this yourself. Instead you should use OpenMP to measure the times (advantage: consistent and easy to use). In the second part of the task a simple hash table is to be implemented.

## Task 1
### 1.1
Complete the sorting algorithm library consisting of the header file sorting.h and implement the following algorithms in the associated cpp file sorting.cpp and in its own namespace sorting:
* Heapsort
* Mergesort
* Natural Mergesort - The difference between the original mergesort and the natural mergesort is the first step of the recursive division into different sublists. **The original mergesort** subdivides the entire set of numbers until partial lists of size 1 are generated and then reassembles them recursively while 2 adjacent subsequences are mixed and thus sorted. The natural mergesort does not divide the entire set of numbers into sublists of size 1, but recognizes already presorted subsequences (so-called runs) and divides the sublists into these runs. As soon as this is done, the natural mergesort iteratively sets the sublists iteratively in a similar way as the normal mergesort. In Figs. 1 and 2 shows the difference between these two methods for the same set of numbers can be seen.<br  />
![ads_p4_01](https://user-images.githubusercontent.com/115429300/196440350-13186648-c390-4f37-8ca0-b058bca3c6fa.png)
* Quicksort - Implement the quicksort method with the partition algorithm.
* Hybrid Quicksort - Evaluate the cross over point from which n0 Insertion Sort sorts faster than quicksort. Then use Insertion Sort for all subsequences that have less than n0 elements and Quicksort for all subsequences that have equal or more elements than n0.
* Shellsort
  1. Shellsort with Hibbard sequence *(Hi = 2Hi−1 + 1)*
  2. Shellsort with distance sequence *(Hi = 3Hi−1 + 1)*
 
 ### 1.2
 Create or complete the main program. In the main program the sorting algorithms are to be measured with a corresponding problem size n and the results of the time measurements are to be written into text files.
 
 ### 1.3
 Measure the execution times as a function of problem size n for:
 * Heapsort, n = 1000 : 1000 : 1000000
 * Mergesort, n = 1000 : 1000 : 1000000
 * Quicksort, n = 1000 : 1000 : 1000000
 * Hybrid Quicksort, n = 1000 : 1000 : 1000000
 * Shellsort, sequence 1, n = 1000 : 1000 : 1000000
 * Shellsort, sequence 2, n = 1000 : 1000 : 1000000 
 
 Where n = 1000 : 1000 : 1000000 means, for example, that you should start at problem size n = 1000 and increase the problem size by 1000 in each step until you reach 1000000. After each step the execution time for this problem size is written into a text file. Do not measure the total execution time! Initialize your data structures before with random numbers (integers) before each measurement. <br  />
 Repeat the measurements 10 times per algorithm per n and calculate the average value from this and **save only the average runtime as the measurement result**.
 
 ### 1.4
 Graph their measurement results using MATLAB, Octave or GNUPLOT (examples: see 1.6).
 
 ### 1.5
 Plan enough time for the measurements.
 
 ### 1.6 Example of the runtime comparison of the sorting algorithms
 The plots should look like this, of course depending on the CPU used (in the figures the legends have been anonymized): <br  />
 ![ads_p4_02](https://user-images.githubusercontent.com/115429300/196489848-2b139a2f-6a2e-4fd3-bc64-7dee841db95a.png)
 
 
 ## Task 2
 Implement a hash table as an array (without re-hashing) by completing the template hashtable.h or hashtable.cpp. Implement the following features:
 
 ### 2.1 Konstruktor
 When creating a class instance a vector<int> dimensioned according to the passed parameter is to be allocated dynamically on the heap. Initially all values of the vector get the value -1. The size of the hash table is initialized with the passed value, the collision counter and the number of stored elements should be initialized with 0. The constructor also initializes the occupancy factor with 0.6 and the hash method with the method of quadratic probing.
 
 ### 2.2 Destruktor
 Ensure that all memory dynamically allocated at runtime is freed when the object is destroyed.
 
 ### 2.3 Calculation of the hash index
 Implement the method HashTable::hashValue(int item) which computes the hash index hi(x). Pass the key to the method. If a collision occurs, the collision counter should be incremented. For collision avoidance the following collision strategies are to be used, where M is the table size:
 * Linear probing : *hi(x) = (x + i)%M*
 * Square probing : *hi(x) = (x + i ∗ i)%M*
 * Double hashing : *hi(x) = (x + i ∗ (R − x%R))%M, whereas R < M is the next smaller prime number to M*. <br  />
 
 If the hash table space is free, the element x is stored in the hash table at the position hi(x). Primarily, the strategy for quadratic probing is to be used in the practical course. The other probing strategies are to be implemented and demonstrated in the lab.

### 2.4 Rehashing 
If the occupancy factor of the hash table has exceeded a threshold value (here: 0.6, i.e. the table is 60% full), an automatic rehashing shall be performed. For this purpose a new hash table shall be created with size **Mneu > 2 ∗Malt** and **Mneu** is a prime number. A maximum table size of 1000 shall be assumed. You can thus include all prime numbers up to 1000 in a vector in advance. All values from the old hash table have to be transferred with the new hash function (which depends on the table size). The memory of the old hash table is to be released again.

### 2.5 Insert into the hash table:
Implement the HashTable::insert(int item) function to insert items. Before inserting, check if the table is theoretically too full. If this is the case, the table should be rehashed before the insertion. Now calculate the hash index with the chosen hash method (this should be an attribute of the hash table). If the insertion is successful the counter for the number of elements is to be increased.

### 2.6 
Program a main program main, in which one can select the collision strategy as well as the occupancy factor. The main program allows you to select the collision strategy and the occupancy factor and then to insert elements into the hash table. Output the hash index for the inserted element.

### 2.7
After the unit tests have run successfully, create a hash table of size 1000 in your main program and automatically insert 200 random numbers in the range of values from 1000 to 1500 and output the number of collisions on the console.

That's it!
Thankyou for reading!
