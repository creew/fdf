/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_hooks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 13:41:51 by eklompus          #+#    #+#             */
/*   Updated: 2019/10/17 13:41:52 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int				expose_hook(void *param)
{
	t_fdf *fdf;

	fdf = (t_fdf *)param;
	redraw_main_screen(fdf);
	return (0);
}

int				close_notify(void *param)
{
	t_fdf *fdf;

	fdf = (t_fdf *)param;
	destroy_all_exit(fdf);
	return (0);
}

static void		set_name(char *dst, size_t size, char *src)
{
	int		len;

	ft_strcpy(dst, "File - \"");
	len = ft_strlen(dst);
	ft_strncpy(dst + len, src, size - len - 2);
	len = ft_strlen(dst);
	dst[len++] = '\"';
	dst[len] = '\0';
}

int				set_hooks(t_fdf *fdf, char *filename)
{
	char	buf[128];

	set_name(buf, sizeof(buf), filename);
	if (fdf->mlx_ptr)
	{
		fdf->wnd_ptr = mlx_new_window(fdf->mlx_ptr, fdf->wnd_width,
			fdf->wnd_height, buf);
		if (fdf->wnd_ptr)
		{
			mlx_hook(fdf->wnd_ptr, KEYPRESS, KEYPRESSMASK, key_hook, fdf);
			mlx_hook(fdf->wnd_ptr, EXPOSE, EXPOSUREMASK, expose_hook, fdf);
			mlx_hook(fdf->wnd_ptr, MOTIONNOTIFY, POINTERMOTIONMASK,
				mouse_move, fdf);
			mlx_hook(fdf->wnd_ptr, DESTROYNOTIFY, 0, close_notify, fdf);
			mlx_hook(fdf->wnd_ptr, BUTTONPRESS, BUTTONPRESSMASK,
				button_pressed, fdf);
			mlx_hook(fdf->wnd_ptr, BUTTONRELEASE, BUTTONRELEASEMASK,
				button_released, fdf);
			mlx_do_key_autorepeaton(fdf->mlx_ptr);
			mlx_loop(fdf->mlx_ptr);
		}
	}
	return (RET_OK);
}
