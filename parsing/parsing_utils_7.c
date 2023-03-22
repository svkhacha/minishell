/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_7.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darakely <darakely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 13:51:22 by darakely          #+#    #+#             */
/*   Updated: 2022/12/13 14:42:17 by darakely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*norm_continue_clear(char **split_space, char **str, char *check)
{
	int	len;

	len = check_size_str(check, "exit");
	if (ft_strncmp(check, "exit", len) == 0)
	{
		free_array(&split_space);
		free(check);
		check = 0;
		return (*str);
	}
	free_array(&split_space);
	free(check);
	check = 0;
	return (0);
}

char	*continue_clear(char **split_space, char **str, char *check)
{
	int	len;

	len = check_size_str(check, "unset");
	if (ft_strncmp(check, "unset", len) == 0)
	{
		free_array(&split_space);
		free(check);
		check = 0;
		return (*str);
	}
	len = check_size_str(check, "env");
	if (ft_strncmp(check, "env", len) == 0)
	{
		free_array(&split_space);
		free(check);
		check = 0;
		return (*str);
	}
	return (norm_continue_clear(split_space, str, check));
}

char	*norm_clear_promt_builtins(char **split_space, char **str, char *check)
{
	int	len;

	len = check_size_str(check, "cd");
	if (ft_strncmp(check, "cd", len) == 0)
	{
		free_array(&split_space);
		free(check);
		check = 0;
		return (*str);
	}
	len = check_size_str(check, "export");
	if (ft_strncmp(check, "export", len) == 0)
	{
		free_array(&split_space);
		free(check);
		check = 0;
		return (*str);
	}
	return (continue_clear(split_space, str, check));
}

char	*continue_clear_promt_builtins(char **split_space, \
		char **str, char *check)
{
	int	len;

	len = check_size_str(check, "echo");
	if (ft_strncmp(check, "echo", len) == 0)
	{
		free_array(&split_space);
		free(check);
		check = 0;
		return (*str);
	}
	len = check_size_str(check, "pwd");
	if (ft_strncmp(check, "pwd", len) == 0)
	{
		free_array(&split_space);
		free(check);
		check = 0;
		return (*str);
	}
	return (norm_clear_promt_builtins(split_space, str, check));
}

char	*clear_promt_builtins(char **str)
{
	char	**split_space;
	char	*check;

	split_space = 0;
	check = 0;
	split_space = ft_split(*str, ' ');
	if (split_space)
		check = correct_heredoc_name(split_space[0], 0, 0);
	else
		return (0);
	if (check && !*check)
	{
		free_array(&split_space);
		free(check);
		check = 0;
		return (0);
	}
	return (continue_clear_promt_builtins(split_space, str, check));
}
