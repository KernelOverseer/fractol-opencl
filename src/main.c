/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiri <kerneloverseer@pm.me>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/04 13:53:02 by abiri             #+#    #+#             */
/*   Updated: 2019/05/09 16:26:06 by abiri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	main(int argc, char **argv)
{
	t_env			*env;
	unsigned char	fractid;

	if (argc != 2)
	{
		ft_printf("Fract'ol :\nUsage: ./fractol <fractal id>\n");
		ft_printf("please choose a fractal to visualise\n");
		ft_printf("0 - Mandelbrot\n1 - Julia\n2 - Burningship\n\
3 - celtic mandelbar\n4 - Burningship 5th\n");
		return (1);
	}
	fractid = ft_atoi(argv[1]);
	if (fractid < 0 || fractid > 4)
	{
		ft_printf("Fract'ol : fractal not available\n");
		return (1);
	}
	env = ft_fractol_init(fractid);
	ft_load_events(env, fractid);
	env->func(env);
	mlx_loop(env->mlx);
	return (0);
}
