/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiri <kerneloverseer@pm.me>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/04 13:53:02 by abiri             #+#    #+#             */
/*   Updated: 2021/11/27 16:14:50 by abiri            ###   ########.fr       */
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
3 - celtic mandelbar\n4 - Burningship 5th\n5 - Celtic Mandelbrot\n\
6 - Mandeldrop\n");
		ft_printf("\n========== KEYS =========\n");
		ft_printf("+      : more iterations\n");
		ft_printf("-      : less iterations\n");
		ft_printf("RIGHT  : move right\n");
		ft_printf("LEFT   : move left\n");
		ft_printf("UP     : move up\n");
		ft_printf("DOWN   : move down\n");
		ft_printf("c      : next color\n");	
		ft_printf("SCROLL : zoom in and out\n");
		ft_printf("CLICK  : lock/unlock Julia\n");
		return (1);
	}
	fractid = ft_atoi(argv[1]);
	if (fractid < 0 || fractid > 6)
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
