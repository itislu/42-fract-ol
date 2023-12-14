/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_manual.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 18:35:24 by ldulling          #+#    #+#             */
/*   Updated: 2023/12/14 19:44:22 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	print_manual(void)
{
	ft_printf(
		"************************* FRACTOL MANUAL *************************\n"
		"\n"
		"USAGE: ./fractol [options]\n"
		"\n"
		"OPTIONS:\n"
		"  -m,  --mandelbrot     Display the Mandelbrot set.\n"
		"  -mm, --multibrot      Display the Multibrot set.\n"
		"  -j,  --julia          Display the Julia set.\n"
		"  -jj, --multijulia     Display the Multijulia set.\n"
		"  -b,  --barnsley       Display the Barnsley Fern.\n"
		"  -h,  --help           Display this Manual in the terminal.\n"
		"\n"
		"CONTROLS:\n"
		"  Mouse wheel           Zoom in and out.\n"
		"  Numpad Enter          Enable/disable zoom optimizations.\n"
		"  Numpad 1-9            Switch between levels of detail.\n"
		"                        1:   Minimum\n"
		"                        2-5: 10%% - 20%% - 33%% - 50%%\n"
		"                        6-9: 150%% - 200%% - 500%% - 1000%%\n"
		"  Numpad 0              Reset level of detail to 100%%.\n"
		"  Numpad +/-            Increase/decrease level of detail by 50%%.\n"
		"\n"
	);
}
