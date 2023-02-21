/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lreille <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 07:02:56 by lreille           #+#    #+#             */
/*   Updated: 2023/02/20 11:07:40 by lreille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <term.h>
# include <stdbool.h>
# include <sys/ioctl.h>
# include <sys/wait.h>

typedef struct s_temp
{
	int	i;
	int	j;
	int	k;
}	t_temp;

//minishell.c

char		*get_path(char **env);
void		sig_handle(int signum);
void		ft_loop(char **env, char **new_env);

// exec_builtins.c

int		exec_builtins(char **command, char **env, char *input);

//exec_binary.c

char		*ft_concat(char *s1, char *s2);
void		env_loop(char **command, char *path, char **env);
int			exec_binary(char **command, char *path, char **env);

//ft_echo_utils1.c

int			ft_var_sep_pos(char **cmd, char *command, char *input);
char		**ft_split_and_clean_vars(char *str);
int			ft_count_dol(char *str);
int			ft_contains_var(char *str);
void		ft_print_with_dol(char *str, char **env);

//ft_echo_utils2.c

int			ft_only_n(char *str);
int			ft_option_n(char **command);
char		*ft_cleanvar(char *str, int i);
char		*ft_size_cut(char *input, int start, int len);
int			ft_var_increment_check(char *str);

//ft_builtins.c

void		ft_cd(char **command);
void		ft_pwd(void);
void		ft_env(char **env);
void		ft_echo(char **command, char **env, char *input);

//ft_check.c

int			ft_open_quotes(char **command);
int			verif_path(char **command, char *path);
char		*clean_command(char **command);
char		*clean_binary_cmd(char *command);

//ft_split.c

int			ft_nbchar(char *str, int i, char c);
int			ft_word_cnt(char *str, char c);
char		**ft_setsplit(char *s, char **str, char c);
char		**ft_split(char *str, char c);


//ft_smartsplit_utils.c

void		ft_lock(char *str, char *sign, int i, int d, int s);
char		ft_sep(int d, int s);
int			ft_nice_squote(char c, int s, int d);
int			ft_nice_dquote(char c, int s, int d);
char		*ft_look(char *str);

//ft_smartplit.c

char		ft_filter(char *s, int i);
int			ft_nchar(char *str, int i, char c);
int			ft_word_count(char *str);
char		**ft_setsmartsplit(char *s, char **str);
char		**ft_smartsplit(char *str);

//ft_export_utils1.c
char		*get_var(char *str);
char		*get_val(char *str);
int			ft_var_position(char **env, char *str);
char		**ft_env_dup(char **env);
char		*ft_add_quotes(char *str);

//ft_export_utils2.c
char		**ft_split_var(char **env, char *str);
char		*ft_form_env_with_val(char *str, char *s);
char		*ft_form_env_without_val(char *str);
char		**ft_overwrite(char **env, char *str, int position);
int			ft_double_strlen(char **str);

//ft_export_utils3.c
char		**env_build_with_val(char **env, char *str);
char		**env_build_no_val(char **env, char *str);
char		**ft_exportenv(char **env, char *str);
int			ft_check_format(char *str);
void		ft_exportprint(char **env);

//ft_export.c
void		ft_free_all(char **str);
void		ft_export(char **env, char *str);
//ft_unset.c

char		**ft_remove_var(char **env, char *str);
void		ft_unset(char **env, char *str);

//ft_utils1.c

int			ft_strcmp(const char *s1, const char *s2);
char		*ft_strchr(const char *s, int c);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
size_t		ft_strlen(const char *str);
char		*ft_strdup(const char *s1);

//ft_utils2.c

int			ft_isdigit(int c);
int			ft_isalpha(int c);
int			ft_isalnum(int c);
int			ft_isprintable(char c);
int			ft_isnotprintable(char c);

//ft_utils3.c

void		*ft_memcpy(void *dst, const void *src, size_t n);
void		*ft_calloc(size_t count, size_t size);
void		ft_bzero(void *s, size_t n);

#endif
