/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_syntax_error.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darakely <darakely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 13:52:19 by darakely          #+#    #+#             */
/*   Updated: 2022/12/12 15:24:19 by darakely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	continue_print_syntax_error(char **ptr, t_data *data)
{
	ft_putstr_fd("❌ minishell: syntax error near unexpected token `", \
	STDERR_FILENO);
	ft_putstr_fd(*ptr, STDERR_FILENO);
	ft_putstr_fd("'\n", STDERR_FILENO);
	*data->error_code = 258;
	free(*ptr);
	*ptr = 0;
}

void	print_syntax_error(t_data *data, char *error)
{
	char	*ptr;
	int		i;

	ptr = malloc(sizeof(char) * (ft_strlen(error) + 1));
	if (!ptr)
		return ;
	i = 0;
	while (error[i] && error[i] != ' ' && (error[i] == '|' || (error[i] == '<' \
		&& error[i + 1] && error[i + 1] != '<') || error[i] == '>' || \
		error[i] == ';' || error[i] == '\\' || error[i] == '*' || \
		error[i] == '&'))
	{
		ptr[i] = error[i];
		i++;
	}
	if (i == 0)
	{
		while (error[i] == '<' || error[i] == '>')
		{
			ptr[i] = error[i];
			i++;
		}
	}
	ptr[i] = '\0';
	continue_print_syntax_error(&ptr, data);
}
