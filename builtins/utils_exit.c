/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darakely <darakely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 17:31:53 by darakely          #+#    #+#             */
/*   Updated: 2022/12/13 16:50:26 by darakely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	continue_check_long_num(t_data *data, char *str, int j)
{
	int				for_exit;
	unsigned char	error;

	(void)j;
	error = ft_atoi(str);
	*data->error_code = error;
	ft_putstr_fd("exit\n", STDOUT_FILENO);
	for_exit = *data->error_code;
	free_all(data, 0);
	exit(for_exit);
}

int	print_too_many_arguments(t_data *data, char **print_exit)
{
	ft_putstr_fd("exit\n", STDOUT_FILENO);
	ft_putstr_fd("❌ minishell: exit: too many arguments\n", \
	STDERR_FILENO);
	*data->error_code = 1;
	free_array(&print_exit);
	return (-1);
}

int	continue_continue_check_exit_code(char **check, int i)
{
	int	j;

	j = 0;
	if (check[0][i] == '-' || check[0][i] == '+')
	{
		if (check[0][i] == '-')
			j = 1;
		i++;
	}
	return (j);
}

void	continue_ft_exit(t_data *data, char **check, int *for_exit)
{
	unsigned char	error;

	ft_putstr_fd("exit\n", STDOUT_FILENO);
	if (check && check[0])
	{
		error = ft_atoi(check[0]);
		*data->error_code = error;
	}
	*for_exit = *data->error_code;
	free_all(data, 0);
}

void	continue_check_exit_code_2(t_data *data, char **check)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (check[0][i])
	{
		if (!(check[0][i] >= '0' && check[0][i] <= '9'))
		{
			if (!(check[0][i] == '-' || check[0][i] == '+'))
				print_error_exit(data, check[0]);
			if ((check[0][i] == '-' || check[0][i] == '+') && \
			(check[0][i + 1] && !(check[0][i + 1] >= '0' && \
			check[0][i + 1] <= '9')))
				print_error_exit(data, check[0]);
			if (check[0][0] == '-' || check[0][0] == '+')
			{
				if (check[0][1] == '\0')
					print_error_exit(data, check[0]);
			}
			else
				j++;
		}
		i++;
	}
}
