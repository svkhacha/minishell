/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darakely <darakely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 15:26:41 by darakely          #+#    #+#             */
/*   Updated: 2022/12/13 21:32:52 by darakely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	norm_split_pipes(t_data *data, int j, int flag)
{
	if (j == 0 && flag == 0)
	{
		if (data->info_parsing->flag_for_prelast_redirect[j] == _outfile)
			dup2(data->info_redirect->fd_outfiles[0], STDOUT_FILENO);
		else if (data->info_parsing->flag_for_prelast_redirect[j] == _append)
			dup2(data->info_redirect->fd_append[0], STDOUT_FILENO);
		else if (data->info_parsing->flag_for_prelast_redirect[j] == _infile)
			dup2(data->info_redirect->fd_infiles[0], STDIN_FILENO);
	}
	else
	{
		if (data->info_parsing->flag_for_prelast_redirect[j] == _outfile)
			dup2(data->info_redirect->fd_outfiles \
			[data->info_parsing->index_outfile], STDOUT_FILENO);
		else if (data->info_parsing->flag_for_prelast_redirect[j] == _append)
			dup2(data->info_redirect->fd_append \
			[data->info_parsing->index_append], STDOUT_FILENO);
		else if (data->info_parsing->flag_for_prelast_redirect[j] == _infile)
			dup2(data->info_redirect->fd_infiles \
			[data->info_parsing->index_infile], STDIN_FILENO);
	}
}

void	continue_split_pipes(t_data *data, char **pipe, int j, char *check)
{
	char	**check_unset;
	int		k;

	check_unset = 0;
	k = check_size_str(check, "export");
	if (ft_strncmp(check, "export", k) == 0)
		ft_export(data, &pipe[j + 1]);
	k = check_size_str(check, "unset");
	if (ft_strncmp(check, "unset", k) == 0)
	{
		ft_unset(data, check_unset, &pipe[j + 1], 0);
		free_array(&check_unset);
		unset_env(data, 0, &pipe[j + 1], check_unset);
		free_array(&check_unset);
	}
	k = check_size_str(check, "exit");
	if (ft_strncmp(check, "exit", k) == 0)
		ft_exit(data, &pipe[j + 1]);
	k = check_size_str(check, "echo");
	if (ft_strncmp(check, "echo", k) == 0)
		ft_echo(data, &pipe[j + 1]);
	k = check_size_str(check, "env");
	if (ft_strncmp(check, "env", k) == 0)
		ft_env(data);
}

void	continue_split_pipes_2(t_data *data, char **splited_pipe)
{
	char	*check;
	int		k;

	check = 0;
	k = 0;
	data->i = 0;
	check = correct_heredoc_name(splited_pipe[data->i], 0, 0);
	k = check_size_str(check, "pwd");
	if (ft_strncmp(check, "pwd", k) == 0)
		ft_pwd(data);
	k = check_size_str(check, "cd");
	if (ft_strncmp(check, "cd", k) == 0)
		ft_cd(data, splited_pipe[data->i + 1]);
	else
		continue_split_pipes(data, splited_pipe, data->i, check);
	my_free(&check);
}

void	split_pipes(t_data *data, char *str, int j, int flag)
{
	char	**splited_promt;
	char	**splited_pipe;

	splited_pipe = 0;
	splited_promt = 0;
	data->i = 0;
	splited_promt = ft_split(data->promt, '|');
	if (splited_promt[j])
	{
		splited_pipe = ft_split(str, ' ');
		if (data->info_parsing->flag_for_prelast_redirect[j] != _default)
			norm_split_pipes(data, j, flag);
		if (splited_pipe[data->i])
			continue_split_pipes_2(data, splited_pipe);
		if (flag == 0 && j == 0 && \
		data->info_parsing->flag_for_prelast_redirect[j] != _default)
			dup2(data->info_pipe->output, STDOUT_FILENO);
	}
	free_array(&splited_pipe);
	free_array(&splited_promt);
}
