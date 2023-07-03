/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktomat <ktomat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 14:26:13 by ktomat            #+#    #+#             */
/*   Updated: 2023/07/03 13:55:49 by ktomat           ###   ########.fr       */
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
	int				infile_d;
	int				outfile_d;
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

// //type.c
// void	ft_find_type(t_list **list);
// char	*ft_find_comm_path(char *path, char *command);
// char	*ft_envp(char **envp, char *pwd);

// // parsing.c
// int		ft_cp_line_long(char *prompt, int *i, char *b);
// char	*ft_cp_line(char *prompt, int *i, char *b);
// t_list	*ft_parsing(char *prompt, char *b);
// int		count_list(t_list **list);

// char	**ft_flags(char **envp, t_list **inputs);

// //builtin
// void	check_builtin(char *cmd, char **flags, char **env_copy);
// char	**env_copy1(char **env);
// int		count_list(t_list **list);
// void	ft_env(char *cmd, char **flags, char **env_copy);
// void	ft_echo(char *cmd, char **flags);
// void	ft_exit(char *cmd, char **flags);
// void	ft_pwd(char *cmd, char **flags, char **env_copy);
// void	ft_cd(char *cmd, char **flags, char **env_copy);
// void	ft_export(char *cmd, char **flags, char **env_copy);
// char	**ft_unset(char *cmd, char **flags, char **env_copy);

// //signal
// int		rl_replace_line(const char *text, int i);
// void	init_termios(void);
// void	custom_handler(int signal);
// void	custom_handler1(int signal);

#endif