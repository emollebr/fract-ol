/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emollebr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 12:00:13 by emollebr          #+#    #+#             */
/*   Updated: 2023/05/16 12:00:16 by emollebr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	ft_isfloat(char *c)
{
	int	i;

	i = 0;
	while (c[i] != '\0')
	{
		if ((c[i] >= '0' && c[i] <= '9') || c[i] == '-' || c[i] == '.')
			i++;
		else
			return (0);
	}
	return (1);
}

void	printmsg(t_vars *mlx)
{
	int		fd1;
	char	*s;

	s = "init";
	fd1 = open("src/msg.txt", O_RDONLY);
	if (fd1 < 0)
		exit(0);
	while (s)
	{
		s = get_next_line(fd1);
		if (s != NULL)
			ft_printf("%s", s);
		free(s);
	}
	close(fd1);
	free((void *)mlx);
	exit(0);
	return ;
}

void	julia_vars(t_vars *mlx, char **av)
{
	if (mlx->fractal == 2)
	{
		if (ft_isfloat(av[2]) == 1 && ft_isfloat(av[3]) == 1)
		{
			mlx->julia.re = ft_atof(av[2]);
			mlx->julia.im = ft_atof(av[3]);
		}
		else
		{
			ft_printf("Invalid c-values!\n");
			free((void *)mlx);
			exit(0);
		}
	}
	else
	{
		ft_printf("Only Julia takes more arguments. Try again.\n");
		free((void *)mlx);
		exit(0);
	}
}

void	frac_con(t_vars *mlx, char **av)
{
	if (ft_strncmp(av[1], "m\0", 2) == 0)
		mlx->fractal = 1;
	else if (ft_strncmp(av[1], "j\0", 2) == 0)
		mlx->fractal = 2;
	else if (ft_strncmp(av[1], "b\0", 2) == 0)
		mlx->fractal = 3;
	else
	{
		ft_printf("Invalid fractal!\n");
		printmsg(mlx);
	}
}

void	arg_handling(int ac, char **av, t_vars *mlx)
{
	if (ac == 1)
		printmsg(mlx);
	if (ac > 4)
	{
		ft_printf("Too many arguments!\n");
		free((void *)mlx);
		exit(0);
	}
	if (ac > 1)
		frac_con(mlx, av);
	if (ac == 3)
	{
		ft_printf("Please type two c-values for julia...\n");
		free((void *)mlx);
		exit(0);
	}
	if (ac == 4)
		julia_vars(mlx, av);
}
