/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darakely <darakely@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 10:24:15 by darakely          #+#    #+#             */
/*   Updated: 2022/12/13 22:30:27 by darakely         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "readline/readline.h"
# include "readline/history.h"
# include <sys/ioctl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <termios.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <dirent.h>
# include <signal.h>
# include <limits.h>
# include <stdio.h>
# include <fcntl.h>
# include <errno.h>

# define CYAN       "\33[3;32m"
# define RESET		"\33[0;m"
# define PINK 		"\33[1;35m"
# define WHITE		"\033[1;33m"
# define RED       	"\33[1;31m"

typedef enum redirect
{
	_default = 0,
	_outfile = 1,
	_heredoc = 2,
	_append = 3,
	_infile = 4
}			t_flag_redir;

typedef struct s_env
{
	int				status;
	char			*value;
	struct s_env	*next;
	char			*key;
}				t_env;

typedef struct s_export
{
	int				status;
	char			*value;
	struct s_export	*next;
	char			*key;
}				t_export;

typedef struct s_redirection
{
	int		*count_outfiles_in_pipe;
	int		*count_infiles_in_pipe;
	int		*heredoc_count_in_pipe;
	int		*count_append_in_pipe;
	char	**heredoc_name;
	int		index_outfile;
	int		index_infile;
	int		index_append;
	int		*fd_outfiles;
	int		*fd_infiles;
	int		*fd_heredoc;
	int		*fd_append;
	char	**outfiles;
	char	**heredoc;
	char	**infiles;
	char	**append;
}				t_redirection;

typedef struct s_pipe
{
	char	**split_space;
	char	**split_pipe;
	int		count_pipe;
	char	**cmd_args;
	int		(*fd)[2];
	int		cnt_cmd;
	char	**path;
	int		output;
	int		input;
	char	*cmd;
	pid_t	*pid;
}				t_pipe;

typedef struct s_parsing
{
	int		*flag_for_prelast_redirect;
	char	**split_new_promt_execve;
	int		*flag_for_last_redirect;
	int		*fixed_prelast_redirect;
	char	**split_new_promt;
	char	**hidden_files;
	char	**split_pipes;
	char	**split_space;
	int		check_outfile;
	int		index_outfile;
	int		index_heredoc;
	int		check_append;
	int		check_infile;
	int		index_infile;
	int		index_append;
}				t_parsing;

typedef struct s_data
{
	t_redirection	*info_redirect;
	t_parsing		*info_parsing;
	t_export		*info_export;
	t_pipe			*info_pipe;
	t_env			*info_env;
	size_t			count_dollar;
	int				last_heredoc;
	char			*for_history;
	int				*error_code;
	int				for_current;
	size_t			len_dollar;
	int				count_pipe;
	int				heredoc;
	char			*promt;
	int				flag;
	int				gr;
	int				x;
	int				i;
	int				j;
	int				a;
	int				k;
}				t_data;

//parsing_utils_9
int					norm_check_syntax_error_and_heredoc(t_data *data, \
					char *str, int i);
int					check_syntax_error_and_heredoc_2(t_data *data, \
					char *str, int i, int a);
int					check_syntax_error_and_heredoc_3(t_data *data, \
					int *flag, int check);
int					norm_clear_promt_for_exec(char *new_promt, \
					char *str, int *i, int *j);

//parsing_utils_8
void				norm_parsing(t_data *data);
void				continue_parsing(t_data *data, int k, char *new_promt, \
					char **split_for_malloc);
int					norm_fixed_prelast_redirect(char *str, int len);
int					fixed_prelast_redirect(char *str);
int					continue_norm_fixed_prelast_redirect(char *str, \
					int *len, int *j, t_flag_redir flag);

//parsing_utils_6
int					check_open_heredoc(t_data *data, int *flag, \
					int *check, int last_heredoc);
void				create_file_for_heredoc(t_data *data);
int					check_last_redirect(char *str, int i, t_flag_redir flag);
int					check_prelast_redirect(char *str, int i);
void				norm_check_open_heredoc(t_data *data, int *flag);

//parsing_utils_5
void				continue_norm_ft_execve(t_data *data, char *new_promt);
void				norm_norm_ft_execve_2(t_data *data);
void				norm_norm_ft_execve_3(t_data *data);
void				continue_norm_ft_execve_2(t_data *data, int flag);
int					continue_norm_ft_execve_3(t_data *data, char **correct_env);

//parsing_utils_4
void				norm_close_all_fds(t_data *data);
void				kill_all_proccess(t_data *data, int i);
void				continue_norm_check_cmd(t_data *data, \
					char *absolute_path_cmd);
void				ft_dup2(t_data *data, int i);
int					check_backslash(char *str);
void				ft_dup2(t_data *data, int i);

//get_execve_2
void				norm_check_cmd_2(t_data *data, \
					char **path, char *absolute_path_cmd);
void				norm_get_execve(t_data *data, char **env, \
					char *new_promt);
void				get_dup2_redirect(t_data *data, int i);

//minishell_2
void				get_exit(t_data *data);
int					a(void);
t_data				init_lists(int argc, char **argv, char **env, t_data *data);
void				change_shlvl(t_data *data);
void				norm_change_shlvl(t_data *data);
int					check_syntax_error(char *str);

//minishell_3
void				norm_change_shlvl_in_export(t_data *data, char *new_shlvl, \
					char *str);
void				change_shlvl_in_export(t_data *data, char *check, \
					char *str, char *new_shlvl);

//parsing_utils
void				continue_free(t_data *data);
void				free_all_redirect_name(t_data *data);
void				close_all_fds(t_data *data);

//get_value_env
void				get_value_env(t_data *data, char **promt);

//utils_get_value_env
char				*change_dollar(t_data *data, char *delim, \
					int len, char *ptr);

//signal
void				get_and_set_attr(int flag);
void				ft_ctrl_slash(int sig_num);
void				ft_ctrl_c(int sig_num);
int					ft_signal(void);

//get_execve
void				close_pipes(t_pipe *pipe);
int					ft_execve(t_data *data, char *new_promt);
char				*find_path(char **env);
char				*check_cmd(t_data *data, char **path, \
					char *absolute_path_cmd, int flag);
int					get_execve(t_data *data, char *new_promt, \
					char **env, int i);

//utils_get_execve
void				norm_check_cmd(t_data *data, char *absolute_path_cmd);
void				ft_dup2(t_data *data, int i);
void				kill_all_proccess(t_data *data, int i);
int					norm_ft_execve(t_data *data, char **correct_env, \
					char *new_promt, int flag);

//parsing
void				parsing(t_data *data);
char				*clear_promt_for_exec(char *new_promt);
void				split_pipes(t_data *data, char *str, int j, int flag);
void				create_file_for_heredoc(t_data *data);
char				*clear_promt_builtins(char **str);

//heredoc
void				add_heredoc_name_struct(t_data *data, char *str, \
					char **tmp, int flag);
void				add_heredoc(t_data *data, char *str, int j, char *ptr);
void				open_heredocs(t_data *data, int count_heredoc, \
					int i, int j);
int					check_heredoc(t_data *data, char *str);
void				ft_heredoc(t_data *data, int i, char **pipe, int j);
int					count_all_redirect(t_data *data);

//utils_heredoc
int					check_count_heredoc(t_data *data, int count_heredoc);
void				norm_correct_heredoc_name(char *ptr, char *str, \
					int *i, int *j);
char				*correct_heredoc_name(char *str, int i, int j);
int					close_heredocs(t_data *data, char *heredoc, int i);

//utils_heredoc_2
void				open_current_heredocs(t_data *data, int i);
void				open_heredoc(t_data *data, int i, int fd, char *heredoc);
void				count_heredoc_in_pipe(t_data *data, char **pipe, \
					int k, int j);
void				save_fd(t_data *data, int pos, char *pipe);
int					check_fd_heredoc(t_data *data);
void				continue_add_heredoc_name_struct(t_data *data, int flag, \
					char *str, char **tmp);
int					ft_isalnum(int c);

//env_variables
char				*get_value(t_data *data, char *check, \
					char *clear_check, int i);

//outfiles
int					check_last_outfile(t_data *data, char **pipe, int flag);
void				check_outfile(t_data *data, char *str);
void				add_outfile_name_in_struct(t_data *data, char *str, \
					char **tmp, char *check);
void				get_outfile_name(t_data *data, char *str, int i, char *ptr);
void				ft_outfiles(t_data *data, int i, int j, char **pipe);

//utils_outfiles
int					check_count_last_outfiles(int pos, char *pipe);
void				save_fd_outfiles(t_data *data, int pos, char *pipe);
int					open_all_outfiles(t_data *data, int count_pipe, \
					int x, int check);
void				count_outfile_in_pipe(t_data *data, char **pipe, \
					int k, int count);
int					norm_open_all_outfiles(t_data *data);

//infiles
int					check_last_infile(t_data *data, char **pipe, int flag);
void				check_infile(t_data *data, char *str);
void				add_infile_name_in_struct(t_data *data, char *str, \
					char **tmp, char *check);
void				get_infile_name(t_data *data, char *str, char *ptr);
void				ft_infiles(t_data *data, int i, char **pipe, int j);
int					open_all_infiles(t_data *data, int count_pipe, \
					int x, int j);

//append
int					check_last_append(t_data *data, char **pipe, int flag);
void				check_append(t_data *data, char *str);
void				add_append_name_in_struct(t_data *data, char *str, \
					char **tmp, char *check);
void				get_append_name(t_data *data, char *str, char *ptr, int i);
void				ft_append(t_data *data, int i, int j, char **pipe);

//utils_append
int					check_count_last_append(int pos, char *pipe);
void				save_fd_append(t_data *data, int pos, char *pipe);
int					open_all_append(t_data *data, int count_pipe, \
					int x, int check);
void				count_append_in_pipe(t_data *data, char **pipe, \
					int k, int j);
int					continue_open_all_append(t_data *data, int x);
int					print_append_error(t_data *data, char *error);

//utils_infiles
int					check_count_last_infiles(int pos, char *pipe);
void				save_fd_infiles(t_data *data, int pos, char *pipe);
void				get_fd_infiles(t_data *data, char **pipe);
void				check_infile(t_data *data, char *str);
void				count_infile_in_pipe(t_data *data, char **pipe, \
					int k, int count);
int					print_infile_error(t_data *data, char *error);
void				norm_open_all_infiles(t_data *data, int *check);

//utils_infiles_2
int					norm_open_all_infiles_2(t_data *data, int x, int **check);
int					continue_open_all_infiles(t_data *data, int *check, \
					int *x, int *count_pipe);
void				norm_ft_heredoc(t_data *data, char **pipe, \
					int j, int count);

//utils
char				*ft_strdup(const char *s1);
long long int		ft_atoi(const char *str);
int					ft_strlen(const char *str);
char				*ft_strjoin(char *s1, char *s2);
int					ft_strncmp(char *s1, char *s2, size_t n);
void				norm_ft_infiles(t_data *data, char **pipe, int j);
void				norm_ft_outfiles(t_data *data, char **pipe, int j);

//ft_strchr
char				*ft_strchr(char *str, char c);

//ft_putstr_fd
void				ft_putstr_fd(char *str, int fd);

//free
void				free_struct_pipe(t_data *data);
void				free_struct_redirection(t_data *data);
void				free_list_export(t_export **export);
void				free_list_env(t_env **env);
void				free_array(char ***str);

//free_all
void				free_struct_parsing(t_data *data);
void				free_all(t_data *data, int flag);

//init_structures
void				init_structure(t_data *data);
void				init_structure_pipe(t_data *data);
void				init_structure_parsing(t_data *data);
void				init_structure_redirection(t_data *data);

//print_header
void				print_header(void);

//ft_itoa
int					ft_isprint(int c);
size_t				ft_num_len(int num);
char				*ft_itoa(int n);

//print_syntax_error
void				print_syntax_error(t_data *data, char *error);

//ft_split
char				**ft_split(char const *s, char c);
char				*ft_substr(char const *s, unsigned int start, size_t len);

//utils_env_4
void				continue_add_variable_env(char ***new_split, char *str, \
					char *check);
int					continue_check_plus_env(t_env *info, char *check, \
					char **new_split, t_env *tmp);

//init_env
void				init_env(t_data *data, char **env, int i, char **split);
void				ft_env(t_data *data);
void				add_variable_env(t_data *data, char *split, \
					char **new_split, char *str);
int					check_variable_env(t_data *data, char **new_split, int i);
void				norm_add_variable_env(t_env *info, char **new_split);

//utils_env
void				norm_init_env(t_data *data, char *split);
int					count_equal(char *str);
int					check_add_env(char *str);
void				print_or_not(t_data *data, char *str);
int					norm_add_env(char **new_split, t_data *data);

//utils_env_2
int					check_plus_env(t_data *data, char **new_split, \
					char *check, char **check_plus);
void				change_value_env(t_data *data, char *split);
int					if_plus(char *str);
void				add_plus_env(t_data *data, char **new_split, \
					char **check_plus);
char				*clear_value_env(char *str, int i, int j);

//utils_env_3
int					len_list_env(t_data *data);
char				**get_correct_env(t_data *data);
void				norm_clear_value_env(char *ptr, char *str, int *i, int *j);
void				ft_swap(int *a, int *b);

//cd
void				change_oldpwd_env(t_data *data);
void				change_pwd_env(t_data *data, char *str);
char				*find_home_env(t_data *data);
char				*find_pwd_env(t_data *data);
void				ft_cd(t_data *data, char *str);

//utils_exit
void				continue_check_exit_code_2(t_data *data, char **check);
void				continue_ft_exit(t_data *data, char **check, int *for_exit);
int					continue_continue_check_exit_code(char **check, int i);
int					print_too_many_arguments(t_data *data, char **print_exit);
void				continue_check_long_num(t_data *data, char *str, int j);

//utils_cd
void				check_oldpwd_env(t_data *data);
void				change_pwd_export(t_data *data, char *str, char *check);
void				change_oldpwd_export(t_data *data, char *pwd);
char				*find_home_export(t_data *data);
char				*find_pwd_export(t_data *data);

//utils_cd_2
void				norm_ft_cd(t_data *data, char *str);
void				check_and_get_folder(t_data *data, char *check);
void				add_oldpwd_in_env(t_data *data, char *pwd);
void				continue_change_pwd_export(t_export *info, char *check);

//unset
void				norm_unset_env(t_env *info);
void				norm_unset_export(t_export *info);
void				ft_unset(t_data *data, char **check_unset, \
					char **str, int j);
void				unset_env(t_data *data, int j, char **str, char **check);
int					check_arg(t_data *data, char **str);

//utils_unset_2
void				norm_unset(t_data *data, int j, char *check, \
					char *check_unset);
int					norm_check_arg(t_data *data, char **check_unset, \
					int i, int j);
void				norm_ft_unset(t_data *data, int j, char *check, \
					char *check_unset);

//echo
void				ft_echo(t_data *data, char **str);
char				*clear_echo(char *str, int i, int j);
void				print_echo(char **str, int i);
void				print_flag_echo(char **print, char **check, int i);
int					check_flag(char *str, int i);

//pwd
void				ft_pwd(t_data *data);

//exit
void				print_error_exit(t_data *data, char *str);
int					check_exit_code(char **check, t_data *data, char **str);
int					continue_check_exit_code(char **check, t_data \
					*data, char **str);
int					check_long_num(t_data *data, char *str, \
					int j, char **check_arg);
void				ft_exit(t_data *data, char **str);

//init_export
void				init_export(t_data *data, char **env, int i, char **split);
void				ft_export(t_data *data, char **str);
void				add_variable_export(t_data *data, char *split, \
					char *str, char *check);

//utils_export
int					check_equal(char *str);
void				sort_export(t_data *data, int i);
void				norm_init_export(t_data *data, char *split);
char				*check_back_slash(char *str, char *new_malloc);
char				*my_strdup(char *str);

//utils_export_2
int					my_strlen(char *str);
void				norm_if(char *str, char *new_malloc, int i, int j);
int					norm_else(char *str, char *new_malloc, int i, int j);
char				*find_equal(char *str);
void				norm_add_variable_export(t_export *info, char **new_malloc);

//utils_export_3
char				*clear_str(char *str);
int					check_count_single_quote(char *str);
int					check_add_export(char *str, char *error, int i, int j);
int					check_change_variable(t_export *data, char **new_split);
int					check_variable(t_export *data, char **new_split, \
					int i, char **check_split);

//utils_export_4
int					norm_check_change_variable(t_export *data, char *str, \
					char **new_split);
int					norm_add_variable(t_data *data, char **new_split);
int					check_plus(t_data *data, char **new_split, \
					int i, char *check);
int					find_plus(char *str);
void				add_plus_variable(t_data *data, char **new_split);

//utils_export_5
void				norm_check_plus(t_export *data, char *str);
int					if_backslash(char *str);
char				*clear_double_quote(char *str);
int					norm_check_add_export(char *str, int i);
int					check_size_str(char *s1, char *s2);

//utils_export_6
void				continue_add_variable_export(t_data *data, char *split, \
					char **new_split);
void				norm_free(char **str, char **check_split);
int					print_error(char *error);
int					continue_check_variable(t_export *data, \
					char **check_split, char **str);
int					continue_check_plus(t_data *data, char **new_split);
void				my_free(char **check);

//utils_export_7
void				continue_add_variable_export_2(t_data *data, \
					char *str, char **new_split, char *split);

#endif
