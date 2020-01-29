// Permutations and combinations for small values of n and r
// Timed using time.h

#include <stdio.h>
#include <time.h>

unsigned long long factorial_with_ll(int number, int ll) // ll - lower limit
{
	if (number < 2) return 1;
	unsigned long long product = 1;
	for (unsigned long long i = number; i > ll; --i)
	{
		product *= i;
	}
	return product;
}

unsigned long long combinations(int n, int r)
{
	if (n - r < r) r = n - r;
	return factorial_with_ll(n, n - r) / factorial_with_ll(r, 1);
}

unsigned long long permutations(int n, int r)
{
	return factorial_with_ll(n, n - r);
}

double duration(clock_t start, clock_t end)
{
	return (double)(end - start)/CLOCKS_PER_SEC;
}
void main()
{
// System can calculate upto and including 20!
	int n, r;
	scanf("%d %d", &n, &r);
	
	clock_t start1, end1, start2, end2;
	double duration_perm, duration_comb;
	
	start1 = clock();
	unsigned long long noof_perms = permutations(n, r);
	end1 = clock();
	duration_perm = duration(start1, end1);
	
	start2 = clock();	
	unsigned long long noof_combs = combinations(n, r);
	end2 = clock();
	duration_comb = duration(start2, end2);
	
	printf("(Perms, Combs) = (%llu, %llu)\n", noof_perms, noof_combs);
	printf("\nFor perms, start = %ld, end = %ld, duration = %lf", start1, end1, duration_perm);
	printf("\nFor combs, start = %ld, end = %ld, duration = %lf", start2, end2, duration_comb);
}
