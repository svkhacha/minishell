/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_execve_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darakely <darakely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 11:57:27 by darakely          #+#    #+#             */
/*   Updated: 2022/12/13 12:04:36 by darakely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	norm_get_execve(t_data *data, char **env, char *new_promt)
{
	int	j;

	j = -1;
	free_array(&data->info_pipe->cmd_args);
	data->info_pipe->cmd_args = ft_split(new_promt, ' ');
	data->info_pipe->cmd = check_cmd(data, data->info_pipe->path, \
	correct_heredoc_name(data->info_pipe->cmd_args[0], 0, 0), 0);
	while (data->info_pipe->cmd_args && data->info_pipe->cmd_args[++j])
		data->info_pipe->cmd_args[j] = correct_heredoc_name \
		(data->info_pipe->cmd_args[j], 0, 0);
	execve(data->info_pipe->cmd, data->info_pipe->cmd_args, env);
	check_cmd(data, data->info_pipe->path, \
	data->info_pipe->cmd_args[0], 1);
}

void	norm_check_cmd_2(t_data *data, char **path, char *absolute_path_cmd)
{
	norm_check_cmd(data, absolute_path_cmd);
	if (!path)
	{
		ft_putstr_fd("❌ minishell: ", STDERR_FILENO);
		ft_putstr_fd(correct_heredoc_name \
		(data->info_pipe->cmd_args[0], 0, 0), STDERR_FILENO);
		ft_putstr_fd(" : No such file or directory\n", STDERR_FILENO);
		exit(127);
	}
	ft_putstr_fd("❌ minishell: ", STDERR_FILENO);
	ft_putstr_fd(correct_heredoc_name \
	(data->info_pipe->cmd_args[0], 0, 0), STDERR_FILENO);
	ft_putstr_fd(" : command not found\n", STDERR_FILENO);
	exit (127);
}
