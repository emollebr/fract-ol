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

#ifndef _FRACTOL_H_
# define _FRACTOL_H_

# include <mlx.h>
# include "libft.h"
# include "printf.h"

# define WIDTH 1000
# define HEIGHT 1000
# define MAX_ITERATIONS 1000

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_len;
	int		endian;
}				t_data;

typedef struct	s_vars {
	void	*mlx;
	void	*mlx_win;
	t_data	image;
	t_data	new_image;
}			t_vars;

void	mandelbrot_pixel(int x0, int y0, t_data img);

t_data	create_new_image(t_vars mlx);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
int	destroy(t_vars mlx, t_data img);
int	key_hook(int keycode, void *vars);
int	mouse_hook(int keycode, t_vars *mlx2);
int	main(void);

#endif
