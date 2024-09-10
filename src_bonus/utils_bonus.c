/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niperez <niperez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 11:25:22 by niperez           #+#    #+#             */
/*   Updated: 2024/08/16 17:47:45 by niperez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol_bonus.h"

double	ft_atod(const char *str)
{
	int		signe;
	double	nb;
	double	factor;

	signe = 1;
	nb = 0;
	factor = 1;
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
	{
		factor *= 0.1;
		nb += (*str++ - '0') * factor;
	}
	nb *= signe;
	return (nb);
}

double	map(double val, double new_min, double new_max, double old_max)
{
	return (new_min + (new_max - new_min) * val / old_max);
}

int	color_grad(double val, int min_col, int max_col, double old_max)
{
	int	r;
	int	g;
	int	b;

	r = (int)map(val, (min_col >> 16) & 0xFF, (max_col >> 16) & 0xFF, old_max);
	g = (int)map(val, (min_col >> 8) & 0xFF, (max_col >> 8) & 0xFF, old_max);
	b = (int)map(val, min_col & 0xFF, max_col & 0xFF, old_max);
	return ((r << 16) | (g << 8) | b);
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
