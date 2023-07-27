/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itovar-n <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 14:26:13 by ktomat            #+#    #+#             */
/*   Updated: 2023/07/27 17:10:34 by itovar-n         ###   ########.fr       */
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

typedef struct s_data
{
	char								**env_copy;
	unsigned int						status;
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

// block.c
t_list	*ft_block_build(t_list **list);
t_list	*ft_block(void);

// builtin_1.c 
int		env_copy1(char **env);
void	ft_env(t_param *param);
void	ft_pwd(t_param *param);

//  builtin_exec.c 
char	*all_lower(char *str);
int		is_existing(char *cmd);
int		check_builtin(char *cmd_long);
int		ft_built_exec(t_param *param);

// cd.c
void	ft_cd(t_param *param);

// constants.c
char	*ft_find_pwd(char *pwd, char *infile);
char	*ft_find_path(char *path, char *command, char *infile);

//dolar.c
int		ft_dolar_long(int i, char *prompt, int *j);
char	*ft_dolar_char(int *i, char *prompt, int *j, char *res);

// echo.c
void	ft_echo(t_param *param);

// export.c
void	ft_export(t_param *param);

// free_clean.c
void	*ft_clean_inputs(void *content);
void	*ft_clean_block(void *content);
void	ft_free_param(t_param *param);
void	ft_free_pipe(int **p1, int lst_size);

// free.c
void	ft_free_ii(int **split, int i);
void	ft_free_cc(char **tab);
void	ft_free_cc_c(char **cc, char *c);
void	ft_free_c_c(char *a, char *b);

// ft_exit.c
void	ft_exit(t_param *param);

// ft_heredoc.c
void	ft_heredoc(char *b_c_infile, t_param *param, int done);
int		ft_fd_heredoc(char *heredoc);

// param_flags.c
char	**ft_flags_execve(t_block *b_c);

// param.c
t_param	*ft_param_c(int lst_size, t_block *b_c, int i, int **p1);

// parsing_check_inputs.c
int		ft_txt_redir(char *txt);
int		ft_check_inputs(t_list **inputs);

// parsing_long.c
int		ft_cp_line_long(char *pr, int i, char *b);

// parsing.c
int		ft_cp_line_core(char *prompt, int *i, char *b, char *res);
char	*ft_cp_line(char *prompt, int *i, char *b);
void	ft_init_type(char *txt, t_type *content);
t_list	*ft_parsing(char *prompt, char *b);

// pipe_fork.c
void	ft_fork(t_param *param, int **p1, int **pid, int *size_pid);
int		*ft_new_pid(int *pid, int size_pid);

//pipe.c
int		**ft_pipe(int lst_size);
void	ft_closepipe(int **p1, int lst_size);
void	ft_waitpid(int *pid, int size_pid);
int		ft_pipe_in(t_param *param, int **p1, int i);
int		ft_pipe_out(t_param *param, int **p1, int i);

//signal.c
void	ft_user(int signal);
void	custom_handler(int signal);
void	init_termios(void);

// unset.c
void	ft_unset(t_param *param);

// utils_1.c
char	**ft_nl_charchar(char **tab, char *txt);

// utils.c
int		find_index_envp(char **envp);
char	*find_home(void);
char	*ft_getpath(char **envp, char *prog);
char	*ft_envp(char **envp, char *pwd);

//builtin
void	ft_env(t_param *param);
void	ft_exit(t_param *param);
void	ft_pwd(t_param *param);
void	ft_cd(t_param *param);
void	ft_export(t_param *param);

// from brew library readline
int		rl_replace_line(const char *text, int i);

#endif