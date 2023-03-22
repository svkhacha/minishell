/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darakely <darakely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 10:31:36 by darakely          #+#    #+#             */
/*   Updated: 2022/12/12 18:24:29 by darakely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	norm_add_variable_env(t_env *info, char **new_split)
{
	info->next = malloc(sizeof(t_env));
	if (!info->next)
		return ;
	info->next->next = 0;
	info->next->key = ft_strdup(new_split[0]);
	info->next->value = ft_strdup(new_split[1]);
	info->next->status = 0;
}

int	check_variable_env(t_data *data, char **new_split, int i)
{
	t_env	*tmp;

	tmp = data->info_env;
	new_split[0] = ft_strjoin(new_split[0], "=");
	while (data->info_env)
	{
		i = check_size_str(new_split[1], new_split[0]);
		if (ft_strncmp(data->info_env->key, new_split[0], i) == 0)
		{
			free(data->info_env->value);
			data->info_env->value = 0;
			data->info_env->value = ft_strdup(new_split[1]);
			data->info_env = tmp;
			return (-1);
		}
		data->info_env = data->info_env->next;
	}
	data->info_env = tmp;
	print_or_not(data, new_split[0]);
	return (0);
}

void	add_variable_env(t_data *data, char *split, char **new_split, char *str)
{
	char	*check;

	str = 0;
	new_split = ft_split(split, '=');
	check = ft_strdup(find_equal(split));
	if (check)
		continue_add_variable_env(&new_split, str, check);
	if (!new_split[0] || !*new_split[0])
		;
	else if (check_add_env(new_split[0]) == -1)
		;
	else if (check_plus_env(data, new_split, 0, 0) == -1)
		;
	else if (norm_add_env(new_split, data) == -1)
		;
	free_array(&new_split);
}

void	init_env(t_data *data, char **env, int i, char **split)
{
	t_env	*tmp;

	data->info_env = malloc(sizeof(t_env));
	if (!data->info_env)
		return ;
	data->info_env->next = 0;
	tmp = data->info_env;
	while (env[++i])
	{
		split = ft_split(env[i], '=');
		data->info_env->key = ft_strdup(split[0]);
		data->info_env->status = 0;
		if (ft_strncmp(split[0], "OLDPWD", 6) == 0)
			data->info_env->key = 0;
		else
			norm_init_env(data, split[1]);
		free_array(&split);
		if (!env[i + 1])
			break ;
		data->info_env->next = malloc(sizeof(t_env));
		data->info_env->next->next = 0;
		data->info_env = data->info_env->next;
	}
	data->info_env = tmp;
}

void	ft_env(t_data *data)
{
	char	**print;
	int		i;

	print = get_correct_env(data);
	i = -1;
	while (print && print[++i])
	{
		ft_putstr_fd(print[i], STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
	}
	free_array(&print);
	*data->error_code = 0;
}
