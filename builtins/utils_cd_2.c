/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_cd_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darakely <darakely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 18:13:42 by darakely          #+#    #+#             */
/*   Updated: 2022/12/13 16:00:59 by darakely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	continue_change_pwd_export(t_export *info, char *check)
{
	free(info->value);
	info->value = 0;
	info->value = ft_strdup("\"");
	info->value = ft_strjoin(info->value, check);
	info->value = ft_strjoin(info->value, "\"");
}

void	change_oldpwd_env(t_data *data)
{
	t_env	*tmp;
	char	*pwd;

	tmp = data->info_env;
	pwd = find_pwd_env(data);
	while (data->info_env)
	{
		if (ft_strncmp(data->info_env->key, "OLDPWD=", 7) == 0)
		{
			free(data->info_env->value);
			data->info_env->value = 0;
			data->info_env->value = ft_strdup(pwd);
			data->info_env = tmp;
			free(pwd);
			pwd = 0;
			return ;
		}
		data->info_env = data->info_env->next;
	}
	data->info_env = tmp;
	add_oldpwd_in_env(data, pwd);
	free(pwd);
	pwd = 0;
}

void	check_and_get_folder(t_data *data, char *check)
{
	char	*error;
	char	*str;

	error = 0;
	str = 0;
	str = correct_heredoc_name(check, 0, 0);
	if (chdir(str) < 0)
	{
		error = correct_heredoc_name(check, 0, 0);
		ft_putstr_fd("❌ minishell: cd: ", STDERR_FILENO);
		ft_putstr_fd(error, STDERR_FILENO);
		ft_putstr_fd(" : ", STDERR_FILENO);
		ft_putstr_fd(strerror(errno), STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
		*data->error_code = 1;
	}
	else
		*data->error_code = 0;
	free(error);
	free(str);
	str = 0;
	error = 0;
}

void	norm_ft_cd(t_data *data, char *str)
{
	char	*pwd;
	char	*check;

	pwd = 0;
	check = 0;
	change_oldpwd_env(data);
	change_pwd_env(data, str);
	change_oldpwd_export(data, pwd);
	change_pwd_export(data, str, check);
}
