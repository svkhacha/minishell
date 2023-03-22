/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darakely <darakely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 15:28:57 by darakely          #+#    #+#             */
/*   Updated: 2022/11/20 15:33:16 by darakely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	continue_free(t_data *data)
{
	int	i;

	i = -1;
	while (data->info_redirect->infiles && data->info_redirect->infiles[++i])
	{
		free(data->info_redirect->infiles[i]);
		data->info_redirect->infiles[i] = 0;
	}
	if (data->info_redirect->infiles)
	{
		free(data->info_redirect->infiles);
		data->info_redirect->infiles = 0;
	}
	i = -1;
	while (data->info_redirect->append && data->info_redirect->append[++i])
	{
		free(data->info_redirect->append[i]);
		data->info_redirect->append[i] = 0;
	}
	if (data->info_redirect->append)
	{
		free(data->info_redirect->append);
		data->info_redirect->append = 0;
	}	
}

void	free_all_redirect_name(t_data *data)
{
	int	i;

	i = -1;
	while (data->info_redirect->heredoc && data->info_redirect->heredoc[++i])
	{
		free(data->info_redirect->heredoc[i]);
		data->info_redirect->heredoc[i] = 0;
	}
	if (data->info_redirect->heredoc)
	{
		free(data->info_redirect->heredoc);
		data->info_redirect->heredoc = 0;
	}
	i = -1;
	while (data->info_redirect->outfiles && data->info_redirect->outfiles[++i])
	{
		free(data->info_redirect->outfiles[i]);
		data->info_redirect->outfiles[i] = 0;
	}
	if (data->info_redirect->outfiles)
	{
		free(data->info_redirect->outfiles);
		data->info_redirect->outfiles = 0;
	}
	continue_free(data);
}
