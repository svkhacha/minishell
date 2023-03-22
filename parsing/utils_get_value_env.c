/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_get_value_env.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darakely <darakely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 16:47:28 by darakely          #+#    #+#             */
/*   Updated: 2022/12/13 12:21:02 by darakely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*norm_change_dollar(t_data *data, char *delim)
{
	char	*ptr;
	int		len;

	ptr = 0;
	len = 0;
	if (delim && !*delim)
	{
		ptr = ft_strdup("$");
		return (ptr);
	}
	len = check_size_str(delim, "?");
	if (ft_strncmp(delim, "?", 1) == 0)
	{
		ptr = ft_itoa(*data->error_code);
		return (ptr);
	}
	return (ptr);
}

char	*change_dollar(t_data *data, char *delim, int len, char *ptr)
{
	t_env	*tmp;

	tmp = data->info_env;
	while (data->info_env)
	{
		len = check_size_str(delim, data->info_env->key);
		if (ft_strncmp(data->info_env->key, delim, len - 1) == 0)
		{
			ptr = ft_strdup(data->info_env->value);
			data->info_env = tmp;
			return (ptr);
		}
		data->info_env = data->info_env->next;
	}
	data->info_env = tmp;
	return (norm_change_dollar(data, delim));
}
