/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcacoilo <mcacoilo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 01:13:42 by mcacoilo          #+#    #+#             */
/*   Updated: 2023/02/18 04:47:24 by lreille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirection_and_pipe.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while ((s1[i] || s2[i]) && i < n)
	{
		if (s1[i] != s2[i])
			return (((unsigned char *) s1)[i] - ((unsigned char *) s2)[i]);
		i++;
	}
	return (0);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	i;
	size_t	j;

	if (!s1 || !s2)
		return (strdup(""));
	str = (char *)malloc(sizeof(*s1) * (strlen(s1) + strlen(s2) + 1));
	if (str == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i] != '\0')
	{
		str[j++] = s1[i];
		i++;
	}
	i = 0;
	while (s2[i] != '\0')
	{
		str[j++] = s2[i];
		i++;
	}
	str[j] = '\0';
	return (str);
}

char	*get_path(char **envp)
{
	int	i;

	i = 0;
	while (envp[i] && ft_strncmp("PATH", envp[i], 4))
		i++;
	if (!envp[i])
		return (NULL);
	return (envp[i] + 5);
}

void	close_fd(t_pipex *pipex)
{
	close(pipex->fd[0]);
	close(pipex->fd[1]);
}

int	main(int argc, char **argv, char **envp)//int pipex_func
{
	t_pipex	pipex;

	if (argc != 5)
		return (1);
	pipex.input = open(argv[1], O_RDONLY);
	if (pipex.input < 0)
		return (1);
	pipex.output = open(argv[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (pipex.output < 0)
		return (1);
	if (pipe(pipex.fd) < 0)
		return (1);
	pipex.paths = get_path(envp);
	pipex.path_arr = ft_split(pipex.paths, ':');
	pipex.pid1 = fork();
	if (pipex.pid1 == 0)
		first_child(pipex, argv, envp);
	pipex.pid2 = fork();
	if (pipex.pid2 == 0)
		second_child(pipex, argv, envp);
	close_fd(&pipex);
	waitpid(pipex.pid1, NULL, 0);
	waitpid(pipex.pid2, NULL, 0);
	parent_free(&pipex);
	return (0);
}
