/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 14:05:02 by eklompus          #+#    #+#             */
/*   Updated: 2019/10/17 14:05:03 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	add_rotate(t_fdf *fdf, int x, int y, int z)
{
	fdf->x_rotate += x;
	fdf->y_rotate += y;
	fdf->z_rotate += z;
	fdf->x_rotate %= 360;
	fdf->y_rotate %= 360;
	fdf->z_rotate %= 360;
}

void	set_rotate_add(t_fdf *fdf, int x, int y, int z)
{
	fdf->x_rotate_add = x;
	fdf->y_rotate_add = y;
	fdf->z_rotate_add = z;
}

void	add_shift(t_fdf *fdf, int x, int y)
{
	fdf->shift_x += x;
	fdf->shift_y += y;
}

void	set_shift_add(t_fdf *fdf, int x, int y)
{
	fdf->shift_x_add = x;
	fdf->shift_y_add = y;
}
