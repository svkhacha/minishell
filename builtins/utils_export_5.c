/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_export_5.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darakely <darakely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 12:14:30 by darakely          #+#    #+#             */
/*   Updated: 2022/12/13 17:38:29 by darakely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*clear_double_quote(char *str)
{
	int		i;
	int		j;
	int		len;
	char	*tmp;
	char	*ptr;

	len = ft_strlen(str);
	tmp = (char *)malloc(sizeof(char) * (len + 1));
	if (!tmp)
		return (0);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] != '\"')
		{
			tmp[j] = str[i];
			j++;
		}
		i++;
	}
	tmp[j] = '\0';
	ptr = tmp;
	return (ptr);
}

int	if_backslash(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '\'')
		{
			i++;
			while (str[i] != '\'')
			{
				if (str[i] == '\"')
					j++;
				i++;
			}
		}
		i++;
	}
	if (j)
		return (j);
	return (-1);
}

void	norm_check_plus(t_export *data, char *str)
{
	char	*check;

	check = 0;
	check = correct_heredoc_name(str, 0, 0);
	data->value = ft_strjoin(data->value, check);
	data->value = ft_strjoin(data->value, "\"");
	my_free(&check);
}

int	norm_check_add_export(char *str, int i)
{
	if (str[i] == '=' || (str[0] >= '0' && str[0] <= '9') || str[i] == '+')
		return (-1);
	if (str[i] == '$' || (!str[i - 1] && ((str[i] >= 'a' && str[i] <= 'z') \
		|| (str[i] >= 'A' && str[i] <= 'Z') || str[i] == '_')) \
		|| (str[i - 1] && str[i] >= '0' && str[i] <= '9') \
		|| ((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' \
		&& str[i] <= 'Z') || str[i] == '_') || ((str[i] == '+') \
		&& (str[i + 1] == '\0' && str[i - 1])) || ((str[i] == '$' \
		&& str[i + 1] == '?') && ((str[i - 1] >= 'a' && str[i - 1] <= 'z') \
		|| (str[i - 1] >= 'A' && str[i - 1] <= 'Z') || str[i - 1] == '_')) \
		|| (str[i] == '=' && ((str[i - 1] >= 'a' && str[i - 1] <= 'z') \
		|| (str[i - 1] >= 'A' && str[i - 1] <= 'Z') || str[i - 1] == '_' \
		|| (str[i - 1] == '+' && ((str[i - 2] >= 'a' && str[i - 2] <= 'z') \
		|| (str[i - 2] >= 'A' && str[i - 2] <= 'Z') || str[i - 2] == '_')))))
	{
		if (str[i] == '$')
			return (1);
		return (0);
	}
	return (-1);
}

int	check_size_str(char *s1, char *s2)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	i = ft_strlen(s1);
	j = ft_strlen(s2);
	if (i < j)
		i = j;
	return (i);
}
