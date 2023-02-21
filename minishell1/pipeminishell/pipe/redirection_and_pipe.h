/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_and_pipe.h                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcacoilo <mcacoilo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 01:04:14 by mcacoilo          #+#    #+#             */
/*   Updated: 2023/02/18 04:43:39 by lreille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECTION_AND_PIPE_H
# define REDIRECTION_AND_PIPE_H
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <stdlib.h>
# include <string.h>
# include <errno.h>
# include <sysexits.h>
# include <unistd.h>
//inclure la libft //

typedef struct s_env
{
	char			*data;
	struct s_env	*next;
}				t_env;

typedef struct s_mini
{
	char		*path;
	char		*cmd;
	char		**path_arr;
	int			pid;
	int			argc;
	int			last_status;
	t_env		*env;
	int			space_line;
}				t_mini;

typedef struct s_pipex
{
	int		fd[2];
	int		input;
	int		output;
	int		pid1;
	int		pid2;
	char	**cmd_args;
	char	*cmd;
	char	*paths;
	char	**path_arr;
}	t_pipex;

//pipe.c
char	*ft_strjoin(char const *, char const *);
char	*get_path(char **);
void	close_fd(t_pipex *);
int		pipex_func(int , char **, char **);

//child.c
char	*get_cmd(char **, char *);
void	first_child(t_pipex, char **, char **);
void	second_child(t_pipex, char **, char **);

//free.c
void	parent_free(t_pipex *);
void	child_free(t_pipex *);

//ft_split.c
char	**ft_split(char *, char);
#endif
