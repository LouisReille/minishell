/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   veref_sign.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcacoilo <mcacoilo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 01:13:02 by mcacoilo          #+#    #+#             */
/*   Updated: 2023/02/14 01:37:51 by mcacoilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirection_and_pipe.h"
#include <stdio.h>

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

static t_token  get_redi(char *str, t_token token)
{
    if (ft_strncmp(str, ">", ft_strlen(str)) == 0)
    {
        token.type = REDIR;
        token.value = str;
    }
    else if (ft_strncmp(str, ">>", ft_strlen(str)) == 0)
    {
        token.type = REDIR_APPEND;
        token.value = str;
    }
    else if (ft_strncmp(str, "<", ft_strlen(str)) == 0)
    {
        token.type = INFILE;
        token.value = str;
    }
    else if (ft_strncmp(str, "<<", ft_strlen(str)) == 0)
    {
        token.type = HEREDOC;
        token.value = str;
    }
    return (token);
}

//  ces fonctions ci-dessous ont pr but de verifier que tout cela existe ou pas //
//  je crois que t'avais deja commencé sur ce sujet, c'est pour cela que je te les met en commentaire //
//  A toi de voir si tu veux en mettre dans ton code ou pas //
/* 

static t_token  get_quote(char *str, t_token token)
{
    if (verify_squote(str))
    {
        token.type = SQUOTE;
        token.value = str;
    }
    if (verify_dquote(str))
    {
        token.type = DQUOTE;
        token.value = str;
    }
    return (token);
}

int verify_squote(char *str)
{
    int i;

    i = 0;
    if (str[i] == '\'')
    {
        while (str[i])
            i++;
        if (str[i - 1] == '\'')
            return (1);
    }
    return (0);
}

int verify_dquote(char *str)
{
    int i;

    i = 0;
    if (str[i] == '\\')
    {
        while (str[i])
            i++;
        if (str[i - 1] == '\\')
            return (1);
    }
    return (0);
}

int no_quote(char *set, char c)
{
    int i;

    i = 0;
    while (set[i])
    {
        if (c == set[i])
            return (1);
        i++;
    }
    return (0);
}

static t_token  type_token(char *str)
{
    t_token token;

    token.type = WORD;
    token.value = NULL;
    token = get_redi(str, token);
    token = get_quote(str, token);
    if (ft_strncmp(str, "|", ft_strlen(str)) == 0)
    {
        token.type = PIPE;
        token.value = str;
    }
    else if (ft_strncmp(str, "-", 1) == 0)
    {
        token.type = OPTION;
        token.value = str;
    }
    else if (!(token.value))
    {
        token.type = WORD;
        token.value = str;
    }
    return (token);
}

int verif_error(int *index)
{
    if (index[2] % 2 || index[2] % 2)
    {
        print_error(); // voir pr la faire !
        return (-1);
    }
    return (0);
}
*/