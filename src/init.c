/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 11:59:52 by ldulling          #+#    #+#             */
/*   Updated: 2023/12/02 12:32:40 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	init(t_mlx *mlx)
{
	mlx->xvar = mlx_init();
	if (!mlx->xvar)
		clean_exit(mlx, MLX_ERROR);
	mlx->win = mlx_new_window(mlx->xvar, WINDOW_WIDTH, WINDOW_HEIGHT, "Fractol");
	if (!mlx->win)
		clean_exit(mlx, MLX_ERROR);
	mlx->img = mlx_new_image(mlx->xvar, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!mlx->img)
		clean_exit(mlx, MLX_ERROR);
	mlx->data.addr = mlx_get_data_addr(mlx->img, &mlx->data.bits_per_pixel, &mlx->data.size_line, &mlx->data.endian);
	//TODO: For centering Julia I need to adjust still.
	//TODO: Also check if mine is reversed...
	mlx->data.zoom_factor = 1;
	mlx->data.x_min = -2.0;
	mlx->data.x_max = 1.0;
	mlx->data.y_min = -1.5;
	mlx->data.y_max = 1.5;
	mlx->data.redraw_needed = 1;
}
