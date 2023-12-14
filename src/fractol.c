/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 12:42:58 by ldulling          #+#    #+#             */
/*   Updated: 2023/12/14 19:39:13 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	main(int argc, char *argv[])
{
	t_mlx	mlx;

	if (!parse_arguments(argc, argv, &mlx.data))
	{
		print_manual();
		return (ARG_ERROR);
	}
	init(&mlx);
	mlx_hook(mlx.win, KeyPress, KeyPressMask, key_handling, &mlx);
	mlx_hook(mlx.win, DestroyNotify, NoEventMask, clean_exit, &mlx);
	mlx_hook(mlx.win, ButtonPress, ButtonPressMask, mouse_handling, &mlx.data);
	if (mlx.data.fractal == MANDELBROT)
		mlx_loop_hook(mlx.xvar, render_mandelbrot, &mlx);
	else if (mlx.data.fractal == JULIA)
		mlx_loop_hook(mlx.xvar, render_julia, &mlx);
	else if (mlx.data.fractal == MULTIBROT)
		mlx_loop_hook(mlx.xvar, render_multibrot, &mlx);
	else if (mlx.data.fractal == MULTIJULIA)
		mlx_loop_hook(mlx.xvar, render_multijulia, &mlx);
	else if (mlx.data.fractal == BARNSLEYFERN)
		mlx_loop_hook(mlx.xvar, render_barnsleyfern, &mlx);
	mlx_loop(mlx.xvar);
}
