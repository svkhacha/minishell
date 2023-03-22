/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darakely <darakely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 14:59:55 by darakely          #+#    #+#             */
/*   Updated: 2022/12/14 15:40:16 by darakely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	continue_check_syntax_error(char *str, int i)
{
	if (str[i] != '\0' && str[i] != '<' && str[i] != '>' && \
	((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z') \
	|| str[i] == '$' || str[i] == '\'' || str[i] == '\"' || \
	str[i] == '/' || str[i] == '.'))
		return (0);
	return (-1);
}

int	norm_check_syntax_error(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '\'')
	{
		i++;
		if (str[i] == '\0')
			return (-1);
		while (str[i] && str[i] != '\'')
			i++;
		if (str[i] == '\0')
			return (-1);
	}
	else
	{
		i++;
		if (str[i] == '\0')
			return (-1);
		while (str[i] && str[i] != '\"')
			i++;
		if (str[i] == '\0')
			return (-1);
	}
	return (0);
}

int	check_syntax_error(char *str)
{
	int	i;

	i = 0;
	if (str[i] == ';' || str[i] == '\\')
		return (-1);
	if (str[i] == '<' || str[i] == '>' || str[i] == '\'' || str[i] == '\"')
	{
		if (str[i] && (str[i] == '\'' || str[i] == '\"'))
			return (norm_check_syntax_error(str));
		if (str[i + 1] && (str[i + 1] == '<' || str[i + 1] == '>'))
			i++;
		i++;
		while (str[i] && str[i] == ' ')
			i++;
		return (continue_check_syntax_error(str, i));
	}
	if (str[i] && str[i] == '|')
	{
		while (str[i] && str[i] != '<' && str[i] != '>' && str[i] != '\'' \
		&& str[i] != '\"')
			i++;
		if (str[i] == '\0')
			return (-1);
	}
	return (0);
}

int	check_syntax_error_and_heredoc(t_data *data, int check, int *flag, int j)
{
	data->a = 0;
	data->k = 0;
	data->i = -1;
	data->last_heredoc = 0;
	data->info_parsing->split_pipes = ft_split(data->promt, '|');
	while (data->info_parsing->split_pipes && \
	data->info_parsing->split_pipes[++data->i])
	{
		data->a = 0;
		if (data->info_parsing->split_pipes[data->i][data->a] && \
		data->info_parsing->split_pipes[data->i][data->a] != '\"' \
		&& data->info_parsing->split_pipes[data->i][data->a] != '\'')
		{
			j = check_syntax_error_and_heredoc_3(data, flag, check);
			if (j == 2 || j == -1)
				return (1);
			(*flag)++;
			data->a++;
		}
		if (check_syntax_error_and_heredoc_2 \
		(data, data->info_parsing->split_pipes[data->i], \
		data->i, data->a) == -1)
			return (-1);
	}
	return (0);
}

void	parsing(t_data *data)
{
	int		flag;
	int		i;
	int		k;

	flag = 0;
	i = 0;
	norm_parsing(data);
	k = check_syntax_error_and_heredoc(data, i, &flag, 0);
	if (k)
	{
		data->heredoc = 0;
		return ;
	}
	continue_parsing(data, -1, 0, 0);
}
