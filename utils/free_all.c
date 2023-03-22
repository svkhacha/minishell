/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darakely <darakely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 19:54:57 by darakely          #+#    #+#             */
/*   Updated: 2022/12/12 15:21:40 by darakely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_unlink(t_parsing *info)
{
	int	i;

	i = -1;
	while (info->hidden_files && info->hidden_files[++i])
		unlink(info->hidden_files[i]);
}

void	free_struct_parsing(t_data *data)
{
	ft_unlink(data->info_parsing);
	free_array(&data->info_parsing->split_new_promt_execve);
	free(data->info_parsing->flag_for_prelast_redirect);
	free(data->info_parsing->flag_for_last_redirect);
	free(data->info_parsing->fixed_prelast_redirect);
	free_array(&data->info_parsing->split_new_promt);
	free_array(&data->info_parsing->hidden_files);
	free_array(&data->info_parsing->split_pipes);
	free_array(&data->info_parsing->split_space);
}

void	free_all(t_data *data, int flag)
{
	if (flag == 0)
	{
		free_list_export(&data->info_export);
		free_list_env(&data->info_env);
		free(data->error_code);
		data->error_code = 0;
	}
	free_struct_redirection(data);
	free_struct_parsing(data);
	free_struct_pipe(data);
	free(data->info_redirect);
	free(data->info_parsing);
	free(data->info_pipe);
}
