/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c 12-42-16-946.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktomat <ktomat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 12:22:36 by ktomat            #+#    #+#             */
/*   Updated: 2023/07/11 13:48:00 by ktomat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

typedef struct s_data
{
	int	i;
}			t_data;

t_data g_data;

int	child(char **av, char **env)
{
	return (execve("asdfasdf", av, env));
}

int	main(int ac, char **av, char **env)
{
	pid_t	pid;

	g_data.i = 0;
	fork();
	if (pid == 0)
		printf("%d\n", child(av, env));
	waitpid(pid, NULL, 0);
}
