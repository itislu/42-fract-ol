/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 11:45:02 by ldulling          #+#    #+#             */
/*   Updated: 2023/12/14 18:26:15 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	color(int iter, int max_iter, t_complex z)
{
	static int	initial_max_iter;
	double		abs_z;
	double		smooth_color;

	if (!initial_max_iter)
		initial_max_iter = max_iter;
	if (iter == max_iter)
		smooth_color = 0;
	else
	{
		abs_z = z.real * z.real + z.imag * z.imag;
		smooth_color = iter + 1 - log(log(abs_z)) / log(2.0);
		smooth_color /= initial_max_iter;
	}
	return (save_rgb_in_int(smooth_color));
}

int	save_rgb_in_int(double smooth_color)
{
	int	r;
	int	g;
	int	b;

	r = (9 * (1 - smooth_color) * pow(smooth_color, 3) * 255);
	g = (15 * pow((1 - smooth_color), 2) * pow(smooth_color, 2) * 255);
	b = (8.5 * pow((1 - smooth_color), 3) * smooth_color * 255);
	return ((r << 16) | (g << 8) | b);
}
