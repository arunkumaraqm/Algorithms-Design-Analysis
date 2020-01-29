// Recursive Towers of Hanoi - not working with actual stacks, just displaying instructions
#include <stdio.h>

typedef char String[6];

#define move(A, B) printf("From %s to %s. \n", A, B)

void towers(int n, String A, String aux, String B)
{
	if (n <= 1)
	{
		move(A, B); 
		return;
	}
	
	towers(n - 1, A, B, aux);
	move(A, B);
	towers(n - 1, aux, A, B);
}

void main()
{
	int n;
	scanf("%d", &n);
	towers(n, "A", "aux", "B");
}
