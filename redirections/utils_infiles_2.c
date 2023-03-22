/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_infiles_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darakely <darakely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 21:40:25 by darakely          #+#    #+#             */
/*   Updated: 2022/12/13 22:28:49 by darakely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	norm_ft_infiles(t_data *data, char **pipe, int j)
{
	int	i;

	i = -1;
	pipe = ft_split(data->promt, '|');
	while (pipe[++i])
		;
	i += j + 1;
	count_infile_in_pipe(data, pipe, i, -1);
	free_array(&pipe);
}

int	norm_open_all_infiles_2(t_data *data, int x, int **check)
{
	data->info_redirect->fd_infiles[data->i] = \
	open(data->info_redirect->infiles[x], O_RDWR);
	if (data->info_redirect->fd_infiles[data->i] == -1)
		return (print_infile_error(data, data->info_redirect->infiles[x]));
	data->j++;
	data->i++;
	*check = 0;
	return (0);
}

int	continue_open_all_infiles(t_data *data, int *check, int *x, int *count_pipe)
{
	int	current;

	(void)x;
	(void)count_pipe;
	current = 0;
	if (data->info_redirect->count_infiles_in_pipe && \
	(*check == data->info_redirect->count_infiles_in_pipe[data->j]))
	{
		if (norm_open_all_infiles_2(data, *x, &check) == -1)
			return (-1);
		data->x++;
		data->count_pipe--;
	}
	else
	{
		current = open(data->info_redirect->infiles[data->for_current], O_RDWR);
		if (current == -1)
			return (print_infile_error \
			(data, data->info_redirect->infiles[data->for_current]));
	}
	return (0);
}
