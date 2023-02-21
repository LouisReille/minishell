/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo_utils1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lreille <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 02:22:57 by lreille           #+#    #+#             */
/*   Updated: 2023/02/20 11:30:49 by lreille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


int	ft_var_sep_pos(char **cmd, char *command, char *input)
{
	int	i;
	int	j;
	int	k;
	char	*s;
	char	*str;

	i = ft_strlen(cmd[0]);
	j = 0;
	k = 0;
	str = ft_look(input);
	while (input[i])
	{
		s = ft_size_cut(input, i, ft_strlen(command));
		if (ft_strncmp(s, command, ft_strlen(command) + 1) == 0)
		{
			free(s);
			return (i);
		}
		free(s);
		i++;
	}
	return (0);
}

char	**ft_split_and_clean_vars(char *str)
{
	char	**s;
	char	**s1;
	int	i;

	i = 0;
	s = ft_split(str, '$');
	s1 = malloc(sizeof(char **) * ft_double_strlen(s) + 1);
	while (s[i])
	{
		s1[i] = ft_cleanvar(s[i], 0);
		i++;
	}
	s1[i] = NULL;
	i = 0;
	while (s[i])
		free(s[i++]);
	return (s1);
}

int	ft_count_dol(char *str)
{
	int	i;
	int	cnt;

	i = 0;
	cnt = 0;
	while (str[i])
	{
		if (str[i] == '$')
			cnt++;
		i++;
	}
	return (cnt);
}

void	ft_print_with_dol_void(char *str, char **s, char **env, t_temp *temp)
{
	while (str[temp->i] != '$')
		printf("%c", str[temp->i++]);
	while (str[temp->i])
	{
		if (str[temp->i] == '$' && ft_isalnum(str[temp->i + 1]) == 0 && str[temp->i + 1] != '$')
			printf("$");
		if (str[temp->i] == '$' && str[temp->i + 1] != '$' &&
				str[temp->i + 1] != '?' && str[temp->i + 1] != '\0')
		{
			temp->k = ft_var_position(env, s[temp->j]);
			if (temp->k >= 0)
				printf("%s", get_val(env[temp->k]));
			temp->i = temp->i + ft_strlen(s[temp->j]);
			temp->j++;
		}
		if (str[temp->i] == '$' && str[temp->i++ + 1] == '$')
		{
			printf("[PID]");
		}
		//	printf("%c", str[temp->i + 1]);
		
		temp->i++;
	}
}

void	ft_print_with_dol(char *str, char **env)
{
	char	**s;
	t_temp	temp;
	temp.i = 0;
	temp.k = 0;
	temp.j = ft_var_increment_check(str);
	s = ft_split_and_clean_vars(str);
	ft_print_with_dol_void(str, s, env, &temp);
	ft_free_all(s);
}
