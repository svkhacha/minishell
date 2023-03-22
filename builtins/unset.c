/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darakely <darakely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 14:57:44 by darakely          #+#    #+#             */
/*   Updated: 2022/12/12 19:58:10 by darakely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	norm_unset_export(t_export *info)
{
	info->status = 1;
	free(info->value);
	info->value = 0;
}

void	norm_unset_env(t_env *info)
{
	info->status = 1;
	free(info->value);
	info->value = 0;
}

void	unset_env(t_data *data, int j, char **str, char **check)
{
	t_env		*tmp;
	char		**check_unset;

	tmp = data->info_env;
	check_unset = 0;
	if (str)
		check_unset = ft_split(*str, ' ');
	while (check_unset && str)
	{
		while (data->info_env)
		{
			check = ft_split(data->info_env->key, '=');
			if (check && data->info_env->key)
				norm_unset(data, j, check[0], check_unset[0]);
			data->info_env = data->info_env->next;
			free_array(&check);
		}
		data->info_env = tmp;
		str++;
		free_array(&check_unset);
		check_unset = ft_split(*str, ' ');
	}
	data->info_env = tmp;
	free_array(&check);
	free_array(&check_unset);
}

int	check_arg(t_data *data, char **str)
{
	int		i;
	int		j;
	char	**check_unset;

	i = 0;
	check_unset = 0;
	if (str)
		check_unset = ft_split(data->promt, ' ');
	while (check_unset && check_unset[i])
	{
		j = 0;
		while (check_unset[i][j])
		{
			if (norm_check_arg(data, check_unset, i, j) == -1)
			{
				free_array(&check_unset);
				*data->error_code = 1;
				return (-1);
			}
			j++;
		}
		i++;
	}
	free_array(&check_unset);
	return (0);
}

void	ft_unset(t_data *data, char **check_unset, char **str, int j)
{
	t_export	*tmp;
	char		**check;

	if (check_arg(data, str) == -1)
		return ;
	tmp = data->info_export;
	check = 0;
	if (str)
		check_unset = ft_split(*str, ' ');
	while (check_unset && str)
	{
		while (data->info_export)
		{
			check = ft_split(data->info_export->key, '=');
			if (check)
				norm_ft_unset(data, j, check[0], check_unset[0]);
			data->info_export = data->info_export->next;
			free_array(&check);
		}
		data->info_export = tmp;
		str++;
		free_array(&check_unset);
		check_unset = ft_split(*str, ' ');
	}
	free_array(&check);
}
