/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_9.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darakely <darakely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 15:16:42 by darakely          #+#    #+#             */
/*   Updated: 2022/12/13 23:11:00 by darakely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	norm_clear_promt_for_exec(char *new_promt, char *str, int *i, int *j)
{
	new_promt[*j] = str[*i];
	(*i)++;
	(*j)++;
	if (str[*i] == '\'' || str[*i] == '\"')
	{
		new_promt[*j] = str[*i];
		(*j)++;
		(*i)++;
		while (str[*i] && str[*i] != '\'' && str[*i] != '\"')
		{
			new_promt[*j] = str[*i];
			(*i)++;
			(*j)++;
		}
		new_promt[*j] = str[*i];
		(*i)++;
		(*j)++;
		return (-1);
	}
	return (0);
}

int	check_syntax_error_and_heredoc_2(t_data *data, char *str, int i, int a)
{
	t_flag_redir	check_redir;

	check_redir = _default;
	if (a == 0 && check_syntax_error(&str[a]) == -1)
	{
		print_syntax_error(data, &str[a]);
		return (-1);
	}
	data->info_parsing->flag_for_prelast_redirect[i] = \
	check_prelast_redirect(data->info_parsing->split_pipes[i], -1);
	data->info_parsing->flag_for_last_redirect[i] = \
	check_last_redirect \
	(data->info_parsing->split_pipes[i], -1, check_redir);
	data->info_parsing->fixed_prelast_redirect[i] = \
	fixed_prelast_redirect(data->info_parsing->split_pipes[i]);
	return (0);
}

int	norm_check_syntax_error_and_heredoc(t_data *data, char *str, int i)
{
	if (check_syntax_error(&str[i]) == -1)
	{
		print_syntax_error(data, &str[i]);
		return (-1);
	}
	return (0);
}

int	check_syntax_error_and_heredoc_3(t_data *data, int *flag, int check)
{
	while (data->info_parsing->split_pipes[data->i][data->a] && \
	data->info_parsing->split_pipes[data->i][data->a] != '\"' \
	&& data->info_parsing->split_pipes[data->i][data->a] != '\'')
	{
		if (norm_check_syntax_error_and_heredoc \
		(data, data->info_parsing->split_pipes[data->i], data->a) == -1)
			return (-1);
		if (data->info_parsing->split_pipes[data->i][data->a] == '<' && \
		(data->info_parsing->split_pipes[data->i][data->a + 1] && \
		data->info_parsing->split_pipes[data->i][data->a + 1] == '<'))
			return (check_open_heredoc(data, flag, &data->k, check));
		data->a++;
	}
	return (0);
}
