/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darakely <darakely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 17:32:16 by darakely          #+#    #+#             */
/*   Updated: 2022/12/13 23:00:30 by darakely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	continue_continue_close_all_fds(t_data *data)
{
	data->i = -1;
	if (data->info_redirect->fd_append && \
	data->info_redirect->fd_append[0] != -1)
	{
		while (data->info_redirect->count_append_in_pipe && \
		data->info_redirect->count_append_in_pipe[++data->i] != -1)
		{
			data->j = -1;
			while (data->info_redirect->fd_append && \
			data->info_redirect->fd_append[++data->j] != -1)
				close(data->info_redirect->fd_append[data->j]);
		}
	}
	norm_close_all_fds(data);
}

void	continue_close_all_fds(t_data *data)
{
	data->i = -1;
	if (data->info_redirect->fd_infiles && \
	data->info_redirect->fd_infiles[0] != -1)
	{
		while (data->info_redirect->count_infiles_in_pipe && \
		data->info_redirect->count_infiles_in_pipe[++data->i] != -1)
		{
			data->j = -1;
			while (data->info_redirect->fd_infiles && \
			data->info_redirect->fd_infiles[++data->j] != -1)
				close(data->info_redirect->fd_infiles[data->j]);
		}
	}
	continue_continue_close_all_fds(data);
}

void	close_all_fds(t_data *data)
{
	data->i = -1;
	close(data->info_pipe->output);
	close(data->info_pipe->input);
	if (data->info_redirect->fd_outfiles && \
	data->info_redirect->fd_outfiles[0] != -1)
	{
		while (data->info_redirect->count_outfiles_in_pipe && \
		data->info_redirect->count_outfiles_in_pipe[++data->i] != -1)
		{
			data->j = -1;
			while (data->info_redirect->fd_outfiles && \
			data->info_redirect->fd_outfiles[++data->j] != -1)
				close(data->info_redirect->fd_outfiles[data->j]);
		}
	}
	continue_close_all_fds(data);
}

void	continue_clear_promt(char *str, int *i)
{
	while (str[*i] && (str[*i] == '<' || str[*i] == '>'))
		(*i)++;
	while (str[*i] && str[*i] == ' ')
		(*i)++;
	while (str[*i] && (str[*i] != '<' && str[*i] != '>' \
	&& str[*i] != '|' && str[*i] != '\'' && str[*i] != '\"' && str[*i] != ' '))
		(*i)++;
	if (str[*i] && (str[*i] == '\'' || str[*i] == '\"'))
	{
		(*i)++;
		while (str[*i] && str[*i] != '\'' && str[*i] != '\"')
			(*i)++;
		(*i)++;
	}
}

char	*clear_promt_for_exec(char *str)
{	
	int		i;
	int		j;
	char	*new_promt;

	i = 0;
	j = 0;
	new_promt = (char *)malloc(sizeof(char) * (ft_strlen(str) + 1));
	while (str[i])
	{
		if (str[i] && (str[i] != '<' && str[i] != '>'))
		{
			while (str[i] && str[i] != '<' && str[i] != '>')
			{
				if (norm_clear_promt_for_exec(new_promt, str, &i, &j) == -1)
					break ;
			}
			new_promt[j] = '\0';
		}
		if (str[i] && (str[i] == '<' || str[i] == '>'))
			continue_clear_promt(str, &i);
	}
	return (new_promt);
}
