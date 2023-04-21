float	*get_complex_nums(int z)
{
	float	num[2];

	if (z == 0)
	{
		num[0] = 0;
		num[1] = 0;
	}
	else if (z == 1)
	{
		num[0] == −0.8;
		num[1] == 0.156;
	}
		return(num);
}

void	mandelbrot_pixel(float x, float y, float *c_num, t_data img)
{
	int	i;
	float	x_temp;

	x = x * (1.0 - -2.0) / (WIDTH - 1) - 2.0;
	y = y * (1.5 - -1.5) / (HEIGHT - 1) - 1.5;
	i = 0;
	x_temp = 0;
	while ((x * x + y * y <= 4) && (i < MAX_ITERATIONS))
	{
    	x_temp = (x * x) - (y * y) + c_num[0];
		y = (2 * x * y) + c_num[1];
		x = x_temp;
		i++;
	}
	if (i == MAX_ITERATIONS)
		my_mlx_pixel_put(&img, x, y, 0X000000);
	else
		my_mlx_pixel_put(&img, x, y, 0X000000 + i);
}

void mandelbrot(t_vars mlx, int z)
{
	int	x;
	int	y;
	float	*c_num;

	x = 0;
	y = 0;
	c_num = get_complex_nums(z);
	while (y < HEIGHT)
	{
		while (x < WIDTH)
		{
			mandelbrot_pixel(x, y, c_num, mlx.image);
			x++;
		}
		x = 0;
		y++;
	}

}


