/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_export_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darakely <darakely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 20:06:23 by darakely          #+#    #+#             */
/*   Updated: 2022/12/12 18:14:52 by darakely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	norm_add_variable_export(t_export *info, char **new_malloc)
{
	info->next = malloc(sizeof(t_export));
	if (!info->next)
		return ;
	info->next->key = ft_strdup(new_malloc[0]);
	info->next->value = ft_strdup(new_malloc[1]);
	info->next->status = 0;
	info->next->next = 0;
}

char	*find_equal(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=' && ((str[i - 1] >= 'a' && str[i - 1] <= 'z') \
				|| (str[i - 1] >= 'A' && str[i - 1] <= 'Z') \
				|| (str[i - 1] == '_' || str[i - 1] == '+') \
				|| (str[i - 1] >= '0' \
				&& str[i - 1] <= '9')))
			return (&str[i + 1]);
		i++;
	}
	return (NULL);
}

void	norm_if(char *str, char *new_malloc, int i, int j)
{
	new_malloc[j] = '\\';
	new_malloc[j + 1] = str[i];
}

int	norm_else(char *str, char *new_malloc, int i, int j)
{
	if (str[i] != '\'' && str[i] != '\"')
	{
		new_malloc[j] = str[i];
		return (0);
	}
	return (-1);
}

int	my_strlen(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] != '\"' && str[i] != '\'')
			j++;
		i++;
	}
	return (j);
}
