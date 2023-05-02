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
# define MAX_ITERATIONS 100

# define MIN_REAL -2.0
# define MAX_REAL 1.0
# define MIN_IMAG -1.5
# define MAX_IMAG 1.5

typedef struct		s_complex
{
	float			re;
	float			im;
}					t_complex;

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
	t_complex	min;
	t_complex	max;
	t_complex	pos;
	float	scale;
	int8_t	color[4];
}			t_vars;

#endif
