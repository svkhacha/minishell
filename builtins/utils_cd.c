/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darakely <darakely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 18:56:23 by darakely          #+#    #+#             */
/*   Updated: 2022/12/12 18:21:53 by darakely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_oldpwd_env(t_data *data)
{
	t_env	*tmp;
	char	*pwd;

	tmp = data->info_env;
	pwd = find_pwd_env(data);
	while (data->info_env)
	{
		if (ft_strncmp(data->info_env->key, "OLDPWD=", 7) == 0)
		{
			data->info_env = tmp;
			return ;
		}
		data->info_env = data->info_env->next;
	}
	data->info_env = tmp;
	while (data->info_env->next)
		data->info_env = data->info_env->next;
	data->info_env->next = malloc(sizeof(t_env));
	if (!data->info_env->next)
		return ;
	data->info_env->next->next = 0;
	data->info_env->next->key = ft_strdup("OLDPWD=");
	data->info_env->next->value = ft_strdup(pwd);
	data->info_env->next->status = 0;
	data->info_env = tmp;
}

void	change_pwd_export(t_data *data, char *str, char *check)
{
	t_export	*tmp;
	char		pwd[1024];

	tmp = data->info_export;
	while (data->info_export)
	{
		if (ft_strncmp(data->info_export->key, "PWD=", 4) == 0)
		{
			check = ft_strdup(getcwd(pwd, sizeof(pwd)));
			if (check)
			{
				continue_change_pwd_export(data->info_export, check);
				break ;
			}
			data->info_export->value = \
			ft_strjoin(data->info_export->value, "/");
			data->info_export->value = \
			ft_strjoin(data->info_export->value, str);
			break ;
		}
		data->info_export = data->info_export->next;
	}
	data->info_export = tmp;
	free(check);
	check = 0;
}

char	*find_pwd_export(t_data *data)
{
	t_export	*tmp;
	char		*pwd;

	tmp = data->info_export;
	pwd = 0;
	while (data->info_export)
	{
		if (ft_strncmp(data->info_export->key, "PWD=", 4) == 0)
		{
			pwd = correct_heredoc_name(data->info_export->value, 0, 0);
			break ;
		}
		data->info_export = data->info_export->next;
	}
	data->info_export = tmp;
	return (pwd);
}

char	*find_home_export(t_data *data)
{
	t_export	*tmp;
	char		*home;

	home = 0;
	tmp = data->info_export;
	while (data->info_export)
	{
		if (ft_strncmp(data->info_export->key, "HOME=", 5) == 0)
		{
			if (data->info_export->status == 0)
				home = ft_strdup(data->info_env->value);
			break ;
		}
		data->info_export = data->info_export->next;
	}
	data->info_export = tmp;
	return (home);
}

void	change_oldpwd_export(t_data *data, char *pwd)
{
	t_export	*tmp;

	tmp = data->info_export;
	pwd = find_pwd_export(data);
	while (data->info_export)
	{
		if (ft_strncmp(data->info_export->key, "OLDPWD", 6) == 0)
		{
			if (ft_strncmp(data->info_export->key, "OLDPWD=", 7) != 0)
				data->info_export->key = \
								ft_strjoin(data->info_export->key, "=");
			free(data->info_export->value);
			data->info_export->value = 0;
			data->info_export->value = ft_strdup("\"");
			data->info_export->value = \
			ft_strjoin(data->info_export->value, pwd);
			data->info_export->value = \
			ft_strjoin(data->info_export->value, "\"");
			break ;
		}
		data->info_export = data->info_export->next;
	}
	data->info_export = tmp;
	free(pwd);
	pwd = 0;
}
