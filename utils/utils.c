/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darakely <darakely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 10:38:10 by darakely          #+#    #+#             */
/*   Updated: 2022/12/12 15:25:20 by darakely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		j;
	int		i;
	size_t	len;
	char	*str;

	len = ft_strlen(s1) + ft_strlen(s2);
	str = malloc(sizeof(char) * (len + 1));
	i = 0;
	while (s1 && s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2 && s2[j])
	{
		str[i] = s2[j];
		i++;
		j++;
	}
	str[i] = '\0';
	free(s1);
	s1 = 0;
	return (str);
}

long long int	ft_atoi(const char *str)
{
	int				i;
	int				s;
	long long int	res;

	i = 0;
	s = 1;
	res = 0;
	if (!str)
		return (0);
	while (str[i] == ' ' || str[i] == '\n' || str[i] == '\t'
		|| str[i] == '\v' || str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
		s = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = (res * 10) + (str[i] - '0');
		i++;
	}
	return (res * s);
}

char	*ft_strdup(const char *s1)
{
	int		i;
	size_t	len;
	char	*ptr;

	ptr = 0;
	if (!s1)
		return (0);
	len = ft_strlen(s1);
	ptr = malloc(sizeof(char) * (len + 1));
	if (!ptr)
		return (0);
	i = 0;
	while (s1 && s1[i])
	{
		ptr[i] = s1[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

int	ft_strncmp(char *s1, char *s2, size_t n)
{
	unsigned const char	*c1;
	unsigned const char	*c2;
	size_t				i;

	c1 = (unsigned const char *)s1;
	c2 = (unsigned const char *)s2;
	i = 0;
	if (!s1 || !s2)
		return (0);
	while (i < n)
	{
		if ((c1[i] != c2[i] || s1[i] == 0) || s2[i] == 0)
			return (c1[i] - c2[i]);
		i++;
	}
	return (0);
}
