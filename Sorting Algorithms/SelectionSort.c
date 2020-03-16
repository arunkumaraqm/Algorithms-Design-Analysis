// Selection sort with display every iteration
#include <stdio.h>

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

#define swap(one, two) do{\
	int temp = one;\
	one = two;\
	two = temp;}while(0)

void selection_sort(int size, int arr[])
{
	int i, j, smallest, pos;
	for (i = 0; i < size; ++i)
	{
		smallest = arr[i];
		pos = i;
		
		for (j = i + 1; j < size; ++j)
		{
			if (arr[j] < smallest)
			{
				smallest = arr[j];
				pos = j;
			}
		}
		
		swap(arr[i], arr[pos]);
		printf("After Iteration %d, ", i + 1); print_arr(size, arr);//
	}
}

void main()
{
	int size;
	scanf("%d", &size);
	int arr[size];
	read_arr(size, arr);
	selection_sort(size, arr);
}


