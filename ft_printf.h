/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grannou <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 08:01:51 by grannou           #+#    #+#             */
/*   Updated: 2021/06/20 09:02:32 by grannou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdarg.h>
# include <limits.h>
# include <stdlib.h>

/*
** Useful define:
*/

# define FLAGS "-0 +#"
# define TYPES "cspdiuxXonfge%"
# define BINARY "01"
# define OCTAL "01234567"
# define DECI "0123456789"
# define HEXA_LOW "0123456789abcdef"
# define HEXA_UP "0123456789ABCDEF"

/*
** Defines a structure for parsing the printf string argument:
*/

typedef struct s_format
{
	int		minus;
	int		zero;
	int		plus;
	int		blank;
	int		sharp;
	char	*sharp_prefix;
	char	prefix;
	int		width;
	int		wpad;
	int		dot;
	int		prec;
	int		ppad;
	int		star;
	char	type;
	char	*base;
	int		n_ret;
}			t_format;

/*
** In ft_printf.c
*/
t_format	*init_format(t_format *format);
int			display_format_bonus(t_format *format, va_list ap);
int			display_format(int i, t_format *format, va_list ap);
int			parse(char *str, va_list ap, t_format *format);
int			ft_printf(const char *str, ...);

/*
** In fill_format.c
*/
void		special_case(t_format *format);
void		set_prefix(int nbr, t_format *format);
void		width_prec_star(char *str, int i, va_list ap, t_format *format);
void		fill_format(char *str, int i, va_list ap, t_format *format);

/*
** In print_cs.c
*/
int			print_c(int nbr, t_format *format);
void		set_str_pads(int strlen, t_format *format);
int			print_s(char *str, t_format *format);

/*
** In print_p.c
*/
int			ft_ullint_len_base(unsigned long long int n, int base_len);
void		set_ullint_pads(int nbrlen, t_format *format);
int			justify_ullint(unsigned long long int nbr, t_format *format);
int			justify_ullint_zero(unsigned long long int nbr, t_format *format);
int			print_p(unsigned long long ptr, t_format *format);

/*
** In print_di.c
*/
int			ft_int_len(int nbr);
void		set_nbr_pads(int nbr, int nbrlen, t_format *format);
int			justify_nbr(int nbr, t_format *format);
int			justify_nbr_zero(int nbr, t_format *format);
int			print_di(int nbr, t_format *format);

/*
** In print_u.c
*/
int			ft_uint_len(unsigned int n);
void		set_uint_pads(int nbrlen, t_format *format);
int			justify_uint(unsigned int nbr, t_format *format);
int			justify_uint_zero(unsigned int nbr, t_format *format);
int			print_u(unsigned int nbr, t_format *format);

/*
** In print_xX.c
*/
int			ft_uint_len_base(unsigned int n, int base_len);
void		set_xuint_pads(unsigned int nbr, int nbrlen, t_format *format);
int			justify_xuint(unsigned int nbr, t_format *format);
int			justify_xuint_zero(unsigned int nbr, t_format *format);
int			print_xX(unsigned int nbr, t_format *format);

/*
** In print_bonus.c
*/
void		set_ouint_pads(unsigned int nbr, int nbrlen, t_format *format);
int			print_o(unsigned int nbr, t_format *format);
int			print_b(unsigned int nbr, t_format *format);
int			print_n(int i, t_format *format, va_list ap);

/*
** In print_bonus2.c
*/
int			print_f(double nbr, t_format *format);
int			print_g(double nbr, t_format *format);
int			print_e(double nbr, t_format *format);

/*
** In ft_printf_utils.c
*/
int			print_count_char(int c);
int			print_count_str(char *str);
int			print_count_str_max(char *str, int max_len);
int			ft_strlen(char *str);
int			pad_n_chars(char c, int n);

/*
** In ft_printf_utils2.c
*/
int			is_percent(char c);
int			is_digit(char c);
int			is_type(char c);
int			is_bonus_type(char c);
int			is_flag(char c);

/*
** In ft_printf_utils3.c
*/
int			has_prefix(int nbr, t_format *format);
int			print_count_nbr_base(int nbr, t_format *format, int prefix);
int			print_count_uint_base(unsigned int nbr, t_format *format,
				int prefix);
int			print_count_ullint_base(unsigned long long int nbr, \
				t_format *format, int prefix);

#endif
