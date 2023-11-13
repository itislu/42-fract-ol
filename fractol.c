#include "fractol.h"

int clean_exit(t_mlx *mlx, int error)
{
	if (mlx->win)
		mlx_destroy_window(mlx->xvar, mlx->win);
	if (mlx->img)
		mlx_destroy_image(mlx->xvar, mlx->img);
	mlx_destroy_display(mlx->xvar);
	free(mlx->xvar);
	if (!error)
		exit(0);
	else
		exit(MLX_ERROR);
}

int key_handling(int keysymbol, t_mlx *mlx)
{
	if (keysymbol == XK_Escape)
		clean_exit(mlx, 0);
	return (0);
}

int zoom(int button, int x, int y, t_mlx *mlx)
{
	double	mouse_x_percent;
	double	mouse_y_percent;
	double	x_range;
	double	y_range;

	if (button == Button4)
	{
		mlx->zoom_factor = 0.95;
	}
	else if (button == Button5)
	{
		mlx->zoom_factor = 1.05;
	}
	if (button == Button4 || button == Button5)
	{
		mouse_x_percent = (double)x / WINDOW_WIDTH;
		mouse_y_percent = (double)y / WINDOW_HEIGHT;

		x_range = mlx->x_max - mlx->x_min;
		y_range = mlx->y_max - mlx->y_min;

		mlx->x_min = mlx->x_min + x_range * (1 - mlx->zoom_factor) * mouse_x_percent;
		mlx->x_max = mlx->x_min + x_range * mlx->zoom_factor;

		mlx->y_min = mlx->y_min + y_range * (1 - mlx->zoom_factor) * mouse_y_percent;
		mlx->y_max = mlx->y_min + y_range * mlx->zoom_factor;

		mlx->redraw_needed = 1;
	}

	return (0);
}

void img_pixel_put(t_mlx *mlx, int x, int y, int color)
{
	char	*pixel;
	int		i;
	int		next_byte;

	pixel = mlx->data + (y * mlx->size_line + x * (mlx->bits_per_pixel / 8));
	if (mlx->endian)
	{
		i = mlx->bits_per_pixel;
		next_byte = -8;
	}
	else
	{
		i = 0;
		next_byte = 8;
	}
	while (i != mlx->bits_per_pixel)
	{
		*pixel++ = (color >> i) & 0XFF;
		i += next_byte;
	}
}

void draw_mandelbrot(t_mlx *mlx, int max_iteration)
{
	int			iteration;
	int			color;
	int			i;
	int			j;
	t_complex	c;		// Possibly use math.h for this
	t_complex	z;
	t_complex	z_temp;

	i = 0;
	while (i < WINDOW_HEIGHT)
	{
		j = 0;
		while (j < WINDOW_WIDTH)
		{
			// Map pixel coordinates to complex plane coordinates
			c.real = mlx->x_min + (mlx->x_max - mlx->x_min) * j / (WINDOW_WIDTH - 1.0);
			c.imag = mlx->y_min + (mlx->y_max - mlx->y_min) * i / (WINDOW_HEIGHT - 1.0);
			z.real = 0;
			z.imag = 0;

			iteration = 0;
			while (z.real * z.real + z.imag * z.imag <= 4.0 && iteration < max_iteration)
			{
				z_temp.real = z.real * z.real - z.imag * z.imag + c.real;
				z_temp.imag = 2.0 * z.real * z.imag + c.imag;
				z = z_temp;
				iteration++;
			}

			// Map the number of iterations to a color (adjust as needed)
			if (iteration == max_iteration)
				color = 0;
			else if (iteration < max_iteration / 3)
				color = (iteration << 16);
			else if (iteration < max_iteration / 3 * 2)
				color = (iteration << 8);
			else if (iteration < max_iteration)
				color = (iteration << 0);

			img_pixel_put(mlx, j, i, color * 50);

			j++;
		}
		i++;
	}
}

void draw_julia(t_mlx *mlx, int max_iteration, double escape_radius)
{
	int			iteration;
	int			color;
	int			i;
	int			j;
	t_complex	c;
	t_complex	z;
	t_complex	z_temp;

	i = 0;
	while (i < WINDOW_HEIGHT)
	{
		j = 0;
		while (j < WINDOW_WIDTH)
		{
			// Map pixel coordinates to complex plane coordinates
			c.real = -0.79; //mlx->mouse_x;		// should fluctuate between [-2,2]
			c.imag = 0.23; //mlx->mouse_y;		// should fluctuate between [-2,2]
			z.real = mlx->x_min + (mlx->x_max - mlx->x_min) * j / (WINDOW_WIDTH - 1.0);
			z.imag = mlx->y_min + (mlx->y_max - mlx->y_min) * i / (WINDOW_HEIGHT - 1.0);

			iteration = 0;
			while (z.real * z.real + z.imag * z.imag < escape_radius * escape_radius && iteration < max_iteration)
			{
				z_temp.real = z.real * z.real - z.imag * z.imag + c.real;
				z_temp.imag = 2.0 * z.real * z.imag + c.imag;
				z = z_temp;
				iteration++;
			}

			// Map the number of iterations to a color (adjust as needed)
			if (iteration == max_iteration)
				color = 0;
			else if (iteration < max_iteration / 3)
				color = (iteration << 16);
			else if (iteration < max_iteration / 3 * 2)
				color = (iteration << 8);
			else if (iteration < max_iteration)
				color = (iteration << 0);

			img_pixel_put(mlx, j, i, color * 50);

			j++;
		}
		i++;
	}
}

int render_mandelbrot(t_mlx *mlx)
{
	if (mlx->redraw_needed)
	{
		draw_mandelbrot(mlx, 0x110);
		mlx_put_image_to_window(mlx->xvar, mlx->win, mlx->img, 0, 0);
		mlx->redraw_needed = 0;
	}
	return (0);
}

int render_julia(t_mlx *mlx)
{
	if (mlx->redraw_needed)
	{
		draw_julia(mlx, 0x110, 2.0);
		mlx_put_image_to_window(mlx->xvar, mlx->win, mlx->img, 0, 0);
		mlx->redraw_needed = 0;
	}
	return (0);
}

int	check_arguments(int argc, char *argv[])
{
	if (argc < 2)
	{
		return (0);
	}
	else if (ft_strcmp(argv[1], "mandelbrot") != 0 || ft_strcmp(argv[1], "julia") != 0)
	{
		return (1);
	}
	return (0);
}

int main(int argc, char *argv[])
{
	t_mlx mlx;

	mlx.zoom_factor = 1;
	mlx.x_min = -2.0;
	mlx.x_max = 1.0;
	mlx.y_min = -1.5;
	mlx.y_max = 1.5;
	mlx.redraw_needed = 1;

	/* Arguments Check */
	if (!check_arguments(argc, argv))
		return (ARG_ERROR);

	/* MLX Initialization */
	mlx.xvar = mlx_init();
	if (!mlx.xvar)
		clean_exit(&mlx, MLX_ERROR);
	mlx.win = mlx_new_window(mlx.xvar, WINDOW_WIDTH, WINDOW_HEIGHT, "Mandelbrot Set");
	if (!mlx.win)
		clean_exit(&mlx, MLX_ERROR);
	mlx.img = mlx_new_image(mlx.xvar, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!mlx.img)
		clean_exit(&mlx, MLX_ERROR);
	mlx.data = mlx_get_data_addr(mlx.img, &mlx.bits_per_pixel, &mlx.size_line, &mlx.endian);

	/* Key Events */
	mlx_hook(mlx.win, KeyPress, KeyPressMask, key_handling, &mlx);
	mlx_hook(mlx.win, DestroyNotify, NoEventMask, clean_exit, &mlx);
	mlx_hook(mlx.win, ButtonPress, ButtonPressMask, zoom, &mlx);

	/* Loop render */
	if (ft_strcmp(argv[1], "mandelbrot") == 0)
		mlx_loop_hook(mlx.xvar, render_mandelbrot, &mlx);
	else if (ft_strcmp(argv[1], "julia") == 0)
		mlx_loop_hook(mlx.xvar, render_julia, &mlx);
	mlx_loop(mlx.xvar);

	return 0;
}