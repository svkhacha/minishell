/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outfiles.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darakely <darakely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 13:27:36 by darakely          #+#    #+#             */
/*   Updated: 2022/12/13 22:30:12 by darakely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_last_outfile(t_data *data, char **pipe, int flag)
{
	int	i;
	int	j;
	int	count;
	int	size;

	i = -1;
	size = 0;
	(void)data;
	while (pipe[++i])
	{
		j = -1;
		count = 0;
		while (pipe[i][++j])
		{
			if (pipe[i][j] == '>' && (pipe[i][j + 1] && pipe[i][j + 1] != '>'))
				count++;
		}
		if (flag == 0)
			size += check_count_last_outfiles(count, pipe[i]);
	}
	return (size);
}

void	add_outfile_name_in_struct(t_data *data, char *str, \
		char **tmp, char *check)
{
	data->i = 0;
	while (data->info_redirect->outfiles && \
	data->info_redirect->outfiles[data->i])
		data->i++;
	tmp = (char **)malloc(sizeof(char *) * (data->i + 2));
	data->i = 0;
	while (data->info_redirect->outfiles && \
	data->info_redirect->outfiles[data->i])
	{
		tmp[data->i] = ft_strdup(data->info_redirect->outfiles[data->i]);
		data->i++;
	}
	check = correct_heredoc_name(str, 0, 0);
	tmp[data->i] = ft_strdup(check);
	my_free(&check);
	tmp[data->i + 1] = 0;
	free_array(&data->info_redirect->outfiles);
	data->info_redirect->outfiles = malloc(sizeof(char *) * (data->i + 2));
	data->i = -1;
	while (tmp[++data->i])
		data->info_redirect->outfiles[data->i] = ft_strdup(tmp[data->i]);
	data->info_redirect->outfiles[data->i] = 0;
	free_array(&tmp);
}

void	get_outfile_name(t_data *data, char *str, int i, char *ptr)
{
	ptr = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (str[i] == '\"' || str[i] == '\'')
	{
		i++;
		while (str[i] && str[i] != '\'' && str[i] != '\"')
		{
			ptr[i - 1] = str[i];
			i++;
		}
		ptr[i - 1] = '\0';
	}
	else
	{
		while (str[i] && str[i] != ' ' && str[i] != '<' && \
		str[i] != '|' && str[i] != '>')
		{
			ptr[i] = str[i];
			i++;
		}
		ptr[i] = '\0';
	}
	add_outfile_name_in_struct(data, ptr, 0, 0);
	my_free(&ptr);
}

void	check_outfile(t_data *data, char *str)
{
	int	i;

	i = 1;
	while (str[i] && str[i] == ' ')
		i++;
	if (str[i] && ft_isprint(str[i]) == 0 && str[i] != '<' && \
		str[i] != '>' && str[i] != '\\' && str[i] != ';' && \
		str[i] != '*' && str[i] != '|' && str[i] != '&')
		get_outfile_name(data, &str[i], 0, 0);
}

void	ft_outfiles(t_data *data, int i, int j, char **pipe)
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
		else if (data->promt[i] == '>' && (data->promt[i + 1] && \
		data->promt[i + 1] == '>'))
			i++;
		else if (data->promt[i] == '>' && (data->promt[i + 1] \
		&& data->promt[i + 1] != '>'))
		{
			check_outfile(data, &data->promt[i]);
			j++;
		}
	}
	norm_ft_outfiles(data, pipe, j);
}
