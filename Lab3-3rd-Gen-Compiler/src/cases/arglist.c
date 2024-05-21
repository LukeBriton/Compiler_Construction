void add(int a, int b, int c, int d, int e)
{
	a = 4;
	b = 3;
	int f;
	e = 2;
	
	return 0;
}

int main()
{
	int a = 5;
	int b = 5*7;
	int c = 2;
	int d = 6;
	int e = 999;
	add(a, b, c, d, e);
	println_int(e);
	a = add(1, 2, 3, 4, 5);
	return 0;
}