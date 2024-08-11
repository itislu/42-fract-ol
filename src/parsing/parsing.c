/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 11:33:29 by ldulling          #+#    #+#             */
/*   Updated: 2023/12/14 19:14:18 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

bool	parse_arguments(int argc, char *argv[], t_data *data)
{
	bool	success;

	success = false;
	if (argc < 2)
		return (success);
	else if (ft_strmatches_any(argv[1], 2, "-m", "--mandelbrot"))
		success = setup_fixed(argc, data, MANDELBROT);
	else if (ft_strmatches_any(argv[1], 2, "-j", "--julia"))
		success = setup_config(argc, argv, data, JULIA);
	else if (ft_strmatches_any(argv[1], 2, "-mm", "--multibrot"))
		success = setup_fixed(argc, data, MULTIBROT);
	else if (ft_strmatches_any(argv[1], 2, "-jj", "--multijulia"))
		success = setup_config(argc, argv, data, MULTIJULIA);
	else if (ft_strmatches_any(argv[1], 2, "-b", "--barnsley"))
		success = setup_fixed(argc, data, BARNSLEYFERN);
	else if (ft_strmatches_any(argv[1], 2, "-h", "--help"))
	{
		print_manual();
		exit(0);
	}
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
