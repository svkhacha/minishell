/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darakely <darakely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 12:11:46 by darakely          #+#    #+#             */
/*   Updated: 2022/12/13 16:27:10 by darakely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	continue_print_echo(char **check, char **str, char *for_free, int i)
{
	while (str && *str)
	{
		for_free = correct_heredoc_name(*str, 0, 0);
		ft_putstr_fd(for_free, STDOUT_FILENO);
		ft_putstr_fd(" ", STDOUT_FILENO);
		str++;
		free_array(&check);
		if (str)
			check = ft_split(*str, ' ');
		i++;
		free(for_free);
		for_free = 0;
	}
}

void	print_echo(char **str, int i)
{
	char	**check;
	char	*for_free;
	int		len;

	check = 0;
	for_free = 0;
	if (str && *str)
		check = ft_split(*str, ' ');
	if (check)
		len = check_size_str(check[0], "-n");
	else
		len = 0;
	if (check && *check && ft_strncmp(check[0], "-n", len) == 0)
	{
		free_array(&check);
		return ;
	}
	continue_print_echo(check, str, for_free, i);
	ft_putstr_fd("\n", STDOUT_FILENO);
	my_free(&for_free);
}

void	print_flag_echo(char **print, char **check, int i)
{
	if (*print)
	{
		while (i-- > 0)
			print++;
		check = ft_split((*print) + ft_strlen(*print), ' ');
	}
	while (print && *print)
	{
		if (check[0])
			ft_putstr_fd(check[0], STDOUT_FILENO);
		else
		{
			if (ft_strncmp(*print, "-n", ft_strlen(*print)) != 0)
				ft_putstr_fd(*print, STDOUT_FILENO);
		}
		print++;
		free_array(&check);
		check = ft_split(*print, ' ');
		ft_putstr_fd(" ", STDOUT_FILENO);
	}	
	free_array(&check);
}

int	check_flag(char *str, int i)
{
	char	*check;

	check = 0;
	if (str)
		check = correct_heredoc_name(str, 0, 0);
	else
		return (-1);
	if (check[i] == '-' && (check[i + 1] && check[i + 1] == 'n'))
	{
		i++;
		while (check[i] && check[i] == 'n')
			i++;
		if (check[i] == 'n' || check[i] == '\0')
		{
			free(check);
			check = 0;
			return (0);
		}
	}
	free(check);
	check = 0;
	return (-1);
}

void	ft_echo(t_data *data, char **str)
{
	char	**check;
	int		flag;
	int		i;

	flag = 0;
	i = 0;
	check = 0;
	while (str && flag == 0 && str[i])
	{
		flag = check_flag(str[i], 0);
		i++;
	}
	if (i > 1)
		print_flag_echo(str, check, --i);
	else
		print_echo(str, 0);
	*data->error_code = 0;
}
