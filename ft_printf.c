/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grannou <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 08:00:24 by grannou           #+#    #+#             */
/*   Updated: 2021/06/20 09:44:59 by grannou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_format	*init_format(t_format *format)
{
	format->minus = 0;
	format->zero = 0;
	format->plus = 0;
	format->blank = 0;
	format->sharp = 0;
	format->width = 0;
	format->wpad = 0;
	format->dot = 0;
	format->prec = -1;
	format->ppad = 0;
	format->star = 0;
	return (format);
}

int	display_format_bonus(t_format *format, va_list ap)
{
	int		ret;

	ret = 0;
	if (format->type == 'o')
		ret += print_o(va_arg(ap, unsigned int), format);
	if (format->type == 'b')
		ret += print_b(va_arg(ap, unsigned int), format);
	if (format->type == 'f')
		ret += print_f(va_arg(ap, double), format);
	if (format->type == 'g')
		ret += print_g(va_arg(ap, double), format);
	if (format->type == 'e')
		ret += print_e(va_arg(ap, double), format);
	return (ret);
}

int	display_format(int i, t_format *format, va_list ap)
{
	int		ret;

	ret = 0;
	if (format->type == '%')
		ret += print_c('%', format);
	if (format->type == 'c')
		ret += print_c(va_arg(ap, int), format);
	if (format->type == 's')
		ret += print_s(va_arg(ap, char *), format);
	if (format->type == 'p')
		ret += print_p(va_arg(ap, unsigned long long), format);
	if (format->type == 'd' || format->type == 'i')
		ret += print_di(va_arg(ap, int), format);
	if (format->type == 'u')
		ret += print_u(va_arg(ap, unsigned int), format);
	if (format->type == 'x' || format->type == 'X')
		ret += print_xX(va_arg(ap, unsigned int), format);
	if (is_bonus_type(format->type))
		ret += display_format_bonus(format, ap);
	if (format->type == 'n')
		ret += print_n(i, format, ap);
	return (ret);
}

int	parse(char *str, va_list ap, t_format *format)
{
	int			i;
	int			ret;

	i = 0;
	ret = 0;
	while (str[i] != '\0')
	{
		while (str[i] && str[i] != '%')
			ret += print_count_char(str[i++]);
		if (str[i] == '%')
		{
			format = init_format(format);
			while (str[++i] && !(is_type(str[i])))
				fill_format(str, i, ap, format);
			format->type = str[i++];
			special_case(format);
			ret += display_format(i, format, ap);
		}
	}
	return (ret);
}

int	ft_printf(const char *str, ...)
{
	va_list		ap;
	int			ret;
	t_format	*format;

	ret = 0;
	if (!str)
		return (-1);
	format = (t_format *)malloc(sizeof(t_format) * 1);
	if (!format)
		return (-1);
	va_start(ap, str);
	ret += parse((char *)str, ap, format);
	va_end(ap);
	free(format);
	return (ret);
}
