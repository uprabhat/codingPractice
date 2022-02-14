#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int shuffle(int *list,int size) {
	int tmp;
	for(int i=0;i<size;i++) {
		int pos=rand()%size;
		tmp=*(list+pos);
		*(list+pos)=*(list+i);
		*(list+i)=tmp;
	}
	return(1);
}

//int linSearchArr(int num, int arr[]) {// doesn't work because arrarys are never passed completely, only the pointer is passed
// Linear Search //
int linSearchArr(int num, int arr[], int size) {
	int pos=-1;
  //printf("ARR:%zu : %zu : %zu \n",sizeof(arr),sizeof(*arr),sizeof(int));
	for(int i=0;i<size;i++) {
    //printf("linSearch: %d : %d \n",i,*(arr+i));
		if(arr[i]==num) {
			pos=i;
			break;
		}
	}
	return(pos);
}
/// PTR based ///
int* linSearch(int num, int* arr, int size) {
	int* pos=(int *)malloc(sizeof(int));
	int j=1;
	for(int i=0;i<size;i++) {
    //printf("linSearch: %d : %d \n",i,*(arr+i));
		if(*(arr+i)==num) {
			pos=(int *)realloc(pos,((j+1)*sizeof(int))) ;
			*(pos+j)=i;
			j++;
		}
	}
	*(pos)=(j-1);
	return(pos);
}

// Binary Seearch : requires a sorted array //
int binarySearch(int *list,int num,int low, int high) {
	int mid=low+(high-low)/2;
	if(*(list+mid)==num) {
		return(mid);
	} else if(high==low) {
		return(-1);
	} else if(*(list+mid)<num) {
		return(binarySearch(list,num,(mid+1),high));
	} else {
		return(binarySearch(list,num,0,mid));
	}
}


//Selection Sort // Select the smallest and move to the start
/*
The selection sort algorithm sorts an array by repeatedly finding the minimum element (considering ascending order) from unsorted part and putting it at the beginning. The algorithm maintains two subarrays in a given array.
1) The subarray which is already sorted. 
2) Remaining subarray which is unsorted.
In every iteration of selection sort, the minimum element (considering ascending order) from the unsorted subarray is picked and moved to the sorted subarray. 
*/
int selectionSort(int* list, int size) {
	int smallest,tmp;
	for(int sortedIdx=0;sortedIdx<(size-1);sortedIdx++) {
		smallest=sortedIdx;
		for(int currPtr=sortedIdx+1;currPtr<size;currPtr++) {
			if (*(list+smallest)>*(list+currPtr)) {
				smallest=currPtr;
			}
		}
		if(smallest!=sortedIdx) {
			tmp=*(list+smallest);
			*(list+smallest)=*(list+sortedIdx);
			*(list+sortedIdx)=tmp;
		}
	}
	return(1);
}


//Bubble Sort//
/*
Bubble Sort is the simplest sorting algorithm that works by repeatedly swapping the adjacent elements if they are in wrong order.
*/
int bubbleSort(int* list, int size) {
	for(int sortedPos=0;sortedPos<(size-1);sortedPos++) {
		for(int fwdChk=0;fwdChk<(size-sortedPos-1);fwdChk++) {
			if(*(list+fwdChk)>*(list+fwdChk+1)) {
				int tmp=*(list+fwdChk);
				*(list+fwdChk)=*(list+fwdChk+1);
				*(list+fwdChk+1)=tmp;
			}
		}
	}
	return(1);
}

//Insertion Sort// 
/*
Insertion sort is a simple sorting algorithm that works similar to the way you sort playing cards in your hands. The array is virtually split into a sorted and an unsorted part. Values from the unsorted part are picked and placed at the correct position in the sorted part.
Algorithm 
To sort an array of size n in ascending order: 
1: Iterate from arr[1] to arr[n] over the array. 
2: Compare the current element (key) to its predecessor. 
3: If the key element is smaller than its predecessor, compare it to the elements before. Move the greater elements one position up to make space for the swapped element.
*/
int insertionSort(int* list, int size) {
	for(int sortedPos=0;sortedPos<(size-1);sortedPos++) {
		int nxtNum=*(list+sortedPos+1);
		for(int backChk=sortedPos;backChk>=0;backChk--) {
			if(nxtNum<*(list+backChk)) {
				*(list+backChk+1)=*(list+backChk);
			} else {
				if(backChk!=sortedPos) {
					*(list+backChk+1)=nxtNum;
				}
				break;
			}
		}
	}
	return(1);
}
//More optimized code: https://www.geeksforgeeks.org/insertion-sort/


//Merge Sort// nLog(n)
/*
Like QuickSort, Merge Sort is a Divide and Conquer algorithm. It divides the input array into two halves, calls itself for the two halves, and then merges the two sorted halves. The merge() function is used for merging two halves. The merge(arr, l, m, r) is a key process that assumes that arr[l..m] and arr[m+1..r] are sorted and merges the two sorted sub-arrays into one.
*/
void merge(int *list, int l, int m, int r);

int mergeSort(int* list, int l, int r) {
	if(l==r) { return(1);}
	int m=l+(r-l)/2;
	mergeSort(list,l,m);
	mergeSort(list,m+1,r);
	merge(list,l,m,r);
	return(1);
}

void merge(int *list,int l,int m,int r) {
	int* cpList1=(int*)malloc((m-l+1)*(sizeof(int)));
	memcpy(cpList1,list+l,((m-l+1)*sizeof(int)));
	int* cpList2=(int*)malloc((r-m)*(sizeof(int)));
	memcpy(cpList2,list+m+1,((r-m)*sizeof(int)));
	int ptr1=0; //0 to m-l
	int ptr2=0; //0 to r-m-1
	int mergePtr=l; // l to r
	while((ptr1<=(m-l)) && (ptr2<=(r-m-1))) {
		//printf("DBG[l=%d,m=%d,r=%d]: ptr1=%d, ptr2=%d, mergePtr=%d:\n",l,m,r,ptr1,ptr2,mergePtr);
		if(*(cpList1+ptr1)<*(cpList2+ptr2)) {
			*(list+mergePtr)=*(cpList1+ptr1);
			ptr1++;
		} else {
			*(list+mergePtr)=*(cpList2+ptr2);
			ptr2++;
		}
		mergePtr++;
	}
	while(ptr1<=(m-l)) {
		*(list+mergePtr)=*(cpList1+ptr1);
		ptr1++; mergePtr++;
	}
	while(ptr2<=(r-m-1)) {
		*(list+mergePtr)=*(cpList2+ptr2);
		ptr2++; mergePtr++;
	}
	free(cpList1);
	free(cpList2);
}
/*
Quicksort: nLog(n)
Like Merge Sort, QuickSort is a Divide and Conquer algorithm. It picks an element as pivot and partitions the given array around the picked pivot. There are many different versions of quickSort that pick pivot in different ways. 

Always pick first element as pivot.
Always pick last element as pivot (implemented below)
Pick a random element as pivot.
Pick median as pivot.
The key process in quickSort is partition(). Target of partitions is, given an array and an element x of array as pivot, put x at its correct position in sorted array and put all smaller elements (smaller than x) before x, and put all greater elements (greater than x) after x. All this should be done in linear time.
*/

int partition(int *list, int l, int r); //return index of pivotted element

int quickSort(int *list,  int l, int r) {
	if(l<r) {
		int pivot=partition(list,l,r);
		quickSort(list,l,pivot-1);
		quickSort(list,pivot+1,r);
	}
	return(1);
}


int partition(int *list, int l, int r) {
	int p=r ; //index of pivot
	int i=l-1 ; //index of last element which is lesser than pivot : also used at the end to insert pivot value
	int j=l ; //index of element being checked
	int tmp;
	/*printf("partition:  I/P : l=%d r=%d : [",l,r);
	for (int k=l;k<=r;k++) { printf("%d,",*(list+k));}
	printf("]\n"); */
	while(j<p) {
		if(*(list+j) < *(list+p)) {
			i++;
			// printf(">>>%d@%d interchanged with %d@%d\n",*(list+j),j,*(list+i),i);
			tmp=*(list+j);
			*(list+j)=*(list+i);
			*(list+i)=tmp;
		} else {
			//printf(">>>%d@%d not  changed with %d@%d\n",*(list+j),j,*(list+i),i);
		}
		j++;
	}
	i++;
	//printf(">>>%d@%d interchanged with %d@%d\n",*(list+i),i,*(list+p),p);
	tmp=*(list+i);
	*(list+i)=*(list+p);
	*(list+p)=tmp;
	/*printf("partition:  O/P : l=%d r=%d : [",l,r);
	for (int k=l;k<=r;k++) { printf("%d,",*(list+k));}
	printf("]\n");*/
	return(i);
}

/*
[9,8,7,9,1]
>QS:[9,8,7,9,1] | 0 | 4
>>partition:[9,8,7,9,1] | 0 | 4
>>>p=4,i=-1,j=0 : nothing
>>>p=4,i=-1,j=1 : nothing
>>>p=4,i=-1,j=2 : nothing
>>>p=4,i=-1,j=3 : nothing
>>>swap i=0, with , p=4 : [1,8,7,9,9]
>>pivot=0
>QS:[1,8,7,9,9] | 0 | -1
>QS:[1,8,7,9,9] | 1 | 4
>>partition:[1,8,7,9,9] | 1 | 4
>>>p=4,i=0,j=1 : swap(1,1): Nothing: [1,8,7,9,9]
>>>p=4,i=1,j=2 : swap(2,2): Nothing
>>>p=4,i=2,j=3 : swap(3,3): Nothing
>>>swap i=4, with , p=4 : [1,8,7,9,9]
>>>pivot=4
>QS:[1,8,7,9,9] | 4 | 4
>>partition:[1,8,7,9,9] | 1 | 3
>>>p=4,i=0,j=1 : swap(1,1): Nothing: [1,8,7,9,9]
>>>p=4,i=1,j=2 : swap(2,2): Nothing
>>>swap i=3, with , p=3 : [1,8,7,9,9]
>>>pivot=3
>QS:[1,8,7,9,9] | 1 | 2
>>partition:[1,8,7,9,9] | 1 | 2
>>>p=2,i=0,j=1 : nothing
>>>p=4,i=1,j=2 : swap(2,2): Nothing
>>>swap i=3, with , p=3 : [1,8,7,9,9]
>>>pivot=3

*/

//////////////////////////////////////////////////////////////////////////////////////////
int main(int argc, char** argv) {
	//8 4 6 8 7 3 2 5 7 9 4 2 5 7 8
	int* list=malloc((argc-1)*sizeof(int));
	for(int i=1;i<argc;i++) {
		*(list+i-1)=atoi(*(argv+i));
	}
	int arr[argc-1];
  //printf("SIZE=%zu\n",sizeof(arr));
	for (int i=1;i<argc;i++) {
		arr[i-1]=atoi(*(argv+i));
		//printf("Added number %d at position %d\n",arr[i-1],i-1);
	}
	//print to check or just check/assert//
	printf("Enter number to search:");
	int num=8;
	//scanf("%d",&num);
	int pos=linSearchArr(num, arr,sizeof(arr)/sizeof(int));
  printf("Linear Search Arr: Number found at position %d\n",pos);

	int* poses=linSearch(num, arr,sizeof(arr)/sizeof(int));
	printf("MultiPos::: ");
  for(int i=0;i<*(poses);i++){
    printf("%d,",poses[i+1]);
  }
	printf("\n");
	free(poses);

	//////////// Sorting ////////////
	if(selectionSort(list,argc-1)) {
		printf("Selection Sort list is:");
		for(int i=0;i<(argc-1);i++) {printf("%d,",*(list+i));}
		printf("\n");
	}

	poses=linSearch(num, list,sizeof(arr)/sizeof(int));
	printf("MultiPos::: ");
  for(int i=0;i<*(poses);i++){
    printf("%d,",poses[i+1]);
  }
	printf("\n");
	free(poses);
	printf("Binary Search: Number found at position %d\n",binarySearch(list,num,0,argc-1));

	if(shuffle(list,argc-1)) {
		printf("Shuffled list is:");
		for(int i=0;i<(argc-1);i++) {printf("%d,",*(list+i));}
		printf("\n");
	}
	if(insertionSort(list,argc-1)) {
		printf("Insertion Sort list is:");
		for(int i=0;i<(argc-1);i++) {printf("%d,",*(list+i));}
		printf("\n");
	}

	if(shuffle(list,argc-1)) {
		printf("Shuffled list is:");
		for(int i=0;i<(argc-1);i++) {printf("%d,",*(list+i));}
		printf("\n");
	}
	if(bubbleSort(list,argc-1)) {
		printf("Bubble Sort list is:");
		for(int i=0;i<(argc-1);i++) {printf("%d,",*(list+i));}
		printf("\n");
	}


	if(shuffle(list,argc-1)) {
		printf("Shuffled list is:");
		for(int i=0;i<(argc-1);i++) {printf("%d,",*(list+i));}
		printf("\n");
	}
	if(mergeSort(list,0,argc-2)) {
		printf("Merge Sort list is:");
		for(int i=0;i<(argc-1);i++) {printf("%d,",*(list+i));}
		printf("\n");
	}

	if(shuffle(list,argc-1)) {
		printf("Shuffled list is:");
		for(int i=0;i<(argc-1);i++) {printf("%d,",*(list+i));}
		printf("\n");
	}
	if(quickSort(list,0,argc-2)) {
		printf("Quick Sort list is:");
		for(int i=0;i<(argc-1);i++) {printf("%d,",*(list+i));}
		printf("\n");
	}



	////////////////////////////////
	free(list);
	return(0);
}
