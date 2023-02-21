/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_and_pipe.h                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcacoilo <mcacoilo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 01:04:14 by mcacoilo          #+#    #+#             */
/*   Updated: 2023/02/13 01:17:12 by mcacoilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECTION_AND_PIPE_H
# define REDIRECTION__AND_PIPE_H
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <stdlib.h>
# include <string.h>
# include <errno.h>
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

#endif
