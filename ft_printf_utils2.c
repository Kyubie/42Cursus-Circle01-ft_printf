/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grannou <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 08:20:00 by grannou           #+#    #+#             */
/*   Updated: 2021/06/20 08:49:00 by grannou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	is_percent(char c)
{
	return (c == '%');
}

int	is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

int	is_type(char c)
{
	return (c == 'c' | c == 's' | c == 'p' | c == 'd' | c == 'i' | c == 'u' \
			| c == 'x' | c == 'X' | c == 'o' | c == 'b' | c == '%' | c == 'n' \
			| c == 'f' | c == 'g' | c == 'e');
}

int	is_bonus_type(char c)
{
	return (c == 'o' | c == 'b' | c == 'f' | c == 'g' | c == 'e');
}

int	is_flag(char c)
{
	return (c == '-' | c == '0' | c == ' ' | c == '+' | c == '#' | c == '*');
}
