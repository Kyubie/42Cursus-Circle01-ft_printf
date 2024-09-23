/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_p.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grannou <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 16:20:36 by grannou           #+#    #+#             */
/*   Updated: 2021/06/17 09:39:04 by grannou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_ullint_len_base(unsigned long long nbr, int base_len)
{
	int		count;

	count = 0;
	while (nbr != 0 && ++count)
		nbr = nbr / base_len;
	return (count);
}

void	set_ullint_pads(int nbrlen, t_format *format)
{
	if (format->width > nbrlen)
	{
		if (format->width >= format->prec)
		{
			if (format->prec < nbrlen)
				format->wpad = format->width - nbrlen - 2;
			else
				format->wpad = format->width - format->prec - 2;
		}
		else
			format->wpad = format->prec - 2;
	}
	if (format->wpad <= 0 || format->width < format->prec \
		|| format->width < nbrlen)
		format->wpad = 0;
	format->ppad = format->prec - nbrlen;
	if (format->ppad < 0)
		format->ppad = 0;
}

int	justify_ullint(unsigned long long int nbr, t_format *format)
{
	int		ret;

	ret = 0;
	if (format->minus == 0)
	{
		ret += pad_n_chars(' ', format->wpad);
		ret += pad_n_chars('0', format->ppad);
		ret += print_count_str("0x");
		if (nbr != 0 || (nbr == 0 && format->prec < 0))
			ret += print_count_ullint_base(nbr, format, 0);
	}
	if (format->minus == 1)
	{
		ret += pad_n_chars('0', format->ppad);
		ret += print_count_str("0x");
		if (nbr != 0 || (nbr == 0 && format->prec < 0
				&& ((format->width != 0) || (format->minus == 1))))
			ret += print_count_ullint_base(nbr, format, 0);
		ret += pad_n_chars(' ', format->wpad);
	}
	return (ret);
}

int	justify_ullint_zero(unsigned long long int nbr, t_format *format)
{
	int		ret;

	ret = 0;
	ret += pad_n_chars('0', format->ppad);
	if (format->minus == 0)
	{
		ret += pad_n_chars('0', format->ppad);
		ret += pad_n_chars('0', format->wpad);
		ret += print_count_str("0x");
		ret += print_count_ullint_base(nbr, format, 0);
	}
	if (format->minus == 1)
	{
		ret += print_count_str("0x");
		ret += print_count_ullint_base(nbr, format, 0);
		ret += pad_n_chars('0', format->ppad);
		ret += pad_n_chars(' ', format->wpad);
	}
	return (ret);
}

int	print_p(unsigned long long int nbr, t_format *format)
{
	int		ret;
	int		nbrlen;

	ret = 0;
	nbrlen = ft_ullint_len_base(nbr, 16);
	set_prefix(nbr, format);
	set_ullint_pads(nbrlen, format);
	if (nbr == 0 && format->wpad > 0 && format->dot == 0)
		format->wpad -= 1;
	if (format->zero == 0)
		return (justify_ullint(nbr, format));
	else
		return (justify_ullint_zero(nbr, format));
	return (0);
}
