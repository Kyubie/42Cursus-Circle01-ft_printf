/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_xX.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grannou <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/07 10:48:06 by grannou           #+#    #+#             */
/*   Updated: 2021/06/20 09:37:57 by grannou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_uint_len_base(unsigned int nbr, int base_len)
{
	int		count;

	count = 0;
	while (nbr != 0 && ++count)
		nbr = nbr / base_len;
	return (count);
}

void	set_xuint_pads(unsigned int nbr, int nbrlen, t_format *format)
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
	if (format->sharp == 1 && nbr != 0)
		format->wpad -= 2;
	if (format->wpad <= 0 || format->width < format->prec \
		|| format->width < nbrlen)
		format->wpad = 0;
	format->ppad = format->prec - nbrlen;
	if (format->ppad < 0)
		format->ppad = 0;
}

int	justify_xuint(unsigned int nbr, t_format *format)
{
	int		ret;

	ret = 0;
	if (format->minus == 0)
	{
		ret += pad_n_chars(' ', format->wpad);
		ret += pad_n_chars('0', format->ppad);
		if (nbr != 0 && format->sharp == 1)
			ret += print_count_str(format->sharp_prefix);
		if (nbr != 0 || (nbr == 0 && format->prec < 0))
			ret += print_count_uint_base(nbr, format, 0);
	}
	if (format->minus == 1)
	{
		ret += pad_n_chars('0', format->ppad);
		if (nbr != 0 && format->sharp == 1)
			ret += print_count_str(format->sharp_prefix);
		if (nbr != 0 || (nbr == 0 && format->prec < 0
				&& ((format->width != 0) || (format->minus == 1))))
			ret += print_count_uint_base(nbr, format, 0);
		ret += pad_n_chars(' ', format->wpad);
	}
	return (ret);
}

int	justify_xuint_zero(unsigned int nbr, t_format *format)
{
	int		ret;

	ret = 0;
	ret += pad_n_chars('0', format->ppad);
	if (format->minus == 0)
	{
		ret += pad_n_chars('0', format->ppad);
		ret += pad_n_chars('0', format->wpad);
		if (nbr != 0 && format->sharp == 1)
			ret += print_count_str(format->sharp_prefix);
		ret += print_count_uint_base(nbr, format, 0);
	}
	if (format->minus == 1)
	{
		if (nbr != 0 && format->sharp == 1)
			ret += print_count_str(format->sharp_prefix);
		ret += print_count_uint_base(nbr, format, 0);
		ret += pad_n_chars('0', format->ppad);
		ret += pad_n_chars(' ', format->wpad);
	}
	return (ret);
}

int	print_xX(unsigned int nbr, t_format *format)
{
	int		ret;
	int		nbrlen;

	ret = 0;
	nbrlen = ft_uint_len_base(nbr, 16);
	if (format->type == 'x')
		format->sharp_prefix = "0x";
	if (format->type == 'X')
		format->sharp_prefix = "0X";
	set_xuint_pads(nbr, nbrlen, format);
	if (nbr == 0 && format->wpad > 0 && format->dot == 0)
		format->wpad -= 1;
	if (format->zero == 0)
		return (justify_xuint(nbr, format));
	else
		return (justify_xuint_zero(nbr, format));
	return (0);
}
