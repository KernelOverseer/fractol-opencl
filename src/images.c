/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mlx_images.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiri <kerneloverseer@pm.me>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 18:24:05 by abiri             #+#    #+#             */
/*   Updated: 2019/05/09 18:02:55 by abiri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void		ft_pixelput(t_image *image, int x, int y, int color)
{
	char	*imagebits;
	int		offset;

	if (x < 0 || x >= (int)image->width || y < 0 || y >= (int)image->height)
		return ;
	imagebits = (char *)image->ptr;
	offset = idx(y, x, image->width) * image->bpp;
	*((int *)(imagebits + offset)) = color;
}

t_image		*ft_new_image(void *mlx, unsigned int width, unsigned int height)
{
	void	*img;
	t_image *result;

	if (!(result = malloc(sizeof(t_image))))
		return (NULL);
	if (!(img = mlx_new_image(mlx, width, height)))
		return (NULL);
	result->ptr = mlx_get_data_addr(img, &(result->bpp),
			&(result->size_line), &(result->endian));
	result->img = img;
	result->width = width;
	result->height = height;
	result->bpp /= 8;
	return (result);
}

int			idx(int row, int col, int dim)
{
	return (row * dim + col);
}

int			rgb(unsigned char r, unsigned char g, unsigned char b)
{
	return ((b << 16) | (g << 8) | r);
}

double		ft_map(double n, double max, double tomin, double tomax)
{
	double percent;
	double result;

	percent = n / max;
	result = (tomax - tomin) * percent + tomin;
	return (result);
}
