// Implementation of 0/1 knapsack 

// Input format:
// Line 1 - noof_items, capacity
// Line 2 - weights array
// Line 3 - profits array

// Output format:
// Line 1 - items included
// Line 2 - maximum profit

// Time complexity:
// O(noof_items * capacity)

#include <stdio.h>
#include <stdbool.h>
#define Max 50 // Limit on no. of items
#define larger(a, b) (a > b)? a: b

// Global variables. Note that table isn't global.
// Item indices go from 1 to noof_items. 
// weights[0], profits[0] is never considered.
int noof_items;
int capacity;
int weights[Max + 1];
int profits[Max + 1];
int included_items[Max  + 1]; // Array containing indices of items included.
int noof_items_included; // zero by default

// Reading all input
// Modifies noof_items, capacity, weights, profits
void read_data()
{
	scanf("%d %d", &noof_items, &capacity);
	int i;
	for (i = 1; i <= noof_items; ++i) scanf("%d", &weights[i]);
	for (i = 1; i <= noof_items; ++i) scanf("%d", &profits[i]);
}

// Fills the dp table; Modifies table.
void fill_table(int table[noof_items + 1][capacity + 1])
{
	int i, j, old_value, calculated_value;

	// Zeroth row should be full of zeroes.
	for (j = 0; j <= capacity; ++j) table[0][j] = 0;

	for (i = 1; i <= noof_items; ++i)
	{
		// If weight of an item exceeds total capacity,
		// it definitely cannot be included. The row 
		// for this item will be the same as previous row.
		if (weights[i] > capacity)
		{
			for (j = 0; j <= capacity; ++j)
				table[i][j] = table[i - 1][j];
			continue;
		}

		// Copying previous row values until weights[i] is reached.
		for (j = 0; j < weights[i]; ++j)
			table[i][j] = table[i - 1][j];

		// Finding the new row values using formula.
		for (j = weights[i]; j <= capacity; ++j)
		{
			old_value = table[i - 1][j];
			calculated_value = table[i-1][j - weights[i]] + profits[i];
			table[i][j] = larger(old_value, calculated_value);
		}
	}

	/*// Displaying table.
	for (i = 0; i <= noof_items; ++i)
	{
		printf("(%d, %d, %d) ", weights[i], profits[i], i);
		for (j = 0; j <= capacity; ++j)
			printf("%d ", table[i][j]);
		printf("\n");
	}*/
}

// Modifies included_items
void find_items_to_include(int table[noof_items + 1][capacity + 1])
{
	int instantaneous_capacity = capacity;
	int cur = noof_items;
	int value; // A value from the table

	while (true)
	{
		value = table[cur][instantaneous_capacity]; // Initially, the last value from the table.
		if (value == 0) break; // No more profit to be gained by including an additional item.

		// Going up the column till the value in the table changes.
		do{
			cur--;
		} while (table[cur][instantaneous_capacity] == value);

		// Then including the item corresponding to the row below.
		included_items[noof_items_included] = cur + 1;
		noof_items_included += 1;
		instantaneous_capacity -= weights[cur + 1];
	}
}

// Writes all output to console
void print_included_items_and_minimum_cost(int table[noof_items + 1][capacity + 1])
{
	int i;
	for (i = noof_items_included - 1; i >= 0; --i)
		printf("%d ", included_items[i]);
	printf("\n");
	printf("%d\n", table[noof_items][capacity]);
}

// Driver function
void main()
{
	read_data();
	int table[noof_items + 1][capacity + 1];
	fill_table(table);
	find_items_to_include(table);
	print_included_items_and_minimum_cost(table);
}
