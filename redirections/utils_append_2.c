/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_append_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darakely <darakely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 11:33:48 by darakely          #+#    #+#             */
/*   Updated: 2022/12/13 18:18:13 by darakely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	continue_open_all_append(t_data *data, int x)
{
	if (data->info_redirect->outfiles && data->info_redirect->outfiles[x] == 0)
		while (data->info_redirect->outfiles && \
		data->info_redirect->outfiles[x] == 0)
			x--;
	data->info_redirect->fd_append[data->i] = \
	open(data->info_redirect->append[x], O_CREAT | O_RDWR | O_APPEND, 0644);
	if (data->info_redirect->fd_append[data->i] == -1)
		return (print_append_error(data, data->info_redirect->append[x]));
	data->j++;
	data->i++;
	return (0);
}
