# CS-325-Group-Assignments

Idea:
1. Read the array from binary file.
2. Put them into m arrays consisting of n elements
3. Use Merge function in MergeSort to Merge all m arrays
4. Find K with for loop <-can probably just do array[k] since the merged array would be in order, but other than that, I think the algorithm looks fine.

Is it satisfy running time output? <-I think so? Merging an array is probably a log n, and since there are m arrays, you get mlog n.
