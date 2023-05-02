
#include "fractol.h"

t_data	create_new_image(t_vars *mlx)
{
	t_data	img;

	img.img = mlx_new_image(mlx->mlx, WIDTH, HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_len, &img.endian);
	return (img);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, float color)
{
	char	*dst;

	dst = data->addr + (y * data->line_len + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int	setRgb(int r, int g, int b)
{
	return (*(int *)(unsigned char [3]){r, g, b});
}

float	get_color(int i)
{
	int	x;
	int		mapping [16];

	if ( i == MAX_ITERATIONS)
		return(000000);
	else
	{
		x = i % 16;
		mapping[0] = setRgb(66, 30, 15);
   		mapping[1] = setRgb(25, 7, 26);
    	mapping[2] = setRgb(9, 1, 47);
    	mapping[3] = setRgb(4, 4, 73);
    	mapping[4] = setRgb(0, 7, 100);
    	mapping[5] = setRgb(12, 44, 138);
    	mapping[6] = setRgb(24, 82, 177);
    	mapping[7] = setRgb(57, 125, 209);
    	mapping[8] = setRgb(134, 181, 229);
    	mapping[9] = setRgb(211, 236, 248);
    	mapping[10] = setRgb(241, 233, 191);
    	mapping[11] = setRgb(248, 201, 95);
    	mapping[12] = setRgb(255, 170, 0);
    	mapping[13] = setRgb(204, 128, 0);
    	mapping[14] = setRgb(153, 87, 0);
    	mapping[15] = setRgb(106, 52, 3);
	}
	return (mapping[x]);
}

void	mandelbrot_pixel(int x0, int y0, t_data img, float scale, t_complex pos)
{
	int	i;
	float	x;
	float	y;
	float	x_temp;
	float	x_scaled;
	float	y_scaled;
	float	c;
	
	c = 
	x_scaled = (x0 + pos.re) * (MAX_REAL - MIN_REAL) / ((WIDTH - 1) * scale) + MIN_REAL;
	y_scaled = (y0 + pos.im) * (MAX_IMAG - MIN_IMAG) / ((HEIGHT - 1) * scale) + MIN_IMAG;
	i = 0;
	x = 0;
	y = 0;
	x_temp = 0;
	while ((x * x + y * y <= 4) && (i < MAX_ITERATIONS))
	{
    	x_temp = (x * x) - (y * y) + x_scaled;
		y = (2 * x * y) + y_scaled;
		x = x_temp;
		i++;
	}
	my_mlx_pixel_put(&img, x0, y0, get_color(i));
}

int	mandelbrot_image(t_vars *mlx)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (y < HEIGHT)
	{
		while (x < WIDTH)
		{
			mandelbrot_pixel(x, y, mlx->image, mlx->scale, mlx->pos);
			x++;
		}
		x = 0;
		y++;
	}
	return (0);
}

int	destroy(t_vars *mlx)
{
	mlx_destroy_image(mlx->mlx, mlx->image.img);
	mlx_destroy_window(mlx->mlx, mlx->mlx_win);
	exit(0);
}

int	key_hook(int keycode, t_vars *mlx)
{
	if (keycode == 65307)
		exit(0);
	if (keycode == 65361)
		mlx->pos.re -= 100;
	if (keycode == 65363)
		mlx->pos.re += 100;
	if (keycode == 65362)
		mlx->pos.im -= 100;
	if (keycode == 65364)
		mlx->pos.im += 100;
	mlx_destroy_image(mlx->mlx, mlx->image.img);
	mlx->image = create_new_image(mlx);
	mandelbrot_image(mlx);
	mlx_put_image_to_window(mlx->mlx, mlx->mlx_win,mlx->image.img, 0, 0);
	return(0);
}	

int	fract_mouse_hook(int keycode, int x, int y, t_vars *mlx)
{
	mlx_destroy_image(mlx->mlx, mlx->image.img);
	mlx->image = create_new_image(mlx);
	if (keycode == 4)
	{
		mlx->scale = mlx->scale * 1.15;
		mlx->pos.re += mlx->pos.re / mlx->scale;
		mlx->pos.im += mlx->pos.im / mlx-> scale;
	}
	else if (keycode == 5)
	{
		mlx->scale = mlx->scale * 0.85;
		mlx->pos.re -= mlx->pos.re * mlx->scale;
		mlx->pos.im -= mlx->pos.im * mlx-> scale;
	}
	printf("%i\n%i\n", x, y);
	mandelbrot_image(mlx);
	mlx_put_image_to_window(mlx->mlx, mlx->mlx_win,mlx->image.img, 0, 0);
	return (0);
}

/*t_complex	get_julia(t_vars *mlx, int num)
{
	t_complex	julia;

	julia = {0.26, 0.54};
	return(julia[num]);

}*/

void	fill_vars(t_vars *mlx)
{
	mlx->mlx = mlx_init();
	mlx->mlx_win = mlx_new_window(mlx->mlx, WIDTH, HEIGHT, "fract-ol");
	mlx->image = create_new_image(mlx);
	mlx->scale = 1;
	mlx->pos.re = 1;
	mlx->pos.im = 1;
	//mlx->julia = get_julia(0);
}

int	main(void)
{
	t_vars	*mlx;
	int		x;
	int		y;

	x = 0;
	y = 0;

	mlx = malloc(sizeof(t_vars) * 1);
	fill_vars(mlx);
	mandelbrot_image(mlx);
	mlx_put_image_to_window(mlx->mlx, mlx->mlx_win, mlx->image.img, 0, 0);
	mlx_hook(mlx->mlx_win, 17, 0, &destroy, mlx);
	mlx_mouse_hook(mlx->mlx_win, &fract_mouse_hook, mlx);
	mlx_key_hook(mlx->mlx_win, &key_hook, mlx);
	mlx_loop(mlx->mlx);
}