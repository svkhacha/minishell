/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_4.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darakely <darakely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 12:12:21 by darakely          #+#    #+#             */
/*   Updated: 2022/12/13 20:01:26 by darakely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_backslash(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] == '/')
		i++;
	if (str[i] == '\0')
		return (0);
	return (-1);
}

void	ft_dup2(t_data *data, int i)
{
	if (data->info_parsing->flag_for_last_redirect[i] == _default)
	{
		if (i == 0)
			dup2(data->info_pipe->fd[0][1], STDOUT_FILENO);
		else if (i == data->info_pipe->count_pipe - 1)
			dup2(data->info_pipe->fd[i - 1][0], STDIN_FILENO);
		else
		{
			dup2(data->info_pipe->fd[i - 1][0], STDIN_FILENO);
			dup2(data->info_pipe->fd[i][1], STDOUT_FILENO);
		}
	}
	else
		get_dup2_redirect(data, i);
	close_pipes(data->info_pipe);
}

void	continue_norm_check_cmd(t_data *data, char *absolute_path_cmd)
{
	if (ft_strchr(absolute_path_cmd, '/') != 0 && \
	opendir(absolute_path_cmd) == 0)
	{
		ft_putstr_fd("❌ minishell: ", STDERR_FILENO);
		ft_putstr_fd(correct_heredoc_name \
		(data->info_pipe->cmd_args[0], 0, 0), STDERR_FILENO);
		ft_putstr_fd(" : No such file or directory\n", STDERR_FILENO);
		exit (127);
	}
}

void	kill_all_proccess(t_data *data, int i)
{
	int	j;

	j = -1;
	perror("❌ minishell: fork");
	while (data->info_pipe->pid && ++j < i)
	{
		kill(data->info_pipe->pid[j], SIGTERM);
		waitpid(data->info_pipe->pid[j], NULL, 0);
	}
}

void	norm_close_all_fds(t_data *data)
{
	data->i = -1;
	if (data->info_redirect->fd_heredoc && \
	data->info_redirect->fd_heredoc[0] != -1)
	{
		while (data->info_redirect->heredoc_count_in_pipe && \
		data->info_redirect->heredoc_count_in_pipe[++data->i] != -1)
		{
			data->j = -1;
			while (data->info_redirect->fd_heredoc && \
			data->info_redirect->fd_heredoc[++data->j] != -1)
				close(data->info_redirect->fd_heredoc[data->j]);
		}
	}
}
