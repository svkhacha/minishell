/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darakely <darakely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 18:54:36 by darakely          #+#    #+#             */
/*   Updated: 2022/12/13 17:12:27 by darakely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_struct_pipe(t_data *data)
{
	free_array(&data->info_pipe->split_space);
	free_array(&data->info_pipe->split_pipe);
	free_array(&data->info_pipe->cmd_args);
	free_array(&data->info_pipe->path);
	free(data->info_pipe->cmd);
	free(data->info_pipe->pid);
	free(data->info_pipe->fd);
}

void	free_struct_redirection(t_data *data)
{
	free(data->info_redirect->count_outfiles_in_pipe);
	free(data->info_redirect->count_infiles_in_pipe);
	free(data->info_redirect->heredoc_count_in_pipe);
	free(data->info_redirect->count_append_in_pipe);
	free_array(&data->info_redirect->heredoc_name);
	free_array(&data->info_redirect->outfiles);
	free_array(&data->info_redirect->heredoc);
	free_array(&data->info_redirect->infiles);
	free_array(&data->info_redirect->append);
	free(data->info_redirect->fd_outfiles);
	free(data->info_redirect->fd_infiles);
	free(data->info_redirect->fd_heredoc);
	free(data->info_redirect->fd_append);
}

void	free_list_export(t_export **export)
{
	t_export	*tmp;

	while (*export)
	{
		tmp = (*export)->next;
		free((*export)->key);
		free((*export)->value);
		free((*export));
		(*export) = tmp;
	}
	free((*export));
	*export = 0;
}

void	free_list_env(t_env **env)
{
	t_env	*tmp;

	while ((*env))
	{
		tmp = (*env)->next;
		free((*env)->key);
		free((*env)->value);
		free((*env));
		(*env) = tmp;
	}
	free((*env));
	*env = 0;
}

void	free_array(char ***str)
{
	int	i;

	i = 0;
	if (*str)
	{
		while ((*str)[i])
		{
			free((*str)[i]);
			(*str)[i] = 0;
			i++;
		}
		free(*str);
		*str = 0;
	}
}
