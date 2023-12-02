#include "fractol.h"

int main(int argc, char *argv[])
{
	t_mlx	mlx;

	/* Print out how to use the program */

	/* Arguments Check */
	if (!parse_arguments(argc, argv, &mlx.data))
		return (ARG_ERROR);	// Potentially "display a list of available parameters"

	/* MLX Initialization */
	init(&mlx);

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
