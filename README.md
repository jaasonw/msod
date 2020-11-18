# msod

Mergesorts arbitrarily large files using disk space instead of ram. This is a true disk sort, meaning there is no instance in time where the entire data set ever gets
loaded into memory. 

Regardless of the size of the data this program will only consume around 500kb of ram

![image](https://i.imgur.com/jubxu3i.png)

That being said, because this is optimized for memory usage, it isn't particularly fast at sorting, but here are benchmarks anyways (chunk size: 500)

90000 numbers (~0.5MB): 25s (0:25)

900000 numbers (~5MB): 270s (4:30)

9000000 numbers (~58MB): 2726s (45:25)

## How it works
1. Split input into chunks of 500 numbers
2. Load small chunks into ram and perform an in memory mergesort on these small chunks so we end up with sorted chunks (this is the only time sorting happens in memory)
3. Place all files into a sorting queue
4. Remove 2 files from the queue and perform an on disk merge operation and requeue the resulting file
5. Repeat until only 1 file remains in queue
6. Sorted
