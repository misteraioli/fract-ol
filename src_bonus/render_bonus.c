/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niperez <niperez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 11:22:22 by niperez           #+#    #+#             */
/*   Updated: 2024/08/16 17:46:43 by niperez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol_bonus.h"

static double	ft_abs(double val)
{
	if (val > 0)
		return (val);
	else
		return (-val);
}

static t_complex	abs_complex(t_complex z)
{
	t_complex	result;

	result.x = ft_abs(z.x);
	result.y = ft_abs(z.y);
	return (result);
}

static void	select_fractal(t_complex *z, t_complex *c, t_fractal *fractal)
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
	select_fractal(&z, &c, fractal);
	i = 0;
	while (i < fractal->nb_iter)
	{
		if (!ft_strcmp(fractal->name, "burning_ship"))
			z = abs_complex(z);
		z = sum_complex(square_complex(z), c);
		if ((z.x * z.x) + (z.y * z.y) > fractal->esc_value)
		{
			color = color_grad(i, BLACK, fractal->color, fractal->nb_iter);
			*(unsigned int *)(fractal->img.pixels_ptr + pixel_pos) = color;
			return ;
		}
		i++;
	}
	*(unsigned int *)(fractal->img.pixels_ptr + pixel_pos) = BLACK;
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
	mlx_put_image_to_window(fractal->mlx, fractal->mlx_window,
		fractal->img.ptr, 0, 0);
}
