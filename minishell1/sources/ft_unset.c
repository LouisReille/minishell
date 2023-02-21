/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lreille <lreille@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 03:43:55 by lreille           #+#    #+#             */
/*   Updated: 2023/02/11 20:51:37 by lreille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**ft_remove_var(char **env, char *str)
{
	char	**env_dup;
	int		i;

	i = 0;
	env_dup = ft_env_dup(env);
	while (env[i])
	{
		if (i >= ft_var_position(env, str))
			env_dup[i] = env[i + 1];
		else
			env_dup[i] = env[i];
		i++;
	}
	return (env_dup);
}

void	ft_unset(char **env, char *str)
{
	char	**new_env;
	int		i;

	i = 0;
	new_env = ft_remove_var(env, str);
	while (new_env[i])
	{
		env[i] = new_env[i];
		i++;
	}
	env[i] = NULL;
}
