/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niperez <niperez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 11:25:22 by niperez           #+#    #+#             */
/*   Updated: 2024/08/02 16:14:41 by niperez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	msg_error(void)
{
	ft_putstr_fd("Error: Invalid arguments\n", 2);
	ft_putstr_fd("Please use: ./fractol mandelbrot or\n", 2);
	ft_putstr_fd("Please use: ./fractol julia <x_num> <y_num>\n", 2);
	exit(EXIT_FAILURE);
}

double	ft_atod(const char *str)
{
	int		signe;
	double	nb;

	signe = 1;
	nb = 0;
	while ((9 <= *str && *str <= 13) || *str == ' ')
		str++;
	if (*str == '-')
		signe *= -1;
	if (*str == '-' || *str == '+')
		str++;
	while (ft_isdigit(*str))
		nb = (10 * nb) + (*str++ - '0');
	if (*str == '.')
		str++;
	while (ft_isdigit(*str))
		nb += (*str++ - '0') / 10;
	nb *= signe;
	return (nb);
}

double	map(double val, double new_min, double new_max, double old_max)
{
	return (new_min + (new_max - new_min) * val / old_max);
}

t_complex	sum_complex(t_complex z1, t_complex z2)
{
	t_complex	result;

	result.x = z1.x + z2.x;
	result.y = z1.y + z2.y;
	return (result);
}

t_complex	square_complex(t_complex z)
{
	t_complex	result;

	result.x = (z.x * z.x) - (z.y * z.y);
	result.y = 2 * z.x * z.y;
	return (result);
}
