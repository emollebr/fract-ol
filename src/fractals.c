/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractals.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emollebr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 11:45:12 by emollebr          #+#    #+#             */
/*   Updated: 2023/05/16 11:45:19 by emollebr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	scale_coords(int x, int y, t_vars *mlx)
{
	mlx->x_scaled = (x + mlx->pos.re) * (MAX_REAL - MIN_REAL);
	mlx->x_scaled = mlx->x_scaled / ((WIDTH - 1) * mlx->scale) + MIN_REAL;
	mlx->y_scaled = (y + mlx->pos.im) * (MAX_IMAG - MIN_IMAG);
	mlx->y_scaled = mlx->y_scaled / ((HEIGHT - 1) * mlx->scale) + MIN_IMAG;
}

void	burning_ship_pixel(int x0, int y0, t_data img, t_vars *mlx)
{
	int		i;
	float	x;
	float	y;
	float	x_temp;

	scale_coords(x0, y0, mlx);
	i = 0;
	x = 0;
	y = 0;
	x_temp = 0;
	while ((x * x + y * y <= 4) && (i < MAX_ITERATIONS))
	{
		x_temp = (x * x) - (y * y) + mlx->x_scaled;
		y = (2 * x * y);
		if (y < 0)
			y = -y;
		y = y + mlx->y_scaled;
		x = x_temp;
		i++;
	}
	my_mlx_pixel_put(&img, x0, y0, get_color(i));
}

void	julia_pixel(int x0, int y0, t_data img, t_vars *mlx)
{
	int		i;
	float	x;
	float	y;
	float	x_temp;

	scale_coords(x0, y0, mlx);
	x = mlx->x_scaled;
	y = mlx->y_scaled;
	i = 0;
	x_temp = 0;
	while ((x * x + y * y <= 4) && (i < MAX_ITERATIONS))
	{
		x_temp = (x * x) - (y * y) + mlx->julia.re;
		y = (2 * x * y) + mlx->julia.im;
		x = x_temp;
		i++;
	}
	my_mlx_pixel_put(&img, x0, y0, get_color(i));
}

void	mandelbrot_pixel(int x0, int y0, t_data img, t_vars *mlx)
{
	int		i;
	float	x;
	float	y;
	float	x_temp;

	scale_coords(x0, y0, mlx);
	i = 0;
	x = 0;
	y = 0;
	x_temp = 0;
	while ((x * x + y * y <= 4) && (i < MAX_ITERATIONS))
	{
		x_temp = (x * x) - (y * y) + mlx->x_scaled;
		y = (2 * x * y) + mlx->y_scaled;
		x = x_temp;
		i++;
	}
	my_mlx_pixel_put(&img, x0, y0, get_color(i));
}

int	generate_image(t_vars *mlx)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (y < HEIGHT)
	{
		while (x < WIDTH)
		{
			if (mlx->fractal == 1)
				mandelbrot_pixel(x, y, mlx->image, mlx);
			if (mlx->fractal == 2)
				julia_pixel(x, y, mlx->image, mlx);
			if (mlx->fractal == 3)
				burning_ship_pixel(x, y, mlx->image, mlx);
			x++;
		}
		x = 0;
		y++;
	}
	return (0);
}
