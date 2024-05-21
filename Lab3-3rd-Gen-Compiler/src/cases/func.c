int test(int arg1, int arg2) { return (arg1 + arg2) * arg1 / arg2 & arg1; }
int func(int arg1, int arg2) { return (arg1 + arg2) * arg1 / arg2 & arg1; }

int main()
{
	int a;
	a = test(1, 2) + func(3, 4) + 9 * 10;
	int b;
	b = test(func(1, 2), func(3, 4));
	int c;
	func(test(1, 2), test(3, 4));
	return 0;
}