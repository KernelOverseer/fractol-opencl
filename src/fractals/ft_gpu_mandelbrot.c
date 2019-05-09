/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_GPU_mandelbrot.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiri <kerneloverseer@pm.me>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 18:37:43 by abiri             #+#    #+#             */
/*   Updated: 2019/05/09 17:03:17 by abiri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static	void	ft_loadargs(t_env *env, t_opencl *cl, cl_mem device_result)
{
	clSetKernelArg(cl->kernel, 0, sizeof(env->a_min), &(env->a_min));
	clSetKernelArg(cl->kernel, 1, sizeof(env->a_max), &(env->a_max));
	clSetKernelArg(cl->kernel, 2, sizeof(env->b_min), &(env->b_min));
	clSetKernelArg(cl->kernel, 3, sizeof(env->b_max), &(env->b_max));
	clSetKernelArg(cl->kernel, 4, sizeof(env->max_iter), &(env->max_iter));
	clSetKernelArg(cl->kernel, 5, sizeof(env->image->width),
			&(env->image->width));
	clSetKernelArg(cl->kernel, 6, sizeof(env->image->height),
			&(env->image->height));
	clSetKernelArg(cl->kernel, 7, sizeof(cl_mem), &(device_result));
}

static	void	ft_drawpixels(double *vals, t_env *env)
{
	size_t	i;
	size_t	j;
	int		n;
	int		col;

	i = 0;
	while (i < env->image->height)
	{
		j = 0;
		while (j < env->image->width)
		{
			n = vals[i * env->image->width + j];
			if (n == 0)
				col = 0;
			else
				col = get_color(n, env);
			ft_pixelput(env->image, i, j, col);
			j++;
		}
		i++;
	}
}

void			ft_gpu_mandelbrot(t_env *env)
{
	double		*vals;
	size_t		globalsize;
	size_t		localsize;
	size_t		n;
	cl_mem		device_result;

	localsize = 64;
	n = env->image->width * env->image->height * sizeof(double);
	vals = ft_memalloc(n);
	globalsize = ceil(n / (float)localsize) * localsize;
	env->cldata->kernel = clCreateKernel(env->cldata->program,
			"fractal", &(env->cldata->err));
	device_result = clCreateBuffer(env->cldata->context,
			CL_MEM_WRITE_ONLY, n, NULL, NULL);
	ft_loadargs(env, env->cldata, device_result);
	clEnqueueNDRangeKernel(env->cldata->queue, env->cldata->kernel, 1,
			NULL, &globalsize, &localsize, 0, NULL, NULL);
	clFinish(env->cldata->queue);
	clEnqueueReadBuffer(env->cldata->queue, device_result, CL_TRUE, 0, n, vals,
			0, NULL, NULL);
	clReleaseMemObject(device_result);
	ft_drawpixels(vals, env);
	free(vals);
	mlx_put_image_to_window(env->mlx, env->window, env->image->img, 0, 0);
}
