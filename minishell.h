/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktomat <ktomat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 14:26:13 by ktomat            #+#    #+#             */
/*   Updated: 2023/07/24 14:42:28 by ktomat           ###   ########.fr       */
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
# define ERROR1 "Syntax error: Error text reviewd file block_build_utils"

typedef struct s_data
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
	char	**in;
	char	**out;
}	t_block;

typedef struct s_param
{
	char		*cmd;
	char		*infile;
	char		*outfile;
	char		*heredoc;
	int			lst_size;
	char		*chev_out;
	int			fd_in;
	int			fd_out;
	char		**flags;
}				t_param;

// block_build_utils.c
int		ft_inout(t_list **temp, t_block *b_c);
t_block	*ft_init_block(void);
int		ft_is_redir(t_list *temp);
void	ft_is_command(t_list **temp, t_block *b_c);
int		ft_treat_redir_after(t_list **temp, t_block *b_c);

// parsing.c
int		ft_cp_line_long(char *prompt, int i, char *b);
int		ft_cp_line_core(char *prompt, int *i, char *b, char *res);
char	*ft_cp_line(char *prompt, int *i, char *b);
void	ft_init_type(char *txt, t_type *content);
t_list	*ft_parsing(char *prompt, char *b);

//dolar.c
int		ft_dolar_long(int i, char *prompt, int *j);
char	*ft_dolar_char(int *i, char *prompt, int *j, char *res);

// block.c
t_list	*ft_block_build(t_list **list);
t_list	*ft_block(void);

// free_clean.c
void	ft_free_cc(char **tab);
void	*ft_clean_inputs(void *content);
void	*ft_clean_block(void *content);
void	ft_free_cc(char **tab);
void	ft_free_pipe(int **p1, int lst_size);

// utils.c
int		find_index_envp(char **envp);
char	*find_home(void);
char	*ft_getpath(char **envp, char *prog);
char	*ft_envp(char **envp, char *pwd);
void	ft_exit_isa(char *s);

// utils_1.c
char	**ft_nl_charchar(char **tab, char *txt);
void	ft_cd_util(char *current_path, char *old_path);
char	**ft_flags_execve(t_block *b_c);

//builtin
int		env_copy1(char **env);
int		count_list(t_list **list);
void	ft_env(t_param *param);
void	ft_echo(t_param *param);
void	ft_exit(t_param *param);
void	ft_pwd(t_param *param);
void	ft_cd(t_param *param);
void	ft_export(t_param *param);
void	ft_unset(t_param *param);

//signal
int		rl_replace_line(const char *text, int i);
void	init_termios(void);
void	custom_handler(int signal);
void	custom_handler1(int signal);
char	*find_home(void);
void	init_termios(void);
void	custom_handler(int signal);

//ft_exec
void	ft_heredoc(char *b_c_infile, t_param *param, int done);
int		ft_fd_heredoc(char *heredoc);

//pipex
char	*ft_envp(char **envp, char *pwd);
char	*ft_find_pwd(char *pwd, char *infile);
char	*ft_find_path(char *path, char *command, char *infile);

void	ft_free_cc(char **split);
void	ft_free_ii(int **split, int i);
void	ft_free_param(t_param *param);
void	ft_free_cc_c(char **cc, char *c);

//pipe.c
int		**ft_pipe(int lst_size);
void	ft_closepipe(int **p1, int lst_size);
void	ft_waitpid(int *pid);
int		ft_pipe_out(t_param *param, int **p1, int i);
int		ft_pipe_in(t_param *param, int **p1, int i);

//builtins-exec.c
int		check_builtin(char *cmd_long);
int		ft_built_exec(t_param *param);

t_param	*ft_param(int lst_size, t_block *b_c, int i, int **p1);
void	ft_fork(t_param *param, int **p1, int *pid);
int		*ft_new_pid(int *pid);

//error
void	msg_error(char *str, int status);

//TEST//
char	*ft_getpath(char **envp, char *prog);

#endif