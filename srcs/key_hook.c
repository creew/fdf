/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 08:20:33 by eklompus          #+#    #+#             */
/*   Updated: 2019/10/15 08:20:33 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		set_mode(t_fdf *fdf, int mode)
{
	fdf->z_scale = 0.2;
	fdf->z_rotate = 0;
	fdf->x_rotate = 0;
	fdf->y_rotate = 0;
	fdf->parallel = 1;
	if (mode == 0)
		fdf->x_rotate = 270;
	if (mode == 1)
		fdf->y_rotate = 90;
	calc_optimal_size(fdf, 0);
}

static int	process_key3(t_fdf *fdf, int key)
{
	if (key == Z_KEY)
		add_rotate(fdf, 0, 0, -5);
	else if (key == A_KEY)
		add_rotate(fdf, 0, 0, 5);
	else if (key == S_KEY)
		add_rotate(fdf, 5, 0, 0);
	else if (key == X_KEY)
		add_rotate(fdf, -5, 0, 0);
	else if (key == D_KEY)
		add_rotate(fdf, 0, 5, 0);
	else if (key == C_KEY)
		add_rotate(fdf, 0, -5, 0);
	else
		return (0);
	return (1);
}

static int	process_key2(t_fdf *fdf, int key)
{
	if (key == ONE_KEY || key == ONE_NUM_KEY)
		set_mode(fdf, 0);
	else if (key == TWO_KEY || key == TWO_NUM_KEY)
		set_mode(fdf, 1);
	else if (key == THREE_KEY || key == THREE_NUM_KEY)
		set_mode(fdf, 2);
	else if (key == POINT_KEY || key == POINT_NUM_KEY)
		fdf->woo = !fdf->woo;
	else
		process_key3(fdf, key);
	return (1);
}

static int	process_key(t_fdf *fdf, int key)
{
	if (key == ESC_KEY)
		destroy_all_exit(fdf);
	else if (key == ZERO_NUM_KEY || key == ZERO_KEY)
	{
		fdf->parallel = 0;
		calc_optimal_size(fdf, 1);
	}
	else if (key == ARROW_LEFT_KEY)
		add_rotate(fdf, 0, 0, -5);
	else if (key == ARROW_RIGHT_KEY)
		add_rotate(fdf, 0, 0, 5);
	else if (key == ARROW_UP_KEY)
		fdf->z_scale += 0.1;
	else if (key == ARROW_DOWN_KEY)
		fdf->z_scale -= 0.1;
	else if (key == PLUS_KEY || key == PLUS_NUM_KEY)
		fdf->scale += 0.2;
	else if (key == MINUS_KEY || key == MINUS_NUM_KEY)
		fdf->scale -= 0.2;
	else
	{
		if (process_key2(fdf, key) == 0)
			return (0);
	}
	return (1);
}

int			key_hook(int key, void *param)
{
	t_fdf *fdf;

	fdf = (t_fdf *)param;
	if (process_key(fdf, key) == 0)
		return (0);
	redraw_image(fdf);
	redraw_main_screen(fdf);
	return (0);
}
