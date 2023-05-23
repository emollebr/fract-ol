/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emollebr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 11:45:36 by emollebr          #+#    #+#             */
/*   Updated: 2023/05/16 11:45:40 by emollebr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

t_data	create_new_image(t_vars *mlx)
{
	t_data	img;

	img.img = mlx_new_image(mlx->mlx, WIDTH, HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel,
			&img.line_len, &img.endian);
	return (img);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, float color)
{
	char	*dst;

	dst = data->addr + (y * data->line_len + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	fill_vars(t_vars *mlx)
{
	mlx->scale = 1;
	mlx->pos.re = 1;
	mlx->pos.im = 1;
	if (!mlx->julia.re && !mlx->julia.im)
	{
		mlx->julia.re = -0.4;
		mlx->julia.im = 0.6;
	}
}

int	main(int ac, char **av)
{
	t_vars	*mlx;
	int		x;
	int		y;

	x = 0;
	y = 0;
	mlx = malloc(sizeof(t_vars) * 1);
	if (!mlx)
		exit(0);
	arg_handling(ac, av, mlx);
	mlx->mlx = mlx_init();
	if (mlx->mlx)
	{
		mlx->mlx_win = mlx_new_window(mlx->mlx, WIDTH, HEIGHT, "fract-ol");
		mlx->image = create_new_image(mlx);
		fill_vars(mlx);
		generate_image(mlx);
		mlx_put_image_to_window(mlx->mlx, mlx->mlx_win, mlx->image.img, 0, 0);
		mlx_hook(mlx->mlx_win, 17, 0, &destroy, mlx);
		mlx_mouse_hook(mlx->mlx_win, &fract_mouse_hook, mlx);
		mlx_key_hook(mlx->mlx_win, &key_hook, mlx);
		mlx_loop(mlx->mlx);
		mlx_destroy_image(mlx->mlx, mlx->image.img);
		mlx_destroy_window(mlx->mlx, mlx->mlx_win);
		free(mlx->mlx);
	}		
	free((void *)mlx);
}
