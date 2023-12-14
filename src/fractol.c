/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 12:42:58 by ldulling          #+#    #+#             */
/*   Updated: 2023/12/14 12:01:53 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	else if (mlx.data.set == MULTIBROT)
		mlx_loop_hook(mlx.xvar, render_multibrot, &mlx);
	else if (mlx.data.set == MULTIJULIA)
		mlx_loop_hook(mlx.xvar, render_multijulia, &mlx);
	mlx_loop(mlx.xvar);

	return 0;
}
