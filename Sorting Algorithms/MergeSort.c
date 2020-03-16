#include <stdio.h>
#include <time.h>
	
void read_arr(int size, int arr[])
{
	for (int i = 0; i < size; ++i)
		scanf("%d", arr + i);
}

void print_arr(int size, int arr[])
{
	printf("[ ");
	for (int i = 0; i < size; ++i)
		printf("%d ", *(arr + i));
	printf("]\n");
}

int merge(int* arr, int left, int right) 
{

//	int mid = right - (right - left) / 2;
	int mid = (left + right)/2;
	int size_one = mid - left + 1, size_two = right - mid;
	int one[size_one], two[size_two];
	
	// Copying
	for (int i = 0; i < size_one; ++i) one[i] = arr[left + i];
	for (int j = 0; j < size_two; ++j) two[j] = arr[mid + 1 + j];	
	
	int cur_one = 0, cur_two = 0, cur_arr = left;
	
	// Merging
	while (cur_one != size_one && cur_two != size_two)
	{
		if (one[cur_one] < two[cur_two]) 
		{
			arr[cur_arr++] = one[cur_one++];
		}
		else arr[cur_arr++] = two[cur_two++];
	}
	
	while (cur_one != size_one) arr[cur_arr++] = one[cur_one++];
	while (cur_two != size_two) arr[cur_arr++] = two[cur_two++];
}

void merge_sort(int* arr, int left, int right) 
{
	if (left < right)
	{
//		int mid = right - (right - left) / 2;
		int mid = (left + right)/2;
		merge_sort(arr, left, mid);
		merge_sort(arr, mid + 1, right);
		merge(arr, left, right);
	}
}	

#define MERGESORT(size, arr) merge_sort(arr, 0, size - 1)

#define duration(start, end) \
	((double)(end - start)/CLOCKS_PER_SEC)

void main()
{
	int size;
	scanf("%d", &size);
	int arr[size];
	read_arr(size, arr);

	clock_t start = clock();	
	
	MERGESORT(size, arr);

	clock_t end = clock();
	double dur = duration(start, end);
	
	print_arr(size, arr);
	printf("Start, End, Duration: %ld, %ld, %lf\n", start, end, dur);
}

/*
TESTS

#1 
In: 2
20 10
Out: 10 20

#2
In: 5
10 20 30 40 50
Out: 10 20 20 50 50

#3
In: 5
50 40 30 20 10
Out: 10 20 20 50 50

#4
In: 8
20 60 60 10 50 80 40 70
Out: 10 20 40 50 60 60 70 80

#5
In: 200
352 13 15 748 324 841 573 540 199 261 642 833 795 310 237 731 220 781 448 596 637 791 16 20 784 580 418 912 451 919 895 190 275 471 936 971 725 848 901 474 953 995 922 134 503 473 100 133 28 396 104 214 437 162 209 615 762 963 110 399 868 955 221 726 127 683 294 943 990 494 413 20 926 174 863 441 108 955 203 569 871 137 93 93 53 833 74 626 54 68 892 606 450 803 197 6 158 637 211 468 829 901 670 261 326 44 399 647 593 52 526 527 356 834 831 114 123 919 710 641 633 368 447 427 593 513 609 840 749 206 234 533 701 776 71 662 961 950 75 14 409 971 827 402 789 965 308 250 855 471 670 913 373 799 737 676 474 284 560 884 161 206 312 165 117 539 803 906 442 647 130 524 999 806 283 689 265 607 102 729 378 766 473 598 360 844 699 667 842 317 877 199 616 181 102 193 12 993 602 438
Out: [ 6 12 13 14 15 16 20 20 28 44 52 53 54 68 71 74 75 93 93 100 102 102 104 108 110 114 117 123 127 130 133 134 137 158 161 162 165 174 181 190 193 197 199 199 203 206 206 209 211 214 220 221 234 237 250 261 261 265 275 283 284 294 308 310 312 317 324 326 352 356 360 368 373 378 396 399 399 402 409 413 418 427 437 438 441 442 447 448 450 451 468 471 471 473 473 474 474 494 503 513 524 526 527 533 539 540 560 569 573 580 593 593 596 598 602 606 607 609 615 616 626 633 637 637 641 642 647 647 662 667 670 670 676 683 689 699 701 710 725 726 729 731 737 748 749 762 766 776 781 784 789 791 795 799 803 803 806 827 829 831 833 833 834 840 841 842 844 848 855 863 868 871 877 884 892 895 901 901 906 912 913 919 919 922 926 936 943 950 953 955 955 961 963 965 971 971 990 993 995 999 ]



*/

