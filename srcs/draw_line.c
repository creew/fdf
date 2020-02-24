/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 08:20:02 by eklompus          #+#    #+#             */
/*   Updated: 2019/10/15 08:20:03 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		set_point(t_img_param *img, int x, int y, int color)
{
	char *data;

	data = img->data;
	if (x >= 0 && y >= 0 && x < img->width && y < img->height)
	{
		data += y * img->sizeline;
		data += x * img->bits_per_pixel / 8;
		*data = FT_32COLOR_GET_B(color);
		*(data + 1) = FT_32COLOR_GET_G(color);
		*(data + 2) = FT_32COLOR_GET_R(color);
		*(data + 3) = FT_32COLOR_GET_A(color);
	}
}

int			get_color(int color1, int color2, int total, int step)
{
	t_uint	r;
	t_uint	g;
	t_uint	b;
	int		c1;
	int		c2;

	if (total != 0)
	{
		c1 = (color1 >> 16) & 0xFF;
		c2 = (color2 >> 16) & 0xFF;
		r = c1 + (c2 - c1) * step / total;
		c1 = (color1 >> 8) & 0xFF;
		c2 = (color2 >> 8) & 0xFF;
		g = c1 + (c2 - c1) * step / total;
		c1 = (color1) & 0xFF;
		c2 = (color2) & 0xFF;
		b = c1 + (c2 - c1) * step / total;
	}
	else
		return (color1);
	return ((int)((r & 0xFFu) << 16u | (g & 0xFFu) << 8u | (b & 0xFFu)));
}

static void	draw_point_st(t_img_param *img, int st, t_point *p)
{
	if (st & 1)
		set_point(img, p->y, p->x, p->color);
	else
		set_point(img, p->x, p->y, p->color);
}

static void	process_line(t_img_param *img, t_point *p1, t_point *p2, int st)
{
	t_point		lp;
	int			delta;
	int			len_x;
	int			len_y;

	len_x = p2->x - p1->x;
	len_y = ft_abs(p2->y - p1->y);
	delta = -len_x;
	lp.y = p1->y;
	lp.x = p1->x;
	while (lp.x <= p2->x)
	{
		lp.color = get_color(st & 2 ? p2->color : p1->color, st & 2 ?
			p1->color : p2->color, p2->x - p1->x, lp.x - p1->x);
		draw_point_st(img, st, &lp);
		delta += 2 * len_y;
		if (delta > 0)
		{
			delta -= 2 * len_x;
			lp.y += p2->y >= p1->y ? 1 : -1;
		}
		lp.x++;
	}
}

void		draw_line(t_img_param *img, t_point *p1, t_point *p2)
{
	int			st;
	t_point		lp1;
	t_point		lp2;

	st = ft_abs(p2->y - p1->y) > ft_abs(p2->x - p1->x) ? 1 : 0;
	tpoint_copy(&lp1, p1);
	tpoint_copy(&lp2, p2);
	if (st)
	{
		swap_int(&lp1.x, &lp1.y);
		swap_int(&lp2.x, &lp2.y);
	}
	if (lp1.x > lp2.x)
	{
		swap_int(&lp1.x, &lp2.x);
		swap_int(&lp1.y, &lp2.y);
		st |= 2;
	}
	process_line(img, &lp1, &lp2, st);
}
