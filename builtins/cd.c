/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darakely <darakely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 17:15:11 by darakely          #+#    #+#             */
/*   Updated: 2022/12/13 16:07:07 by darakely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	change_pwd_env(t_data *data, char *str)
{
	t_env	*tmp;
	char	pwd[1024];

	tmp = data->info_env;
	while (data->info_env)
	{
		if (ft_strncmp(data->info_env->key, "PWD=", 4) == 0)
		{
			if (getcwd(pwd, sizeof(pwd)) == 0)
			{
				ft_putstr_fd("❌ minishell: cd: error retrieving current directory: \
getcwd: cannot access parent directories:", STDERR_FILENO);
				ft_putstr_fd(strerror(errno), STDERR_FILENO);
				ft_putstr_fd("\n", STDERR_FILENO);
				data->info_env->value = ft_strjoin(data->info_env->value, "/");
				data->info_env->value = ft_strjoin(data->info_env->value, str);
				break ;
			}
			free(data->info_env->value);
			data->info_env->value = 0;
			data->info_env->value = ft_strdup(getcwd(pwd, sizeof(pwd)));
			break ;
		}
		data->info_env = data->info_env->next;
	}
	data->info_env = tmp;
}

char	*find_pwd_env(t_data *data)
{
	t_env	*tmp;
	char	*pwd;

	tmp = data->info_env;
	pwd = 0;
	while (data->info_env)
	{
		if (ft_strncmp(data->info_env->key, "PWD=", 4) == 0)
		{
			pwd = ft_strdup(data->info_env->value);
			break ;
		}
		data->info_env = data->info_env->next;
	}
	data->info_env = tmp;
	return (pwd);
}

char	*find_home_env(t_data *data)
{
	t_env	*tmp;
	char	*home;

	home = 0;
	tmp = data->info_env;
	while (data->info_env)
	{
		if (ft_strncmp(data->info_env->key, "HOME=", 5) == 0)
		{
			if (data->info_env->status == 0)
				home = ft_strdup(data->info_env->value);
			break ;
		}
		data->info_env = data->info_env->next;
	}
	data->info_env = tmp;
	return (home);
}

void	add_oldpwd_in_env(t_data *data, char *pwd)
{
	t_env	*tmp;

	tmp = data->info_env;
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

void	ft_cd(t_data *data, char *str)
{
	char	*home;

	home = find_home_env(data);
	if (str)
		check_and_get_folder(data, str);
	else
	{
		if (chdir(home) < 0)
		{
			ft_putstr_fd("❌ minishell: cd: HOME not set\n", STDERR_FILENO);
			*data->error_code = 1;
		}
		else
			*data->error_code = 0;
	}
	norm_ft_cd(data, str);
	free(home);
	home = 0;
}
