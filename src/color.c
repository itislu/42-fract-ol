/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 11:45:02 by ldulling          #+#    #+#             */
/*   Updated: 2023/12/02 11:45:09 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	color(int iter, int max_iter, t_complex z)
{
	double	abs_z;
	int		color;

	if (iter == max_iter)
		color = 0;
	else
	{
		abs_z = z.real * z.real + z.imag * z.imag;
		color = iter + 1 - log(log(abs_z)) / log(2.0);
	}
	color = (color * 0x00330055) % 0x00CCCCCC;
	return (color);
}
