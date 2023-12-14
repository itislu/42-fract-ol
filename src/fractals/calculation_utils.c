/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculation_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 11:40:21 by ldulling          #+#    #+#             */
/*   Updated: 2023/12/14 18:04:24 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	map_cmplxplane_to_win(t_complex *cmpt, t_data *data, t_coord img)
{
	cmpt->real = data->x_min + (data->x_max - data->x_min) * (img.x
			/ (WIN_WIDTH - 1.0));
	cmpt->imag = data->y_min + (data->y_max - data->y_min) * (img.y
			/ (WIN_HEIGHT - 1.0));
}

t_complex	calc_next_iteration(t_complex z, t_complex c)
{
	t_complex	new_z;

	new_z.real = z.real * z.real - z.imag * z.imag + c.real;
	new_z.imag = 2.0 * z.real * z.imag + c.imag;
	return (new_z);
}

t_complex	calc_next_iteration_multi(t_complex z, t_complex c, double n)
{
	t_complex	new_z;

	new_z.real = pow(z.real * z.real + z.imag * z.imag, n / 2)
		* cos(n * atan2(z.imag, z.real)) + c.real;
	new_z.imag = pow(z.real * z.real + z.imag * z.imag, n / 2)
		* sin(n * atan2(z.imag, z.real)) + c.imag;
	return (new_z);
}
