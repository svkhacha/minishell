/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_export_4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darakely <darakely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 18:30:55 by darakely          #+#    #+#             */
/*   Updated: 2022/12/13 17:34:00 by darakely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	norm_check_change_variable(t_export *data, char *str, char **new_split)
{
	char	*check;
	int		i;

	i = check_size_str(data->key, str);
	check = 0;
	check = clear_str(data->key);
	if (ft_strncmp(check, str, i - 1) == 0)
	{
		if (ft_strncmp(data->key, str, ft_strlen(str)) != 0)
		{
			data->key = ft_strjoin(data->key, "=");
			data->key = ft_strjoin(data->key, "\"");
		}
		free(data->value);
		data->value = 0;
		data->value = ft_strdup(new_split[1]);
		data->value = ft_strjoin(data->value, "\"");
		data->status = 0;
		free(check);
		check = 0;
		return (-1);
	}
	free(check);
	check = 0;
	return (0);
}

int	norm_add_variable(t_data *data, char **new_split)
{
	t_export	*tmp;

	tmp = data->info_export;
	new_split[0] = ft_strjoin(new_split[0], "=");
	if (check_change_variable(tmp, new_split) == -1)
		return (-1);
	new_split[0] = ft_strjoin(new_split[0], "\"");
	if (new_split[1])
		new_split[1] = ft_strjoin(new_split[1], "\"");
	else
		new_split[0] = ft_strjoin(new_split[0], "\"");
	data->info_export = tmp;
	return (0);
}

int	find_plus(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '+')
		{
			if ((str[i + 1] == '=') && (((str[i - 1] >= 'a' \
				&& str[i - 1] <= 'z') || (str[i - 1] >= 'A' \
				&& str[i - 1] <= 'Z') || str[i - 1] == '_') || \
				(str[i - 1] >= '0' && str[i - 1] <= '9')))
				return (0);
			return (-1);
		}
		i++;
	}
	return (-1);
}

void	add_plus_variable(t_data *data, char **new_split)
{
	t_export	*tmp;
	char		**str;

	tmp = data->info_export;
	while (data->info_export->next)
		data->info_export = data->info_export->next;
	str = ft_split(new_split[0], '+');
	data->info_export->next = malloc(sizeof(t_export));
	if (!data->info_export->next)
		return ;
	data->info_export->next->key = ft_strdup(str[0]);
	data->info_export->next->key = \
		ft_strjoin(data->info_export->next->key, "=");
	data->info_export->next->key = \
		ft_strjoin(data->info_export->next->key, "\"");
	data->info_export->next->value = ft_strdup(new_split[1]);
	data->info_export->next->status = 0;
	data->info_export = tmp;
	free_array(&str);
}

int	check_plus(t_data *data, char **new_split, int i, char *check)
{
	t_export	*tmp;
	char		**str;
	int			j;

	tmp = data->info_export;
	str = ft_split(new_split[0], '+');
	str[0] = ft_strjoin(str[0], "=");
	j = -1;
	while (data->info_export)
	{
		i = check_size_str(str[0], data->info_export->key);
		check = correct_heredoc_name(data->info_export->key, 0, 0);
		if (ft_strncmp(str[0], check, i) == 0)
		{
			j = continue_check_plus(data, new_split);
			break ;
		}
		my_free(&check);
		data->info_export = data->info_export->next;
	}
	data->info_export = tmp;
	add_plus_variable(data, new_split);
	free_array(&str);
	my_free(&check);
	return (j);
}
