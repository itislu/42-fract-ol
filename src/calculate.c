/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 11:40:21 by ldulling          #+#    #+#             */
/*   Updated: 2023/12/14 15:38:03 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	draw_mandelbrot(t_data *data, int max_iter)
{
	int			iter;
	t_coord		img;
	t_complex	c;
	t_complex	z;

	img.y = 0;
	while (img.y < WIN_HEIGHT)
	{
		img.x = 0;
		while (img.x < WIN_WIDTH)
		{
			map_cmplxplane_to_win(&c, data, img);
			z.real = 0;
			z.imag = 0;
			iter = -1;
			while (z.real * z.real + z.imag * z.imag <= 4.0
				&& ++iter < max_iter)
				z = calculate_next_iteration(z, c);
			img_pixel_put(data, img.x, img.y, color(iter, max_iter, z));
			img.x++;
		}
		img.y++;
	}
}

void draw_multibrot(t_data *data, int max_iter)
{
	static double n = 1.0;

	int			iter;
	t_coord		img;
	t_complex	c;
	t_complex	z;

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
			{
				double xtmp = pow(z.real * z.real + z.imag * z.imag, n / 2) * cos(n * atan2(z.imag, z.real)) + c.real;
				z.imag = pow(z.real * z.real + z.imag * z.imag, n / 2) * sin(n * atan2(z.imag, z.real)) + c.imag;
				z.real = xtmp;
			}
			img_pixel_put(data, img.x, img.y, color(iter, max_iter, z));
			img.x++;
		}
		img.y++;
	}
	n += 0.10;
}

void	draw_julia(t_data *data, int max_iter, double esc_radius)
{
	int			iter;
	t_coord		img;
	t_complex	z;

	img.y = 0;
	while (img.y < WIN_HEIGHT)
	{
		img.x = 0;
		while (img.x < WIN_WIDTH)
		{
			map_cmplxplane_to_win(&z, data, img);
			iter = -1;
			while (z.real * z.real + z.imag * z.imag <= esc_radius
				&& ++iter < max_iter)
				z = calculate_next_iteration(z, data->c_default);
			img_pixel_put(data, img.x, img.y, color(iter, max_iter, z));
			img.x++;
		}
		img.y++;
	}
}

void draw_multijulia(t_data *data, int max_iter, double esc_radius)
{
	//! Is splitting a little bit in the middle

	static double n = 1.0;

	int			iter;
	t_coord		img;
	t_complex	z;

	img.y = 0;
	while (img.y < WIN_HEIGHT)
	{
		img.x = 0;
		while (img.x < WIN_WIDTH)
		{
			map_cmplxplane_to_win(&z, data, img);
			iter = -1;
			while (z.real * z.real + z.imag * z.imag <= esc_radius && ++iter < max_iter)
			{
				double xtmp = pow(z.real * z.real + z.imag * z.imag, n / 2) * cos(n * atan2(z.imag, z.real)) + data->c_default.real;
				z.imag = pow(z.real * z.real + z.imag * z.imag, n / 2) * sin(n * atan2(z.imag, z.real)) + data->c_default.imag;
				z.real = xtmp;
			}
			img_pixel_put(data, img.x, img.y, color(iter, max_iter, z));
			img.x++;
		}
		img.y++;
	}
	n += 0.10;
}

void	map_cmplxplane_to_win(t_complex *cmpt, t_data *data, t_coord img)
{
	cmpt->real = data->x_min + (data->x_max - data->x_min) * (img.x
		/ (WIN_WIDTH - 1.0));
	cmpt->imag = data->y_min + (data->y_max - data->y_min) * (img.y
		/ (WIN_HEIGHT - 1.0));
}

t_complex	calculate_next_iteration(t_complex z, t_complex c)
{
	t_complex	new_z;

	new_z.real = z.real * z.real - z.imag * z.imag + c.real;
	new_z.imag = 2.0 * z.real * z.imag + c.imag;
	return (new_z);
}
