/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_hook.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 08:19:49 by eklompus          #+#    #+#             */
/*   Updated: 2019/10/15 08:19:50 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int			button_pressed(int button, int x, int y, void *param)
{
	t_fdf *fdf;

	fdf = (t_fdf *)param;
	if (x >= 0 && y >= 0 && x < fdf->wnd_width && y < fdf->wnd_height)
		set_key_pressed(&fdf->mouse_keys, button, x, y);
	if (button == 4)
	{
		fdf->scale += 0.2;
		redraw_image(fdf);
	}
	else if (button == 5)
	{
		fdf->scale -= 0.2;
		redraw_image(fdf);
	}
	redraw_main_screen(fdf);
	return (0);
}

int			button_released(int button, int x, int y, void *param)
{
	t_fdf	*fdf;
	int		diffx;
	int		diffy;

	fdf = (t_fdf *)param;
	set_key_released(&fdf->mouse_keys, button, x, y);
	if (x >= 0 && y >= 0 && x < fdf->wnd_width && y < fdf->wnd_height)
	{
		if (button == 1)
		{
			get_key_diff(&fdf->mouse_keys, 1, &diffx, &diffy);
			add_rotate(fdf, diffy / 10, diffy / 10, diffx / 10);
			set_rotate_add(fdf, 0, 0, 0);
		}
		else if (button == 2)
		{
			get_key_diff(&fdf->mouse_keys, 2, &diffx, &diffy);
			add_shift(fdf, diffx, diffy);
			set_shift_add(fdf, 0, 0);
		}
		redraw_image(fdf);
	}
	redraw_main_screen(fdf);
	return (0);
}

int			mouse_move(int x, int y, void *param)
{
	t_fdf	*fdf;
	int		diffx;
	int		diffy;

	fdf = (t_fdf *)param;
	if (x >= 0 && y >= 0 && x < fdf->wnd_width && y < fdf->wnd_height)
	{
		set_current_xy(&fdf->mouse_keys, x, y);
		if (is_key_pressed(&fdf->mouse_keys, 1))
		{
			get_key_diff(&fdf->mouse_keys, 1, &diffx, &diffy);
			set_rotate_add(fdf, diffy / 10, diffy / 10, diffx / 10);
			redraw_image(fdf);
		}
		if (is_key_pressed(&fdf->mouse_keys, 2))
		{
			get_key_diff(&fdf->mouse_keys, 2, &diffx, &diffy);
			set_shift_add(fdf, diffx, diffy);
			redraw_image(fdf);
		}
	}
	redraw_main_screen(fdf);
	return (0);
}
