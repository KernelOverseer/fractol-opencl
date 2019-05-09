/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiri <kerneloverseer@pm.me>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 18:09:58 by abiri             #+#    #+#             */
/*   Updated: 2019/05/09 17:24:49 by abiri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int				mouse_move(int x, int y, void *param)
{
	t_env *env;

	env = (t_env *)param;
	if (!env->fixed)
	{
		env->mousex = x;
		env->mousey = y;
		env->func(env);
	}
	return (0);
}

int				mouse_zoom(int button, int x, int y, void *param)
{
	t_env	*env;
	double	newx;
	double	newy;

	env = (t_env *)param;
	newx = ft_map(x, env->image->width, env->a_min, env->a_max);
	newy = ft_map(y, env->image->height, env->b_min, env->b_max);
	if (button == MOUSE_SCROLL_DOWN)
	{
		env->a_min = (env->a_min - newx) / 2 + newx;
		env->a_max = (env->a_max - newx) / 2 + newx;
		env->b_min = (env->b_min - newy) / 2 + newy;
		env->b_max = (env->b_max - newy) / 2 + newy;
	}
	else if (button == MOUSE_SCROLL_UP)
	{
		env->a_min = (env->a_min - newx) * 2 + newx;
		env->a_max = (env->a_max - newx) * 2 + newx;
		env->b_min = (env->b_min - newy) * 2 + newy;
		env->b_max = (env->b_max - newy) * 2 + newy;
	}
	else if (button == MOUSE_LEFT_BUTTON)
		env->fixed = (env->fixed) ? 0 : 1;
	env->func(env);
	return (0);
}

static	void	move(int key, t_env *env)
{
	if (key == KEY_RIGHT)
	{
		env->a_min += (env->a_max - env->a_min) / 10;
		env->a_max += (env->a_max - env->a_min) / 10;
	}
	else if (key == KEY_LEFT)
	{
		env->a_min -= (env->a_max - env->a_min) / 10;
		env->a_max -= (env->a_max - env->a_min) / 10;
	}
	else if (key == KEY_UP)
	{
		env->b_min -= (env->b_max - env->b_min) / 10;
		env->b_max -= (env->b_max - env->b_min) / 10;
	}
	else if (key == KEY_DOWN)
	{
		env->b_min += (env->b_max - env->b_min) / 10;
		env->b_max += (env->b_max - env->b_min) / 10;
	}
}

int				keypress_hook(int key, void *param)
{
	t_env *env;

	env = (t_env *)param;
	if (key == KEY_RIGHT || key == KEY_LEFT || key == KEY_UP || key == KEY_DOWN)
		move(key, env);
	else if (key == KEY_PLUS)
		env->max_iter += 10;
	else if (key == KEY_MINUS)
		env->max_iter -= 10;
	else if (key == KEY_ESC)
		exit(0);
	else if (key == KEY_C)
		env->colorindex++;
	env->func(env);
	return (0);
}

int				window_close(void *param)
{
	(void)param;
	exit(0);
	return (0);
}
