/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_get_execve.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darakely <darakely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 19:33:44 by darakely          #+#    #+#             */
/*   Updated: 2022/12/13 21:27:44 by darakely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	norm_check_cmd(t_data *data, char *absolute_path_cmd)
{
	if ((ft_strchr(absolute_path_cmd, '/') != 0 && opendir(absolute_path_cmd)) \
	|| (check_backslash(absolute_path_cmd) == 0))
	{
		ft_putstr_fd("❌ minishell: ", STDERR_FILENO);
		ft_putstr_fd(correct_heredoc_name \
		(data->info_pipe->cmd_args[0], 0, 0), STDERR_FILENO);
		ft_putstr_fd(" : is a directory\n", STDERR_FILENO);
		exit (126);
	}
	if (access(absolute_path_cmd, F_OK) == 0 && \
	access(absolute_path_cmd, X_OK) != 0)
	{
		ft_putstr_fd("❌ minishell: ", STDERR_FILENO);
		ft_putstr_fd(correct_heredoc_name \
		(data->info_pipe->cmd_args[0], 0, 0), STDERR_FILENO);
		ft_putstr_fd(" : Permission denied\n", STDERR_FILENO);
		exit (126);
	}
	continue_norm_check_cmd(data, absolute_path_cmd);
}

void	continue_get_dup2_redirect(t_data *data, int i)
{
	if (data->info_parsing->fixed_prelast_redirect[i] == _outfile)
	{
		data->info_parsing->index_outfile++;
		dup2(data->info_redirect->fd_outfiles \
		[data->info_parsing->index_outfile], STDOUT_FILENO);
	}
	else if (data->info_parsing->fixed_prelast_redirect[i] == _append)
	{
		data->info_parsing->index_append++;
		dup2(data->info_redirect->fd_append \
		[data->info_parsing->index_append], STDOUT_FILENO);
	}
	else if (data->info_parsing->fixed_prelast_redirect[i] == _infile)
	{
		data->info_parsing->index_infile++;
		dup2(data->info_redirect->fd_infiles \
		[data->info_parsing->index_infile], STDIN_FILENO);
	}
}

void	norm_get_dup2_redirect(t_data *data, int i)
{
	if (data->info_parsing->flag_for_last_redirect[i] == _outfile)
		dup2(data->info_redirect->fd_outfiles \
		[data->info_parsing->index_outfile], STDOUT_FILENO);
	else if (data->info_parsing->flag_for_prelast_redirect[i] == _append)
		dup2(data->info_redirect->fd_append \
		[data->info_parsing->index_append], STDOUT_FILENO);
	else if (data->info_parsing->flag_for_prelast_redirect[i] == _infile)
		dup2(data->info_redirect->fd_infiles \
		[data->info_parsing->index_infile], STDIN_FILENO);
}

void	get_dup2_redirect(t_data *data, int i)
{
	if (data->info_parsing->flag_for_last_redirect[i] == _heredoc)
	{
		dup2(data->info_redirect->fd_heredoc \
		[data->info_parsing->index_heredoc], STDIN_FILENO);
		if (data->info_parsing->flag_for_prelast_redirect[i] == _outfile)
			dup2(data->info_redirect->fd_outfiles \
			[data->info_parsing->index_outfile], STDOUT_FILENO);
		else if (data->info_parsing->flag_for_prelast_redirect[i] == _append)
			dup2(data->info_redirect->fd_append \
			[data->info_parsing->index_append], STDOUT_FILENO);
		else if (data->info_parsing->flag_for_prelast_redirect[i] == _infile)
			dup2(data->info_redirect->fd_infiles \
			[data->info_parsing->index_infile], STDIN_FILENO);
	}
	else
		norm_get_dup2_redirect(data, i);
	if (data->info_parsing->fixed_prelast_redirect[i] != _default)
		continue_get_dup2_redirect(data, i);
}

int	norm_ft_execve(t_data *data, char **correct_env, char *new_promt, int flag)
{
	char	**split_space;

	continue_norm_ft_execve(data, new_promt);
	split_space = ft_split(new_promt, ' ');
	if (data->info_pipe->split_pipe && data->info_pipe->split_pipe[0] \
	&& !data->info_pipe->split_pipe[1])
	{
		if (clear_promt_builtins(&split_space[0]) != 0)
		{
			split_pipes(data, new_promt, 0, 0);
			free_array(&split_space);
			free_array(&correct_env);
			return (0);
		}
	}
	if (continue_norm_ft_execve_3(data, correct_env) == -1)
		return (-1);
	continue_norm_ft_execve_2(data, flag);
	free_array(&correct_env);
	free_array(&split_space);
	return (0);
}
