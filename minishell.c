/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darakely <darakely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 10:23:12 by darakely          #+#    #+#             */
/*   Updated: 2022/12/14 16:25:48 by darakely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	*g_status;

int	check_promt(t_data *data)
{
	if (!data->promt)
		get_exit(data);
	if (*g_status == -100)
	{
		*g_status = 1;
		free_all(data, 1);
		my_free(&data->promt);
		return (-1);
	}
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	t_data	data;

	data = init_lists(argc, argv, env, &data);
	print_header();
	g_status = malloc(sizeof(int));
	data.error_code = g_status;
	*g_status = *data.error_code;
	change_shlvl(&data);
	while (1)
	{
		ft_signal();
		init_structure(&data);
		data.promt = readline("Minishell$  ");
		if (check_promt(&data) == -1)
			continue ;
		data.for_history = ft_strdup(data.promt);
		parsing(&data);
		if (ft_strlen(data.for_history) > 0)
			add_history(data.for_history);
		free(data.promt);
		free(data.for_history);
		close_all_fds(&data);
		free_all(&data, 1);
	}
	return (0);
}
