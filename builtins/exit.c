/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darakely <darakely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 15:08:10 by darakely          #+#    #+#             */
/*   Updated: 2022/12/13 16:45:05 by darakely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_error_exit(t_data *data, char *str)
{
	int	error;

	*data->error_code = 255;
	error = *data->error_code;
	ft_putstr_fd("exit\n", STDOUT_FILENO);
	ft_putstr_fd("❌ minishell: exit: ", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
	free(str);
	str = 0;
	free_all(data, 0);
	exit(error);
}

int	check_long_num(t_data *data, char *str, int j, char **check_arg)
{
	int				i;
	char			**print_exit;

	i = -1;
	print_exit = 0;
	print_exit = ft_split(data->promt, '|');
	if ((ft_strncmp(str, "9223372036854775807", 19) <= 0) || \
	(j == 1 && ft_strncmp(str, "9223372036854775808", 19) <= 0))
	{
		while (check_arg[++i])
			;
		if (i > 1)
			return (print_too_many_arguments(data, print_exit));
		continue_check_long_num(data, str, j);
	}
	print_error_exit(data, check_arg[0]);
	return (0);
}

int	continue_check_exit_code(char **check, t_data *data, char **str)
{
	int		i;
	int		j;
	char	*for_free;

	i = 0;
	j = 0;
	*data->error_code = ft_atoi(check[0]);
	for_free = 0;
	for_free = correct_heredoc_name(check[0], 0, 0);
	free(check[0]);
	check[0] = 0;
	check[0] = ft_strdup(for_free);
	free(for_free);
	for_free = 0;
	j = continue_continue_check_exit_code(check, i);
	while (check[0][i] == '0')
		i++;
	if (ft_strlen(&check[0][i]) > 19)
		print_error_exit(data, check[0]);
	if (check_long_num(data, &check[0][i], j, str) == -1)
		return (-1);
	return (0);
}

int	check_exit_code(char **check, t_data *data, char **str)
{
	char	*for_free;

	for_free = 0;
	for_free = clear_value_env(check[0], 0, 0);
	free(check[0]);
	check[0] = 0;
	check[0] = ft_strdup(for_free);
	free(for_free);
	for_free = 0;
	continue_check_exit_code_2(data, check);
	if (continue_check_exit_code(check, data, str) == -1)
		return (-1);
	return (0);
}

void	ft_exit(t_data *data, char **str)
{
	char			**print_exit;
	char			**check;
	int				for_exit;

	print_exit = 0;
	check = 0;
	if (str)
		check = ft_split(*str, ' ');
	print_exit = ft_split(data->promt, '|');
	if (str)
	{
		if (check && check[0])
		{
			if (check_exit_code(check, data, str) == -1)
			{
				free_array(&check);
				free_array(&print_exit);
				return ;
			}
		}
	}
	continue_ft_exit(data, check, &for_exit);
	free_array(&check);
	free_array(&print_exit);
	exit(for_exit);
}
