/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktomat <ktomat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 13:10:25 by ktomat            #+#    #+#             */
/*   Updated: 2023/06/23 14:48:11 by ktomat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_redir(t_list *temp)
{
	if (!ft_strncmp(temp->txt, "<<", 2) && ft_strlen(temp->txt) == 2)
		temp->dc_g = 1;
	else if (!ft_strncmp(temp->txt, ">>", 2) && ft_strlen(temp->txt) == 2)
		temp->dc_d = 1;
	else if (!ft_strncmp(temp->txt, "<", 1) && ft_strlen(temp->txt) == 1)
		temp->c_g = 1;
	else if (!ft_strncmp(temp->txt, ">", 1) && ft_strlen(temp->txt) == 1)
		temp->c_d = 1;
	else if (!ft_strncmp(temp->txt, "|", 1) && ft_strlen(temp->txt) == 1)
		temp->pipe = 1;
	else
		return (0);
	return (1);
}

void	ft_is_command(t_list *temp)
{
	if (!temp)
		return ;
	temp->cmd = 1;
	temp = temp->next;
	while (temp && ft_is_redir(temp) == 0)
	{
		temp->arg = 1;
		temp = temp->next;
	}
}

//permet de donner un type a chaque maillon de la liste chainee
void	ft_find_type(t_list **l)
{
	t_list	*temp;

	temp = *l;
	while (temp)
	{
		ft_is_redir(temp);
		if (temp->c_g == 1)
		{	
			temp = temp->next;
			temp->infile = 1;
		}
		else if (temp->c_d == 1)
		{	
			temp = temp->next;
			temp->outfile = 1;
		}
		else if (temp->dc_g == 1)
		{	
			temp = temp->next;
			temp->infile_d = 1;
		}
		else if (temp->dc_d == 1)
		{	
			temp = temp->next;
			temp->outfile_d = 1;
		}
		else if (temp->pipe == 0)
			ft_is_command(temp);
		if (!temp)
			break ;
		temp = temp->next;
	}
}

int	count_list(t_list **list)
{
	t_list	*temp;
	int		i;

	i = 0;
	temp = *list;
	while (*list)
	{
		i++;
		*list = (*list)->next;
	}
	*list = temp;
	return (i);
}

int	tab_len(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

//free les strdup et le tableau en dernier
char	**env_copy(char **env)
{
	char	**env_copy;
	int		i;

	i = 0;
	env_copy = ft_calloc(sizeof(char **), tab_len(env) + 1);
	if (env_copy == NULL)
		return (NULL);
	while (env[i])
	{
		env_copy[i] = ft_strdup(env[i]);
		i++;
	}
	return (env_copy);
}

//permet de changer les regles du terminal et de ne pas afficher le ctrl c
void	init_termios(void)
{
	struct termios	termios;

	if ((tcgetattr(STDIN_FILENO, &termios)) == -1)
		exit(EXIT_FAILURE);
	termios.c_lflag &= ~(ECHOCTL);
	if ((tcsetattr(STDIN_FILENO, TCSANOW, &termios)) == -1)
		exit(EXIT_FAILURE);
}
