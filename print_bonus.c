/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grannou <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 14:15:05 by grannou           #+#    #+#             */
/*   Updated: 2021/06/20 09:38:11 by grannou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	set_ouint_pads(unsigned int nbr, int nbrlen, t_format *format)
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
		format->wpad -= 1;
	if (format->wpad <= 0 || format->width < format->prec \
		|| format->width < nbrlen)
		format->wpad = 0;
	format->ppad = format->prec - nbrlen;
	if (format->ppad < 0)
		format->ppad = 0;
}

int	print_o(unsigned int nbr, t_format *format)
{
	int		ret;
	int		nbrlen;

	ret = 0;
	nbrlen = ft_uint_len_base(nbr, 8);
	set_ouint_pads(nbr, nbrlen, format);
	format->sharp_prefix = "0";
	if (nbr == 0 && format->wpad > 0 && format->dot == 0)
		format->wpad -= 1;
	if (format->zero == 0)
		return (justify_xuint(nbr, format));
	else
		return (justify_xuint_zero(nbr, format));
	return (0);
}

int	print_b(unsigned int nbr, t_format *format)
{
	int		ret;
	int		nbrlen;

	ret = 0;
	nbrlen = ft_uint_len_base(nbr, 2);
	set_prefix(nbr, format);
	set_uint_pads(nbrlen, format);
	if (nbr == 0 && format->wpad > 0 && format->dot == 0)
		format->wpad -= 1;
	if (format->zero == 0)
		return (justify_uint(nbr, format));
	else
		return (justify_uint_zero(nbr, format));
	return (0);
}

int	print_n(int i, t_format *format, va_list ap)
{
	void	*n_ret;

	n_ret = va_arg(ap, void *);
	*((int *)n_ret) = i;
	format->n_ret = i;
	return (0);
}
