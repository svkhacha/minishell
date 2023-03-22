/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_5.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darakely <darakely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 12:46:55 by darakely          #+#    #+#             */
/*   Updated: 2022/12/13 20:32:19 by darakely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	continue_norm_ft_execve_3(t_data *data, char **correct_env)
{
	data->i = -1;
	while (++data->i < data->info_pipe->count_pipe)
	{
		norm_norm_ft_execve_3(data);
		if (get_execve(data, data->info_pipe->split_pipe[data->i], \
		correct_env, data->i) == -1)
		{
			close_pipes(data->info_pipe);
			return (-1);
		}
	}
	close_pipes(data->info_pipe);
	return (0);
}

void	continue_norm_ft_execve_2(t_data *data, int flag)
{
	data->j = -1;
	while (++data->j < data->i)
	{
		waitpid(data->info_pipe->pid[data->j], data->error_code, 0);
		if (WIFSIGNALED(*data->error_code))
		{
			if (flag == 0)
			{
				if (*data->error_code == SIGQUIT)
					ft_putstr_fd("Quit: 3", STDOUT_FILENO);
				ft_putstr_fd("\n", STDOUT_FILENO);
				flag = 1;
			}
			*data->error_code = WTERMSIG(*data->error_code) + 128;
		}
		if (WIFEXITED(*data->error_code))
			*data->error_code = WEXITSTATUS(*data->error_code);
	}
}

void	norm_norm_ft_execve_3(t_data *data)
{
	if (data->info_parsing->flag_for_prelast_redirect[data->i] == _outfile)
		data->info_parsing->index_outfile++;
	if (data->info_parsing->flag_for_prelast_redirect[data->i] == _append)
		data->info_parsing->index_append++;
	if (data->info_parsing->flag_for_prelast_redirect[data->i] == _infile)
		data->info_parsing->index_infile++;
	if (data->info_parsing->flag_for_last_redirect[data->i] == _heredoc)
		data->info_parsing->index_heredoc++;
}

void	norm_norm_ft_execve_2(t_data *data)
{
	if (data->info_parsing->fixed_prelast_redirect[data->i] == _outfile)
		data->info_parsing->index_outfile++;
	if (data->info_parsing->fixed_prelast_redirect[data->i] == _append)
		data->info_parsing->index_append++;
	if (data->info_parsing->fixed_prelast_redirect[data->i] == _infile)
		data->info_parsing->index_infile++;
	if (data->info_parsing->fixed_prelast_redirect[data->i] == _heredoc)
		data->info_parsing->index_heredoc++;
}

void	continue_norm_ft_execve(t_data *data, char *new_promt)
{
	data->i = -1;
	data->info_pipe->split_pipe = ft_split(new_promt, '|');
	while (data->info_pipe->split_pipe && \
	data->info_pipe->split_pipe[++data->i])
		;
	data->info_pipe->count_pipe = data->i;
	data->info_pipe->pid = malloc(sizeof(pid_t) * (data->i + 1));
	data->j = -1;
	while (++data->j <= data->i)
		data->info_pipe->pid[data->j] = -1;
	data->info_pipe->cnt_cmd = (data->info_pipe->count_pipe - 1);
	data->info_pipe->fd = malloc(sizeof(int *) * (data->info_pipe->count_pipe));
	data->i = -1;
	while (++data->i < data->info_pipe->count_pipe - 1)
		pipe(data->info_pipe->fd[data->i]);
	data->i = -1;
	data->info_parsing->split_new_promt_execve = ft_split(new_promt, '|');
}
