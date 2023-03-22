/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_execve.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darakely <darakely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 12:30:28 by darakely          #+#    #+#             */
/*   Updated: 2022/12/13 19:55:11 by darakely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*find_path(char **env)
{
	int	i;

	i = -1;
	while (env[++i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
			return (env[i] + 5);
	}
	return (0);
}

char	*check_cmd(t_data *data, char **path, char *absolute_path_cmd, int flag)
{
	int		i;
	char	*full_path;
	char	*cmd;
	int		len;

	i = 0;
	if (flag == 1)
		norm_check_cmd_2(data, path, absolute_path_cmd);
	while (path && path[i])
	{
		full_path = ft_strjoin(path[i], "/");
		cmd = ft_strjoin(full_path, absolute_path_cmd);
		if (access(cmd, F_OK) == 0)
			return (cmd);
		i++;
	}
	len = check_size_str("./minishell", correct_heredoc_name \
	(absolute_path_cmd, 0, 0));
	if (ft_strncmp(correct_heredoc_name(absolute_path_cmd, 0, 0), \
	"./minishell", len) == 0)
		return (correct_heredoc_name(absolute_path_cmd, 0, 0));
	if (access(absolute_path_cmd, F_OK) == 0)
		return (absolute_path_cmd);
	return (0);
}

void	close_pipes(t_pipe *pipe)
{
	int	i;

	i = -1;
	while (++i < pipe->count_pipe - 1)
	{
		close(pipe->fd[i][0]);
		close(pipe->fd[i][1]);
	}
}

int	get_execve(t_data *data, char *new_promt, char **env, int i)
{
	pid_t	pid;

	pid = fork();
	data->info_pipe->pid[i] = pid;
	if (pid < 0)
	{
		kill_all_proccess(data, i);
		return (-1);
	}
	else if (pid == 0)
	{
		get_and_set_attr(1);
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		ft_dup2(data, i);
		if (clear_promt_builtins \
		(&data->info_parsing->split_new_promt_execve[i]) != 0)
			split_pipes(data, new_promt, i, 1);
		if (clear_promt_builtins \
		(&data->info_parsing->split_new_promt_execve[i]) == 0)
			norm_get_execve(data, env, new_promt);
		exit(0);
	}
	return (0);
}

int	ft_execve(t_data *data, char *new_promt)
{
	int		i;
	char	*path;
	char	**correct_env;

	correct_env = get_correct_env(data);
	path = find_path(correct_env);
	if (path)
		data->info_pipe->path = ft_split(path, ':');
	i = 0;
	norm_ft_execve(data, correct_env, new_promt, 0);
	return (0);
}
