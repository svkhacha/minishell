/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darakely <darakely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 17:19:28 by darakely          #+#    #+#             */
/*   Updated: 2022/12/12 18:33:04 by darakely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	if_plus(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '+')
			return (0);
		i++;
	}
	return (-1);
}

void	add_plus_env(t_data *data, char **new_split, char **check_plus)
{
	t_env	*tmp;
	char	*check;

	check = 0;
	tmp = data->info_env;
	while (data->info_env->next)
		data->info_env = data->info_env->next;
	data->info_env->next = malloc(sizeof(t_env));
	if (!data->info_env->next)
		return ;
	data->info_env->next->next = 0;
	data->info_env->next->key = ft_strdup(check_plus[0]);
	check = correct_heredoc_name(new_split[1], 0, 0);
	data->info_env->next->value = ft_strdup(check);
	data->info_env->next->status = 0;
	data->info_env = tmp;
	free(check);
	check = 0;
}

int	check_plus_env(t_data *data, char **new_split, \
					char *check, char **check_plus)
{
	t_env	*tmp;
	int		i;

	tmp = data->info_env;
	check_plus = ft_split(new_split[0], '+');
	if (if_plus(new_split[0]) != 0 || !check_plus || \
	!check_plus[0] || !*check_plus[0])
	{
		free_array(&check_plus);
		return (0);
	}
	check_plus[0] = ft_strjoin(check_plus[0], "=");
	while (data->info_env)
	{
		i = check_size_str(data->info_env->key, check_plus[0]);
		if (ft_strncmp(data->info_env->key, check_plus[0], i) == 0)
			return (continue_check_plus_env(data->info_env, check, \
			new_split, tmp));
		data->info_env = data->info_env->next;
	}
	data->info_env = tmp;
	add_plus_env(data, new_split, check_plus);
	free_array(&check_plus);
	return (-1);
}

char	*clear_value_env(char *str, int i, int j)
{
	char	*ptr;

	if (!str || !*str)
		return (NULL);
	ptr = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!ptr)
		return (0);
	while (str[i])
	{
		if (str[i] == '\"')
		{
			i++;
			while (str[i] != '\"' && str[i])
			{
				ptr[j] = str[i];
				j++;
				i++;
			}
			i++;
		}
		else
			norm_clear_value_env(ptr, str, &i, &j);
	}
	ptr[j] = '\0';
	return (ptr);
}

void	change_value_env(t_data *data, char *split)
{
	t_env	*tmp;
	char	*str;
	char	**check;

	tmp = data->info_env;
	str = 0;
	check = ft_split(split, '=');
	while (data->info_env->next)
		data->info_env = data->info_env->next;
	str = clear_value_env(check[1], 0, 0);
	free(data->info_env->value);
	data->info_env->value = 0;
	data->info_env->value = ft_strdup(str);
	data->info_env = tmp;
	free_array(&check);
	free(str);
	str = 0;
}
