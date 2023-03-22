/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darakely <darakely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 17:21:58 by darakely          #+#    #+#             */
/*   Updated: 2022/12/13 20:08:40 by darakely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	*g_status;

void	get_exit(t_data *data)
{
	int	error_code;

	error_code = *data->error_code;
	write(1, "exit\n", 5);
	get_and_set_attr(1);
	free_all(data, 0);
	exit(error_code);
}

int	a(void)
{
	return (0);
}

t_data	init_lists(int argc, char **argv, char **env, t_data *data)
{
	char	**split_env;
	char	**split_export;

	split_env = 0;
	split_export = 0;
	init_env(data, env, -1, split_env);
	init_export(data, env, -1, split_export);
	rl_event_hook = a;
	(void)(argc+argv);
	return (*data);
}

void	norm_change_shlvl(t_data *data)
{
	int		shlvl;
	char	*new_shlvl;

	new_shlvl = 0;
	shlvl = ft_atoi(data->info_env->value);
	shlvl++;
	if (shlvl > 1000)
	{
		ft_putstr_fd("❌ minishell: warning: shell level (", STDOUT_FILENO);
		ft_putstr_fd(ft_itoa(shlvl), STDOUT_FILENO);
		ft_putstr_fd(") too high, resetting to 1\n", STDOUT_FILENO);
		shlvl = 1;
	}
	else if (shlvl == 1000)
		shlvl = 0;
	free(data->info_env->value);
	data->info_env->value = 0;
	new_shlvl = ft_itoa(shlvl);
	if (shlvl == 0)
		data->info_env->value = 0;
	else
		data->info_env->value = ft_strdup(new_shlvl);
	free(new_shlvl);
	new_shlvl = 0;
}

void	change_shlvl(t_data *data)
{
	t_env	*tmp;
	int		len;
	char	*str;
	char	*new_shlvl;
	char	*check;

	new_shlvl = 0;
	check = 0;
	str = 0;
	tmp = data->info_env;
	len = 0;
	while (data->info_env)
	{
		len = check_size_str(data->info_env->key, "SHLVL=");
		if (ft_strncmp(data->info_env->key, "SHLVL=", len) == 0)
		{
			norm_change_shlvl(data);
			break ;
		}
		data->info_env = data->info_env->next;
	}
	data->info_env = tmp;
	change_shlvl_in_export(data, check, str, new_shlvl);
}
