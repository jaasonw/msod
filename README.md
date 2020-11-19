# msod

Mergesorts arbitrarily large files using disk space instead of ram. This is a true disk sort, meaning there is no instance in time where the entire data set ever gets
loaded into memory. 

Regardless of the size of the data, this program will consume an approximately constant amount of ram, configurable through chunk size (larger chunks = more ram = faster sort). 
At a 50,000 chunk size, this consumes less than 1MB of ram

![image](https://i.imgur.com/ENw9j1j.png)

That being said, because this is optimized for memory usage, it isn't particularly fast at sorting, but here are benchmarks anyways (chunk size: 50,000)

900000 numbers (~5MB): 30s (00:00:30)

9000000 numbers (~58MB):  286s (00:04:46)

90000000 numbers (~571MB):  16209s (04:30:09)

## How it works
1. Split input into chunks of 50,000 numbers
2. Load small chunks into ram and perform an in memory mergesort on these small chunks so we end up with sorted chunks (this is the only time sorting happens in memory)
3. Place all files into a sorting queue
4. Remove 2 files from the queue and perform an on disk merge operation and requeue the resulting file
5. Repeat until only 1 file remains in queue
6. Sorted
