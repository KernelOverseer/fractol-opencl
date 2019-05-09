/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opencltools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiri <kerneloverseer@pm.me>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 11:34:53 by abiri             #+#    #+#             */
/*   Updated: 2019/05/09 16:51:26 by abiri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_opencl.h"
#include "fractol.h"

size_t			ft_filesize(const char *filename)
{
	int		fd;
	size_t	result;
	char	buffer[13];
	int		ret;

	fd = open(filename, O_RDONLY);
	result = 0;
	if (fd < 0)
		return (0);
	while ((ret = read(fd, buffer, 12)))
		result += ret;
	close(fd);
	return (result);
}

char			*readfile(const char *filename, size_t size)
{
	char	buffer[2];
	char	*content;
	size_t	index;
	int		fd;

	index = 0;
	content = ft_memalloc(sizeof(char) * (size + 1));
	fd = open(filename, O_RDONLY);
	while (index < size)
	{
		read(fd, buffer, 1);
		ft_memcpy(content + index, buffer, 1);
		index += 1;
	}
	close(fd);
	return (content);
}

/*
**	loading and building the program
*/

cl_program		build_program(cl_context ctx, const char *filename)
{
	cl_program	program;
	size_t		size;
	char		*buffer;
	int			err;

	size = ft_filesize(filename);
	buffer = readfile(filename, size);
	program = clCreateProgramWithSource(ctx, 1, (const char **)&buffer,
			NULL, &err);
	if (err < 0)
	{
		ft_printf("FRACTOL %*@<fatal>%@ : OpenCl Couldn't create the program \
: please re-verify the file's integrity\n", cRED);
		exit(1);
	}
	free(buffer);
	err = clBuildProgram(program, 0, NULL, NULL, NULL, NULL);
	if (err < 0)
	{
		ft_printf("FRACTOL %*@<fatal>%*@ : ERROR with OpenCL program\n", cRED);
		exit(1);
	}
	return (program);
}

/*
**	Getting the id of the device calculations will be running on
*/

cl_device_id	create_device(void)
{
	cl_platform_id	plat_id;
	cl_device_id	device_id;
	int				err;

	err = clGetPlatformIDs(1, &plat_id, NULL);
	if (err < 0)
	{
		ft_printf("FRACTOL %*@<fatal>%@ : OpenCl Couldn't identify a platform \
for GPU acceleration\n", cRED);
		exit(1);
	}
	err = clGetDeviceIDs(plat_id, CL_DEVICE_TYPE_GPU, 1, &device_id, NULL);
	if (err == CL_DEVICE_NOT_FOUND)
	{
		ft_printf("FRACTOL  %*@<info>%@ : no GPU was identified by OpenCL, \
using the CPU\n", cYELLOW);
		err = clGetDeviceIDs(plat_id, CL_DEVICE_TYPE_CPU, 1, &device_id, NULL);
	}
	if (err < 0)
	{
		ft_printf("FRACTOL %*@<fatal>%@ : no CPU was identified by OpenCl, \
cannot procede\n", cRED);
		exit(1);
	}
	return (device_id);
}

/*
**	initial initialisation of openCl and packing al infos in a t_opencl struct
*/

t_opencl		*prepare_opencl(char *programfile)
{
	t_opencl	*st;

	if (!(st = ft_memalloc(sizeof(t_opencl))))
		return (NULL);
	st->device = create_device();
	st->context = clCreateContext(NULL, 1, &(st->device), NULL, NULL,
			&(st->err));
	st->program = build_program(st->context, programfile);
	st->queue = clCreateCommandQueue(st->context, st->device, 0, &(st->err));
	return (st);
}
