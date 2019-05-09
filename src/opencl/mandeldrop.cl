__kernel void fractal(	long double a_min,
							long double a_max,
							long double b_min,
							long double b_max,
							int max_iter,
							unsigned int width,
							unsigned int height,
							int			mouseX,
							int			mouseY,
							__global double *res)
{
	int id = get_global_id(0);
	
	if (id > (int)width*height)
		return;
	long double aa;
	long double bb;
	long double ca;
	long double cb;
	long double ta;
	long double tb;
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
	percent = (long double)mouseX/(long double)width;
	ca = percent;
	percent = (long double)mouseY/(long double)height;
	cb = percent;

	int n = 0;
	long double val;
	long double t;
	t = ca;
	val = a*a+b*b;
	a = a - a*t + (t*a)/val;
	b = b - t*b - (t*b)/val;
	ta = a;
	tb = b;
	while (n < max_iter)
	{
		aa = a*a - b*b;
		bb = a*b + a*b;
		a = aa + ta;
		b = bb + tb;
		if (a*a+b*b > (long double)16)
			break;
		n++;
	}
	if (n == max_iter)
	{
		res[id] = 0;
		return;
	}
	res[id] = n;
}
