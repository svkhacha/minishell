/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darakely <darakely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 12:34:50 by darakely          #+#    #+#             */
/*   Updated: 2022/12/13 18:48:19 by darakely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	last_check_oldpwd(t_data *data)
{
	t_export	*tmp;

	tmp = data->info_export;
	while (data->info_export->next)
	{
		if (ft_strncmp(data->info_export->key, "OLDPWD", 6) == 0)
		{
			data->info_export->value = 0;
			data->info_export = tmp;
			return ;
		}
		data->info_export = data->info_export->next;
	}
	data->info_export->next = malloc(sizeof(t_export));
	if (!data->info_export->next)
		return ;
	data->info_export->next->key = ft_strdup("OLDPWD");
	data->info_export->next->value = 0;
	data->info_export->next->next = 0;
	data->info_export->next->status = 0;
	data->info_export = tmp;
}

void	add_variable_export(t_data *data, char *split, char *str, char *check)
{
	char		**new_split;
	char		**if_split_error;

	new_split = ft_split(split, '=');
	if_split_error = 0;
	if (new_split && new_split[0])
	{
		check = correct_heredoc_name(new_split[0], 0, 0);
		my_free(&new_split[0]);
		new_split[0] = ft_strdup(check);
		my_free(&check);
		if (count_equal(new_split[0]) > 0)
		{
			if_split_error = ft_split(new_split[0], '=');
			my_free(&new_split[0]);
			new_split[0] = ft_strdup(if_split_error[0]);
		}
	}
	if (check_add_export(new_split[0], split, 0, 0) == -1)
		data->gr = 1;
	if (data->gr != 1)
		continue_add_variable_export_2(data, str, new_split, split);
	if (data->flag == 0)
		free_array(&new_split);
	free_array(&if_split_error);
}

int	check_export(t_data *data, char **str, int i, char **split)
{
	if (str)
		split = ft_split(*str, ' ');
	else
		return (0);
	if (split && split[0])
	{
		while (str && split && split[i])
		{
			add_variable_export(data, split[i], 0, 0);
			if (check_equal(split[i]) == 0)
				add_variable_env(data, split[i], 0, 0);
			str++;
			if (!str)
				break ;
			free_array(&split);
			split = ft_split(*str, ' ');
		}
		sort_export(data, 0);
		free_array(&split);
		return (-1);
	}
	free_array(&split);
	return (0);
}

void	init_export(t_data *data, char **env, int i, char **split)
{
	t_export	*tmp;

	data->info_export = malloc(sizeof(t_export));
	data->info_export->next = 0;
	tmp = data->info_export;
	while (env[++i])
	{
		split = ft_split(env[i], '=');
		data->info_export->key = ft_strdup(split[0]);
		data->info_export->status = 0;
		norm_init_export(data, split[1]);
		free_array(&split);
		if (env[i + 1])
		{
			data->info_export->next = malloc(sizeof(t_export));
			if (!data->info_export->next)
				return ;
			data->info_export->next->next = 0;
		}
		else
			break ;
		data->info_export = data->info_export->next;
	}
	data->info_export = tmp;
	last_check_oldpwd(data);
}

void	ft_export(t_data *data, char **str)
{
	t_export	*tmp;

	tmp = data->info_export;
	if (check_export(data, str, 0, 0) == -1)
		return ;
	sort_export(data, 0);
	while (data->info_export)
	{
		if (data->info_export->status == 0)
		{
			ft_putstr_fd("declare -x ", STDOUT_FILENO);
			ft_putstr_fd(data->info_export->key, STDOUT_FILENO);
			if (data->info_export->value)
				ft_putstr_fd(data->info_export->value, STDOUT_FILENO);
			ft_putstr_fd("\n", STDOUT_FILENO);
		}
		data->info_export = data->info_export->next;
	}
	data->info_export = tmp;
	*data->error_code = 0;
}
