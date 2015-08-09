extern int g_val1 ;
extern int l_val1 ;
static int func(int a, int b)
{
	int tmp = a ;
	g_val1 = 3 ;
//	l_val1 = 4 ;
	a = b ;
	b = tmp ;
}

