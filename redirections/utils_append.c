/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_append.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darakely <darakely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 14:05:59 by darakely          #+#    #+#             */
/*   Updated: 2022/12/13 18:21:25 by darakely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	norm_open_all_append(t_data *data)
{
	int	x;

	x = 0;
	data->i = -1;
	while (data->info_redirect->append && \
	data->info_redirect->append[++data->i])
	{
		x = open(data->info_redirect->append[data->i], \
		O_CREAT | O_APPEND | O_RDWR, 0644);
		if (x == -1)
			return (print_append_error \
			(data, data->info_redirect->append[data->i]));
		close(x);
	}
	return (0);
}

int	print_append_error(t_data *data, char *error)
{
	char	*str;

	str = 0;
	str = correct_heredoc_name(error, 0, 0);
	ft_putstr_fd("❌ minishell: ", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putstr_fd(" : ", STDERR_FILENO);
	ft_putstr_fd(strerror(errno), STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	*data->error_code = 1;
	free(str);
	str = 0;
	return (-1);
}

void	count_append_in_pipe(t_data *data, char **pipe, int k, int j)
{
	int	count;

	data->i = 0;
	data->info_redirect->fd_append = malloc(sizeof(int) * k);
	data->info_redirect->count_append_in_pipe = malloc(sizeof(int) * k);
	count = -1;
	while (++count < k)
	{
		data->info_redirect->fd_append[count] = -1;
		data->info_redirect->count_append_in_pipe[count] = -1;
	}
	while (pipe && pipe[data->i])
	{
		j = 0;
		count = 0;
		while (pipe[data->i][j])
		{
			if (pipe[data->i][j] == '>' && (pipe[data->i][j + 1] \
			&& pipe[data->i][j + 1] == '>'))
				count++;
			j++;
		}
		data->info_redirect->count_append_in_pipe[data->i] = count;
		data->i++;
	}
}

int	check_count_last_append(int pos, char *pipe)
{
	int	i;

	i = 0;
	if (pos > 0)
	{
		if (pos > 1)
		{
			i = -1;
			while (pos >= 1 && pipe[++i])
				if (pipe[i] == '>' && (pipe[i + 1] && pipe[i + 1] == '>'))
					pos--;
		}
		return (1);
	}
	return (0);
}

int	open_all_append(t_data *data, int count_pipe, int x, int check)
{
	data->i = 0;
	data->j = 0;
	while (data->info_redirect->append && count_pipe > 0)
	{
		check++;
		if (data->info_redirect->count_append_in_pipe && \
		data->info_redirect->count_append_in_pipe[data->j] == 0)
		{
			count_pipe--;
			check = 0;
			data->j++;
		}
		else if (data->info_redirect->count_append_in_pipe && \
		(check == data->info_redirect->count_append_in_pipe[data->j]))
		{
			if (continue_open_all_append(data, x) == -1)
				return (-1);
			check = 0;
			count_pipe--;
		}
		x++;
	}
	if (norm_open_all_append(data) == -1)
		return (-1);
	return (0);
}
