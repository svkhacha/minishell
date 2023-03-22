/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_export_7.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darakely <darakely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 19:21:24 by darakely          #+#    #+#             */
/*   Updated: 2022/12/13 18:48:02 by darakely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	continue_add_variable_export_2(t_data *data, char *str, \
									char **new_split, char *split)
{
	char	*check;

	check = ft_strdup(find_equal(split));
	if (new_split[1] == 0)
	{
		str = ft_strdup(new_split[0]);
		free_array(&new_split);
		new_split = malloc(sizeof(char *) * 3);
		new_split[0] = ft_strdup(str);
		new_split[1] = 0;
		new_split[2] = 0;
		my_free(&str);
		data->flag = 1;
	}
	my_free(&new_split[1]);
	new_split[1] = ft_strdup(check);
	my_free(&check);
	check = correct_heredoc_name(new_split[1], 0, 0);
	my_free(&new_split[1]);
	new_split[1] = ft_strdup(check);
	continue_add_variable_export(data, split, new_split);
	my_free(&check);
	if (data->flag == 1)
		free_array(&new_split);
}
