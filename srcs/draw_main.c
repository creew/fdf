/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 15:14:34 by eklompus          #+#    #+#             */
/*   Updated: 2019/10/13 15:14:35 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		draw_if_in_rect(t_fdf *fdf, t_img_param *img, t_point *p1, t_point *p2)
{
	if ((p1->x >= 0 && p1->x < fdf->wnd_width && p1->y >= 0 && p1->y < fdf->wnd_height) ||
		(p2->x >= 0 && p2->x < fdf->wnd_width && p2->y >= 0 && p2->y < fdf->wnd_height))
	{
		if (fdf->woo)
			draw_woo(img, p1, p2);
		else
			draw_line(img, p1, p2);
	}
}

static void	draw_lines(t_fdf *fdf, t_img_param *img)
{
	int		i;
	int		j;
	t_point	*point;

	point = fdf->mapout;
	i = -1;
	while (++i < fdf->map_height)
	{
		j = -1;
		while (++j < fdf->map_width)
		{
			if (i != (fdf->map_height - 1))
				draw_if_in_rect(fdf, img, point, point + fdf->map_width);
			if (j != (fdf->map_width - 1))
				draw_if_in_rect(fdf, img, point, point + 1);
			point++;
		}
	}
}

void		redraw_image(t_fdf *fdf)
{
	t_img_param		img;

	img.height = MAIN_HEIGHT;
	img.width = MAIN_WIDTH;
	img.data = mlx_get_data_addr(fdf->main_image, &img.bits_per_pixel,
		&img.sizeline, &img.endian);
	if (img.data)
	{
		fill_color(&img, BLACK_COLOR);
		do_transformations(fdf);
		draw_lines(fdf, &img);
	}
}

void		print_text(t_fdf *fdf)
{
	char	buf[64];

	ft_sprintf(buf, "scale: %d%%", (int)(fdf->scale * 100));
	mlx_string_put(fdf->mlx_ptr, fdf->wnd_ptr, 20, 0, WHITE_COLOR, buf);
	ft_sprintf(buf, "z scale: %d%%", (int)(fdf->z_scale * 100));
	mlx_string_put(fdf->mlx_ptr, fdf->wnd_ptr, 20, 17, WHITE_COLOR, buf);
	ft_sprintf(buf, "x angle: %d degree", get_x_offset(fdf) % 360);
	mlx_string_put(fdf->mlx_ptr, fdf->wnd_ptr, 180, 0, WHITE_COLOR, buf);
	ft_sprintf(buf, "y angle: %d degree", get_y_offset(fdf) % 360);
	mlx_string_put(fdf->mlx_ptr, fdf->wnd_ptr, 180, 17, WHITE_COLOR, buf);
	ft_sprintf(buf, "z angle: %d degree", get_z_offset(fdf) % 360);
	mlx_string_put(fdf->mlx_ptr, fdf->wnd_ptr, 400, 0, WHITE_COLOR, buf);
	ft_sprintf(buf, "drawline algo: %s", fdf->woo ? "Wu" : "Bresenham");
	mlx_string_put(fdf->mlx_ptr, fdf->wnd_ptr, 400, 17, WHITE_COLOR, buf);
}

int			redraw_main_screen(t_fdf *fdf)
{
	mlx_clear_window(fdf->mlx_ptr, fdf->wnd_ptr);
	if (fdf->upper_border)
		mlx_put_image_to_window(fdf->mlx_ptr, fdf->wnd_ptr,
			fdf->upper_border, 0, 0);
	if (fdf->bottom_border)
		mlx_put_image_to_window(fdf->mlx_ptr, fdf->wnd_ptr,
			fdf->bottom_border, 0, BB_YPOS);
	if (fdf->main_image)
		mlx_put_image_to_window(fdf->mlx_ptr, fdf->wnd_ptr,
			fdf->main_image, 0, MAIN_YPOS);
	print_text(fdf);
	return (RET_OK);
}
