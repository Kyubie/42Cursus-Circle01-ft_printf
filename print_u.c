/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_u.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grannou <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 11:32:51 by grannou           #+#    #+#             */
/*   Updated: 2021/06/20 08:54:15 by grannou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_uint_len(unsigned int nbr)
{
	int		count;

	count = 0;
	while (nbr != 0 && ++count)
		nbr = nbr / 10;
	return (count);
}

void	set_uint_pads(int nbrlen, t_format *format)
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
	if (format->wpad <= 0 || format->width < format->prec \
		|| format->width < nbrlen)
		format->wpad = 0;
	format->ppad = format->prec - nbrlen;
	if (format->ppad < 0)
		format->ppad = 0;
}

int	justify_uint(unsigned int nbr, t_format *format)
{
	int		ret;

	ret = 0;
	if (format->minus == 0)
	{
		ret += pad_n_chars(' ', format->wpad);
		ret += pad_n_chars('0', format->ppad);
		if (nbr != 0 || (nbr == 0 && format->prec < 0))
			ret += print_count_uint_base(nbr, format, 0);
	}
	if (format->minus == 1)
	{
		ret += pad_n_chars('0', format->ppad);
		if (nbr != 0 || (nbr == 0 && format->prec < 0
				&& ((format->width != 0) || (format->minus == 1))))
			ret += print_count_uint_base(nbr, format, 0);
		ret += pad_n_chars(' ', format->wpad);
	}
	return (ret);
}

int	justify_uint_zero(unsigned int nbr, t_format *format)
{
	int		ret;

	ret = 0;
	ret += pad_n_chars('0', format->ppad);
	if (format->minus == 0)
	{
		ret += pad_n_chars('0', format->ppad);
		ret += pad_n_chars('0', format->wpad);
		ret += print_count_uint_base(nbr, format, 0);
	}
	if (format->minus == 1)
	{
		ret += print_count_uint_base(nbr, format, 0);
		ret += pad_n_chars('0', format->ppad);
		ret += pad_n_chars(' ', format->wpad);
	}
	return (ret);
}

int	print_u(unsigned int nbr, t_format *format)
{
	int		ret;
	int		nbrlen;

	ret = 0;
	nbrlen = ft_uint_len(nbr);
	set_uint_pads(nbrlen, format);
	if (nbr == 0 && format->wpad > 0 && format->dot == 0)
		format->wpad -= 1;
	if (format->zero == 0)
		return (justify_uint(nbr, format));
	else
		return (justify_uint_zero(nbr, format));
	return (0);
}
