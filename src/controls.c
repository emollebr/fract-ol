/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emollebr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 11:57:47 by emollebr          #+#    #+#             */
/*   Updated: 2023/05/16 11:57:49 by emollebr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	set_rgb(int r, int g, int b)
{
	return (*(int *)(unsigned char [3]){r, g, b});
}

float	get_color(int i)
{
	int	mapping [16];

	if (i == MAX_ITERATIONS)
		return (000000);
	else
	{
		mapping[0] = set_rgb(66, 30, 15);
		mapping[1] = set_rgb(25, 7, 26);
		mapping[2] = set_rgb(9, 1, 47);
		mapping[3] = set_rgb(4, 4, 73);
		mapping[4] = set_rgb(0, 7, 100);
		mapping[5] = set_rgb(12, 44, 138);
		mapping[6] = set_rgb(24, 82, 177);
		mapping[7] = set_rgb(57, 125, 209);
		mapping[8] = set_rgb(134, 181, 229);
		mapping[9] = set_rgb(211, 236, 248);
		mapping[10] = set_rgb(241, 233, 191);
		mapping[11] = set_rgb(248, 201, 95);
		mapping[12] = set_rgb(255, 170, 0);
		mapping[13] = set_rgb(204, 128, 0);
		mapping[14] = set_rgb(153, 87, 0);
		mapping[15] = set_rgb(106, 52, 3);
	}
	return (mapping[i % 16]);
}

int	destroy(t_vars *mlx)
{
	/*
	mlx_destroy_image(mlx->mlx, mlx->image.img);
	mlx_destroy_window(mlx->mlx, mlx->mlx_win);
	free((void *)mlx);
	exit(0);
	*/
	mlx_loop_end(mlx->mlx);
	return (0);
}

int	key_hook(int keycode, t_vars *mlx)
{
	if (keycode == 65307)
		destroy(mlx);
	if (keycode == 65361)
		mlx->pos.re -= 100;
	if (keycode == 65363)
		mlx->pos.re += 100;
	if (keycode == 65362)
		mlx->pos.im -= 100;
	if (keycode == 65364)
		mlx->pos.im += 100;
	if (keycode > 97 && keycode < 110)
		fill_vars(mlx);
	if (keycode == 109)
		mlx->fractal = 1;
	if (keycode == 106)
		mlx->fractal = 2;
	if (keycode == 98)
		mlx->fractal = 3;
	mlx_destroy_image(mlx->mlx, mlx->image.img);
	mlx->image = create_new_image(mlx);
	generate_image(mlx);
	mlx_put_image_to_window(mlx->mlx, mlx->mlx_win, mlx->image.img, 0, 0);
	return (0);
}

int	fract_mouse_hook(int keycode, int x, int y, t_vars *mlx)
{
	mlx_destroy_image(mlx->mlx, mlx->image.img);
	mlx->image = create_new_image(mlx);
	if (keycode == 4)
	{
		mlx->scale = mlx->scale * 1.10;
		mlx->pos.re += mlx->pos.re / mlx->scale;
		mlx->pos.im += mlx->pos.im / mlx-> scale;
	}
	else if (keycode == 5)
	{
		mlx->scale = mlx->scale * 0.90;
		mlx->pos.re -= mlx->pos.re * mlx->scale;
		mlx->pos.im -= mlx->pos.im * mlx-> scale;
	}
	if (keycode == 1 || keycode == 3)
	{
		mlx->julia.re = (x + mlx->pos.re) * (MAX_REAL - MIN_REAL);
		mlx->julia.re = mlx->julia.re / ((WIDTH - 1) * mlx->scale) + MIN_REAL;
		mlx->julia.im = (y + mlx->pos.im) * (MAX_IMAG - MIN_IMAG);
		mlx->julia.im = mlx->julia.im / ((HEIGHT - 1) * mlx->scale) + MIN_IMAG;
	}
	generate_image(mlx);
	mlx_put_image_to_window(mlx->mlx, mlx->mlx_win, mlx->image.img, 0, 0);
	return (0);
}
