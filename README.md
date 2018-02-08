# CPSC457_Assign4
An assignment completed for the Spring 2017 offering of CPSC457 at the University of Calgary.  

Simulates three page replacement algorithms, optimal, least recently used (LRU), and clock.

The program requires two command line inputs
1) The number of frames to use, between 1 and 20
2) The name of the configuration file 

Sample Compilation and Execution
- g++ pagesin.cPP
- ./a.out 4 < test1.txt

This program requires a configuration file, which contains 0 to 5000 integers between 0 and 100.

A sample configuration file has been included, called test1.txt.
