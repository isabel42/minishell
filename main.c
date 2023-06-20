/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktomat <ktomat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 16:06:33 by ktomat            #+#    #+#             */
/*   Updated: 2023/06/20 16:43:04 by ktomat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_envp(char **envp, char *pwd)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], pwd, ft_strlen(pwd)) == 0)
			return (envp[i] + ft_strlen(pwd));
		i++;
	}
	return (NULL);
}

void	ft_free_cc(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

void	ft_free_cc_c(char **cc, char *c)
{
	ft_free_cc(cc);
	free(c);
}

char	*ft_find_comm_path(char *path, char *command)
{
	char	**path_split;
	char	*path_command;
	char	*slash_command;
	int		i;

	if (access(command, X_OK) == 0)
		return (command);
	i = 0;
	if (command)
	{
		slash_command = ft_strjoin("/", command);
		path_split = ft_split(path, ':');
		while (path_split[i])
		{
			path_command = ft_strjoin(path_split[i], slash_command);
			if (access(path_command, X_OK) == 0)
			{
				ft_free_cc_c(path_split, slash_command);
				return (path_command);
			}
			free(path_command);
			i++;
		}
		ft_free_cc_c(path_split, slash_command);
	}
	return (NULL);
}

char	**ft_flags(char **envp, char *prompt)
{
	char	**flags;
	char	*only_flag;
	int		j;

	flags = malloc(sizeof(flags) * 3);
	if (!flags)
		exit(0);
	j = 0;
	while (prompt[j] != ' ' && prompt[j] != '\0')
		j++;
	if (prompt[j] == '\0')
		only_flag = NULL;
	else
	{
		while (prompt[j] == ' ')
			j++;
		if (prompt[j] == '\0')
			only_flag = NULL;
		else
			only_flag = prompt + j;
	}
	flags[0] = ft_envp(envp, "PATH=");
	flags[1] = only_flag;
	flags[2] = NULL;
	return (flags);
}

int	ft_isspace(char c)
{
	char *s;

	s = " \t\n\v\f\r";
	if (ft_strrchr(s, c))
		return (1);
	return (0);
}

int	ft_cp_line_long(char *prompt, int *i, char *b)
{
	int	j;
	int	open_quotes;
	char	*quotes;

	j = 0;
	open_quotes = 0;
	while (prompt[*i + j] != '\0' && (prompt[*i + j] != ' ' || open_quotes == 1))
	{
		if (ft_strrchr(b, prompt[*i + j]) && open_quotes == 0)
		{
			open_quotes = 1;
			quotes = ft_strrchr(b, prompt[*i + j]);
		}
		else if (quotes == ft_strrchr(b, prompt[*i + j]) && open_quotes == 1)
			open_quotes = 0;
		j++;
	}
	return (j + 1);

}

char	*ft_cp_line(char *prompt, int *i, char *b)
{
	char	*res;
	int		j;

	j = ft_cp_line_long(prompt, i, b);
	res = malloc(sizeof(char) * (j + 1));
	if (!res)
		return (NULL);
	res[j] = '\0';
	j--;
	while (j >= 0)
	{
		res[j] = prompt[*i + j];
		j--;
	}
	*i = *i + ft_strlen(res);
	return (res);
}

int	main (int argc, char **argv, char **envp)
{
	char	*prompt;
	char	*command;
	char	*txt;
	char	**split_prompt;
	int		pid;
	t_list	*inputs;

	(void) argc;
	(void) argv;
	(void) envp;
	inputs = NULL;
	while (42)
	{
		pid = 0;
		prompt = readline("minishell> ");
		add_history(prompt);
		while (prompt[pid] != '\0')
		{
			txt = ft_cp_line(prompt, &pid, "\'\"");
			printf("txt: %s\n", txt);
			ft_lstadd_back(&inputs, ft_lstnew(txt));
		}
		ft_find_type(&inputs, envp);
		while (inputs)
		{
			printf("%s : infile %d : cmd %d : c_g %d : c_d %d : dc_g %d : dc_d %d : pipe %d\n", inputs->txt, inputs->file, inputs->cmd, inputs->c_g, inputs->c_d, inputs->dc_g, inputs->dc_d, inputs->pipe);
			inputs = inputs->next;
		}
		split_prompt = ft_split(prompt, ' ');
		command = ft_find_comm_path(ft_envp(envp, "PATH="), split_prompt[0]);
		pid = fork();
		if (pid == 0)
			execve(command, ft_flags(envp, prompt), NULL);
		waitpid(pid, NULL, 0);
	}
	return (0);
}
