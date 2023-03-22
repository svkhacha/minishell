/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_unset_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darakely <darakely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 17:39:46 by darakely          #+#    #+#             */
/*   Updated: 2022/12/12 15:17:52 by darakely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	norm_unset(t_data *data, int j, char *check, char *check_unset)
{
	char	*str;

	str = 0;
	str = correct_heredoc_name(check_unset, 0, 0);
	j = check_size_str(check, str);
	if (ft_strncmp(check, str, j) == 0)
		norm_unset_env(data->info_env);
	free(str);
	str = 0;
}

int	norm_check_arg(t_data *data, char **check_unset, int i, int j)
{
	char	*check;

	check = 0;
	if (check_unset[i][j] == ' ' || \
	(norm_check_add_export(check_unset[i], j) == -1))
	{
		check = correct_heredoc_name(check_unset[i], 0, 0);
		ft_putstr_fd("❌ minishell: unset: `", STDERR_FILENO);
		ft_putstr_fd(check, STDERR_FILENO);
		ft_putstr_fd("' : not a valid identifier\n", STDERR_FILENO);
		*data->error_code = 1;
		free(check);
		check = 0;
		return (-1);
	}
	return (0);
}

void	norm_ft_unset(t_data *data, int j, char *check, char *check_unset)
{
	char	*str;

	str = 0;
	str = correct_heredoc_name(check_unset, 0, 0);
	j = check_size_str(check, check_unset);
	if (ft_strncmp(check, str, j) == 0)
		norm_unset_export(data->info_export);
	free(str);
	str = 0;
}
