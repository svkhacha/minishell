/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_heredoc_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darakely <darakely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 18:09:30 by darakely          #+#    #+#             */
/*   Updated: 2022/12/13 22:24:49 by darakely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	norm_ft_heredoc(t_data *data, char **pipe, int j, int count)
{
	int	i;

	i = -1;
	pipe = ft_split(data->promt, '|');
	check_count_heredoc(data, count);
	while (pipe[++i])
		;
	i += j + 1;
	count_heredoc_in_pipe(data, pipe, i, 0);
	free_array(&pipe);
}

void	norm_open_heredoc(t_data *data, int fd, char *heredoc, int i)
{
	char	*clear_check;
	char	*tmp;
	int		k;

	clear_check = ft_strdup(heredoc);
	k = check_size_str(data->info_redirect->heredoc_name[i], \
			data->info_redirect->heredoc[i]);
	if (ft_strncmp(data->info_redirect->heredoc[i], \
				data->info_redirect->heredoc_name[i], k) == 0)
		tmp = get_value(data, heredoc, clear_check, 0);
	else
		tmp = ft_strdup(heredoc);
	write(fd, tmp, ft_strlen(tmp));
	write(fd, "\n", 1);
	free(tmp);
}

void	open_heredoc(t_data *data, int i, int fd, char *heredoc)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, SIG_DFL);
		heredoc = readline("> ");
		while (close_heredocs(data, heredoc, i))
		{
			norm_open_heredoc(data, fd, heredoc, i);
			heredoc = readline("> ");
			if (!heredoc)
				exit(0);
		}
		exit(0);
	}
	waitpid(pid, data->error_code, 0);
	if (WIFSIGNALED(data->error_code))
	{
		data->heredoc = WTERMSIG(data->error_code);
		write(1, "\n", 1);
	}
	if (WIFEXITED(data->error_code))
		*data->error_code = WEXITSTATUS(data->error_code);
}

void	count_heredoc_in_pipe(t_data *data, char **pipe, int k, int j)
{
	int	count;

	data->i = 0;
	data->info_redirect->heredoc_count_in_pipe = malloc(sizeof(int) * k);
	data->info_redirect->fd_heredoc = malloc(sizeof(int) * k);
	count = -1;
	while (++count < k)
	{
		data->info_redirect->heredoc_count_in_pipe[count] = -1;
		data->info_redirect->fd_heredoc[count] = -1;
	}
	while (pipe && pipe[data->i])
	{
		j = 0;
		count = 0;
		while (pipe[data->i][j])
		{
			if (pipe[data->i][j] == '<' && (pipe[data->i][j + 1] \
			&& pipe[data->i][j + 1] == '<'))
				count++;
			j++;
		}
		data->info_redirect->heredoc_count_in_pipe[data->i] = count;
		data->i++;
	}
}

int	check_fd_heredoc(t_data *data)
{
	char	**pipe;
	int		i;
	int		j;
	int		count;

	pipe = ft_split(data->promt, '|');
	i = -1;
	while (pipe[++i])
	{
		j = -1;
		count = 0;
		while (pipe[i][++j])
		{
			if (pipe[i][j] == '<' && (pipe[i][j + 1] && pipe[i][j + 1] == '<'))
				count++;
		}
	}
	free_array(&pipe);
	return (0);
}
