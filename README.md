# C-YCSB
C++ port of YCSB

#### Building:
`mkdir build `  
`cd build `  
`cmake .. `  
`make `  

#### Running:
`./cycsb -threads [thread_count] -db [db_name] -wl [workload_class] `  

Example:  
`./cycsb -threads 1 -db pebblesdb -wl coreworkload `  

#### TODO:
- move all exceptions into exceptions.h
- benchmark overhead of serialization
- handle deleting existing db?
