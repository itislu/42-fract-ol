/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 11:59:52 by ldulling          #+#    #+#             */
/*   Updated: 2023/12/14 19:38:33 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	init(t_mlx *mlx)
{
	mlx->xvar = mlx_init();
	if (!mlx->xvar)
		clean_exit(mlx, MLX_ERROR);
	mlx->win = mlx_new_window(mlx->xvar, WIN_WIDTH, WIN_HEIGHT, "Fractol");
	if (!mlx->win)
		clean_exit(mlx, MLX_ERROR);
	mlx->img = mlx_new_image(mlx->xvar, WIN_WIDTH, WIN_HEIGHT);
	if (!mlx->img)
		clean_exit(mlx, MLX_ERROR);
	mlx->data.addr = mlx_get_data_addr(mlx->img, &mlx->data.bits_per_pixel,
			&mlx->data.size_line, &mlx->data.endian);
	//TODO: Also check if mine is reversed...
	default_view(mlx);
	mlx->data.redraw_needed = true;
	mlx->data.toggle.is_zoom_optimize = ZOOM_OPTIMIZE_ON_OFF_DEFAULT;
	mlx->data.toggle.zoom_optimize_factor = 1.0;
}

void	default_view(t_mlx *mlx)
{
	double	aspect_ratio;

	mlx->data.zoom_factor = 1;
	mlx->data.max_iter = MAX_ITERATIONS;
	aspect_ratio = (double) WIN_WIDTH / WIN_HEIGHT;
	if (aspect_ratio >= 1.0)
	{
		mlx->data.x_min = -INITIAL_VIEW * aspect_ratio;
		mlx->data.x_max = INITIAL_VIEW * aspect_ratio;
		mlx->data.y_min = -INITIAL_VIEW;
		mlx->data.y_max = INITIAL_VIEW;
	}
	else
	{
		mlx->data.x_min = -INITIAL_VIEW;
		mlx->data.x_max = INITIAL_VIEW;
		mlx->data.y_min = -INITIAL_VIEW / aspect_ratio;
		mlx->data.y_max = INITIAL_VIEW / aspect_ratio;
	}
}
