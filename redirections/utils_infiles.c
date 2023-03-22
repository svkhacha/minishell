/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_infiles.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darakely <darakely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 18:44:24 by darakely          #+#    #+#             */
/*   Updated: 2022/12/13 18:57:57 by darakely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	norm_open_all_infiles(t_data *data, int *check)
{
	*check = 0;
	data->j++;
}

int	print_infile_error(t_data *data, char *error)
{
	char	*str;

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

void	check_infile(t_data *data, char *str)
{
	int	i;

	i = 1;
	while (str[i] && str[i] == ' ')
		i++;
	if (str[i] && ft_isprint(str[i]) == 0 && str[i] != '<' && str[i] != '>' && \
			str[i] != '\\' && str[i] != ';' && str[i] != '*' \
			&& str[i] != '&' && str[i] != '|')
		get_infile_name(data, &str[i], 0);
}

void	count_infile_in_pipe(t_data *data, char **pipe, int k, int count)
{
	data->i = -1;
	data->info_redirect->fd_infiles = malloc(sizeof(int) * k);
	data->info_redirect->count_infiles_in_pipe = malloc(sizeof(int) * k);
	while (++count < k)
	{
		data->info_redirect->fd_infiles[count] = -1;
		data->info_redirect->count_infiles_in_pipe[count] = -1;
	}
	while (pipe && pipe[++data->i])
	{
		data->j = 0;
		count = 0;
		while (pipe[data->i][data->j])
		{
			if (pipe[data->i][data->j] == '<' && (pipe[data->i][data->j + 1] \
			&& pipe[data->i][data->j + 1] == '<'))
				data->j++;
			else if (pipe[data->i][data->j] == '<' && \
			(pipe[data->i][data->j + 1] && pipe[data->i][data->j + 1] != '<'))
				count++;
			data->j++;
		}
		data->info_redirect->count_infiles_in_pipe[data->i] = count;
	}
}

int	check_count_last_infiles(int pos, char *pipe)
{
	int	i;

	i = 0;
	if (pos > 0)
	{
		if (pos > 1)
		{
			i = -1;
			while (pos >= 1 && pipe[++i])
				if (pipe[i] == '<' && (pipe[i + 1] && pipe[i + 1] != '<'))
					pos--;
		}
		return (1);
	}
	return (0);
}
