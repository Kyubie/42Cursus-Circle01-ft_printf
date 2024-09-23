/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_cs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grannou <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 14:03:08 by grannou           #+#    #+#             */
/*   Updated: 2021/06/17 08:51:41 by grannou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_c(int nbr, t_format *format)
{
	int		ret;

	ret = 0;
	format->wpad = format->width - 1;
	if (format->wpad <= 0 || format->width < format->prec || format->width < 1)
		format->wpad = 0;
	if (format->minus == 0)
	{
		if (format->zero == 0)
			ret += pad_n_chars(' ', format->wpad);
		else
			ret += pad_n_chars('0', format->wpad);
		ret += print_count_char(nbr);
	}
	else
	{
		ret += print_count_char(nbr);
		if (format->zero == 0)
			ret += pad_n_chars(' ', format->wpad);
		else
			ret += pad_n_chars('0', format->wpad);
	}
	return (ret);
}

void	set_str_pads(int strlen, t_format *format)
{
	if (format->prec > strlen || format->prec < 0)
		format->ppad = strlen;
	if (format->prec <= strlen && format->prec >= 0)
		format->ppad = format->prec;
	format->wpad = format->width - format->ppad;
	if (format->wpad <= 0)
		format->wpad = 0;
}

int	print_s(char *str, t_format *format)
{
	int		ret;
	int		i;
	int		strlen;

	ret = 0;
	i = 0;
	if (!str)
		str = "(null)";
	if (format->dot == 1 && format->prec == 0)
		str = "";
	strlen = ft_strlen(str);
	set_str_pads(strlen, format);
	if (format->minus == 0)
	{
		ret += pad_n_chars(' ', format->wpad);
		ret += print_count_str_max(str, format->ppad);
	}
	else
	{
		ret += print_count_str_max(str, format->ppad);
		ret += pad_n_chars(' ', format->wpad);
	}
	return (ret);
}
