/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_value_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darakely <darakely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 15:02:31 by darakely          #+#    #+#             */
/*   Updated: 2022/12/13 12:16:46 by darakely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	skip_if_single_quote(char *line, int *i, int *len)
{
	int		j;

	j = *i;
	if (line && line[j] && line[j] == 39)
	{
		if (*i > 0 && line[(*i) - 1] == '\\')
		{
			*i += 1;
			*len += 1;
			return ;
		}
		j++;
		while (line[j] && line[j] != 39)
		{
			if (line[j] == '\\')
				j++;
			if (line[j])
				j++;
		}
	}
	*i = j;
	*len = j;
}

char	*join(char *promt, int i, char *delim, char *env_line)
{
	char	*prom;

	prom = ft_strdup(promt);
	prom = ft_strjoin(prom, env_line);
	prom = ft_strjoin(prom, promt + i);
	free (promt);
	free(delim);
	free(env_line);
	promt = 0;
	delim = 0;
	env_line = 0;
	return (prom);
}

static void	if_dollar_sign(t_data *data, char **promt, int *i, int *len)
{
	char	*delim;
	char	*env_line;
	int		j;

	delim = NULL;
	j = 0;
	if ((*promt)[*i] == '$' && (*promt)[++(*i)])
	{
		j = *i;
		while ((*promt)[*i] && (ft_isalnum((*promt)[*i])
			|| (*promt)[*i] == '?' || (*promt)[*i] == '_'))
			(*i)++;
		delim = ft_substr(*promt, j, (*i) - j);
		env_line = change_dollar(data, delim, 0, 0);
		*len += ft_strlen(env_line);
		(*promt)[j - 1] = 0;
		*promt = join(*promt, *i, delim, env_line);
		(*i) = (*len) - 1;
		if ((*i) < 0)
			*i = 0;
		(*len)--;
	}
}

void	get_value_env(t_data *data, char **promt)
{
	int		len;
	int		i;
	int		in_double_quote;

	i = 0;
	len = 0;
	in_double_quote = 1;
	while (*promt && (*promt)[i])
	{
		if (in_double_quote)
			skip_if_single_quote(*promt, &i, &len);
		if ((*promt)[i] == '"' && in_double_quote == 1)
			in_double_quote = 0;
		else if ((*promt)[i] == '"' && in_double_quote == 0)
			in_double_quote = 1;
		if_dollar_sign(data, promt, &i, &len);
		if ((*promt)[i])
		{
			i++;
			len++;
		}
	}
}
