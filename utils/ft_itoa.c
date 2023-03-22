/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darakely <darakely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 17:10:04 by darakely          #+#    #+#             */
/*   Updated: 2022/12/05 14:20:10 by darakely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_isprint(int c)
{
	if (c > 32 && c <= 126)
		return (0);
	return (-1);
}

size_t	ft_num_len(int num)
{
	int	i;

	i = 0;
	if (num <= 0)
		i++;
	while (num)
	{
		i++;
		num = num / 10;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	int		len;
	char	*str;
	long	num;

	len = ft_num_len(n);
	num = n;
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	if (num < 0)
	{
		str[0] = '-';
		num = -num;
	}
	if (num == 0)
		str[0] = '0';
	str[len--] = '\0';
	while (num)
	{
		str[len] = num % 10 + '0';
		len--;
		num = num / 10;
	}
	return (str);
}
