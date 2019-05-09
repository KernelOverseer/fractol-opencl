__kernel void fractal(	long double a_min,
							long double a_max,
							long double b_min,
							long double b_max,
							int max_iter,
							unsigned int width,
							unsigned int height,
							__global unsigned int *res)
{
	int id = get_global_id(0);
	
	if (id > (int)width*height)
		return;
	double aa;
	double bb;
	double ca;
	double cb;
	double a;
	double b;
	double zisqr,zrsqr,zisqrsqr,zrsqrsqr,zrzisqr;
	double percent;
	int x;
	int y;

	x = id/width;
	y = id%width;

	percent = (long double)x/(long double)width;
	a = percent*((long double)(a_max-a_min))+a_min;
	percent = (long double)y/(long double)height;
	b = percent*((long double)(b_max-b_min))+b_min;

	int n = 0;
	ca = a;
	cb = b;
	while (n < max_iter)
	{
		zisqr = b * b;
		zrsqr = a * a;
		zisqrsqr = zisqr * zisqr;
		zrsqrsqr = zrsqr * zrsqr;
		zrzisqr = zrsqr * zisqr;
		bb = fabs(b) * (5 * zrsqrsqr - 10 * zrzisqr + zisqrsqr);
		aa = fabs(a) * (zrsqrsqr - 10 * zrzisqr + 5 * zisqrsqr);
		a = aa + ca;
		b = bb + cb;
		if (a*a+b*b > (long double)16)
			break;
		n++;
	}
	if (n == max_iter)
		res[id] = 0;
	else
		res[id] = n;
/*
	int col;
	if (n == max_iter)
		col = 0;
	else
		col = ft_map(n, max_iter, 0, 0xffffff);*/
}
