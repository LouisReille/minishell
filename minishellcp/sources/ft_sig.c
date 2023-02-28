/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sig.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lreille <lreille@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 17:19:29 by lreille           #+#    #+#             */
/*   Updated: 2023/02/28 13:43:17 by lreille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <signal.h>

void	action(int signum)
{
	(void)signum;
	if (signum == 2)
	{
		printf("\n");
		rl_on_new_line();
	//	rl_replace_line("", 0);
		rl_redisplay();
	//	exit(127);
	}
	if (signum == 3)
	{
	//	printf("\n");
		rl_on_new_line();
		rl_redisplay();
	//	exit(127);
	}
}

void	rm_ctrl(void)
{
	struct termios	attr;

	tcgetattr(STDIN_FILENO, &attr);
	attr.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &attr);
}

