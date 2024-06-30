int main()
{
	int a = 0, c = 9;
	if (a == 0)
		a = a + 1;
	else
		a = a -1;
	int b = 2;
	if (b != 0)
		b = b + 1;
	else if (b != 2)
		b = c;
	else if (b % 100 == 0)
		b = 1;
	else
		b = b - 1;
	if(c == 8)
	{
		if(2 >= 1)
			return 2;
		else
			return 1;
	}
	else
		c = c + 1;
	return 0;
}