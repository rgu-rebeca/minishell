/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgu <rgu@student.42madrid.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 20:33:32 by rgu               #+#    #+#             */
/*   Updated: 2025/06/04 20:36:42 by rgu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <sys/wait.h>
# include <fcntl.h>

typedef enum s_token_type
{
	T_WORD,
	T_PIPE,
	T_REDIR_IN,
	T_REDIR_OUT,
	T_REDIR_APPEND,
	T_HERDOC
}	t_token_type;

typedef struct s_cmd
{
	char	**args;
	char	*infile;
	char	*outfile;
	int		append;
}	t_cmd;

typedef struct s_token
{
	char			*value;
	t_token_type	type;
	struct s_token	*next;
}	t_token;
void	setup_signals(void);
void	execute_command(t_cmd *cmd, char **envp);
char	*get_command_path(char *cmd, char **envp);
void	free_args(char **args);
t_cmd	*parse_command(char *line);
int		ft_strcmp(char *str1, char *str2);
int		count_word(t_token *tokens);
void	execute_pipeline(char *line, char **envp);
int		ft_isspace(int a);
char	*expand_env_vars(const char *str);
t_token	*tokenize(char *line);
t_cmd	*parse_tokens(t_token *tokens);
int		ft_isspace(int a);
void	free_tokens(t_token *tokens);
void	execute_command_simple(t_cmd *cmd, char **envp);
int		is_built_in(t_cmd *cmd);
void	exec_built_in(t_cmd *cmd);
void	exec_cd(t_cmd *cmd);
void	free_command(t_cmd *cmd);
void	exec_pwd(void);
void	exec_echo(t_cmd *cmd);
void	exec_exit(t_cmd *cmd);
#endif