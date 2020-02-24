/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_images.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 15:20:40 by eklompus          #+#    #+#             */
/*   Updated: 2019/10/13 15:20:41 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	combine_color32(int r, int g, int b, int a)
{
	return ((int)(((a & 0xFFu) << 24u) | ((r & 0xFFu) << 16u) |
	((g & 0xFFu) << 8u) | (b & 0xFFu)));
}

void		fill_color(t_img_param *img, t_uint setcolor)
{
	char	*color;
	char	*data;
	int		count;
	int		col;

	data = img->data;
	count = -1;
	while (++count < img->height)
	{
		col = 0;
		while (col < img->sizeline)
		{
			color = data + col;
			*color = FT_32COLOR_GET_B(setcolor);
			*(color + 1) = FT_32COLOR_GET_G(setcolor);
			*(color + 2) = FT_32COLOR_GET_R(setcolor);
			*(color + 3) = FT_32COLOR_GET_A(setcolor);
			col += img->bits_per_pixel / 8;
		}
		data += img->sizeline;
	}
}

int			init_upper_border(t_fdf *fdf)
{
	t_img_param		img;

	img.height = UB_HEIGHT;
	img.width = UB_WIDTH;
	fdf->upper_border = mlx_new_image(fdf->mlx_ptr, img.width, img.height);
	if (fdf->upper_border)
	{
		img.data = mlx_get_data_addr(fdf->upper_border, &img.bits_per_pixel,
			&img.sizeline, &img.endian);
		if (img.data)
			fill_color(&img, combine_color32(255u, 0u, 0u, 10u));
	}
	return (RET_OK);
}

int			init_bottom_border(t_fdf *fdf)
{
	t_img_param		img;

	img.height = BB_HEIGHT;
	img.width = BB_WIDTH;
	fdf->bottom_border = mlx_new_image(fdf->mlx_ptr, img.width, img.height);
	if (fdf->bottom_border)
	{
		img.data = mlx_get_data_addr(fdf->bottom_border, &img.bits_per_pixel,
			&img.sizeline, &img.endian);
		if (img.data)
			fill_color(&img, combine_color32(0u, 255u, 0u, 10u));
	}
	return (RET_OK);
}

int			init_main_image(t_fdf *fdf)
{
	t_img_param		img;

	img.height = MAIN_HEIGHT;
	img.width = MAIN_WIDTH;
	fdf->main_image = mlx_new_image(fdf->mlx_ptr, img.width, img.height);
	if (fdf->main_image)
	{
		img.data = mlx_get_data_addr(fdf->main_image, &img.bits_per_pixel,
			&img.sizeline, &img.endian);
		if (img.data)
			fill_color(&img, combine_color32(0u, 0u, 0u, 0u));
	}
	return (RET_OK);
}
