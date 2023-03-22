/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darakely <darakely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 21:02:57 by darakely          #+#    #+#             */
/*   Updated: 2022/12/09 14:08:42 by darakely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*check_back_slash(char *str, char *new_malloc)
{
	int		i;
	int		j;

	i = -1;
	j = 0;
	if (check_count_single_quote(str) % 2 != 0)
		return (clear_str(str));
	if (if_backslash(str) == -1)
		return (clear_double_quote(str));
	while (str[++i])
	{
		if (str[i] == '\"')
		{
			norm_if(str, new_malloc, i, j);
			j += 2;
		}
		else
		{
			if (norm_else(str, new_malloc, i, j) == 0)
				j++;
		}
	}
	new_malloc[j] = '\0';
	return (new_malloc);
}

char	*my_strdup(char *str)
{
	int		i;
	int		len;
	char	*new_malloc;

	i = 0;
	len = 0;
	if (ft_strlen(str) == my_strlen(str))
		return (str);
	else
	{
		while (str[i])
		{
			if (str[i] == '\'' || str[i] == '\"')
				len++;
			i++;
		}
		new_malloc = (char *)malloc(sizeof(char) * (i + len + 1));
		if (!new_malloc)
			return (0);
		new_malloc[i + len] = '\0';
		return (check_back_slash(str, new_malloc));
	}
}

void	norm_init_export(t_data *data, char *split)
{
	data->info_export->key = ft_strjoin(data->info_export->key, "=");
	data->info_export->value = ft_strdup("\"");
	data->info_export->value = ft_strjoin(data->info_export->value, split);
	data->info_export->value = ft_strjoin(data->info_export->value, "\"");
	data->info_export->status = 0;
}

void	sort_export(t_data *data, int i)
{
	t_export	*tmp;
	char		*swap;

	tmp = data->info_export;
	while (data->info_export->next)
	{
		i = check_size_str(data->info_export->key, \
			data->info_export->next->key);
		if (ft_strncmp(data->info_export->key, data->info_export->next->key, i) \
			> 0)
		{
			ft_swap(&data->info_export->status, \
					&data->info_export->next->status);
			swap = data->info_export->key;
			data->info_export->key = data->info_export->next->key;
			data->info_export->next->key = swap;
			swap = data->info_export->value;
			data->info_export->value = data->info_export->next->value;
			data->info_export->next->value = swap;
			data->info_export = tmp;
		}
		else
			data->info_export = data->info_export->next;
	}
	data->info_export = tmp;
}

int	check_equal(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (0);
		i++;
	}
	return (-1);
}
