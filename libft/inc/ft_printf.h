/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 19:26:08 by ldulling          #+#    #+#             */
/*   Updated: 2023/11/18 16:36:23 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft.h"
# include <stdarg.h>
# include <unistd.h>

# ifndef FD
#  define FD 1
# endif
# define SPECIFIERS "cspdiuxX%"
# define FLAGS "#+- 0"
# define NULL_PRINTOUT_PTR "(nil)"
# define NULL_PRINTOUT_STR "(null)"
# define FROM_NEGATIVE_WIDTH 2
# define NO_PRECISION_SET -1
# define NEGATIVE_PRECISION -2

typedef struct s_struct
{
	int		hash;
	int		plus;
	int		space;
	int		minus;
	int		zero;
	int		width;
	int		precision;
	char	specifier;
	int		unresolved;
}	t_struct;

int		ft_printf(const char *format, ...);
int		print_char(unsigned char c, t_struct *f);
int		print_nbr(long nbr, t_struct *f);
int		print_parsed(const char *format, int parsed, t_struct *f);
int		print_ptr(size_t ptr, t_struct *f);
int		print_str(const char *str, t_struct *f);
int		set_format(const char *format, int *i, t_struct *f, va_list *ap);

#endif
