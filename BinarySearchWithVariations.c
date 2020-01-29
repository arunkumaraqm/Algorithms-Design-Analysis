// Iterative, Recursive, and Lazy Iterative Binary Search
// Timed using time.h

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

int iter_binary_search(int *arr, int beg, int end, int ele) 
{
	int mid;
	while (beg <= end)
	{
		//mid = (beg + end)/2;
		mid = beg + (end - beg)/2; // Preventing overflow - floor of average
		if (arr[mid] < ele)
		{
			beg = mid + 1;
		}
		else if (arr[mid] > ele)
		{
			end = mid - 1;
		}
		else
		{
			return mid;
		}
	}
	return -1;
}

int rec_binary_search(int *arr, int beg, int end, int ele) 
{
	if (beg <= end)
	{
		int mid = beg + (end - beg)/2; // Preventing overflow - floor of average
		if (arr[mid] < ele)
		{
			return rec_binary_search(arr, mid + 1, end, ele);
		}
		else if (arr[mid] > ele)
		{
			return rec_binary_search(arr, beg, mid - 1, ele);
		}
		else
		{
			return mid;
		}
	}
	return -1;
}

int lazy_binary_search(int *arr, int beg, int end, int ele) 
{
	int mid;
	while (beg != end)
	{
		//mid = (beg + end)/2;
		mid = beg + (end - beg + 1)/2; // Preventing overflow - ceil of average 
		if (arr[mid] <= ele)
		{
			beg = mid;
		}
		else 
		{
			end = mid - 1;
		}
	}
	if (arr[beg] == ele) return beg;
	
	return -1;
}


double duration(clock_t start, clock_t end)
{
	return (double)(end - start)/CLOCKS_PER_SEC;
}

void print_result(char name[50], long double start, long double end, double duration, int res)
{
	printf("%s : ", name);
	if (res == -1)
	{
		printf("Not found.\n");
	}
	else
	{
		printf("An occurence is found at %d.\n", res);
	}
	printf("(Start, End, Duration) = (%Lf, %Lf, %lf)\n", start, end, duration);
}

void main()
{
	int size;
	scanf("%d", &size);
	int arr[size];
	read_arr(size, arr);
	int search_key;
	scanf("%d", &search_key);

	clock_t start = clock();	
	int res1 = iter_binary_search(arr, 0, size - 1, search_key);
	clock_t end = clock();	
	double dur1 = duration(start, end);
	print_result("Iterative", start, end, dur1, res1);
	
	start = clock();	
	int res2 = rec_binary_search(arr, 0, size - 1, search_key);
	end = clock();	
	double dur2 = duration(start, end);
	print_result("Recursive", start, end, dur2, res2);
	
	start = clock();	
	int res3 = lazy_binary_search(arr, 0, size - 1, search_key);
	end = clock();	
	double dur3 = duration(start, end);
	print_result("Lazy Iterative", start, end, dur3, res3);		
}

/* Test
240
0 5 10 15 20 25 30 35 40 45 50 55 60 65 70 75 80 85 90 95 100 105 110 115 120 125 130 135 140 145 150 155 160 165 170 175 180 185 190 195 200 205 210 215 220 225 230 235 240 245 250 255 260 265 270 275 280 285 290 295 300 305 310 315 320 325 330 335 340 345 350 355 360 365 370 375 380 385 390 395 400 405 410 415 420 425 430 435 440 445 450 455 460 465 470 475 480 485 490 495 500 505 510 515 520 525 530 535 540 545 550 555 560 565 570 575 580 585 590 595 600 605 610 615 620 625 630 635 640 645 650 655 660 665 670 675 680 685 690 695 700 705 710 715 720 725 730 735 740 745 750 755 760 765 770 775 780 785 790 795 800 805 810 815 820 825 830 835 840 845 850 855 860 865 870 875 880 885 890 895 900 905 910 915 920 925 930 935 940 945 950 955 960 965 970 975 980 985 990 995 1000 1005 1010 1015 1020 1025 1030 1035 1040 1045 1050 1055 1060 1065 1070 1075 1080 1085 1090 1095 1100 1105 1110 1115 1120 1125 1130 1135 1140 1145 1150 1155 1160 1165 1170 1175 1180 1185 1190 1195
25
*/
