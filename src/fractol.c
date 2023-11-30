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
		data->zoom_factor = 0.95;
	else if (button == Button5)
		data->zoom_factor = 1.05;
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

	pixel = data->addr + (y * data->size_line + x * (data->bits_per_pixel / 8));
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

int	color(int iter, int max_iter, t_complex z)
{
	double	abs_z;
	int		color;

	if (iter == max_iter)
		color = 0;
	else
	{
		abs_z = z.real * z.real + z.imag * z.imag;
		color = iter + 1 - log(log(abs_z)) / log(2.0);
	}
	color = (color * 0x00330055) % 0x00CCCCCC;
	return (color);
}

t_complex	calculate_next_iteration(t_complex z, t_complex c)
{
	t_complex	new_z;

	new_z.real = z.real * z.real - z.imag * z.imag + c.real;
	new_z.imag = 2.0 * z.real * z.imag + c.imag;
	return (new_z);
}

void	map_complexplane_to_window(t_complex *cmpt, t_data *data, t_coord coord)
{
	cmpt->real = data->x_min + (data->x_max - data->x_min) * coord.x
			/ (WINDOW_WIDTH - 1.0);
	cmpt->imag = data->y_min + (data->y_max - data->y_min) * coord.y
			/ (WINDOW_HEIGHT - 1.0);
}

void draw_mandelbrot(t_data *data, int max_iter)
{
	int			iter;
	t_coord		coord;
	t_complex	c;
	t_complex	z;

	coord.y = 0;
	while (coord.y < WINDOW_HEIGHT)
	{
		coord.x = 0;
		while (coord.x < WINDOW_WIDTH)
		{
			map_complexplane_to_window(&c, data, coord);
			z.real = 0;
			z.imag = 0;
			iter = -1;
			while (z.real * z.real + z.imag * z.imag <= 4.0
				&& ++iter < max_iter)
				z = calculate_next_iteration(z, c);
			img_pixel_put(data, coord.x, coord.y, color(iter, max_iter, z));
			coord.x++;
		}
		coord.y++;
	}
}

void draw_julia(t_data *data, int max_iter, double esc_radius)
{
	int			iter;
	t_coord		coord;
	t_complex	z;

	coord.y = 0;
	while (coord.y < WINDOW_HEIGHT)
	{
		coord.x = 0;
		while (coord.x < WINDOW_WIDTH)
		{
			map_complexplane_to_window(&z, data, coord);
			iter = -1;
			while (z.real * z.real + z.imag * z.imag < esc_radius * esc_radius
				&& ++iter < max_iter)
				z = calculate_next_iteration(z, data->c_default);
			img_pixel_put(data, coord.x, coord.y, color(iter, max_iter, z));
			coord.x++;
		}
		coord.y++;
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

	//TODO: For centering Julia I need to adjust still.
	//TODO: Also check if mine is reversed...
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
	mlx.data.addr = mlx_get_data_addr(mlx.img, &mlx.data.bits_per_pixel, &mlx.data.size_line, &mlx.data.endian);

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
