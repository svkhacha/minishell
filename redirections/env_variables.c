/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_variables.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darakely <darakely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 18:39:45 by darakely          #+#    #+#             */
/*   Updated: 2022/12/09 14:14:17 by darakely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*correct_value(char *str)
{
	char	*ptr;
	int		i;
	int		j;

	ptr = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!ptr)
		return (0);
	i = 0;
	j = 0;
	while (str[i])
	{
		while (!((str[i] >= 'a' && str[i] <= 'z') || \
					(str[i] >= 'A' && str[i] <= 'Z') || str[i] == '$'))
		{
			ptr[j] = str[i];
			i++;
			j++;
		}
		break ;
	}
	ptr[j] = '\0';
	return (ptr);
}

char	*get_end_value(char *str)
{
	char	*ptr;
	int		i;
	int		j;

	ptr = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!ptr)
		return (0);
	i = 0;
	j = 0;
	while (str[i] && (str[i] == '\'' || str[i] == '\"'))
		i++;
	while (str[i] && (str[i] == '$' || (str[i] >= 'a' && str[i] <= 'z') \
		|| (str[i] >= 'A' && str[i] <= 'Z') || (str[i] >= '0' \
		&& str[i] <= '9')))
		i++;
	while (str[i])
	{
		ptr[j] = str[i];
		i++;
		j++;
	}
	ptr[j] = '\0';
	return (ptr);
}

char	*get_value(t_data *data, char *check, char *clear_check, int i)
{
	t_env	*tmp;
	char	*correct_value_name;
	char	*clear;

	tmp = data->info_env;
	clear = clear_str(check);
	clear++;
	while (data->info_env)
	{
		i = check_size_str(data->info_env->key, clear);
		if (data->info_env->status == 0 && data->info_env->key \
				&& ft_strncmp(data->info_env->key, clear, i - 1) == 0)
		{
			correct_value_name = correct_value(check);
			check = ft_strdup(data->info_env->value);
			correct_value_name = ft_strjoin(correct_value_name, check);
			correct_value_name = ft_strjoin(correct_value_name, \
					get_end_value(clear_check));
			data->info_env = tmp;
			return (correct_value_name);
		}
		data->info_env = data->info_env->next;
	}
	data->info_env = tmp;
	return (check);
}
