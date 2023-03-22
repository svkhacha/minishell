/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darakely <darakely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 12:56:09 by darakely          #+#    #+#             */
/*   Updated: 2022/12/13 22:24:47 by darakely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_all_redirect(t_data *data)
{
	int	i;
	int	j;

	j = 0;
	i = -1;
	while (data->info_redirect->outfiles && data->info_redirect->outfiles[++i])
		j++;
	i = -1;
	while (data->info_redirect->heredoc && data->info_redirect->heredoc[++i])
		j++;
	i = -1;
	while (data->info_redirect->infiles && data->info_redirect->infiles[++i])
		j++;
	i = -1;
	while (data->info_redirect->append && data->info_redirect->append[++i])
		j++;
	return (j);
}

void	add_heredoc_name_struct(t_data *data, char *str, char **tmp, int flag)
{
	char	*check;

	data->i = 0;
	check = 0;
	while (data->info_redirect->heredoc && \
	data->info_redirect->heredoc[data->i])
		data->i++;
	tmp = (char **)malloc(sizeof(char *) * (data->i + 2));
	free_array(&data->info_redirect->heredoc_name);
	data->info_redirect->heredoc_name = malloc(sizeof(char *) * (data->i + 2));
	data->i = 0;
	while (data->info_redirect->heredoc && \
	data->info_redirect->heredoc[data->i])
	{
		tmp[data->i] = ft_strdup(data->info_redirect->heredoc[data->i]);
		data->info_redirect->heredoc_name[data->i] = ft_strdup(tmp[data->i]);
		data->i++;
	}
	check = correct_heredoc_name(str, 0, 0);
	tmp[data->i] = ft_strdup(check);
	tmp[data->i + 1] = 0;
	data->info_redirect->heredoc_name[data->i + 1] = 0;
	my_free(&check);
	continue_add_heredoc_name_struct(data, flag, str, tmp);
	free_array(&tmp);
}

void	add_heredoc(t_data *data, char *str, int flag, char *ptr)
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
		flag = 1;
	}
	else
	{
		while (str[data->i] && str[data->i] != ' ' && str[data->i] != '<' && \
		str[data->i] != '|' && str[data->i] != '>')
		{
			ptr[data->i] = str[data->i];
			data->i++;
		}
		ptr[data->i] = '\0';
	}
	add_heredoc_name_struct(data, ptr, 0, flag);
	my_free(&ptr);
}

int	check_heredoc(t_data *data, char *str)
{
	int	i;

	i = 2;
	while (str[i] && str[i] == ' ')
		i++;
	if (str[i] && ft_isprint(str[i]) == 0 && (str[i] != '|' && str[i] != '<' \
			&& str[i] != '>' && str[i] != ';' && str[i] != '\\' \
			&& str[i] != '*' && str[i] != '&'))
	{
		add_heredoc(data, &str[i], 0, 0);
		return (1);
	}
	return (0);
}

void	ft_heredoc(t_data *data, int i, char **pipe, int j)
{
	int		count;

	count = 0;
	while (data->promt[i])
	{
		if (data->promt[i] == '\'' || data->promt[i] == '\"')
		{
			i++;
			while (data->promt[i] && data->promt[i] != '\'' \
			&& data->promt[i] != '\"')
				i++;
			i++;
		}
		else if (data->promt[i] == '<' && (data->promt[i + 1] \
					&& data->promt[i + 1] == '<'))
		{
			count += check_heredoc(data, &data->promt[i]);
			i += 2;
			j++;
		}
		else
			i++;
	}
	norm_ft_heredoc(data, pipe, j, count);
}
