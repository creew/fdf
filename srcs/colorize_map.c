/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colorize_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 17:44:09 by eklompus          #+#    #+#             */
/*   Updated: 2019/10/15 17:44:10 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		is_colorized(t_point *point, int size)
{
	int		i;
	int		color;

	if (size)
	{
		i = 0;
		color = point->color;
		point++;
		while (++i < size)
		{
			if (point->color != color)
				return (1);
			point++;
		}
	}
	return (0);
}

void	find_min_max(t_point *point, int size, int *minz, int *maxz)
{
	int		i;

	*minz = 0;
	*maxz = 0;
	if (size)
	{
		i = 0;
		*minz = point->z;
		*maxz = point->z;
		point++;
		while (++i < size)
		{
			if (point->z > *maxz)
				*maxz = point->z;
			if (point->z < *minz)
				*minz = point->z;
			point++;
		}
	}
}

void	colorise_map(t_point *point, int size)
{
	int		i;
	int		maxz;
	int		minz;
	int		middle;

	i = -1;
	find_min_max(point, size, &minz, &maxz);
	middle = (maxz + minz) / 2;
	while (++i < size)
	{
		if (point->z <= middle)
			point->color = get_color(GREEN_COLOR, BROWN_COLOR,
				middle - minz, point->z - minz);
		else
			point->color = get_color(BROWN_COLOR, WHITE_COLOR,
				maxz - middle, point->z - middle);
		point++;
	}
}

void	colorize_not(t_point *point, int size)
{
	if (!is_colorized(point, size))
		colorise_map(point, size);
}
