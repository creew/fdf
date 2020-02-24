/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_woo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 09:44:45 by eklompus          #+#    #+#             */
/*   Updated: 2019/10/17 09:44:46 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		tpoint_copy(t_point *dst, t_point *src)
{
	ft_memcpy(dst, src, sizeof(*src));
}

void		swap_int(int *a, int *b)
{
	int		c;

	c = *a;
	*a = *b;
	*b = c;
}

static void	draw_point_st(t_img_param *img, int st, t_point *p, double intens)
{
	unsigned int color;

	color = ((t_uint)(((p->color >> 16) & 0xFF) * intens) << 16) +
		((t_uint)(((p->color >> 8) & 0xFF) * intens) << 8) +
		((t_uint)(((p->color) & 0xFF) * intens));
	if (st)
		set_point(img, p->y, p->x, (int)color);
	else
		set_point(img, p->x, p->y, (int)color);
}

static void	process_woo(t_img_param *img, t_point *p1, t_point *p2, int st)
{
	t_point		lp;
	double		dx;
	double		dy;
	double		gradient;
	double		y;

	dx = p2->x - p1->x;
	dy = p2->y - p1->y;
	gradient = dy / dx;
	y = p1->y + gradient;
	lp.x = p1->x + 1;
	while (lp.x <= (p2->x - 1))
	{
		lp.color = get_color(p1->color, p2->color, p2->x - p1->x - 2,
			lp.x - p1->x - 1);
		lp.y = (int)y;
		draw_point_st(img, st, &lp, 1 - (y - (int)y));
		lp.y = (int)y + 1;
		draw_point_st(img, st, &lp, y - (int)y);
		y += gradient;
		lp.x++;
	}
}

void		draw_woo(t_img_param *img, t_point *p1, t_point *p2)
{
	int			st;
	t_point		lp1;
	t_point		lp2;

	st = ft_abs(p2->y - p1->y) > ft_abs(p2->x - p1->x);
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
		swap_int(&lp1.color, &lp2.color);
	}
	draw_point_st(img, st, &lp1, 1);
	draw_point_st(img, st, &lp2, 1);
	process_woo(img, &lp1, &lp2, st);
}
