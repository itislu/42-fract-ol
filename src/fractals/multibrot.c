/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multibrot.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 11:40:21 by ldulling          #+#    #+#             */
/*   Updated: 2023/12/14 18:04:24 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	render_multibrot(t_mlx *mlx)
{
	if (mlx->data.redraw_needed)
	{
		calc_multibrot(&mlx->data,
			mlx->data.max_iter * mlx->data.toggle.zoom_optimize_factor);
		mlx_put_image_to_window(mlx->xvar, mlx->win, mlx->img, 0, 0);
		if (mlx->data.toggle.zoom_optimize_factor != 1.0)
			mlx->data.toggle.zoom_optimize_factor = 1.0;
		else
			mlx->data.redraw_needed = false;
	}
	return (0);
}

void	calc_multibrot(t_data *data, int max_iter)
{
	static double	n;
	int				iter;
	t_coord			img;
	t_complex		c;
	t_complex		z;

	img.y = 0;
	while (img.y < WIN_HEIGHT)
	{
		img.x = 0;
		while (img.x < WIN_WIDTH)
		{
			map_cmplxplane_to_win(&c, data, img);
			z = c;
			iter = -1;
			while (z.real * z.real + z.imag * z.imag <= 4 && ++iter < max_iter)
				z = calc_next_iteration_multi(z, c, n);
			img_pixel_put(data, img.x, img.y, color(iter, max_iter, z));
			img.x++;
		}
		img.y++;
	}
	n += 1.00;
}
