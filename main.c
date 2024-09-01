#include <stdio.h>
#include <stdint.h>
#include <string.h>
#define MAX_N 32
#define MAX_DIAG 64


uint64_t col, ld, rd;
int n;
int sum = 0;

void solve (int i)
{
	register int pos = col & (ld >> (n - i)) & (rd >> i);
	if (i == n-1 && pos) 
	{
		sum++;
		return;
	}
	register int bit;
	while ((bit = (pos & (-pos))))
	{
		col ^= bit;
		ld  ^= bit << (n-i);
		rd  ^= bit << (i);
		solve(i + 1);
		col ^= bit;
		ld  ^= bit << (n-i);
		rd  ^= bit << (i);
		pos -= bit;
	}
}

int solve_n(int _n)
{
	n = _n;
	ld = rd = ((uint64_t)1 << (n*2)) - 1;
	col = ((uint64_t)1 << n) - 1;
	int lsum = 0;
	sum = 0;
	for (int i = 0; i < 1 + (n - 1) / 2; i++)
	{
		lsum += sum;
		sum = 0;
		col ^= 1 << i;
		ld ^= 1 << (n + i);
		rd ^= 1 << i;
		solve(1);
		col ^= 1 << i;
		ld ^= 1 << (n + i);
		rd ^= 1 << i;
	}
	if (n&1)
	{
		return lsum * 2 + sum;
	}
	return lsum * 2 + sum * 2;
}

int main()
{
	for (int i = 1; i <= MAX_N; i++)
	{
		int res = solve_n(i);
		printf("%d: %d\n", i, res);
	}
}
