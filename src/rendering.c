/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 11:46:50 by ldulling          #+#    #+#             */
/*   Updated: 2023/12/02 18:56:08 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	render_mandelbrot(t_mlx *mlx)
{
	if (mlx->data.redraw_needed)
	{
		draw_mandelbrot(&mlx->data, mlx->data.max_iter);
		mlx_put_image_to_window(mlx->xvar, mlx->win, mlx->img, 0, 0);
		if (mlx->data.max_iter != MAX_ITERATIONS)
			mlx->data.max_iter = MAX_ITERATIONS;
		else
			mlx->data.redraw_needed = false;
	}
	return (0);
}

int	render_julia(t_mlx *mlx)
{
	if (mlx->data.redraw_needed)
	{
		draw_julia(&mlx->data, mlx->data.max_iter, 2.0);
		mlx_put_image_to_window(mlx->xvar, mlx->win, mlx->img, 0, 0);
		if (mlx->data.max_iter != MAX_ITERATIONS)
			mlx->data.max_iter = MAX_ITERATIONS;
		else
			mlx->data.redraw_needed = false;
	}
	return (0);
}

void	img_pixel_put(t_data *data, int x, int y, int color)
{
	int		bytes_per_pixel;
	int		i;
	int		next_byte;
	char	*pixel;

	bytes_per_pixel = data->bits_per_pixel / 8;
	pixel = data->addr + (y * data->size_line + x * bytes_per_pixel);
	if (data->endian)
	{
		i = data->bits_per_pixel - 8;
		next_byte = -8;
	}
	else
	{
		i = 0;
		next_byte = 8;
	}
	while (bytes_per_pixel--)
	{
		*pixel++ = (color >> i) & 0XFF;
		i += next_byte;
	}
}
