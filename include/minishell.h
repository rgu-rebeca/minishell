#ifndef MINISHELL_H
# define MINISHELL_H
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include <sys/wait.h>
#include <fcntl.h>
typedef enum
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
	struct	s_token	*next;
}	t_token;
void	setup_signals(void);
void	execute_command(t_cmd *cmd, char **envp);
char	*get_command_path(char *cmd, char **envp);
void	free_args(char **args);
t_cmd	*parse_command(char *line);
int		ft_strcmp(char *str1, char *str2);
int		ft_strlen_2(char **str);
void	execute_pipeline(char *line, char **envp);
int	ft_isspace(int a);
#endif