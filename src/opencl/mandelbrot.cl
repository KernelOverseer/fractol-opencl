__kernel void fractal(	long double a_min,
							long double a_max,
							long double b_min,
							long double b_max,
							int max_iter,
							unsigned int width,
							unsigned int height,
							__global double *res)
{
	int id = get_global_id(0);
	
	if (id > (int)width*height)
		return;
	long double aa;
	long double bb;
	long double ca;
	long double cb;
	long double a;
	long double b;
	long double percent;
	int x;
	int y;

	x = id/width;
	y = id%width;

	percent = (long double)x/(long double)width;
	a = percent*((long double)(a_max-a_min))+a_min;
	percent = (long double)y/(long double)height;
	b = percent*((long double)(b_max-b_min))+b_min;

	int n= 0;
	ca = a;
	cb = b;
	while (n < max_iter)
	{
		aa = a*a - b*b;
		bb = a*b + a*b;
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
}
