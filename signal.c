/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktomat <ktomat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 15:38:36 by ktomat            #+#    #+#             */
/*   Updated: 2023/07/11 14:49:18 by ktomat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	custom_handler(int signal)
{
	(void)signal;
	if (signal == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (signal == SIGQUIT)
	{
		rl_on_new_line();
		rl_redisplay();
	}
}

void	init_termios(void)
{
	struct termios	termios;

	signal(SIGINT, custom_handler);
	signal(SIGQUIT, custom_handler);
	if ((tcgetattr(STDIN_FILENO, &termios)) == -1)
		exit(EXIT_FAILURE);
	termios.c_lflag &= ~(ECHOCTL);
	if ((tcsetattr(STDIN_FILENO, TCSANOW, &termios)) == -1)
		exit(EXIT_FAILURE);
}
