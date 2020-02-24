/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 12:45:49 by eklompus          #+#    #+#             */
/*   Updated: 2019/10/13 12:45:56 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <fcntl.h>
#include <unistd.h>

static int		calc_str_width(char *str, t_point *tp)
{
	int		count;
	char	*end;
	long	val;

	count = 0;
	val = ft_strtol(str, &end, 0);
	while (str != end)
	{
		if (tp)
		{
			tp[count].z = (int)val;
			tp[count].color = BLUE_COLOR;
		}
		str = end;
		while (*str != '\0' && *str != ' ')
		{
			val = ft_strtol(str + 1, &end, 0);
			if (tp)
				tp[count].color = (int)val;
			str = end;
		}
		val = ft_strtol(str, &end, 0);
		count++;
	}
	return (count);
}

static t_point	*realloc_map(t_fdf *fdf)
{
	t_point		*data;
	size_t		old_size;
	size_t		new_size;

	old_size = fdf->map_height * fdf->map_width * sizeof(t_point);
	new_size = (fdf->map_height + 1) * fdf->map_width * sizeof(t_point);
	data = (t_point *)ft_memrealloc(fdf->srcmap, old_size, new_size);
	return (data);
}

int				read_file(char *name, t_fdf *fdf)
{
	char	*str;
	int		width;
	int		isfirst;
	int		fd;

	isfirst = 1;
	fd = open(name, O_RDONLY);
	if (fd == -1)
		return (ERR_CAN_T_OPEN_FILE);
	while (get_next_line(fd, &str) == 1)
	{
		width = calc_str_width(str, 0);
		if (isfirst && !(isfirst = 0))
			fdf->map_width = width;
		if (width != fdf->map_width)
			return (ERR_NOT_EQUAL_WIDTH);
		if ((fdf->srcmap = realloc_map(fdf)) == NULL)
			return (ERR_ENOMEM);
		calc_str_width(str, fdf->srcmap + fdf->map_height * fdf->map_width);
		fdf->map_height++;
		ft_strdel(&str);
	}
	close(fd);
	return (RET_OK);
}
