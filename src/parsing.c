/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 11:33:29 by ldulling          #+#    #+#             */
/*   Updated: 2023/12/14 15:16:44 by ldulling         ###   ########.fr       */
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
		success = setup_mandelbrot(argc, argv, data);
	else if (ft_strmatches_any(argv[1], 4,
			"j", "J", "julia", "Julia"))
		success = setup_julia(argc, argv, data);
	else if (ft_strmatches_any(argv[1], 4,
			"mm", "MM", "multibrot", "Multibrot"))
		success = setup_multibrot(argc, argv, data);
	else if (ft_strmatches_any(argv[1], 4,
			"jj", "JJ", "multijulia", "Multijulia"))
		success = setup_multijulia(argc, argv, data);
	else if (ft_strmatches_any(argv[1], 9,
			"b", "B", "bf", "BF", "barnsley", "Barnsley",
			"barnsley fern", "Barnsley fern", "Barnsley Fern"))
		success = setup_barnsleyfern(argc, argv, data);
	else
		success = false;
	return (success);
}

bool	setup_mandelbrot(int argc, char *argv[], t_data *data)
{
	(void) argv;
	data->fractal = MANDELBROT;
	if (argc > 2)
		ft_printf("%s\n", "No need for additional arguments ;)");
	return (true);
}

bool	setup_julia(int argc, char *argv[], t_data *data)
{
	bool	success;

	data->fractal = JULIA;
	success = parse_julia_values(argc, argv, &data->c_default);
	return (success);
}

bool	setup_multibrot(int argc, char *argv[], t_data *data)
{
	(void) argv;
	data->fractal = MULTIBROT;
	if (argc > 2)
		ft_printf("%s\n", "No need for additional arguments ;)");
	return (true);
}

bool	setup_multijulia(int argc, char *argv[], t_data *data)
{
	bool	success;

	data->fractal = MULTIJULIA;
	success = parse_julia_values(argc, argv, &data->c_default);
	return (success);
}

bool	setup_barnsleyfern(int argc, char *argv[], t_data *data)
{
	(void) argv;
	data->fractal = BARNSLEYFERN;
	if (argc > 2)
		ft_printf("%s\n", "No need for additional arguments ;)");
	return (true);
}
