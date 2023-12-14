/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 11:33:29 by ldulling          #+#    #+#             */
/*   Updated: 2023/12/14 17:39:22 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

bool	parse_arguments(int argc, char *argv[], t_data *data)
{
	bool	success;

	if (argc < 2)
		success = false;
	else if (ft_strmatches_any(argv[1], 4,
			"m", "M", "mandelbrot", "Mandelbrot"))
		success = setup_fixed(argc, data, MANDELBROT);
	else if (ft_strmatches_any(argv[1], 4,
			"j", "J", "julia", "Julia"))
		success = setup_config(argc, argv, data, JULIA);
	else if (ft_strmatches_any(argv[1], 4,
			"mm", "MM", "multibrot", "Multibrot"))
		success = setup_fixed(argc, data, MULTIBROT);
	else if (ft_strmatches_any(argv[1], 4,
			"jj", "JJ", "multijulia", "Multijulia"))
		success = setup_config(argc, argv, data, MULTIJULIA);
	else if (ft_strmatches_any(argv[1], 9,
			"b", "B", "bf", "BF", "barnsley", "Barnsley",
			"barnsley fern", "Barnsley fern", "Barnsley Fern"))
		success = setup_fixed(argc, data, BARNSLEYFERN);
	else
		success = false;
	return (success);
}

bool	parse_julia_values(int argc, char *argv[], t_complex *c_default)
{
	if (argc == 2)
	{
		c_default->real = -0.79;
		c_default->imag = 0.23;
		return (true);
	}
	else if (argc == 3)
	{
		if (valid_float_arg(argv[2]))
		{
			c_default->real = ft_atof(argv[2]);
			c_default->imag = c_default->real;
			return (true);
		}
	}
	else
	{
		if (valid_float_arg(argv[2]) && valid_float_arg(argv[3]))
		{
			c_default->real = ft_atof(argv[2]);
			c_default->imag = ft_atof(argv[3]);
			return (true);
		}
	}
	return (false);
}
