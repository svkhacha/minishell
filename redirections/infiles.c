/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infiles.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darakely <darakely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 18:19:48 by darakely          #+#    #+#             */
/*   Updated: 2022/12/13 22:28:21 by darakely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	open_all_infiles(t_data *data, int count_pipe, int x, int check)
{
	data->for_current = 0;
	data->i = 0;
	data->j = 0;
	data->x = 0;
	data->count_pipe = count_pipe;
	while (data->info_redirect->infiles && data->count_pipe > 0)
	{
		check++;
		if (data->info_redirect->count_infiles_in_pipe && \
		data->info_redirect->count_infiles_in_pipe[data->j] == 0)
		{
			norm_open_all_infiles(data, &check);
			data->count_pipe--;
		}
		if (continue_open_all_infiles(data, &check, &x, &count_pipe) == -1)
			return (-1);
		data->for_current++;
	}
	return (0);
}

int	check_last_infile(t_data *data, char **pipe, int flag)
{
	int	i;
	int	j;
	int	count;
	int	size;

	i = -1;
	size = 0;
	(void)data;
	while (pipe && pipe[++i])
	{
		j = -1;
		count = 0;
		while (pipe[i][++j])
		{
			if (pipe[i][j] == '<' && (pipe[i][j + 1] && pipe[i][j + 1] != '<'))
				count++;
		}
		if (flag == 0)
			size += check_count_last_infiles(count, pipe[i]);
	}
	return (size);
}

void	add_infile_name_in_struct(t_data *data, char *str, \
		char **tmp, char *check)
{
	data->i = 0;
	while (data->info_redirect->infiles && \
	data->info_redirect->infiles[data->i])
		data->i++;
	tmp = (char **)malloc(sizeof(char *) * (data->i + 2));
	data->i = 0;
	while (data->info_redirect->infiles && \
	data->info_redirect->infiles[data->i])
	{
		tmp[data->i] = ft_strdup(data->info_redirect->infiles[data->i]);
		data->i++;
	}
	check = correct_heredoc_name(str, 0, 0);
	tmp[data->i] = ft_strdup(check);
	my_free(&check);
	tmp[data->i + 1] = 0;
	free_array(&data->info_redirect->infiles);
	data->info_redirect->infiles = malloc(sizeof(char *) * (data->i + 2));
	data->i = -1;
	while (tmp[++data->i])
		data->info_redirect->infiles[data->i] = ft_strdup(tmp[data->i]);
	data->info_redirect->infiles[data->i] = 0;
	free_array(&tmp);
}

void	get_infile_name(t_data *data, char *str, char *ptr)
{
	data->i = 0;
	ptr = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (str[data->i] == '\"' || str[data->i] == '\'')
	{
		data->i++;
		while (str[data->i] && str[data->i] != '\'' && str[data->i] != '\"')
		{
			ptr[data->i - 1] = str[data->i];
			data->i++;
		}
		ptr[data->i - 1] = '\0';
	}
	else
	{
		while (str[data->i] && str[data->i] != ' ' && str[data->i] != '<' \
		&& str[data->i] != '|' && str[data->i] != '>')
		{
			ptr[data->i] = str[data->i];
			data->i++;
		}
		ptr[data->i] = '\0';
	}
	add_infile_name_in_struct(data, ptr, 0, 0);
	my_free(&ptr);
}

void	ft_infiles(t_data *data, int i, char **pipe, int j)
{
	while (data->promt[++i])
	{
		if (data->promt[i] == '\'' || data->promt[i] == '\"')
		{
			i++;
			while (data->promt[i] && data->promt[i] != '\'' \
			&& data->promt[i] != '\"')
				i++;
		}
		else if (data->promt[i] == '<' && (data->promt[i + 1] && \
		data->promt[i + 1] == '<'))
			i++;
		else if (data->promt[i] == '<' && (data->promt[i + 1] && \
		data->promt[i + 1] != '<'))
		{
			check_infile(data, &data->promt[i]);
			j++;
		}
	}
	norm_ft_infiles(data, pipe, j);
}
