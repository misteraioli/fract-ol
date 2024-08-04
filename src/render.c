/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niperez <niperez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 11:22:22 by niperez           #+#    #+#             */
/*   Updated: 2024/08/04 12:15:39 by niperez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	mandel_vs_julia(t_complex *z, t_complex *c, t_fractal *fractal)
{
	if (!ft_strcmp(fractal->name, "julia"))
	{
		c->x = fractal->julia.x;
		c->y = fractal->julia.y;
	}
	else
	{
		c->x = z->x;
		c->y = z->y;
	}
}

static void	handle_pixel(int x, int y, t_fractal *fractal)
{
	t_complex	z;
	t_complex	c;
	int			i;
	int			color;
	int			pixel_pos;

	pixel_pos = (y * fractal->img.size_line) + (x * (fractal->img.bpp / 8));
	z.x = map(x, -2, +2, WIDTH) * fractal->zoom + fractal->shift_x;
	z.y = map(y, +2, -2, HEIGHT) * fractal->zoom + fractal->shift_y;
	mandel_vs_julia(&z, &c, fractal);
	i = 0;
	while (i < fractal->nb_iter)
	{
		z = sum_complex(square_complex(z), c);
		if ((z.x * z.x) + (z.y * z.y) > fractal->esc_value)
		{
			color = map(i, BLACK, WHITE, fractal->nb_iter);
			*(unsigned int *)(fractal->img.pixels_ptr + pixel_pos) = color;
			return ;
		}
		i++;
	}
	*(unsigned int *)(fractal->img.pixels_ptr + pixel_pos) = WHITE;
}

void	fractal_render(t_fractal *fractal)
{
	int	x;
	int	y;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			handle_pixel(x, y, fractal);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(fractal->mlx, fractal->mlx_window, fractal->img.ptr, 0, 0);
}
