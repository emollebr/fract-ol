/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emollebr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 17:01:42 by emollebr          #+#    #+#             */
/*   Updated: 2023/04/03 17:01:44 by emollebr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <mlx.h>
# include "my_lib.h"

# define WIDTH 1000
# define HEIGHT 1000
# define MAX_ITERATIONS 100

# define MIN_REAL -2.0
# define MAX_REAL 1.0
# define MIN_IMAG -1.5
# define MAX_IMAG 1.5

typedef struct s_complex
{
	float	re;
	float	im;
}		t_complex;

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_len;
	int		endian;
}			t_data;

typedef struct s_vars
{
	void		*mlx;
	void		*mlx_win;
	t_data		image;
	t_complex	julia;
	t_complex	pos;
	float		scale;
	float		x_scaled;
	float		y_scaled;
	int			fractal;
}			t_vars;

t_data	create_new_image(t_vars *mlx);
void	my_mlx_pixel_put(t_data *data, int x, int y, float color);
void	fill_vars(t_vars *mlx);

void	scale_coords(int x, int y, t_vars *mlx);
void	burning_ship_pixel(int x0, int y0, t_data img, t_vars *mlx);
void	julia_pixel(int x0, int y0, t_data img, t_vars *mlx);
void	mandelbrot_pixel(int x0, int y0, t_data img, t_vars *mlx);
int		generate_image(t_vars *mlx);

int		destroy(t_vars *mlx);
int		key_hook(int keycode, t_vars *mlx);
int		fract_mouse_hook(int keycode, int x, int y, t_vars *mlx);
int		set_rgb(int r, int g, int b);
float	get_color(int i);

int		ft_isfloat(char *c);
void	arg_handling(int ac, char **av, t_vars *mlx);
void	printmsg(t_vars *mlx);
void	julia_vars(t_vars *mlx, char **av);
void	frac_con(t_vars *mlx, char **av);

#endif
