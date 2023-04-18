#include "fractol.h"

t_data	create_new_image(t_vars mlx)
{
	t_data	img;

	img.img = mlx_new_image(mlx.mlx, WIDTH, HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_len, &img.endian);
	return (img);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_len + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int	get_pallette(int i)
{
	if (i < 200)
		return(0X5D9BE5);
	if (i < 400)
		return(0XF15BB5);
	if (i < 600)
	return(0XFEE440);
	if (i < 800)
		return(0X00BBF9);
	else
		return(0X00F5D4);
}

void	mandelbrot_pixel(int x0, int y0, t_data img)
{
	int	i;
	int	max_i;
	float	x;
	float	y;
	float	x_temp;
	float x0_scaled;
	float y0_scaled;
	float	MIN_REAL = -2.0;
	float	MAX_REAL = 1.0;
	float	MIN_IMAG = -1.5;
	float	MAX_IMAG = 1.5;

	x0_scaled = x0 * (MAX_REAL - MIN_REAL) / (WIDTH - 1) + MIN_REAL;
	y0_scaled = y0 * (MAX_IMAG - MIN_IMAG) / (HEIGHT - 1) + MIN_IMAG;
	i = 0;
	max_i = 1000;
	x = 0;
	y = 0;
	x_temp = 0;
	while ((x * x + y * y <= 4) && (i < max_i))
	{
    	x_temp = (x * x) - (y * y) + x0_scaled;
		y = (2 * x * y) + y0_scaled;
		x = x_temp;
		i++;
	}
	if (i == max_i)
		my_mlx_pixel_put(&img, x0, y0, get_pallette(i));
	else
		my_mlx_pixel_put(&img, x0, y0, get_pallette(i));
}

int	destroy(t_vars mlx, t_data img)
{
	mlx_destroy_image(mlx.mlx, img.img);
	mlx_destroy_window(mlx.mlx, mlx.mlx_win);
	exit(0);
}

int	key_hook(int keycode, void *vars)
{
	(void)vars;
	if (keycode == 65307)
		exit(0);
	return(0);
}

int	mouse_hook(int keycode, t_vars *mlx2)
{
	t_vars mlx;
	
	mlx  = *mlx2;
	printf("%i\n", keycode);
	if (keycode == 4)
	{
		mlx_destroy_image(mlx.mlx, mlx.image.img);
		//mlx.image = create_new_image(mlx);
		//mlx_put_image_to_window(mlx.mlx, mlx.mlx_win, new_img.img, 0, 0);
	}
	if (keycode == 5)
	{
		mlx_destroy_image(mlx.mlx, mlx.image.img);
		//mlx.image = create_new_image(mlx);
		//mlx_put_image_to_window(mlx.mlx, mlx.mlx_win, new_img.img, 0, 0);
	}
	return (0);
}

int	main(void)
{
	t_vars	mlx;
	int		x;
	int		y;
	
	x = 0;
	y = 0;
	mlx.mlx = mlx_init();
	mlx.mlx_win = mlx_new_window(mlx.mlx, WIDTH, HEIGHT, "fract-ol");
	mlx.image = create_new_image(mlx);
	while (y < HEIGHT)
	{
		while (x < WIDTH)
		{
			mandelbrot_pixel(x, y, mlx.image);
			x++;
		}
		x = 0;
		y++;
	}
	mlx_put_image_to_window(mlx.mlx, mlx.mlx_win, mlx.image.img, 0, 0);
	mlx_hook(mlx.mlx_win, 17, 0, &destroy, NULL);
	mlx_key_hook(mlx.mlx_win, &key_hook, NULL);
	mlx_mouse_hook(mlx.mlx_win, &mouse_hook, &mlx);
	mlx_loop(mlx.mlx);
}