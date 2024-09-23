/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grannou <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/27 09:33:30 by grannou           #+#    #+#             */
/*   Updated: 2021/06/20 08:48:53 by grannou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_count_char(int c)
{
	return (write(1, &c, 1));
}

int	print_count_str(char *str)
{
	int		i;
	int		ret;

	i = -1;
	ret = 0;
	if (str == NULL)
		str = "(null)";
	while (str[++i])
		ret += print_count_char(str[i]);
	return (ret);
}

int	print_count_str_max(char *str, int max_len)
{
	int		i;
	int		ret;

	i = -1;
	ret = 0;
	if (str == NULL)
		str = "(null)";
	while (++i < max_len && str[i])
		ret += print_count_char(str[i]);
	return (ret);
}

int	ft_strlen(char *str)
{
	int		count;

	count = 0;
	while (str[count])
		count++;
	return (count);
}

int	pad_n_chars(char c, int n)
{
	int		ret;

	ret = 0;
	while (n--)
		ret += write(1, &c, 1);
	return (ret);
}
