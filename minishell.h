/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktomat <ktomat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 14:26:13 by ktomat            #+#    #+#             */
/*   Updated: 2023/07/07 13:39:15 by ktomat           ###   ########.fr       */
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

// block_utils.c
char	**ft_nl_charchar(char **tab, char *txt);
t_block	*ft_init_block(void);
int		ft_is_redir(t_list *temp);
void	ft_is_command(t_list **temp, t_block *b_c);
int		ft_treat_redir_after(t_list **temp, t_block *b_c);

// parsing.c
t_list	*ft_parsing(char *prompt, char *b);

//dolar.c
int		ft_dolar_long(int i, char *prompt, int *j);
char	*ft_dolar_char(int *i, char *prompt, int *j, char *res);


// block.c
t_list	*ft_block_build(t_list **list);
t_list	*ft_block(void);

// free_clan.c
void	*ft_clean_inputs(void *content);
void	*ft_clean_block(void *content);

// utils.c
void	ft_exit_isa(char *s);
char	*ft_envp(char **envp, char *pwd);

// char	**ft_flags(char **envp, t_list **inputs);

//builtin
void	check_builtin(char *cmd, char **flags);
int		env_copy1(char **env);
int		count_list(t_list **list);
void	ft_env(char **flags);
void	ft_echo(char *cmd, char **flags);
void	ft_exit(char *cmd, char **flags);
void	ft_pwd(char *cmd, char **flags);
void	ft_cd(char **flags);
void	ft_export(char *cmd, char **flags);
void	ft_unset(char *cmd, char **flags);

//signal
int		rl_replace_line(const char *text, int i);
void	init_termios(void);
void	custom_handler(int signal);
void	custom_handler1(int signal);
char	*find_home(void);
int		rl_replace_line(const char *text, int i);
void	init_termios(void);
void	custom_handler(int signal);

void	ft_is_command(t_list **temp, t_block *b_c);
int		ft_dolar_long(int i, char *prompt, int *j);
char	*ft_dolar_char(int *i, char *prompt, int *j, char *res);
char	*ft_envp(char **envp, char *pwd);


//TEST//
char	*ft_getpath(char **envp, char *prog);

#endif