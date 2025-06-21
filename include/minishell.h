/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rauizqui <rauizqui@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 20:33:32 by rgu               #+#    #+#             */
/*   Updated: 2025/06/21 06:57:40 by rauizqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/ioctl.h>
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>

typedef enum s_token_type
{
	T_WORD,
	T_PIPE,
	T_REDIR_IN,
	T_REDIR_OUT,
	T_REDIR_APPEND,
	T_HERDOC
}					t_token_type;

typedef struct s_cmd
{
	char			**args;
	char			*infile;
	char			*outfile;
	int				append;
	bool args_owner;
		// Indicates if args should be freed when the command is freed
}					t_cmd;

typedef struct s_token
{
	char			*value;
	t_token_type	type;
	struct s_token	*next;
}					t_token;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}					t_env;

void				setup_signals(void);
void				execute_command(t_cmd *cmd, char **envp);
char				*get_command_path(char *cmd, char **envp);
void				free_args(char **args);
t_cmd				*parse_command(char *line);
int					ft_strcmp(const char *str1, const char *str2);
int					count_word(t_token *tokens);
void				execute_pipeline(t_token *tokens, char **envp);
int					ft_isspace(int a);
char				*get_env_value(t_env *env_list, const char *var);
t_token				*tokenize(char *line, t_env *env_list);
t_cmd				*parse_tokens(t_token *tokens);
int					ft_isspace(int a);
void				free_tokens(t_token *tokens);
void				execute_command_simple(t_cmd *cmd, char **envp);
int					is_built_in(t_cmd *cmd);
int					exec_built_in(t_cmd *cmd, t_env **env_list);
void				exec_cd(t_cmd *cmd);
void				free_command(t_cmd *cmd);
void				exec_pwd(void);
void				exec_echo(t_cmd *cmd);
void				exec_exit(t_cmd *cmd);
char				*expand_env_vars(const char *str, t_env *env_list);
void				print_sorted_env(t_env *env);
t_env				*init_env(char **envp);
t_env				*new_env_node(char *key, char *value);
void				split_key_value(const char *arg, char **key, char **value);

void				free_env_list(t_env *env);
int					export_var(t_env **env_list, char *key, char *value);
int					unset_var(t_env **env_list, char *key);
void				print_env(t_env *env_list);
t_env				*find_env_node(t_env *env_list, const char *key);
void				add_env_node(t_env **env_list, char *key, char *value);
void				print_unset_error(char *arg);
void				print_export_error(const char *arg);

#endif