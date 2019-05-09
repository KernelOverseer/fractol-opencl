/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiri <kerneloverseer@pm.me>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 17:23:39 by abiri             #+#    #+#             */
/*   Updated: 2019/05/09 17:01:28 by abiri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void		ft_load_events(t_env *env, unsigned char fractalid)
{
	mlx_hook(env->window, EVENT_KEY_PRESS, 0, &keypress_hook, env);
	mlx_hook(env->window, EVENT_CLOSE, 0, &window_close, NULL);
	mlx_hook(env->window, EVENT_MOUSE_PRESS, 0, &mouse_zoom, env);
	if (fractalid == JULIA)
		mlx_hook(env->window, EVENT_MOUSE_MOVE, 0, &mouse_move, env);
}

t_env		*ft_init_env(void *mlx, unsigned int width, unsigned int height)
{
	t_env *env;

	if (!(env = malloc(sizeof(t_env))))
		return (NULL);
	env->image = ft_new_image(mlx, width, height);
	env->a_min = -2;
	env->a_max = 2;
	env->b_min = -2;
	env->b_max = 2;
	env->max_iter = 1000;
	env->fixed = 0;
	env->colorindex = 0;
	env->colors = load_colors();
	return (env);
}

char		*ft_get_programfile(unsigned char fractalid)
{
	if (fractalid == MANDELBROT)
		return ("./src/opencl/mandelbrot.cl");
	if (fractalid == JULIA)
		return ("./src/opencl/julia.cl");
	if (fractalid == BURNINGSHIP)
		return ("./src/opencl/burningship.cl");
	if (fractalid == CELTICMANDELBAR)
		return ("./src/opencl/celticmandelbar.cl");
	if (fractalid == BURNINGSHIPFIFTH)
		return ("./src/opencl/burningshipfifth.cl");
	return (NULL);
}

t_fractfunc	*ft_load_function(unsigned char fractalid)
{
	if (fractalid == MANDELBROT)
		return (&ft_gpu_mandelbrot);
	if (fractalid == JULIA)
		return (&ft_gpu_julia);
	if (fractalid == BURNINGSHIP)
		return (&ft_gpu_burningship);
	if (fractalid == CELTICMANDELBAR)
		return (&ft_gpu_celticmandelbar);
	if (fractalid == BURNINGSHIPFIFTH)
		return (&ft_gpu_burningshipfifth);
	return (NULL);
}

t_env		*ft_fractol_init(unsigned char fractalid)
{
	void		*mlx;
	t_env		*env;
	t_opencl	*cldata;

	mlx = mlx_init();
	if (!(env = ft_init_env(mlx, WIDTH, HEIGHT)))
	{
		ft_printf("There was an error initialising the image\n");
		exit(1);
	}
	env->window = mlx_new_window(mlx, WIDTH, HEIGHT, "Abiri's Fract'ol");
	env->mlx = mlx;
	env->func = ft_load_function(fractalid);
	if (!(cldata = prepare_opencl(ft_get_programfile(fractalid))))
	{
		ft_printf("There was an error allocating memory for fract'ol\n");
		exit(1);
	}
	env->cldata = cldata;
	return (env);
}
