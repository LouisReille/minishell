/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcacoilo <mcacoilo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 01:14:21 by mcacoilo          #+#    #+#             */
/*   Updated: 2023/02/13 01:17:39 by mcacoilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirection_and_pipe.h"

void	parent_free(t_pipex *pipex)
{
	int	i;

	i = 0;
	close(pipex->input);
	close(pipex->output);
	while (pipex->path_arr[i])
	{
		free(pipex->path_arr[i]);
		i++;
	}
	free(pipex->path_arr);
}

void	child_free(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (pipex->cmd_args[i])
	{
		free(pipex->cmd_args[i]);
		i++;
	}
	free(pipex->cmd_args);
	free(pipex->cmd);
}
