/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darakely <darakely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 14:57:43 by darakely          #+#    #+#             */
/*   Updated: 2022/12/12 19:48:47 by darakely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	continue_ft_pwd(t_data *data)
{
	t_env	*tmp;
	int		len;

	tmp = data->info_env;
	while (data->info_env)
	{
		len = check_size_str("PWD=", data->info_env->key);
		if (ft_strncmp(data->info_env->key, "PWD=", len) == 0)
		{
			ft_putstr_fd(data->info_env->value, STDOUT_FILENO);
			ft_putstr_fd("\n", STDOUT_FILENO);
			data->info_env = tmp;
			break ;
		}
		data->info_env = data->info_env->next;
	}
	data->info_env = tmp;
	*data->error_code = 0;
}

void	ft_pwd(t_data *data)
{
	char	pwd[1024];

	if (getcwd(pwd, sizeof(pwd)))
	{
		ft_putstr_fd(pwd, STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
	}
	else
		continue_ft_pwd(data);
}
