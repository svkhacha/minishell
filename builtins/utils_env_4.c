/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env_4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darakely <darakely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 18:02:57 by darakely          #+#    #+#             */
/*   Updated: 2022/12/12 18:33:26 by darakely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	continue_check_plus_env(t_env *info, char *check, char **new_split, \
							t_env *tmp)
{
	check = correct_heredoc_name(new_split[1], 0, 0);
	info->value = ft_strjoin(info->value, check);
	free(check);
	check = 0;
	info = tmp;
	return (-1);
}

void	continue_add_variable_env(char ***new_split, char *str, char *check)
{
	if (*new_split[1] == 0)
	{
		str = ft_strdup(*new_split[0]);
		free_array(new_split);
		new_split = malloc(sizeof(char *) * 3);
		if (!new_split)
			return ;
		*new_split[0] = ft_strdup(str);
		*new_split[1] = 0;
		*new_split[2] = 0;
		free(str);
		str = 0;
	}
	free(new_split[1]);
	*new_split[1] = 0;
	*new_split[1] = ft_strdup(check);
	free(check);
	check = 0;
	check = correct_heredoc_name(*new_split[1], 0, 0);
	free(new_split[1]);
	*new_split[1] = 0;
	*new_split[1] = ft_strdup(check);
	free(check);
	check = 0;
}
