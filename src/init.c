/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niperez <niperez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 11:20:09 by niperez           #+#    #+#             */
/*   Updated: 2024/10/23 16:40:32 by niperez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	init_data(char **argv, t_fractal *fractal)
{
	fractal->name = argv[1];
	if (!ft_strcmp(fractal->name, "julia"))
	{
		fractal->julia.x = ft_atod(argv[2]);
		fractal->julia.y = ft_atod(argv[3]);
	}
	fractal->esc_value = 4;
	fractal->nb_iter = 16;
	fractal->zoom = 1.0;
	fractal->color = WHITE;
}

static int	init_mlx(t_fractal *fractal)
{
	fractal->mlx = mlx_init();
	if (fractal->mlx == NULL)
		return (1);
	fractal->mlx_window = mlx_new_window(fractal->mlx,
			WIDTH, HEIGHT, fractal->name);
	if (fractal->mlx_window == NULL)
	{
		free(fractal->mlx);
		return (1);
	}
	fractal->img.ptr = mlx_new_image(fractal->mlx, WIDTH, HEIGHT);
	if (fractal->img.ptr == NULL)
	{
		mlx_destroy_display(fractal->mlx);
		free(fractal->mlx);
		return (1);
	}
	fractal->img.pixels_ptr = mlx_get_data_addr(fractal->img.ptr,
			&fractal->img.bpp, &fractal->img.size_line, &fractal->img.endian);
	return (0);
}

static void	init_events(t_fractal *fractal)
{
	mlx_hook(fractal->mlx_window,
		KeyPress, KeyPressMask, key_handler, fractal);
	mlx_hook(fractal->mlx_window,
		ButtonPress, ButtonPressMask, mouse_handler, fractal);
	mlx_hook(fractal->mlx_window,
		DestroyNotify, StructureNotifyMask, close_handler, fractal);
}

void	init_fractal(char **argv, t_fractal *fractal)
{
	init_data(argv, fractal);
	if (init_mlx(fractal))
	{
		ft_putstr_fd("Error malloc", 2);
		exit(1);
	}
	init_events(fractal);
}
