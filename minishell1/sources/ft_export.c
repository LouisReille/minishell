/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lreille <lreille@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 19:01:34 by lreille           #+#    #+#             */
/*   Updated: 2023/02/18 02:52:38 by lreille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_free_all(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
}

void	ft_export(char **env, char *str)
{

	char	**new_env;
	int		i;
	
	i = 0;
	if (ft_check_format(str) == 0)
		printf("mini: export: %s: not a valid identifier\n", str++);
	else
	{
		new_env = ft_exportenv(env, str);
		while (new_env[i])
		{
			env[i] = new_env[i];
			i++;
		}
	}
}
