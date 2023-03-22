/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darakely <darakely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 12:18:30 by darakely          #+#    #+#             */
/*   Updated: 2022/12/09 20:52:07 by darakely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	len_list_env(t_data *data)
{
	t_env	*tmp;
	int		len;

	tmp = data->info_env;
	len = 0;
	while (data->info_env)
	{
		len++;
		data->info_env = data->info_env->next;
	}
	data->info_env = tmp;
	return (len);
}

char	**get_correct_env(t_data *data)
{
	char	**correct_env;
	t_env	*tmp;
	int		len;
	int		i;

	tmp = data->info_env;
	len = len_list_env(data);
	correct_env = (char **)malloc(sizeof(char *) * (len + 1));
	if (!correct_env)
		return (0);
	i = 0;
	while (data->info_env)
	{
		if (data->info_env->status == 0)
		{
			correct_env[i] = ft_strdup(data->info_env->key);
			correct_env[i] = ft_strjoin(correct_env[i], data->info_env->value);
			i++;
		}
		data->info_env = data->info_env->next;
	}
	data->info_env = tmp;
	correct_env[i] = 0;
	return (correct_env);
}

void	ft_swap(int *a, int *b)
{
	int	swap;

	swap = *a;
	*a = *b;
	*b = swap;
}

void	norm_clear_value_env(char *ptr, char *str, int *i, int *j)
{
	if (str[*i] == '\'')
	{
		(*i)++;
		while (str[*i] != '\'' && str[*i])
		{
			ptr[*j] = str[*i];
			(*j)++;
			(*i)++;
		}
		(*i)++;
	}
	else
	{
		ptr[*j] = str[*i];
		(*j)++;
		(*i)++;
	}
}
