# CS-325-Group-Assignments

New Idea:
//find middle index on each array
  int mid = (n/2)+1

//find kth element
if k == 1
  compare and find the smallest elements in each arrays
  //Ex: arr 1 = 9
  //    arr 2 = 5
  //    arr 3 = 7
  //    5 is the smallest
if k <= mid
  compare and find the smallest elements in front of each arrays
  recursively eliminate the smallest elements and k-- until k == 1
else
  Remove the half elements for each arrays for i= 0 to mid-1
  Set k = k-3*(mid-1)
  Recurse until k == 1
  
  
