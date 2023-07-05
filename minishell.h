/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktomat <ktomat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 14:26:13 by ktomat            #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/07/04 15:42:23 by itovar-n         ###   ########.fr       */
=======
/*   Updated: 2023/07/03 12:55:07 by ktomat           ###   ########.fr       */
>>>>>>> kimi
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
# include <termios.h>
# include <signal.h>

# define BUFFER_SIZE 1000 //pour la fonction getcwd

typedef struct s_data//ajouter t_data	g_data; in all files
{
	char					**env_copy;
	volatile sig_atomic_t	status;
}				t_data;

t_data	g_data;

typedef struct s_type
{
	char			*txt;
	int				cmd;
	int				infile;
	int				outfile;
	int				pipe;
	int				c_g;
	int				c_d;
	int				dc_g;
	int				dc_d;
	int				arg;
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

//builtin
void	check_builtin(char *cmd, char **flags, char **env_copy);
char	**env_copy1(char **env);
int		count_list(t_list **list);
void	ft_env(char *cmd, char **flags, char **env_copy);
void	ft_echo(char *cmd, char **flags);
void	ft_exit(char *cmd, char **flags);
void	ft_pwd(char *cmd, char **flags, char **env_copy);
void	ft_cd(char *cmd, char **flags, char **env_copy);
void	ft_export(char *cmd, char **flags, char **env_copy);
char	**ft_unset(char *cmd, char **flags, char **env_copy);

//signal
int		rl_replace_line(const char *text, int i);
void	init_termios(void);
void	custom_handler(int signal);
void	custom_handler1(int signal);

#endif