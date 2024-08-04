/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niperez <niperez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 11:08:23 by niperez           #+#    #+#             */
/*   Updated: 2024/08/04 12:09:13 by niperez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "../libft/inc/libft.h"
# include "../libft/inc/get_next_line.h"
# include "../libft/inc/ft_printf.h"
# include <math.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include "../minilibx-linux/mlx.h"

# define ERROR_MESSAGE	"Please enter \n\t\"./fractol mandelbrot\" or \n\t\"./fractol julia <value_1> <value_2>\"\n"

# define WIDTH	800
# define HEIGHT	900

# define BLACK	0x000000  // RGB(0, 0, 0)
# define WHITE	0xFFFFFF  // RGB(255, 255, 255)
# define RED	0xFF0000  // RGB(255, 0, 0)
# define GREEN	0x00FF00  // RGB(0, 255, 0)
# define BLUE	0x0000FF  // RGB(0, 0, 255)

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
	char	*name;
	t_complex	julia;

	double	esc_value;
	int		nb_iter;
	double	shift_x;
	double	shift_y;
	double	zoom;
	void	*mlx;
	void	*mlx_window;
	t_img	img;
}				t_fractal;

/*
 * PROTOTYPES
 * They are basically IOUs to the compiler
*/
//*** utils ***
double		ft_atod(const char *str);
double		map(double val, double new_min, double new_max, double old_max);
t_complex	sum_complex(t_complex z1, t_complex z2);
t_complex	square_complex(t_complex z);

//*** init ***
void	init_fractal(char **argv, t_fractal *fractal);

//*** render ***
void		fractal_render(t_fractal *fractal);

//*** hooks_events ***
int			key_handler(int keysym, t_fractal *fractal);

//*** clean_up ***
int			close_handler(t_fractal *fractal);
int			mouse_handler(int button, int x, int y, t_fractal *fractal);
int			julia_track(int x, int y, t_fractal *fractal);

#endif
