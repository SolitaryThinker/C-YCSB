# C-YCSB
C++ port of Yahoo! Cloud System Benchmark (YCSB)  


The original Java version of YCSB can be found here:  
https://github.com/brianfrankcooper/YCSB

### Differences with the Java version:
- C-YCSB is in C++!
- Runs faster (probably)
- Less overhead
- C-YCSB doesn't work! (yet)

### Building:
`mkdir build `  
`cd build `  
`cmake .. `  
`make `  

### Running:
`./cycsb -threads [thread_count] -db [db_name] -wl [workload_class] `  

Example:  
`./cycsb -threads 1 -db pebblesdb -wl coreworkload `  

### TODO:
- move all exceptions into exceptions.h?
- benchmark overhead of serialization for Java YCSB
- handle deleting existing db?
