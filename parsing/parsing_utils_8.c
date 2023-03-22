/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_8.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darakely <darakely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 14:42:51 by darakely          #+#    #+#             */
/*   Updated: 2022/12/13 22:55:39 by darakely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	fixed_prelast_redirect(char *str)
{
	t_flag_redir	flag;
	int				i;
	int				j;
	int				len;

	flag = _default;
	i = 0;
	j = 0;
	len = ft_strlen(str);
	while (str[i])
	{
		if (str[i] == '<' && (str[i + 1] && str[i + 1] == '<'))
			j++;
		else if (str[i] == '>' && (str[i + 1] && str[i + 1] == '>'))
			j++;
		else if (str[i] == '<')
			j++;
		else if (str[i] == '>')
			j++;
		i++;
	}
	if (j > 1)
		return (norm_fixed_prelast_redirect(str, len));
	return (flag);
}

void	norm_parsing(t_data *data)
{
	char	**split_for_malloc;
	int		i;
	int		k;

	ft_heredoc(data, 0, 0, 0);
	ft_append(data, -1, 0, 0);
	ft_infiles(data, -1, 0, 0);
	ft_outfiles(data, -1, 0, 0);
	create_file_for_heredoc(data);
	split_for_malloc = ft_split(data->promt, '|');
	k = -1;
	while (split_for_malloc && split_for_malloc[++k])
		;
	data->info_parsing->flag_for_last_redirect = malloc(sizeof(int) * (k + 1));
	data->info_parsing->flag_for_prelast_redirect = \
	malloc(sizeof(int) * (k + 1));
	data->info_parsing->fixed_prelast_redirect = malloc(sizeof(int) * (k + 1));
	i = -1;
	while (++i <= k)
	{
		data->info_parsing->flag_for_prelast_redirect[i] = -1;
		data->info_parsing->flag_for_last_redirect[i] = -1;
		data->info_parsing->fixed_prelast_redirect[i] = -1;
	}
	free_array(&split_for_malloc);
}

void	continue_parsing(t_data *data, int k, char *new_promt, \
		char **split_for_malloc)
{	
	split_for_malloc = ft_split(data->promt, '|');
	get_value_env(data, &data->promt);
	new_promt = clear_promt_for_exec(data->promt);
	data->info_parsing->split_new_promt = ft_split(new_promt, ' ');
	while (split_for_malloc && split_for_malloc[++k])
		;
	if (open_all_infiles(data, k, 0, 0) == -1 || \
	open_all_append(data, k, 0, 0) == -1 || \
	open_all_outfiles(data, k, 0, 0) == -1)
	{
		free_array(&split_for_malloc);
		free(new_promt);
		new_promt = 0;
		return ;
	}
	if (new_promt && *new_promt)
		ft_execve(data, new_promt);
	free_array(&split_for_malloc);
	free(new_promt);
	new_promt = 0;
}

int	continue_norm_fixed_prelast_redirect(char *str, int *len, int *j, \
		t_flag_redir flag)
{
	if (str[*len] == '>' && str[*len - 1] == '>')
	{
		flag = _append;
		*len -= 2;
		*j = 1;
	}
	else if (str[*len] == '>')
	{
		flag = _outfile;
		(*len)--;
		*j = 1;
	}
	else if (str[*len] == '<')
	{
		flag = _infile;
		(*len)--;
		*j = 1;
	}
	else
		(*len)--;
	return (flag);
}

int	norm_fixed_prelast_redirect(char *str, int len)
{
	t_flag_redir	flag;
	int				j;

	j = 0;
	while (len >= 0)
	{
		if (str[len] == '<' && str[len - 1] == '<')
		{
			flag = _heredoc;
			if (j == 1)
				break ;
			len -= 2;
			j = 1;
		}
		flag = continue_norm_fixed_prelast_redirect(str, &len, &j, flag);
	}
	return (flag);
}
