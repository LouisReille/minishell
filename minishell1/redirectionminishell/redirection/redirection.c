/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcacoilo <mcacoilo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 01:38:01 by mcacoilo          #+#    #+#             */
/*   Updated: 2023/02/14 02:08:53 by mcacoilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirection_and_pipe.h"

// va falloir surement mettre ces structures dans un autre .h et le rajouter dans ton minishell.h //

enum	e_type
{
	WORD,
	OPTION,
	REDIR,
	REDIR_APPEND,
	INFILE,
	HEREDOC,
	PIPE,
	SQUOTE,
	DQUOTE
};

typedef struct s_token
{
	enum e_type	type;
	char		*value;
}	t_token;

int is_redirection(t_token token)
{
    if (token.type == REDIR || token.type == REDIR_APPEND || token.type == INFILE
        || token.type == HEREDOC)
        return (1);
    if (token.type == PIPE)
        return (2);
    else
        return (0);
}

static int  count_redirection(t_token *token)
{
    int i;
    int nb;

    i = 0;
    nb = 0;
    while (token[i].value)
    {
        if (is_redirection(token[i]))
            nb++;
        i++;
    }
    return (nb);
}

void    redir_to_file(int redir, t_token **token, int i)
{
    int fd;

    if (redir == REDIR)
    {
        fd = open(token[i + 1]->value, O_CREAT | O_RDWR | O_TRUNC, 0644);
        if (fd < 0)
            return ;
    }
    if (redir == REDIR_APPEND)
    {
        fd = open(token[i + 1]->value, O_CREAT | O_RDWR | O_APPEND, 0644);
        if (fd < 0)
            return ;
    }
    dup2(fd, 1);
    close(fd);
}

void    redir_in_file(t_token **token, int i)
{
    int fd;

    fd = open(token[i + 1]->value, O_RDONLY);
    if (fd < 0)
    dup2(fd, 0);
    close(fd);
}

void    redir_heredoc(t_token **token, int i)
{
    char    *line;
    int     fd;

    fd = open("/tmp/.heredoc", O_RDWR | O_CREAT | O_TRUNC, 0644);
    if (fd < 0)
        return ;
    while (42)
    {
        line = readline("> ");
        if (ft_strncmp(line, token[i + 1][0].value, ft_strlen(token[i + 1][0].value) + ft_strlen(line)) == 0)
            break ;
        ft_putstr_fd(line, fd);
        ft_putstr_fd("\n", fd);
    }  
    close(fd);
    fd = open("/tmp/heredoc", O_RDONLY);
    if (fd < 0)
        return ;
    dup2(fd, 0);
    close(fd);
}

int redirection(t_token **token)
{
    int i;

    i = 0;
    while (token[i] != NULL && token[i]->type != PIPE)
    {
        if (token[i]->type == REDIR)
            redir_to_file(REDIR, token, i);
        if (token[i]->type == REDIR_APPEND)
            redir_to_file(REDIR_APPEND, token, i);
        if (token[i]->type == INFILE)
            redir_in_file(token, i);
        if (token[i]->type == HEREDOC)
            redir_heredoc(token, i);
        i++;
    }
    return (0);
}
