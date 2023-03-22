/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darakely <darakely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 16:04:33 by darakely          #+#    #+#             */
/*   Updated: 2022/12/09 16:31:13 by darakely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_isalnum(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
		return (1);
	return (0);
}

char	*ft_strchr(char *str, char c)
{
	int	i;

	i = -1;
	while (str[++i] && str[i] != c)
		;
	if (str[i] != '\0')
		return (str);
	return (0);
}
