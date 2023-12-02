#include <mlx.h>
#include <stdlib.h>
#include <X11/X.h>
#include <X11/keysym.h>

#define WIN_WIDTH 1280
#define WIN_HEIGHT 720
#define MLX_ERROR 1

/* Not needed */
#include <stdio.h>

typedef struct	s_mlx
{
	void	*xvar;
	void	*win;
	void	*img;
	char	*data;
	int		bits_per_pixel;
	int		size_line;
	int		endian;
	int		color;
}				t_mlx;

int	clean_exit(t_mlx *mlx, int error)
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

int	key_handling(int keysymbol, t_mlx *mlx)
{
	if (keysymbol == XK_Escape)
		clean_exit(mlx, 0);
	return (0);
}

void	img_pixel_put(t_mlx *mlx, int x, int y, int color)
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

void	draw_square(t_mlx *mlx, int color)
{
	//int	color;
	int	x;
	int	y;

	//color = 0X00FF0000;
	y = 5;
	while (y < 720)
	{
		x = 5;
		while (x < 1005)
			img_pixel_put(mlx, x++, y, color);
		y++;
	}
	// while (y < 105)
	// 	img_pixel_put(mlx, x, y++, color);
	// while (x < 105)
	// 	img_pixel_put(mlx, x++, y, color);
	// while (y > 5)
	// 	img_pixel_put(mlx, x, y--, color);
	// while (x > 5)
	// 	img_pixel_put(mlx, x--, y, color);
}

int	render(t_mlx *mlx)
{
	mlx->color = (mlx->color + 0X00000055) % 0X00DDDDDD;
	printf("%#.8x\n", mlx->color);
	draw_square(mlx, mlx->color);
	//mlx_do_sync(mlx->xvar);
	mlx_put_image_to_window(mlx->xvar, mlx->win, mlx->img, 0, 0);
	return (0);
}

int	main(void)
{
	t_mlx	mlx;

	/* Initialization */
	mlx.xvar = mlx_init();
	if (!mlx.xvar)
		clean_exit(&mlx, MLX_ERROR);
	mlx.win = mlx_new_window(mlx.xvar, WIN_WIDTH, WIN_HEIGHT, "Testing!");
	if (!mlx.win)
		clean_exit(&mlx, MLX_ERROR);
	mlx.img = mlx_new_image(mlx.xvar, WIN_WIDTH, WIN_HEIGHT);
	if (!mlx.img)
		clean_exit(&mlx, MLX_ERROR);
	mlx.data = mlx_get_data_addr(mlx.img, &mlx.bits_per_pixel, &mlx.size_line, &mlx.endian);

	/* Draw */
	//draw_square(&mlx);
	mlx.color = 0X00000000;

	/* Key Events */
	mlx_hook(mlx.win, KeyPress, KeyPressMask, key_handling, &mlx);
	mlx_hook(mlx.win, DestroyNotify, NoEventMask, clean_exit, &mlx);

	mlx_loop_hook(mlx.xvar, render, &mlx);
	mlx_loop(mlx.xvar);
}