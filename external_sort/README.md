One number takes 4 bytes on disk. One page can store 10000 numbers, which is 40000 bytes.

We will generate 100,000,000 numbers and write them to a large file. This file will be divided into $100000000/10000=10000$
pages. Assume our memory can only fit in 10 pages.

In the first round, each time we can load at most $10$ pages in memory, sort them, and write them out to one file. 
We need to repeat this process $1000$ times so we will get $1000$ files with sorted numbers on them.

Next, we need to merge these files with our $10$ buffer pages. We can merge numbers from multiple sources with 
a priority queue.

MergeFiles, MergeCurrentRound, Sort methods are not tested.
