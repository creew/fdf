/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eklompus <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 11:03:14 by eklompus          #+#    #+#             */
/*   Updated: 2019/10/11 11:03:15 by eklompus         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	print_usage(void)
{
	ft_putendl("Usage: program fdfmap");
	ft_putendl("   Use your mouse with pushed left button for rotate map,");
	ft_putendl("   or with pushed right button for moving map.");
	ft_putendl("   Scrolling mouse wheel for changing scale.");
	ft_putendl("");
	ft_putendl("Keyboard:");
	ft_putendl("   A/Z - increment/decrement Z angle.");
	ft_putendl("   S/X - increment/decrement X angle.");
	ft_putendl("   D/C - increment/decrement Y angle.");
	ft_putendl("   +/- - increment/decrement common scale.");
	ft_putendl("   up/down - increment/decrement z scale.");
	ft_putendl("   -> - rotate map right.");
	ft_putendl("   <- - rotate map left.");
	ft_putendl("   0 - set iso");
	ft_putendl("   . - toggle woo/bresenham.");
}

void	initfdf(t_fdf *fdf)
{
	bzero(fdf, sizeof(*fdf));
	fdf->wnd_width = WND_WIDTH;
	fdf->wnd_height = WND_HEIGHT;
	fdf->scale = 1;
	fdf->z_scale = 0.2;
}

void	destroy_all_exit(t_fdf *fdf)
{
	if (fdf->mlx_ptr && fdf->upper_border)
		mlx_destroy_image(fdf->mlx_ptr, fdf->upper_border);
	if (fdf->mlx_ptr && fdf->bottom_border)
		mlx_destroy_image(fdf->mlx_ptr, fdf->bottom_border);
	if (fdf->mlx_ptr && fdf->main_image)
		mlx_destroy_image(fdf->mlx_ptr, fdf->main_image);
	if (fdf->mlx_ptr && fdf->wnd_ptr)
		mlx_destroy_window(fdf->mlx_ptr, fdf->wnd_ptr);
	ft_memdel((void **)&fdf->srcmap);
	ft_memdel((void **)&fdf->mapout);
	exit(0);
}

void	process_file(t_fdf *fdf, char *name)
{
	int		ret;

	if ((ret = read_file(name, fdf)) != RET_OK)
	{
		if (ret == ERR_CAN_T_OPEN_FILE)
		{
			ft_putstr("Can't open file: ");
			ft_putendl(name);
		}
		else if (ret == ERR_NOT_EQUAL_WIDTH)
		{
			ft_putstr("Wrong file format file: ");
			ft_putendl(name);
		}
		else if (ret == ERR_ENOMEM)
			ft_putendl("Can't allocate memory");
		else
			ft_putendl("Unknown error");
		destroy_all_exit(fdf);
	}
}

int		main(int ac, char *av[])
{
	t_fdf	fdf;

	if (ac < 2)
	{
		print_usage();
		exit(0);
	}
	initfdf(&fdf);
	process_file(&fdf, av[1]);
	normalize_map(fdf.srcmap, fdf.map_width, fdf.map_height);
	fdf.mlx_ptr = mlx_init();
	fdf.mapout = malloc(sizeof(t_point) * fdf.map_width * fdf.map_height);
	init_upper_border(&fdf);
	init_bottom_border(&fdf);
	init_main_image(&fdf);
	calc_optimal_size(&fdf, 1);
	redraw_image(&fdf);
	set_hooks(&fdf, av[1]);
	return (0);
}
