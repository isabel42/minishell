/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktomat <ktomat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 15:38:36 by ktomat            #+#    #+#             */
/*   Updated: 2023/06/30 12:59:28 by ktomat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_sigquit(int signal)
{
	(void)signal;
	exit(1);
}

void	handle_sigint(int signal)
{
	(void)signal;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	custom_handler(int signal)
{
	if (signal == SIGINT)
		handle_sigint(signal);
	else if (signal == SIGQUIT)
		handle_sigquit(signal);
}

int	init_termios(void)
{
	struct sigaction	sig;
	struct termios		tp;

	sig.sa_handler = &custom_handler;
	sigaction(SIGINT, &sig, NULL);
	sigaction(SIGQUIT, &sig, NULL);
	if (tcgetattr(STDIN_FILENO, &tp) == -1)
		return (-1);
	tp.c_lflag &= ~ECHOCTL;
	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &tp) == -1)
		return (-1);
	return (0);
}
