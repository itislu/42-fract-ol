/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 11:46:50 by ldulling          #+#    #+#             */
/*   Updated: 2023/12/02 11:57:08 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	render_mandelbrot(t_mlx *mlx)
{
	if (mlx->data.redraw_needed)
	{
		draw_mandelbrot(&mlx->data, 272);
		mlx_put_image_to_window(mlx->xvar, mlx->win, mlx->img, 0, 0);
		mlx->data.redraw_needed = 0;
	}
	return (0);
}

int	render_julia(t_mlx *mlx)
{
	if (mlx->data.redraw_needed)
	{
		draw_julia(&mlx->data, 128, 2.0);
		mlx_put_image_to_window(mlx->xvar, mlx->win, mlx->img, 0, 0);
		mlx->data.redraw_needed = 0;
	}
	return (0);
}

void	img_pixel_put(t_data *data, int x, int y, int color)
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
