/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transforms.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 19:05:12 by eklompus          #+#    #+#             */
/*   Updated: 2019/10/14 19:05:13 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	set_size_transform(t_point *arr, int size, double scale, double zscale)
{
	int			i;

	i = -1;
	while (++i < size)
	{
		arr->x = (int)(arr->x * scale);
		arr->y = (int)(arr->y * scale);
		arr->z = (int)(arr->z * scale * zscale);
		arr++;
	}
}

void	set_z_transform(t_point *arr, int size, long z)
{
	int			i;
	t_dpoint	dp;
	double		cosf;
	double		sinf;

	cosf = cos((double)(z) * M_PI / 180);
	sinf = sin((double)(z) * M_PI / 180);
	i = -1;
	while (++i < size)
	{
		dp.x = arr->x * cosf - arr->y * sinf;
		dp.y = arr->x * sinf + arr->y * cosf;
		arr->x = (int)(dp.x);
		arr->y = (int)(dp.y);
		arr++;
	}
}

void	set_x_transform(t_point *arr, int size, long x_rotate)
{
	int			i;
	double		cosf;
	double		sinf;
	t_dpoint	dp;

	cosf = cos((double)(x_rotate) * M_PI / 180);
	sinf = sin((double)(x_rotate) * M_PI / 180);
	i = -1;
	while (++i < size)
	{
		dp.y = arr->y * cosf + arr->z * sinf;
		dp.z = -arr->y * sinf + arr->z * cosf;
		arr->y = (int)dp.y;
		arr->z = (int)dp.z;
		arr++;
	}
}

void	set_y_transform(t_point *arr, int size, long y_rotate)
{
	int			i;
	double		cosf;
	double		sinf;
	t_dpoint	dp;

	cosf = cos((double)(y_rotate) * M_PI / 180);
	sinf = sin((double)(y_rotate) * M_PI / 180);
	i = -1;
	while (++i < size)
	{
		dp.x = arr->x * cosf + arr->z * sinf;
		dp.z = -arr->x * sinf + arr->z * cosf;
		arr->x = (int)dp.x;
		arr->z = (int)dp.z;
		arr++;
	}
}

void	set_iso(t_point *arr, int size)
{
	int		i;
	double	x1;
	double	y1;

	i = -1;
	while (++i < size)
	{
		x1 = (arr->x - arr->y) * FT_COS30;
		y1 = -arr->z + (arr->x + arr->y) * FT_SIN30;
		arr->x = (int)x1;
		arr->y = (int)y1;
		arr++;
	}
}
