/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darakely <darakely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 13:23:24 by darakely          #+#    #+#             */
/*   Updated: 2022/12/13 20:10:03 by darakely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	continue_add_heredoc_name_struct(t_data *data, int flag, \
		char *str, char **tmp)
{
	if (flag == 1)
	{
		data->info_redirect->heredoc_name[data->i] = ft_strdup("\"");
		data->info_redirect->heredoc_name[data->i] = \
		ft_strjoin(data->info_redirect->heredoc_name[data->i], str);
		data->info_redirect->heredoc_name[data->i] = ft_strdup("\"");
	}
	else
		data->info_redirect->heredoc_name[data->i] = ft_strdup(str);
	free_array(&data->info_redirect->heredoc);
	data->info_redirect->heredoc = malloc(sizeof(char *) * (data->i + 2));
	data->i = -1;
	while (tmp[++data->i])
		data->info_redirect->heredoc[data->i] = ft_strdup(tmp[data->i]);
	data->info_redirect->heredoc[data->i] = 0;
}

int	check_count_heredoc(t_data *data, int count_heredoc)
{
	if (count_heredoc == 0)
		return (-1);
	if (count_heredoc > 16)
	{
		ft_putstr_fd("❌ minishell: maximum here-document count exceeded\n", \
		STDERR_FILENO);
		free_all(data, 0);
		exit(2);
	}
	return (0);
}

int	close_heredocs(t_data *data, char *heredoc, int i)
{
	int	j;

	j = check_size_str(data->info_redirect->heredoc[i], heredoc);
	if (ft_strncmp(heredoc, data->info_redirect->heredoc[i], j) == 0)
		return (0);
	return (-1);
}

void	norm_correct_heredoc_name(char *ptr, char *str, int *i, int *j)
{
	if (str[*i] && str[*i] == '\'')
	{
		(*i)++;
		while (str[*i] != '\0' && str[*i] != '\'')
		{
			ptr[*j] = str[*i];
			(*i)++;
			(*j)++;
		}
		ptr[*j] = '\0';
		(*i)++;
	}
	else if (str[*i])
	{
		ptr[*j] = str[*i];
		(*j)++;
		(*i)++;
		ptr[*j] = '\0';
	}
}

char	*correct_heredoc_name(char *str, int i, int j)
{
	char	*ptr;

	if (!str)
		return (0);
	ptr = malloc(sizeof(char) * (ft_strlen(str) + 1));
	while (str[i])
	{
		if (str[i] && str[i] == '\"')
		{
			i++;
			while (str[i] && str[i] != '\"')
			{
				ptr[j] = str[i];
				j++;
				i++;
			}
			ptr[j] = '\0';
			i++;
		}
		else
			norm_correct_heredoc_name(ptr, str, &i, &j);
	}
	ptr[j] = '\0';
	return (ptr);
}
