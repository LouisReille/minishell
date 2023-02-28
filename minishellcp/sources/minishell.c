/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lreille <lreille@student.42mulhouse.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 23:36:35 by lreille           #+#    #+#             */
/*   Updated: 2023/02/28 15:54:14 by lreille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


void	ft_store_data(t_data **data, char *line, int status, t_env *envi)
{
	(*data) = ft_malloc(sizeof(t_data));
	if (check_quote_err(line))
	{
		(*data)->status = 258;
		(*data)->cmd_num = -1;
		return ;
	}
	(*data)->heredoc_node = ft_malloc(sizeof(t_infile_node));
	(*data)->node_head = ft_malloc(sizeof(t_cmd_node));
	(*data)->envi = envi;
	(*data)->status = status;
	make_token(line, (*data));
	(*data)->fd_in = dup(0);
	(*data)->fd_out = dup(1);
	(*data)->curr = (*data)->node_head->next;
	set_heredoc(*data);
}

void	ft_set_std(t_data *data)
{
	dup2(data->fd_in, 0);
	dup2(data->fd_out, 1);
}

void	run_and_restore(t_data *data)
{
	if (data->cmd_num != -1)
	{
		run_command(data);
		ft_set_std(data);
		clear_heredoc(data);
	}
}

int	main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	char			*input;
	t_data		*data;
	t_env 		*envi;
	int				status;
	envi = parse_envp(env);
	status = 0;
	//sigaction(SIGINT, SIGCONT);
	//SIGINT == SIGCONT;
	while (1)
	{
		//signal(SIGINT, SIG_DFL);
		rm_ctrl();
		input = readline("\033[32mMyMinishell-> $ \033[0m");
		if (!input)
			exit(127);
		if (input)
		{
			ft_store_data(&data, input, status, envi);
			run_and_restore(data);
			status = data->status;
			add_history(input);
			ft_free_data(data);
		}
		ft_free(input);
	}
	return 0;//(status);
}
