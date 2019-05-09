/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiri <kerneloverseer@pm.me>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/05 10:46:47 by abiri             #+#    #+#             */
/*   Updated: 2019/05/09 17:11:09 by abiri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H
# include "libft.h"
# include "ft_opencl.h"
# include <mlx.h>
# include <OpenCL/cl.h>
# include <stdio.h>
# include <math.h>
# include "ft_mlx_keys.h"
# define WIDTH 1000
# define HEIGHT 1000

/*
**	Defining fractal ID's
*/

# define MANDELBROT 0
# define JULIA 1
# define BURNINGSHIP 2
# define CELTICMANDELBAR 3
# define BURNINGSHIPFIFTH 4

typedef struct	s_image
{
	void			*img;
	void			*ptr;
	unsigned int	width;
	unsigned int	height;
	int				bpp;
	int				size_line;
	int				endian;
	int				iter;
}				t_image;

typedef struct	s_env	t_env;

typedef	void	t_fractfunc(t_env*);

typedef struct	s_color
{
	int				*tab;
	int				size;
}				t_color;

struct				s_env
{
	t_image			*image;
	t_opencl		*cldata;
	t_fractfunc		*func;
	t_color			**colors;
	void			*window;
	void			*mlx;
	double			a_min;
	double			a_max;
	double			b_max;
	double			b_min;
	int				mouseX;
	int				mouseY;
	int				max_iter;
	int				fixed;
	int				colorindex;
};

/*
**	Initialisation functions :
*/

t_env			*ft_fractol_init(unsigned char fractalid);
void			ft_load_events(t_env *env, unsigned char fractalid);
t_env			*ft_init_env(void	*mlx, unsigned int width, unsigned int height);
char			*ft_get_programfile(unsigned char fractalid);
t_fractfunc		*ft_load_function(unsigned char fractalid);

/*
**	Events functions
*/

int				mouse_move(int x, int y, void *param);
int				mouse_zoom(int button, int x, int y, void *param);
int				keypress_hook(int key, void	*param);
int				window_close(void *param);

/*
**	Images and colors manipulations
*/

void			ft_pixelput(t_image *image, int x, int y, int color);
t_image			*ft_new_image(void *mlx, unsigned int width, unsigned int height);
int				idx(int row, int col, int dim);
int				rgb(unsigned char r, unsigned char g, unsigned char b);
double			ft_map(double n, double max, double tomin, double tomax);

/*
**	Color loading functions
*/

t_color			**load_colors(void);
int				get_color(int iter, t_env *env);

/*
**	Main Fractal Drawing Functions:
*/

void			ft_gpu_julia(t_env *env);
void			ft_gpu_mandelbrot(t_env *env);
void			ft_gpu_burningship(t_env *env);
void			ft_gpu_celticmandelbar(t_env *env);
void			ft_gpu_burningshipfifth(t_env *env);

#endif
