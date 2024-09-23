/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_format.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grannou <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 11:59:24 by grannou           #+#    #+#             */
/*   Updated: 2021/06/20 08:50:26 by grannou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	special_case(t_format *format)
{
	if (format->minus == 1 && format->prec == -1)
		format->zero = 0;
	if (format->minus == 1 && format->zero == 1)
		format->zero = 0;
	if (format->prec != -1 && (format->type == 'd' || format->type == 'i' \
		|| format->type == 'd' || format->type == 'u' || format->type == 'o' \
		|| format->type == 'x' || format->type == 'X' || format->type == 'p'))
		format->zero = 0;
	if (format->zero == 1 && format->dot == 1 && format->prec != -1)
		format->zero = 1;
	if (format->type == 'd' || format->type == 'i' || format->type == 'u')
		format->base = DECI;
	if (format->type == 'x' || format->type == 'p')
		format->base = HEXA_LOW;
	if (format->type == 'X')
		format->base = HEXA_UP;
	if (format->type == 'o')
		format->base = OCTAL;
	if (format->type == 'b')
		format->base = BINARY;
}

void	set_prefix(int nbr, t_format *format)
{
	if (nbr < 0)
		format->prefix = '-';
	if (nbr >= 0 && format->plus == 1)
		format->prefix = '+';
	if (nbr >= 0 && format->blank == 1)
		format->prefix = ' ';
	if (nbr >= 0 && format->plus == 1 && format->blank == 1)
	{
		format->blank = 0;
		format->prefix = '+';
	}
}

void	width_prec_star(char *str, int i, va_list ap, t_format *format)
{
	if (is_digit(str[i]))
	{
		if (format->prec == -1)
			format->width = format->width * 10 + (str[i] - '0');
		else
			format->prec = format->prec * 10 + (str[i] - '0');
	}
	else
	{
		if (format->prec == -1)
		{
			format->width = va_arg(ap, int);
			if (format->width < 0)
			{
				format->minus = 1;
				format->width = -format->width;
			}
		}
		else
			format->prec = va_arg(ap, int);
	}
}

void	fill_format(char *str, int i, va_list ap, t_format *format)
{
	if (str[i] == '-' && format->minus == 0)
		format->minus = 1;
	else if (str[i] == '0' && format->width == 0 && format->dot == 0 \
		&& format->zero == 0)
		format->zero = 1;
	else if (str[i] == '+' && format->plus == 0)
		format->plus = 1;
	else if (str[i] == ' ' && format->blank == 0)
		format->blank = 1;
	else if (str[i] == '#' && format->sharp == 0)
		format->sharp = 1;
	else if (str[i] == '.' && format->dot == 0)
	{
		format->dot = 1;
		format->prec = 0;
	}
	else if (is_digit(str[i]) || (str[i] == '*' && format->star < 2))
	{
		if (str[i] == '*')
			format->star = 1;
		width_prec_star(str, i, ap, format);
	}
}
