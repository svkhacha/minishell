/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darakely <darakely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 17:30:00 by darakely          #+#    #+#             */
/*   Updated: 2022/12/05 18:29:46 by darakely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	norm_change_shlvl_in_export(t_data *data, char *new_shlvl, char *str)
{
	int		shlvl;

	shlvl = ft_atoi(str);
	shlvl++;
	if (shlvl > 1000)
		shlvl = 1;
	else if (shlvl == 1000)
		shlvl = 0;
	free(data->info_export->value);
	data->info_export->value = 0;
	new_shlvl = ft_itoa(shlvl);
	if (shlvl == 0)
	{
		data->info_export->value = ft_strdup("\"");
		data->info_export->value = ft_strjoin(data->info_export->value, "\"");
	}
	else
	{
		data->info_export->value = ft_strdup("\"");
		data->info_export->value = \
		ft_strjoin(data->info_export->value, new_shlvl);
		data->info_export->value = ft_strjoin(data->info_export->value, "\"");
	}
	free(new_shlvl);
	new_shlvl = 0;
}

void	change_shlvl_in_export(t_data *data, char *check, \
		char *str, char *new_shlvl)
{
	t_export	*tmp;
	int			len;

	len = 0;
	tmp = data->info_export;
	while (data->info_export)
	{
		len = check_size_str(data->info_export->key, "SHLVL=");
		if (ft_strncmp(data->info_export->key, "SHLVL=", len) == 0)
		{
			check = correct_heredoc_name(data->info_export->value, 0, 0);
			str = ft_strdup(check);
			norm_change_shlvl_in_export(data, new_shlvl, str);
			break ;
		}
		data->info_export = data->info_export->next;
	}
	data->info_export = tmp;
	free(check);
	free(str);
	str = 0;
	check = 0;
}
