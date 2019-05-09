/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiri <kerneloverseer@pm.me>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 18:05:17 by abiri             #+#    #+#             */
/*   Updated: 2019/05/09 16:38:31 by abiri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void		*ft_error(int error, char *filename)
{
	if (error == -1)
		ft_printf("FRACTOL : Colorfile %s cannot be accessible\n", filename);
	else if (error == 0)
		ft_printf("FRACTOL : Cannot allocate enough memory for color\n");
	else if (error == 1)
		ft_printf("FRACTOL : No color presets can be found at ./colors\n");
	return (NULL);
}

static t_color	*ft_loadcolor(char *filename)
{
	char	*line;
	int		fd;
	int		colorsize;
	int		colorindex;
	t_color *result;

	colorindex = 0;
	if ((fd = open(filename, O_RDONLY)) < 0)
		return (ft_error(-1, filename));
	get_next_line(fd, &line);
	colorsize = ft_atoi(line);
	if (!(result = ft_memalloc(sizeof(t_color))))
		return (ft_error(0, NULL));
	result->size = colorsize;
	result->tab = ft_memalloc(sizeof(int) * (colorsize + 1));
	while (colorsize-- && get_next_line(fd, &line) > 0)
	{
		result->tab[colorindex] = ft_atoi(line);
		colorindex++;
		free(line);
	}
	close(fd);
	return (result);
}

t_color			**load_colors(void)
{
	char	*line;
	int		fd;
	int		colorcount;
	int		colorindex;
	t_color	**colorstock;

	line = NULL;
	colorindex = 0;
	fd = open("./colors/index.col", O_RDONLY);
	get_next_line(fd, &line);
	if (fd < 0 || !line)
		return (ft_error(1, NULL));
	colorcount = ft_atoi(line);
	free(line);
	if (!(colorstock = ft_memalloc(sizeof(t_color *) * (colorcount + 1))))
		return (NULL);
	while (colorcount-- && get_next_line(fd, &line) > 0)
	{
		colorstock[colorindex] = ft_loadcolor(line);
		if (colorstock[colorindex])
			colorindex++;
		free(line);
	}
	close(fd);
	return (colorstock);
}

int				get_color(int iter, t_env *env)
{
	t_color		*colortab;

	if (!env->colors)
		return (ft_map(iter, 240, 0, 0xffffff));
	if (!env->colors[env->colorindex])
		env->colorindex = 0;
	colortab = env->colors[env->colorindex];
	return (colortab->tab[iter % colortab->size]);
}
