/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lreille <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 02:44:48 by lreille           #+#    #+#             */
/*   Updated: 2023/02/18 02:45:23 by lreille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**ft_split_var(char **env, char *str)
{
	int	i;
	char **s;

	if (ft_var_position(env, str) != -1)
		i = ft_var_position(env, str);
	else
		i = ft_var_position(env, str);
	s = ft_split(env[i], '=');
	return (s);
}

char	*ft_form_env_with_val(char *str, char *s)
{
	char	*dv;
	int	i;
	int	j;

	i = 0;
	j = 0;
	dv = malloc(sizeof(char *) * 2555);
	while (str[i])
		dv[j++] = str[i++];
	i = 0;
	dv[j++] = '=';
	while (s[i])
		dv[j++] = s[i++];
	dv[j] = '\0';
	return (dv);
}

char	*ft_form_env_without_val(char *str)
{
	char	*dv;
	int	i;
	int	j;

	i = 0;
	j = 0;
	dv = malloc(sizeof(char *) * strlen(str) + 3);
	while (str[i])
		dv[j++] = str[i++];
	dv[j++] = '=';
	dv[j++] = '\0';
	return (dv);
}

char	**ft_overwrite(char **env, char *str, int position)
{
	char	**n_env;
	int	i;
	int	j;

	i = 0;
	j = 0;
	n_env = malloc(sizeof(char **) * strlen(*env));
	while (env[i])
	{
		if (i == position)
			n_env[j] = strdup(str);
		else
			n_env[j] = strdup(env[i]);
		i++;
		j++;
	}
	if (ft_var_position(env, get_var(str)) == -1)
		n_env[j] = strdup(str);
	else
		n_env[j] = NULL;
	return (n_env);
}


int	ft_double_strlen(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

