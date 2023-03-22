/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darakely <darakely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 17:31:54 by darakely          #+#    #+#             */
/*   Updated: 2022/12/09 20:41:03 by darakely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	norm_init_env(t_data *data, char *split)
{
	data->info_env->key = ft_strjoin(data->info_env->key, "=");
	data->info_env->value = ft_strdup(split);
	data->info_env->status = 0;
}

int	count_equal(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '=')
			j++;
		i++;
	}
	return (j);
}

int	check_add_env(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (norm_check_add_export(str, i) == -1 \
				|| norm_check_add_export(str, i) == 1)
		{
			if (norm_check_add_export(str, i) == 1)
				i += 2;
			else
				return (-1);
		}
		i++;
	}
	return (0);
}

void	print_or_not(t_data *data, char *str)
{
	t_env	*tmp;

	tmp = data->info_env;
	while (data->info_env)
	{
		if (ft_strncmp(data->info_env->key, str, ft_strlen(str)) == 0)
			data->info_env->value = 0;
		data->info_env = data->info_env->next;
	}
	data->info_env = tmp;
}

int	norm_add_env(char **new_split, t_data *data)
{
	t_env	*tmp;

	tmp = data->info_env;
	if (check_variable_env(data, new_split, 0) == -1)
		return (-1);
	while (data->info_env->next)
		data->info_env = data->info_env->next;
	norm_add_variable_env(data->info_env, new_split);
	data->info_env = tmp;
	return (0);
}
