/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_di.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grannou <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 11:31:53 by grannou           #+#    #+#             */
/*   Updated: 2021/06/17 09:44:45 by grannou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_int_len(int nbr)
{
	int		count;

	count = 0;
	while (nbr != 0 && ++ count)
		nbr = nbr / 10;
	return (count);
}

void	set_nbr_pads(int nbr, int nbrlen, t_format *format)
{
	if (format->width > nbrlen)
	{
		if (format->width >= format->prec)
		{
			if (format->prec < nbrlen)
				format->wpad = format->width - nbrlen;
			else
				format->wpad = format->width - format->prec;
		}
		else
			format->wpad = format->prec;
	}
	if (has_prefix(nbr, format))
		format->wpad--;
	if (format->wpad <= 0 || format->width < format->prec \
		|| format->width < nbrlen)
		format->wpad = 0;
	format->ppad = format->prec - nbrlen;
	if (format->ppad < 0)
		format->ppad = 0;
}

int	justify_nbr(int nbr, t_format *format)
{
	int		ret;

	ret = 0;
	if (format->minus == 0)
	{
		ret += pad_n_chars(' ', format->wpad);
		if (has_prefix(nbr, format))
			ret += print_count_char(format->prefix);
		ret += pad_n_chars('0', format->ppad);
		if (nbr != 0 || (nbr == 0 && format->prec < 0))
			ret += print_count_nbr_base(nbr, format, 0);
	}
	if (format->minus == 1)
	{
		if (has_prefix(nbr, format))
			ret += print_count_char(format->prefix);
		ret += pad_n_chars('0', format->ppad);
		if (nbr != 0 || (nbr == 0 && format->width != 0 && format->dot == 0
				&& format->prec < 0))
			ret += print_count_nbr_base(nbr, format, 0);
		ret += pad_n_chars(' ', format->wpad);
	}
	return (ret);
}

int	justify_nbr_zero(int nbr, t_format *format)
{
	int		ret;

	ret = 0;
	if (has_prefix(nbr, format))
		ret += print_count_char(format->prefix);
	ret += pad_n_chars('0', format->ppad);
	if (format->minus == 0)
	{
		ret += pad_n_chars('0', format->ppad);
		ret += pad_n_chars('0', format->wpad);
		ret += print_count_nbr_base(nbr, format, 0);
	}
	if (format->minus == 1)
	{
		ret += print_count_nbr_base(nbr, format, 0);
		ret += pad_n_chars('0', format->ppad);
		ret += pad_n_chars(' ', format->wpad);
	}
	return (ret);
}

int	print_di(int nbr, t_format *format)
{
	int		nbrlen;

	nbrlen = ft_int_len(nbr);
	set_prefix(nbr, format);
	set_nbr_pads(nbr, nbrlen, format);
	if (nbr == 0 && format->wpad > 0 && format->dot == 0)
		format->wpad -= 1;
	if (format->zero == 0)
		return (justify_nbr(nbr, format));
	else
		return (justify_nbr_zero(nbr, format));
}
