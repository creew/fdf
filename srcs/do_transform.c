/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_transform.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 16:35:21 by eklompus          #+#    #+#             */
/*   Updated: 2019/10/16 16:35:22 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		cp_array(t_point *dst, t_point *src, int size)
{
	int		i;

	i = -1;
	while (++i < size)
	{
		dst->x = src->x;
		dst->y = src->y;
		dst->z = src->z;
		dst->color = src->color;
		dst++;
		src++;
	}
}

void		set_shift(t_point *point, int size, int shift_x, int shift_y)
{
	int		i;

	i = -1;
	while (++i < size)
	{
		point->x += shift_x;
		point->y += shift_y;
		point++;
	}
}

void		do_transformations(t_fdf *fdf)
{
	int size;

	size = fdf->map_width * fdf->map_height;
	cp_array(fdf->mapout, fdf->srcmap, size);
	colorize_not(fdf->mapout, size);
	set_size_transform(fdf->mapout, size, fdf->scale, fdf->z_scale);
	set_z_transform(fdf->mapout, size, get_z_offset(fdf));
	set_x_transform(fdf->mapout, size, get_x_offset(fdf));
	set_y_transform(fdf->mapout, size, get_y_offset(fdf));
	if (!fdf->parallel)
		set_iso(fdf->mapout, size);
	set_shift(fdf->mapout, size, get_start_x(fdf), get_start_y(fdf));
}
