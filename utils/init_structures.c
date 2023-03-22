/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structures.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darakely <darakely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 20:10:40 by darakely          #+#    #+#             */
/*   Updated: 2022/12/13 17:00:05 by darakely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init_structure_redirection(t_data *data)
{
	data->info_redirect = malloc(sizeof(t_redirection));
	data->info_redirect->count_outfiles_in_pipe = 0;
	data->info_redirect->heredoc_count_in_pipe = 0;
	data->info_redirect->count_infiles_in_pipe = 0;
	data->info_redirect->count_append_in_pipe = 0;
	data->info_redirect->index_outfile = -1;
	data->info_redirect->index_append = -1;
	data->info_redirect->index_infile = -1;
	data->info_redirect->heredoc_name = 0;
	data->info_redirect->fd_outfiles = 0;
	data->info_redirect->fd_infiles = 0;
	data->info_redirect->fd_heredoc = 0;
	data->info_redirect->fd_append = 0;
	data->info_redirect->outfiles = 0;
	data->info_redirect->infiles = 0;
	data->info_redirect->heredoc = 0;
	data->info_redirect->append = 0;
}

void	init_structure_parsing(t_data *data)
{
	data->info_parsing = malloc(sizeof(t_parsing));
	data->info_parsing->flag_for_prelast_redirect = 0;
	data->info_parsing->flag_for_last_redirect = 0;
	data->info_parsing->split_new_promt_execve = 0;
	data->info_parsing->fixed_prelast_redirect = 0;
	data->info_parsing->split_new_promt = 0;
	data->info_parsing->index_outfile = -1;
	data->info_parsing->index_heredoc = -1;
	data->info_parsing->index_infile = -1;
	data->info_parsing->index_append = -1;
	data->info_parsing->check_outfile = 0;
	data->info_parsing->check_append = 0;
	data->info_parsing->hidden_files = 0;
	data->info_parsing->check_infile = 0;
	data->info_parsing->split_pipes = 0;
	data->info_parsing->split_space = 0;
}

void	init_structure_pipe(t_data *data)
{
	data->info_pipe = malloc(sizeof(t_pipe));
	data->info_pipe->output = dup(STDOUT_FILENO);
	data->info_pipe->input = dup(STDIN_FILENO);
	data->info_pipe->split_space = 0;
	data->info_pipe->split_pipe = 0;
	data->info_pipe->count_pipe = 0;
	data->info_pipe->cmd_args = 0;
	data->info_pipe->cnt_cmd = 0;
	data->info_pipe->path = 0;
	data->info_pipe->pid = 0;
	data->info_pipe->cmd = 0;
	data->info_pipe->fd = 0;
}

void	init_structure_data(t_data *data)
{
	data->count_dollar = 0;
	data->last_heredoc = 0;
	data->for_history = 0;
	data->for_current = 0;
	data->len_dollar = 0;
	data->count_pipe = 0;
	data->heredoc = 0;
	data->promt = 0;
	data->flag = 0;
	data->gr = 0;
	data->x = 0;
	data->i = 0;
	data->j = 0;
	data->a = 0;
	data->k = 0;
}

void	init_structure(t_data *data)
{
	init_structure_redirection(data);
	init_structure_parsing(data);
	init_structure_pipe(data);
	init_structure_data(data);
}
