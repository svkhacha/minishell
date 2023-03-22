/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darakely <darakely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 19:00:41 by darakely          #+#    #+#             */
/*   Updated: 2022/12/13 22:20:40 by darakely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_last_append(t_data *data, char **pipe, int flag)
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
			if (pipe[i][j] == '>' && (pipe[i][j + 1] && pipe[i][j + 1] == '>'))
				count++;
		}
		if (flag == 0)
			size += check_count_last_append(count, pipe[i]);
	}
	return (size);
}

void	add_append_name_in_struct(t_data *data, char *str, \
		char **tmp, char *check)
{
	int		i;

	i = 0;
	while (data->info_redirect->append && data->info_redirect->append[i])
		i++;
	tmp = (char **)malloc(sizeof(char *) * (i + 2));
	i = 0;
	while (data->info_redirect->append && data->info_redirect->append[i])
	{
		tmp[i] = ft_strdup(data->info_redirect->append[i]);
		i++;
	}
	check = correct_heredoc_name(str, 0, 0);
	tmp[i] = ft_strdup(check);
	free(check);
	check = 0;
	tmp[i + 1] = 0;
	free_array(&data->info_redirect->append);
	data->info_redirect->append = (char **)malloc(sizeof(char *) * (i + 2));
	i = -1;
	while (tmp[++i])
		data->info_redirect->append[i] = ft_strdup(tmp[i]);
	data->info_redirect->append[i] = 0;
	free_array(&tmp);
}

void	get_append_name(t_data *data, char *str, char *ptr, int i)
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
	add_append_name_in_struct(data, ptr, 0, 0);
	my_free(&ptr);
}

void	check_append(t_data *data, char *str)
{
	int	i;

	i = 2;
	while (str[i] && str[i] == ' ')
		i++;
	if (str[i] && ft_isprint(str[i]) == 0 && str[i] != '<' && str[i] != '>' \
		&& str[i] != ';' && str[i] != '\\' && str[i] != '*' \
		&& str[i] != '&' && str[i] != '|')
		get_append_name(data, &str[i], 0, 0);
}

void	ft_append(t_data *data, int i, int j, char **pipe)
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
		if (data->promt[i] == '>' && (data->promt[i + 1] && \
					data->promt[i + 1] == '>'))
		{
			check_append(data, &data->promt[i]);
			i++;
			j++;
		}
	}
	pipe = ft_split(data->promt, '|');
	i = -1;
	while (pipe[++i])
		;
	i += j + 1;
	count_append_in_pipe(data, pipe, i, 0);
	free_array(&pipe);
}
