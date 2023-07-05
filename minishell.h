/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 14:26:13 by ktomat            #+#    #+#             */
/*   Updated: 2023/07/04 17:22:31 by itovar-n         ###   ########.fr       */
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

typedef struct s_type
{
	char			*txt;
	int				pipe;
	int				c_g;
	int				c_d;
	int				dc_g;
	int				dc_d;
}	t_type;

typedef struct s_block
{
	char	*cmd;
	char	**arg;
	char	**infile;
	char	**outfile;
}	t_block;

//type.c
char	**ft_nl_charchar(char **tab, char *txt);
void	ft_init_block(t_block *block);
t_list	*ft_find_type(t_list **list);

// parsing.c
t_list	*ft_parsing(char *prompt, char *b);

// block.c
t_list	*ft_block(void);

// free_clan.c
void	*ft_clean_type(void *content);
void	*ft_clean_block(void *content);

// char	**ft_flags(char **envp, t_list **inputs);

#endif