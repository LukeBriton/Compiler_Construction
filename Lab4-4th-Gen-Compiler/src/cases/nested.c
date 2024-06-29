int sum(int x, int y)
{
	int sum;
	int a = 2;
	int b = 3;
	{
		sum = 0;
		int z = 5;
		int p = 6;
		int q = 7;
		sum = x*a + y*b + z;
	}
	sum = 8;
	a = 1;
	b = 10;
	{
		{
			a = 3;
		}
	}
	z = 4;
	p = 9;
	q = 100;
	{
		sum = 1111;
		int z = 2222;
		int p = 3333;
		int q = 4444;
		sum = x*a + y*b + z;
	}
	return sum;
}
	
int main()
{
	int a = 1;
	int b = 2;
	{
		int c = 3;
		c = a + b;
		{
			int d = 4;
			d = c + a;
		}
		c = c - b;
	}
	int e = sum(a, b);
	return 0;
}