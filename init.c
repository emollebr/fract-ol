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

/*int	get_pallette(int i)
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
}*/

int	destroy(t_vars mlx, t_data img)
{
	// close program
	mlx_destroy_image(mlx.mlx, img.img);
	mlx_destroy_window(mlx.mlx, mlx.mlx_win);
	exit(0);
}

int	key_hook(int keycode, void *vars)
{
	(void)vars;
	if (keycode == 65307)
		exit(0);
	if (keycode == 2)
		//cy increase with 0.2
	if (keycode == 3)
		//cy decrease with 0.2
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
		mlx.image = create_new_image(mlx);
		mlx_put_image_to_window(mlx.mlx, mlx.mlx_win, mlx.new_image.img, 0, 0);
	}
	if (keycode == 5)
	{
		mlx_destroy_image(mlx.mlx, mlx.image.img);
		mlx.image = create_new_image(mlx);
		mlx_put_image_to_window(mlx.mlx, mlx.mlx_win, mlx.new_image.img, 0, 0);
	}
	return (0);
}

int	main(void)
{
	t_vars	mlx;
	int	z;

	if(args[1] == "mandelbrot")
		z = 0;
	if (args[1] == "julia")
		z = 1;

	mlx.mlx = mlx_init();
	mlx.mlx_win = mlx_new_window(mlx.mlx, WIDTH, HEIGHT, "fract-ol");
	mlx.image = create_new_image(mlx);
	mandelbrot(mlx, z);
	mlx_put_image_to_window(mlx.mlx, mlx.mlx_win, mlx.image.img, 0, 0);
	mlx_hook(mlx.mlx_win, 17, 0, &destroy, NULL);
	mlx_key_hook(mlx.mlx_win, &key_hook, NULL);
	mlx_mouse_hook(mlx.mlx_win, &mouse_hook, &mlx);
	mlx_loop(mlx.mlx);
}