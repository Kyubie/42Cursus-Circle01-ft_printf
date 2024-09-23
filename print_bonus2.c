/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_bonus2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grannou <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 14:16:13 by grannou           #+#    #+#             */
/*   Updated: 2021/06/20 08:22:30 by grannou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_f(double nbr, t_format *format)
{
	int		ret;

	ret = 0;
	ret += print_count_str("");
	nbr += 0;
	format->minus += 0;
	return (ret);
}

int	print_g(double nbr, t_format *format)
{
	int		ret;

	ret = print_count_str("");
	nbr += 0;
	format->minus += 0;
	return (ret);
}

int	print_e(double nbr, t_format *format)
{
	int		ret;

	ret = 0;
	ret += print_count_str("");
	nbr += 0;
	format->minus += 0;
	return (ret);
}
