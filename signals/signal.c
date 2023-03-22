/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darakely <darakely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 14:23:16 by darakely          #+#    #+#             */
/*   Updated: 2022/12/14 16:15:06 by darakely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern int	*g_status;

void	get_and_set_attr(int flag)
{
	struct termios	ts;

	tcgetattr(STDIN_FILENO, &ts);
	if (flag == 0)
	{
		ts.c_lflag &= ~ECHOCTL;
		tcsetattr(STDIN_FILENO, TCSANOW, &ts);
	}
	else if (flag == 1)
	{
		ts.c_lflag |= ECHOCTL;
		tcsetattr(STDIN_FILENO, TCSANOW, &ts);
	}
}

void	ft_ctrl_c(int sig_num)
{
	(void)sig_num;
	*g_status = -100;
	rl_done = 1;
}

int	ft_signal(void)
{
	get_and_set_attr(0);
	signal(SIGINT, ft_ctrl_c);
	signal(SIGQUIT, SIG_IGN);
	return (0);
}
