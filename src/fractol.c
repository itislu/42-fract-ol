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

int zoom(int button, int x, int y, t_data *data)
{
	double	mouse_x_percent;
	double	mouse_y_percent;
	double	x_range;
	double	y_range;

	if (button == Button4)
	{
		data->zoom_factor = 0.95;
	}
	else if (button == Button5)
	{
		data->zoom_factor = 1.05;
	}
	if (button == Button4 || button == Button5)
	{
		mouse_x_percent = (double)x / WINDOW_WIDTH;
		mouse_y_percent = (double)y / WINDOW_HEIGHT;

		x_range = data->x_max - data->x_min;
		y_range = data->y_max - data->y_min;

		data->x_min = data->x_min + x_range * (1 - data->zoom_factor) * mouse_x_percent;
		data->x_max = data->x_min + x_range * data->zoom_factor;

		data->y_min = data->y_min + y_range * (1 - data->zoom_factor) * mouse_y_percent;
		data->y_max = data->y_min + y_range * data->zoom_factor;

		data->redraw_needed = 1;
	}

	return (0);
}

void img_pixel_put(t_data *data, int x, int y, int color)
{
	char	*pixel;
	int		i;
	int		next_byte;

	pixel = data->data + (y * data->size_line + x * (data->bits_per_pixel / 8));
	if (data->endian)
	{
		i = data->bits_per_pixel;
		next_byte = -8;
	}
	else
	{
		i = 0;
		next_byte = 8;
	}
	while (i != data->bits_per_pixel)
	{
		*pixel++ = (color >> i) & 0XFF;
		i += next_byte;
	}
}

void draw_mandelbrot(t_data *data, int max_iteration)
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
			c.real = data->x_min + (data->x_max - data->x_min) * j / (WINDOW_WIDTH - 1.0);
			c.imag = data->y_min + (data->y_max - data->y_min) * i / (WINDOW_HEIGHT - 1.0);
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

			img_pixel_put(data, j, i, color * 50);

			j++;
		}
		i++;
	}
}

void draw_julia(t_data *data, int max_iteration, double escape_radius)
{
	int			iteration;
	int			color;
	int			i;
	int			j;
	t_complex	z;		// Might be more efficient if it's in the data struct and
	t_complex	z_temp;	// doesn't need to be created every call.

	i = 0;
	while (i < WINDOW_HEIGHT)
	{
		j = 0;
		while (j < WINDOW_WIDTH)
		{
			// Map pixel coordinates to complex plane coordinates
			//data->c_default.real = 0.355; //data->mouse_x;		// should fluctuate between [-2,2]
			//data->c_default.imag = 0.355; //data->mouse_y;		// should fluctuate between [-2,2]
			z.real = data->x_min + (data->x_max - data->x_min) * j / (WINDOW_WIDTH - 1.0);
			z.imag = data->y_min + (data->y_max - data->y_min) * i / (WINDOW_HEIGHT - 1.0);

			iteration = 0;
			while (z.real * z.real + z.imag * z.imag < escape_radius * escape_radius && iteration < max_iteration)
			{
				z_temp.real = z.real * z.real - z.imag * z.imag + data->c_default.real;
				z_temp.imag = 2.0 * z.real * z.imag + data->c_default.imag;
				z = z_temp;
				iteration++;
			}

			// Map the number of iterations to a color (adjust as needed)
			if (iteration == max_iteration)
				color = 0;
			// else if (iteration < max_iteration / 3)
			// 	color = (iteration << 16);
			// else if (iteration < max_iteration / 3 * 2)
			// 	color = (iteration << 8);
			// else if (iteration < max_iteration)
			// 	color = (iteration << 0);
			else
			{
				double abs_z = z.real * z.real + z.imag * z.imag;
				color = iteration + 1 - log(log(abs_z)) / log(2.0);
			}

			img_pixel_put(data, j, i, (color * 0x00110055) % 0x00CCCCCC);

			j++;
		}
		i++;
	}
}

int render_mandelbrot(t_mlx *mlx)
{
	if (mlx->data.redraw_needed)
	{
		draw_mandelbrot(&mlx->data, 272);
		mlx_put_image_to_window(mlx->xvar, mlx->win, mlx->img, 0, 0);
		mlx->data.redraw_needed = 0;
	}
	return (0);
}

int render_julia(t_mlx *mlx)
{
	if (mlx->data.redraw_needed)
	{
		draw_julia(&mlx->data, 128, 2.0);
		mlx_put_image_to_window(mlx->xvar, mlx->win, mlx->img, 0, 0);
		mlx->data.redraw_needed = 0;
	}
	return (0);
}

int	valid_float_arg(char *arg)
{
	size_t	len_arg;
	size_t	len_valid;

	len_arg = ft_strlen(arg);
	len_valid = 0;
	while (ft_isspace(arg[len_valid]))
		len_valid++;
	if (arg[len_valid] == '-' || arg[len_valid] == '+')
		len_valid++;
	while (ft_isdigit(arg[len_valid]))
		len_valid++;
	if (arg[len_valid] == '.')
	{
		len_valid++;
		while (ft_isdigit(arg[len_valid]))
			len_valid++;
	}
	if (len_valid == len_arg)
		return (1);
	return (0);
}

int	parse_julia_values(int argc, char *argv[], t_complex *c_default)
{
	if (argc == 3)
	{
		if (valid_float_arg(argv[2]))
		{
			c_default->real = ft_atof(argv[2]);
			c_default->imag = c_default->real;
			return (1);
		}
	}
	else
	{
		if (valid_float_arg(argv[2]) && valid_float_arg(argv[3]))
		{
			c_default->real = ft_atof(argv[2]);
			c_default->imag = ft_atof(argv[3]);
			return (1);
		}
	}
	return (0);
}

int	parse_arguments(int argc, char *argv[], t_data *data)
{
	if (argc < 2)
		return (0);
	if (ft_strmatches_any(argv[1], 4, "m", "M", "mandelbrot", "Mandelbrot"))
	{
		data->set = MANDELBROT;
		data->c_default.real = (data->x_max - data->x_min) / (WINDOW_WIDTH - 1.0);	// -1.0 really needed?
		data->c_default.imag = (data->y_max - data->y_min) / (WINDOW_HEIGHT - 1.0);
		if (argc > 2)
			ft_printf("%s\n", "No need for additional arguments ;)");
		return (1);
	}
	if (ft_strmatches_any(argv[1], 4, "j", "J", "julia", "Julia"))
	{
		data->set = JULIA;
		if (argc == 2)
		{
			data->c_default.real = -0.79;
			data->c_default.imag = 0.23;
		}
		else if (!parse_julia_values(argc, argv, &data->c_default))
			return (0);
		return (1);
	}
	return (0);
}

int main(int argc, char *argv[])
{
	t_mlx	mlx;

	/* Set default view */
	mlx.data.zoom_factor = 1;
	mlx.data.x_min = -2.0;
	mlx.data.x_max = 1.0;
	mlx.data.y_min = -1.5;
	mlx.data.y_max = 1.5;
	mlx.data.redraw_needed = 1;

	/* Print out how to use the program */

	/* Arguments Check */
	if (!parse_arguments(argc, argv, &mlx.data))
		return (ARG_ERROR);	// Potentially "display a list of available parameters"

	/* MLX Initialization */
	mlx.xvar = mlx_init();
	if (!mlx.xvar)
		clean_exit(&mlx, MLX_ERROR);
	mlx.win = mlx_new_window(mlx.xvar, WINDOW_WIDTH, WINDOW_HEIGHT, "Fractol");
	if (!mlx.win)
		clean_exit(&mlx, MLX_ERROR);
	mlx.img = mlx_new_image(mlx.xvar, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!mlx.img)
		clean_exit(&mlx, MLX_ERROR);
	mlx.data.data = mlx_get_data_addr(mlx.img, &mlx.data.bits_per_pixel, &mlx.data.size_line, &mlx.data.endian);

	/* Key Events */
	mlx_hook(mlx.win, KeyPress, KeyPressMask, key_handling, &mlx);
	mlx_hook(mlx.win, DestroyNotify, NoEventMask, clean_exit, &mlx);
	mlx_hook(mlx.win, ButtonPress, ButtonPressMask, zoom, &mlx.data);

	/* Loop render */
	if (mlx.data.set == MANDELBROT)
		mlx_loop_hook(mlx.xvar, render_mandelbrot, &mlx);
	else if (mlx.data.set == JULIA)
		mlx_loop_hook(mlx.xvar, render_julia, &mlx);
	mlx_loop(mlx.xvar);

	return 0;
}
