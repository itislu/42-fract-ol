#include <mlx.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <X11/X.h>
#include <X11/keysym.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 800
#define MLX_ERROR 1

typedef struct s_mlx
{
	void	*xvar;
	void	*win;
	void	*img;
	char	*data;
	int		bits_per_pixel;
	int		size_line;
	int		endian;
	int		color;
} t_mlx;

typedef struct s_complex
{
	double	real;
	double	imag;
} t_complex;

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

void draw_mandelbrot(t_mlx *mlx, double x_min, double x_max, double y_min, double y_max, int max_iteration)
{
	int	width = WINDOW_WIDTH;
	int	height = WINDOW_HEIGHT;
	int	iteration;
	int	color;

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			// Map pixel coordinates to complex plane coordinates
			double x0 = x_min + (x_max - x_min) * j / (width - 1.0);
			double y0 = y_min + (y_max - y_min) * i / (height - 1.0);

			t_complex c = {x0, y0};
			t_complex z = {0, 0};

			iteration = 0;
			while (z.real * z.real + z.imag * z.imag <= 4.0 && iteration < max_iteration)
			{
				t_complex temp = {
					z.real * z.real - z.imag * z.imag + c.real,
					2.0 * z.real * z.imag + c.imag};
				z = temp;
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
		}
	}
}

int render(t_mlx *mlx)
{
	draw_mandelbrot(mlx, -2.0, 1.0, -1.5, 1.5, 0x1110);
	mlx_put_image_to_window(mlx->xvar, mlx->win, mlx->img, 0, 0);
	return (0);
}

int main(void)
{
	t_mlx mlx;

	/* Initialization */
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

	mlx_loop_hook(mlx.xvar, render, &mlx);
	mlx_loop(mlx.xvar);

	return 0;
}
