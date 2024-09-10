/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niperez <niperez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 11:17:55 by niperez           #+#    #+#             */
/*   Updated: 2024/08/16 17:48:44 by niperez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol_bonus.h"

static int	shift_color(int color)
{
	if (color == WHITE)
		return (RED);
	else if (color == RED)
		return (GREEN);
	else if (color == GREEN)
		return (BLUE);
	else
		return (WHITE);
}

int	close_handler(t_fractal *fractal)
{
	mlx_destroy_image(fractal->mlx, fractal->img.ptr);
	mlx_destroy_window(fractal->mlx, fractal->mlx_window);
	mlx_destroy_display(fractal->mlx);
	free(fractal->mlx);
	exit(0);
}

int	key_handler(int keysym, t_fractal *fractal)
{
	if (keysym == XK_Escape)
		close_handler(fractal);
	else if (keysym == XK_o)
		fractal->nb_iter += 4;
	else if (keysym == XK_i)
		fractal->nb_iter -= 4;
	else if (keysym == XK_c)
		fractal->color = shift_color(fractal->color);
	else if (keysym == XK_Left)
		fractal->shift_x -= (0.5 * fractal->zoom);
	else if (keysym == XK_Right)
		fractal->shift_x += (0.5 * fractal->zoom);
	else if (keysym == XK_Up)
		fractal->shift_y += (0.5 * fractal->zoom);
	else if (keysym == XK_Down)
		fractal->shift_y -= (0.5 * fractal->zoom);
	fractal_render(fractal);
	return (0);
}

int	mouse_handler(int button, int x, int y, t_fractal *fractal)
{
	double	old_zoom;

	old_zoom = fractal->zoom;
	if (button == Button5)
		fractal->zoom *= 0.95;
	else if (button == Button4)
		fractal->zoom *= 1.05;
	fractal->shift_x += map(x, -2.0, 2.0, WIDTH) * (old_zoom - fractal->zoom);
	fractal->shift_y += map(y, 2.0, -2.0, HEIGHT) * (old_zoom - fractal->zoom);
	fractal_render(fractal);
	return (0);
}
