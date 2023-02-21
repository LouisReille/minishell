/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcacoilo <mcacoilo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 01:44:41 by mcacoilo          #+#    #+#             */
/*   Updated: 2023/02/14 01:45:57 by mcacoilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirection_and_pipe.h"

static void free_tokens(t_token **token)
{
    int i;

    i = 0;
    while (token[i])
    {
        free(token[i]);
        i++;
    }
    free(token);
}
