/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   barnsley_fern.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 15:29:59 by ldulling          #+#    #+#             */
/*   Updated: 2023/12/14 18:04:07 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	render_barnsleyfern(t_mlx *mlx)
{
	if (mlx->data.redraw_needed)
	{
		calc_barnsleyfern(&mlx->data, mlx->data.max_iter);
		mlx_put_image_to_window(mlx->xvar, mlx->win, mlx->img, 0, 0);
		mlx->data.redraw_needed = false;
	}
	return (0);
}

void	calc_barnsleyfern(t_data *data, int max_iter)
{
	t_coord	img;
	int		n;
	int		urandom;
	double	xn;
	double	yn;

	urandom = open("/dev/urandom", O_RDONLY);
	if (urandom == -1)
		return ;
	max_iter = 9000000;
	xn = 0.0;
	yn = 0.0;
	n = 0;
	while (n < max_iter)
	{
		choose_random_point(get_random_double(urandom), &xn, &yn);
		map_barnsley_point_to_win(&img, xn, yn);
		if (img.x >= 0 && img.x < WIN_WIDTH && img.y >= 0 && img.y < WIN_HEIGHT)
			img_pixel_put(data, img.x, img.y, 0x00FF00);
		n++;
	}
	close(urandom);
}

double	get_random_double(int urandom)
{
	unsigned int	random_value;

	if (read(urandom, &random_value, sizeof(random_value)) == -1)
		return (0.0);
	return ((double) random_value / UINT_MAX);
}

void	choose_random_point(double r, double *xn, double *yn)
{
	double	x_old;
	double	y_old;

	x_old = *xn;
	y_old = *yn;
	if (r < 0.01)
	{
		*xn = 0.0;
		*yn = 0.16 * y_old;
	}
	else if (r < 0.86)
	{
		*xn = 0.85 * x_old + 0.04 * y_old;
		*yn = -0.04 * x_old + 0.85 * y_old + 1.6;
	}
	else if (r < 0.93)
	{
		*xn = 0.2 * x_old - 0.26 * y_old;
		*yn = 0.23 * x_old + 0.22 * y_old + 1.6;
	}
	else
	{
		*xn = -0.15 * x_old + 0.28 * y_old;
		*yn = 0.26 * x_old + 0.24 * y_old + 0.44;
	}
}

void	map_barnsley_point_to_win(t_coord *img, double xn, double yn)
{
	img->x = (int)((xn + 2.1820) / 4.8378 * WIN_WIDTH);
	img->y = (int)((9.9983 - yn) / 9.9983 * WIN_HEIGHT);
}
