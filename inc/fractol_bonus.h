/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niperez <niperez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 11:08:23 by niperez           #+#    #+#             */
/*   Updated: 2024/08/16 17:46:26 by niperez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_BONUS_H
# define FRACTOL_BONUS_H

# include "../libft/inc/libft.h"
# include "../libft/inc/get_next_line.h"
# include "../libft/inc/ft_printf.h"
# include <math.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include "../minilibx-linux/mlx.h"

# define WIDTH	800
# define HEIGHT	800

# define BLACK	0x000000
# define WHITE	0xFFFFFF
# define RED	0xFF0000
# define GREEN	0x00FF00
# define BLUE	0x0000FF

typedef struct s_complex
{
	double	x;
	double	y;
}				t_complex;

typedef struct s_img
{
	void	*ptr;
	char	*pixels_ptr;
	int		bpp;
	int		size_line;
	int		endian;
}				t_img;

typedef struct s_fractal
{
	char		*name;
	t_complex	julia;

	double		esc_value;
	int			nb_iter;
	double		shift_x;
	double		shift_y;
	double		zoom;
	int			color;
	void		*mlx;
	void		*mlx_window;
	t_img		img;
}				t_fractal;

double		ft_atod(const char *str);
double		map(double val, double new_min, double new_max, double old_max);
int			color_grad(double val, int min_col, int max_col, double old_max);
t_complex	sum_complex(t_complex z1, t_complex z2);
t_complex	square_complex(t_complex z);

void		init_fractal(char **argv, t_fractal *fractal);
void		fractal_render(t_fractal *fractal);
int			key_handler(int keysym, t_fractal *fractal);
int			close_handler(t_fractal *fractal);
int			mouse_handler(int button, int x, int y, t_fractal *fractal);

#endif
