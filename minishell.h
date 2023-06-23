/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 14:26:13 by ktomat            #+#    #+#             */
/*   Updated: 2023/06/22 17:58:51 by itovar-n         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <stdio.h>
# include <errno.h>
# include <sys/wait.h>
# include <fcntl.h>
# include "libft/libft.h"

void	ft_find_type(t_list **list);
char	*ft_find_comm_path(char *path, char *command);
char	*ft_envp(char **envp, char *pwd);

// parsing.c
int		ft_cp_line_long(char *prompt, int *i, char *b);
char	*ft_cp_line(char *prompt, int *i, char *b);
t_list *ft_parsing(char *prompt, char *b);
int					count_list(t_list **list);

char				**ft_flags(char **envp, t_list **inputs);

#endif