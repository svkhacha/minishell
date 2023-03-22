/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_export_6.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darakely <darakely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 19:10:52 by darakely          #+#    #+#             */
/*   Updated: 2022/12/13 17:40:03 by darakely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	continue_check_variable(t_export *data, char **check_split, char **str)
{
	t_export	*tmp;
	int			i;
	int			j;

	j = 0;
	i = 0;
	tmp = data;
	while (data)
	{
		check_split = ft_split(data->key, '=');
		i = check_size_str(check_split[0], str[0]);
		if (ft_strncmp(check_split[0], str[0], i) == 0)
			j = 1;
		free_array(&check_split);
		data = data->next;
	}
	data = tmp;
	return (j);
}

int	print_error(char *error)
{
	char	*check;

	check = correct_heredoc_name(error, 0, 0);
	ft_putstr_fd("❌ minishell: export: `", STDERR_FILENO);
	ft_putstr_fd(check, STDERR_FILENO);
	ft_putstr_fd("' : not a valid identifier\n", STDERR_FILENO);
	free(check);
	check = 0;
	return (-1);
}

void	continue_add_variable_export(t_data *data, char *split, \
		char **new_split)
{
	t_export	*tmp;

	tmp = data->info_export;
	if ((new_split[1] && find_plus(new_split[0]) != 0) || \
	(check_equal(split) == 0 && find_plus(new_split[0]) != 0))
	{
		if (norm_add_variable(data, new_split) == -1)
			return ;
	}
	if (find_plus(new_split[0]) == 0 && check_plus(data, new_split, 0, 0) == 0)
	{
		my_free(&new_split[1]);
		new_split[1] = correct_heredoc_name(data->info_export->value, 0, 0);
	}
	if (check_variable(tmp, new_split, 0, 0) == -1)
		return ;
	while (data->info_export->next)
		data->info_export = data->info_export->next;
	norm_add_variable_export(data->info_export, new_split);
	data->info_export = tmp;
}

int	continue_check_plus(t_data *data, char **new_split)
{
	norm_check_plus(data->info_export, new_split[1]);
	return (0);
}

void	my_free(char **check)
{
	free(*check);
	*check = 0;
}
