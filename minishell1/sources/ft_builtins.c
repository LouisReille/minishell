/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lreille <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 06:47:30 by lreille           #+#    #+#             */
/*   Updated: 2023/02/19 06:59:36 by lreille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_cd(char **command)
{
	char	*home;

	home = getenv("HOME");
	if (command[1] == NULL)
		chdir(home);
	else if (chdir(command[1]) == -1)
		printf("cd : no such file or directory\n");
}

void	ft_pwd(void)
{
	printf("%s\n", getcwd(0, 32000));
}

void	ft_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{	printf("%s\n", env[i]);
		i++;
	}
	env[i] = NULL;
}

int		ft_arg_pos_in_input(char **cmd, char *str)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (cmd[i])
	{
		if (ft_strcmp(cmd[i], str) == 0)
			return (j);
		j = j + ft_strlen(cmd[i]) + 1;
		i++;
	}
	return (j);
}

int		ft_check_quote_cond(char **cmd, char *str, char *input)
{
	char	*s;
	int		i;
	int		j;

	i = 0;
	j = ft_arg_pos_in_input(cmd, str);
	s = ft_look(input);
	if (s[j + 1] == '\'')
		return (0);
	free(s);
	return (1);
}

int		ft_dblq_with_var(char **cmd, char *str, char *input)
{
	if (ft_contains_var(str) == 1 && ft_check_quote_cond(cmd, str, input) == 1)
		return(1);
	return (0);
}

void	ft_echo(char **command, char **env, char *input)
{
	int	i;
	int	j;

	i = ft_option_n(command);
	j = 0;
//	if (ft_open_quotes(command) == 1)
//		printf("prout\n");

	while (command[i])
	{
		j = ft_var_sep_pos(command, command[i], input);
		if (ft_dblq_with_var(command, command[i], input) == 1)
			ft_print_with_dol(command[i], env);
		else if (ft_dblq_with_var(command, command[i], input) == 0)
			printf("%s", command[i]);
		if (input[j + ft_strlen(command[i]) + 1] == ' ' || 
				input[j + ft_strlen(command[i])] == ' ')
			printf(" ");
		i++;
	}
	if (ft_option_n(command) < 2)
		printf("\n");
}
