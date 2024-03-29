/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_opencl.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiri <kerneloverseer@pm.me>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 11:48:56 by abiri             #+#    #+#             */
/*   Updated: 2021/11/27 15:57:32 by abiri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_OPENCL_H
# define FT_OPENCL_H
# define CL_SILENCE_DEPRECATION
# include <OpenCL/cl.h>

/*
**	functions for setting up the device to compute operations on
*/

typedef	struct			s_opencl
{
	cl_device_id		device;
	cl_context			context;
	cl_program			program;
	cl_kernel			kernel;
	cl_command_queue	queue;
	cl_int				err;
	cl_int				i;
}						t_opencl;

size_t					ft_filesize(const char *filename);
char					*readfile(const char *filename, size_t size);
cl_program				build_program(cl_context ctx, const char *filename);
cl_device_id			create_device(void);
t_opencl				*prepare_opencl(char *programfile);

#endif
