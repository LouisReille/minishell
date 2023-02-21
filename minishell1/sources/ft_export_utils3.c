/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lreille <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 02:45:27 by lreille           #+#    #+#             */
/*   Updated: 2023/02/18 02:47:38 by lreille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**env_build_with_val(char **env, char *str)
{
	char	**new_env;
	char	**s;
	char	*var;
	char	*val;
	char	*form;

	s = ft_split(str, '=');
	var = strdup(s[0]);
	val = strdup(s[1]);
	form = ft_form_env_with_val(var, val);
	new_env = ft_overwrite(env, form, ft_var_position(env, var));
	free(s);
	free(var);
	free(val);
	free(form);
	return (new_env);
}

char	**env_build_no_val(char **env, char *str)
{
	char	**new_env;
	char	**s;
	char	*var;
	char	*form;

	s = ft_split(str, '=');
	var = strdup(s[0]);
	form = ft_form_env_without_val(var);
	new_env = ft_overwrite(env, form, ft_var_position(env, var));
	free(s);
	free(var);
	free(form);
	return (new_env);
}


char	**ft_exportenv(char **env, char *str)
{
	char	**split;
	char	**s;

	split = ft_split(str, '=');
	if (split[1] == NULL)
		s = env_build_no_val(env, str);
	else
		s = env_build_with_val(env, str);
	env = ft_env_dup(s);
	return (env);
}

int	ft_check_format(char *str)
{
	if ((ft_isalpha(str[0]) == 1) || str[0] == '_')
		return (1);
	else
		return (0);
}

void	ft_exportprint(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		printf("declare -x ");
		printf("%s=", get_var(env[i]));
		printf("%s\n", ft_add_quotes(get_val(env[i])));
		i++;
	}
}
