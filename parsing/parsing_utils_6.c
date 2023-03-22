/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_6.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darakely <darakely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 13:32:13 by darakely          #+#    #+#             */
/*   Updated: 2022/12/13 15:52:46 by darakely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_prelast_redirect(char *str, int i)
{
	t_flag_redir	flag;

	flag = _default;
	while (str[++i])
	{
		if (str[i] == '<' && (str[i + 1] && str[i + 1] == '<'))
			i++;
		else if (str[i] == '>' && (str[i + 1] && str[i + 1] == '>'))
		{
			flag = _append;
			i++;
		}
		else if (str[i] == '<')
			flag = _infile;
		else if (str[i] == '>')
			flag = _outfile;
	}
	return (flag);
}

int	check_last_redirect(char *str, int i, t_flag_redir flag)
{
	while (str[++i])
	{
		if (str[i] == '<' && (str[i + 1] && str[i + 1] == '<'))
		{
			flag = _heredoc;
			i++;
		}
		else if (str[i] == '>' && (str[i + 1] && str[i + 1] == '>'))
		{
			if (flag != _heredoc)
				flag = _append;
			i++;
		}
		else if (str[i] == '<')
		{
			if (flag != _heredoc)
				flag = _infile;
		}
		else if (str[i] == '>')
		{
			if (flag != _heredoc)
				flag = _outfile;
		}
	}
	return (flag);
}

void	create_file_for_heredoc(t_data *data)
{
	int		i;
	int		j;
	char	*arr;

	i = -1;
	j = 0;
	arr = ft_strdup(".F.B.C.D.F.G.H.J.K.L.M.N.P.Q.R.A");
	data->info_parsing->hidden_files = (char **)malloc(sizeof(char *) * 17);
	if (!data->info_parsing->hidden_files)
		return ;
	while (++i < 16)
	{
		if (j % 2 != 0)
		{
			data->info_parsing->hidden_files[i] = ft_strdup(&arr[j + 1]);
			j++;
		}
		else
			data->info_parsing->hidden_files[i] = ft_strdup(&arr[j]);
		j++;
	}
	data->info_parsing->hidden_files[i] = 0;
	free(arr);
	arr = 0;
}

void	norm_check_open_heredoc(t_data *data, int *flag)
{
	int	fd;
	int	i;

	i = -1;
	fd = 0;
	while (data->info_redirect->fd_heredoc[++i] != -1)
		;
	fd = open(data->info_parsing->hidden_files[*flag], \
	O_TRUNC | O_CREAT | O_RDWR, 0644);
	open_heredoc(data, *flag, fd, 0);
	close(fd);
	data->info_redirect->fd_heredoc[i] = \
	open(data->info_parsing->hidden_files[*flag], O_RDWR);
}

int	check_open_heredoc(t_data *data, int *flag, int *check, int last_heredoc)
{
	int	fd;

	fd = 0;
	(*check)++;
	(void)last_heredoc;
	if (*check == \
	data->info_redirect->heredoc_count_in_pipe[data->last_heredoc])
	{
		norm_check_open_heredoc(data, flag);
		*check = 0;
		data->last_heredoc++;
	}
	else
	{
		fd = open(".MalisHkA", O_TRUNC | O_CREAT | O_RDWR, 0644);
		open_heredoc(data, *flag, fd, 0);
		close(fd);
		unlink(".MalisHkA");
	}
	if (data->heredoc == 2)
		return (2);
	return (1);
}
