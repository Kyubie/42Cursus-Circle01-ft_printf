/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grannou <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 14:47:27 by grannou           #+#    #+#             */
/*   Updated: 2021/06/20 08:49:14 by grannou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	has_prefix(int nbr, t_format *format)
{
	return (nbr < 0 || format->sharp == 1 \
			|| (nbr >= 0 && (format->plus == 1 || format->blank == 1)));
}

int	print_count_nbr_base(int nbr, t_format *format, int prefix)
{
	int		ret;
	int		base_len;

	ret = 0;
	base_len = 0;
	base_len = ft_strlen(format->base);
	if (prefix == 1 && has_prefix(nbr, format))
	{
		ret += print_count_char(format->prefix);
		ret += print_count_nbr_base(nbr, format, 0);
	}
	if (nbr == INT_MIN && base_len == 10)
		ret += print_count_str("2147483648");
	else if (nbr < 0)
		ret += print_count_nbr_base(-nbr, format, 0);
	else if (nbr >= base_len)
	{
		ret += print_count_nbr_base(nbr / base_len, format, 0);
		ret += print_count_nbr_base(nbr % base_len, format, 0);
	}
	else
		ret += print_count_char(format->base[nbr]);
	return (ret);
}

int	print_count_uint_base(unsigned int nbr, t_format *format, int prefix)
{
	int		ret;
	size_t	base_len;

	ret = 0;
	base_len = ft_strlen(format->base);
	if (prefix == 1 && has_prefix(nbr, format))
	{
		ret += print_count_char(format->prefix);
		ret += print_count_uint_base(nbr, format, 0);
	}
	if (nbr == UINT_MAX && base_len == 10)
		ret += print_count_str("4294967295");
	else if (nbr < 0)
		ret += print_count_uint_base(-nbr, format, 0);
	else if (nbr >= base_len)
	{
		ret += print_count_uint_base(nbr / base_len, format, 0);
		ret += print_count_uint_base(nbr % base_len, format, 0);
	}
	else
		ret += print_count_char(format->base[nbr]);
	return (ret);
}

int	print_count_ullint_base(unsigned long long int nbr, t_format *format, \
	int prefix)
{
	int		ret;
	size_t	base_len;

	ret = 0;
	base_len = ft_strlen(format->base);
	if (prefix == 1 && has_prefix(nbr, format))
	{
		ret += print_count_char(format->prefix);
		ret += print_count_ullint_base(nbr, format, 0);
	}
	if (nbr == ULLONG_MAX && base_len == 10)
		ret += print_count_str("18446744073709551615");
	else if (nbr < 0)
		ret += print_count_ullint_base(-nbr, format, 0);
	else if (nbr >= base_len)
	{
		ret += print_count_ullint_base(nbr / base_len, format, 0);
		ret += print_count_ullint_base(nbr % base_len, format, 0);
	}
	else
		ret += print_count_char(format->base[nbr]);
	return (ret);
}
