/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_export_3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darakely <darakely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 18:19:32 by darakely          #+#    #+#             */
/*   Updated: 2022/12/13 17:36:06 by darakely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_variable(t_export *data, char **new_split, int i, char **check_split)
{
	t_export	*tmp;
	char		**str;

	tmp = data;
	str = 0;
	if (find_plus(new_split[0]) == 0)
		str = ft_split(new_split[0], '+');
	else
	{
		str = malloc(sizeof(char *) * 2);
		str[0] = ft_strdup(new_split[0]);
		str[1] = 0;
	}
	i = continue_check_variable(data, 0, str);
	data = tmp;
	free_array(&str);
	free_array(&check_split);
	if (i == 1)
		return (-1);
	return (0);
}

int	check_change_variable(t_export *data, char **new_split)
{
	t_export	*tmp;
	int			i;
	char		*str;

	tmp = data;
	i = 0;
	str = new_split[0];
	if (str[ft_strlen(str) - 1] == '=' || str[ft_strlen(str) - 2] == '=')
	{
		while (data)
		{
			if (norm_check_change_variable(data, str, new_split) == -1)
			{
				data = tmp;
				return (-1);
			}
			data = data->next;
		}		
	}
	data = tmp;
	return (0);
}

int	check_add_export(char *str, char *error, int i, int j)
{
	char	*check;

	check = 0;
	if (!str || !*str)
		return (print_error(error));
	while (str[i] && (j == 0 || j == 1))
	{
		j = norm_check_add_export(str, i);
		if (j == 0 || j == 1)
		{
			i++;
			if (j == 1)
				i++;
		}
	}
	if (j == -1)
		return (print_error(error));
	return (0);
}

char	*clear_str(char *str)
{
	int		i;
	int		j;
	int		len;
	char	*tmp;

	len = ft_strlen(str);
	tmp = (char *)malloc(sizeof(char) * (len + 1));
	if (!tmp || !str)
		return (0);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] != '\'' && str[i] != '\"')
		{
			tmp[j] = str[i];
			j++;
		}
		i++;
	}
	tmp[j] = '\0';
	return (tmp);
}

int	check_count_single_quote(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			j++;
		i++;
	}
	return (j);
}
