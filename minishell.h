/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktomat <ktomat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 14:26:13 by ktomat            #+#    #+#             */
/*   Updated: 2023/06/27 16:15:12 by ktomat           ###   ########.fr       */
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

# define BUFFER_SIZE 1000

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

//type.c
void	ft_find_type(t_list **list);
char	*ft_find_comm_path(char *path, char *command);
char	*ft_envp(char **envp, char *pwd);

// parsing.c
int		ft_cp_line_long(char *prompt, int *i, char *b);
char	*ft_cp_line(char *prompt, int *i, char *b);
t_list	*ft_parsing(char *prompt, char *b);
int		count_list(t_list **list);

char	**ft_flags(char **envp, t_list **inputs);

//builtin
void	check_builtin(char *cmd, char **flags);
char	**env_copy(char **env);
int		count_list(t_list **list);
void	ft_env(char *cmd, char **flags, char **env_copy);
void	ft_echo(char *cmd, char **flags);
void	ft_exit(char *cmd, char **flags);
void	ft_pwd(char *cmd, char **flags, char **env_copy);
void	ft_cd(char *cmd, char **flags, char **env_copy);

#endif