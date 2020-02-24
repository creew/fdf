/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_moves.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 13:22:20 by eklompus          #+#    #+#             */
/*   Updated: 2019/10/14 13:22:22 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		is_key_pressed(t_mousekeys *keys, int button)
{
	if (button == 1)
		return (keys->but1_pressed);
	else if (button == 2)
		return (keys->but2_pressed);
	return (0);
}

void	set_current_xy(t_mousekeys *keys, int x, int y)
{
	keys->cur_x = x;
	keys->cur_y = y;
}

void	set_key_pressed(t_mousekeys *keys, int button, int x, int y)
{
	if (button == 1)
	{
		keys->but1_pressed = 1;
		keys->press1_x = x;
		keys->press1_y = y;
	}
	else if (button == 2)
	{
		keys->but2_pressed = 1;
		keys->press2_x = x;
		keys->press2_y = y;
	}
	set_current_xy(keys, x, y);
}

void	set_key_released(t_mousekeys *keys, int button, int x, int y)
{
	if (button == 1)
	{
		keys->but1_pressed = 0;
	}
	else if (button == 2)
	{
		keys->but2_pressed = 0;
	}
	set_current_xy(keys, x, y);
}

void	get_key_diff(t_mousekeys *keys, int button, int *x, int *y)
{
	if (button == 1)
	{
		*x = keys->cur_x - keys->press1_x;
		*y = keys->cur_y - keys->press1_y;
	}
	else if (button == 2)
	{
		*x = keys->cur_x - keys->press2_x;
		*y = keys->cur_y - keys->press2_y;
	}
}
