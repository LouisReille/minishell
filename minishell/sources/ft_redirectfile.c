/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirectfile.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lreille <lreille@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 17:36:35 by lreille           #+#    #+#             */
/*   Updated: 2023/02/28 18:37:58 by lreille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	read_line(char *limiter, int infile)
{
	char	*line;
	char	*line_nl;

	while (1)
	{
		line = readline("> ");
		if (!line)
			return (0);
		if (ft_strcmp(line, limiter) == 0)
		{
			free(line);
			return (0);
		}
		line_nl = ft_strjoin(line, "\n");
		write(infile, line_nl, ft_strlen(line_nl));
		free(line_nl);
		free(line);
	}
}

char	*make_tmp_name(int idx)
{
	char	*itoa_idx;
	char	*tmp_name;

	itoa_idx = ft_itoa(idx);
	tmp_name = ft_strjoin3(".heredoc", itoa_idx, ".tmp");
	free(itoa_idx);
	idx++;
	if (access(tmp_name, F_OK) == 0)
	{
		while (1)
		{
			free(tmp_name);
			itoa_idx = ft_itoa(idx);
			tmp_name = ft_strjoin3(".heredoc", itoa_idx, ".tmp");
			free(itoa_idx);
			if (access(tmp_name, F_OK) != 0)
				break ;
			idx++;
		}
	}
	else
		return (tmp_name);
	return (tmp_name);
}

char	*make_heredoc(char *limiter, int idx)
{
	int		tmp_file;
	char	*tmp_name;
	pid_t	pid;

	tmp_name = make_tmp_name(idx);
	tmp_file = open(tmp_name, O_RDWR | O_CREAT | O_TRUNC, 0644);
	pid = fork();
	if (pid < 0)
		printf("fork_error");
	if (pid == 0)
	{
		read_line(limiter, tmp_file);
		close(tmp_file);
		exit(0);
	}
	if (pid > 0)
	{
		wait(NULL);
		close(tmp_file);
	}
	return (tmp_name);
}

void	set_heredoc(t_data *data)
{
	t_infile_node	*curr;
	char			*file_name;
	int				i;

	if (!data->heredoc_node)
		return ;
	curr = data->heredoc_node->hnext;
	i = 0;
	while (curr)
	{
		file_name = make_heredoc(curr->limiter, i);
		curr->file = file_name;
		curr = curr->hnext;
		i++;
	}
}
