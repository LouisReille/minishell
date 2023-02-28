/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lreille <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 07:02:56 by lreille           #+#    #+#             */
/*   Updated: 2023/02/28 16:49:22 by lreille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>
# include <fcntl.h>
# include <termios.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef enum e_type
{
	WORD,
	RED_I,
	RED_O,
	RED_A,
	RED_H,
	PIPE,
	T_NULL
}	t_type;

typedef enum s_error
{
	FILE_ERROR,
	CMD_ERROR,
	EXP_ERROR,
	UNSET_ERROR,
	NOT_SET_ERROR,
	NUM_ARG,
	MANY_ARG,
	EXEC_ERROR,
	PERM_ERROR,
}	t_error;

typedef struct s_env//s_envp_node
{
	char				*var;
	char				*val;
	int					idx;
	struct s_env/*s_envp_node*/	*next;
}	t_env;//t_envp_node;

typedef struct s_parsing_node
{
	char					*str;
	t_type					type;
	struct s_parsing_node	*next;
}	t_parsing_node;

/* hnext->heredoc, next-> infile
is_heredoc: 0(false), 1(true)*/
typedef struct s_infile_node
{
	int						is_heredoc;
	char					*file;
	char					*limiter;
	struct s_infile_node	*hnext;
	struct s_infile_node	*next;
}	t_infile_node;

/* type: 0, type: 1 APPEND */
typedef struct s_outfile_node
{
	char					*file;
	int					type;
	struct s_outfile_node	*next;
}	t_outfile_node;

typedef struct s_cmd_node
{
	int					idx;
	char				**cmd;
	t_infile_node		*infile_node;
	t_outfile_node		*outfile_node;
	struct s_cmd_node	*next;
}	t_cmd_node;

typedef struct s_data
{
	t_env/*t_envp_node*/		*envi;//*ev_lst;
	char			**ev;
	int				fd_in;
	int				fd_out;
	int				cmd_num;
	int				status;
	t_parsing_node	*parse;
	t_infile_node	*heredoc_node;
	t_cmd_node		*node_head;
	t_cmd_node		*curr;
}	t_data;

void	ft_sig_handle1();
void	ft_sig_handle2();
void	init_cmd_node(t_cmd_node *node);
char	*get_cd_path(t_data *data, char *key);
void	exec_chdir(t_data *data, char *path, char *old_path);
int	remove_env(t_data *data, char *key);
/* parse_cmd */
t_cmd_node	*new_cmd_node(t_parsing_node **parse, int i, t_data *data);
void		make_cmd_list(t_parsing_node *parse, t_data *data);
char		**set_cmd(t_parsing_node *parsing, t_data *data);
int			get_cmd_num(t_parsing_node *parsing, t_data *data);
void		init_cmd_node(t_cmd_node *node);

/* parse_envp */
t_env	*parse_envp(char **ev);
t_env	*new_envp_node(char *envp);
char		*ft_substr(char *s, int start, int len);
char		*get_value_by_key(t_env *envi, char *key, int len);

/* parse_red */
void		set_red(t_parsing_node *parse, t_cmd_node *node, t_data *data);
void		set_red_lst(t_parsing_node *parsing, t_cmd_node *node, \
t_data *data);
void		append_infile_node(t_infile_node *lst, void *red_node);
void		append_heredoc_node(t_infile_node *lst, void *red_node);
void		append_outfile_node(t_outfile_node *lst, void *red_node);
void		set_infile_node(t_parsing_node *parsing, void *node);
void		set_outfile_node(t_parsing_node *parsing, void *node);
void		*ft_malloc(int size);

/* parsing_utils */
void		make_sep(char *s, int *index, int *len);
int			is_sep(char *str, int index);
int			is_quote(char *s, int index);
int			get_type(char *str);

/* tokenize */
int			make_token(char *line, t_data *data);
char		*ft_worddup(char *str, int index, int len);
void		ft_parse(char *s, t_parsing_node **parse);
int			add_parsing_node(t_parsing_node **now, char *str);

/* interpret */
void		ft_interpret(t_parsing_node *parse, t_env *envi, \
int status);
char		*interpret(char *str, t_env *envi, int status);
char		*ft_strcat(char *str, char *value);
int			get_len_ev(char *str, t_env *envi, int status);

/* interpret_utils */
int			check_dollar(char *str);
int			key_to_value(char *str, t_env *envi,
				char **value, int status);
void		rm_quote(t_parsing_node *node);

/* red_utils */
void		append_infile_node(t_infile_node *lst, void *red_node);
void		append_heredoc_node(t_infile_node *lst, void *red_node);
void		append_outfile_node(t_outfile_node *lst, void *red_node);
void		*ft_calloc(size_t count, size_t size);
void		ft_bzero(void *s, size_t n);

/* exec */
void		restore_std(t_data *data);
int			no_cmd(t_data *data, int flag);
int			run_command(t_data *data);
int			make_pipe(t_data *data, int prev_fd);
void		make_exec(t_data *data, int flag);
int			exec_last(t_data *data, int prev_fd);

/*redirect*/
int			read_line(char *limiter, int infile);
char		*make_heredoc(char *limiter, int idx);
int			input_redirect(t_data *data);
int			output_redirect(t_data *data);
void		clear_heredoc(t_data *data);
void		set_heredoc(t_data *data);

/*non builtin*/
void		exec_non_builtin(t_data *data);
char		**search_origin_path(t_env *envp);
char		*get_path(char *first_cmd, char **splited_path);

/* builtin */
int		check_builtin(char *str);
void		exec_builtin(t_data *data);
void		ft_echo(t_data *data);
void		ft_cd(t_data *data);
void		ft_pwd(t_data *data);
void		ft_export(t_data *data);
void		ft_unset(t_data *data);
void		ft_env(t_data *data);
void		ft_exit(t_data *data);

/*builtin utils*/
int			ft_exit_atoi(char *str, int *is_not_num, int i);
void		add_env(t_data *data, char *key, char *value);
int			is_invalid_key(char *s, int flag);
char		*get_env_path(t_env *envp, char *key);
char		**make_key_value(char *cmd);
int			ft_search_char(char *s, char c);
t_env		*new_envp_node(char *envp);
void		swap_envp_node(t_env *curr, t_env *next);
void		restore_envp_order(t_data *data);
void		envp_ascending_order(t_data *data);
void		show_export(t_data *data);

/* utils */
void		ft_free_str(char **s1, char **s2);
size_t		ft_double_strlen(char **str);
char		*ft_strjoin3(char *s1, char *s2, char *s3);

/* error */
int			ft_errcm(t_data *data, char *s1, char *s2, int status);
void		ft_werr(char *cmd, char *arg, char *comment, t_error error);
int			ft_error(t_data *data, char *arg, t_error error, int status);

/* libft */
int			ft_atoi(const char *str);
char		*ft_strchr(const char *s, int c);
char		*ft_strjoin(char const *s1, char const *s2);
int			ft_strlen(char *str);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
int			ft_strcmp(char *s1, char *s2);
char		**ft_split(char *s, char c);
int			ft_isdigit(int c);
int			ft_isalpha(int c);
char		*ft_strdup(const char *s1);
char		*ft_substr(char *s, int start, int len);
char		*ft_itoa(int n);
void		*ft_calloc(size_t count, size_t size);
void		ft_putstr_fd(char *s, int fd);

/* envp */
char		*ft_strchr(const char *s, int c);
t_env	*parse_envp(char **ev);

/* free */
void		ft_output_clear(t_outfile_node **lst);
void		ft_input_clear(t_infile_node **lst);
void		ft_node_clear(t_cmd_node **lst);
void		ft_envp_clear(t_env **lst);
void		ft_free_data(t_data *data);

void		cmd_node_clear(t_cmd_node	*nodes);
void		infile_node_clear(t_infile_node	*nodes);
void		outfile_node_clear(t_outfile_node	*nodes);
void		free_double_char(char **cmd);
void		free_one_node(t_cmd_node *node);
void		*ft_free(void *ptr);
void		parse_node_clear(t_parsing_node	*nodes);

/* syntax_err */
int			print_syntax_err(const char *str);
int			check_pipe_err(t_parsing_node *parse, t_parsing_node *now);
int			check_red_err(t_parsing_node *now);
int			check_quote_err(char *line);

/* signal */
void		action(int signum);
void		rm_ctrl(void);

#endif
