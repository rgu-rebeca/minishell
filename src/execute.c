#include "../include/minishell.h"
#include "../libft/libft.h"

void	free_args(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		free(args[i++]);
	free(args);
}

t_cmd	*parse_command(char *line)
{
	t_cmd	*cmd;
	char	**tokens;
	int		i;
	int		j;

	cmd = malloc(sizeof(t_cmd));
	cmd->infile = NULL;
	cmd->outfile = NULL;
	cmd->append = 0;
	tokens = ft_split(line, ' ');
	cmd->args = malloc(sizeof(char *) * (ft_strlen_2(tokens) + 1));
	i = 0;
	j = 0;
	while (tokens[i])
	{
		if (ft_strcmp(tokens[i], ">") == 0 && tokens[i + 1])
		{
			cmd->outfile = ft_strdup(tokens[i + 1]);
			cmd->append = 0;
			i += 2;
		}
		else if (ft_strcmp(tokens[i], ">>") == 0 && tokens[i + 1])
		{
			cmd->outfile = ft_strdup(tokens[i + 1]);
			cmd->append = 1;
			i += 2;
		}
		else if (ft_strcmp(tokens[i], "<") == 0 && tokens[i + 1])
		{
			cmd->infile = ft_strdup(tokens[i + 1]);
			i += 2;
		}
		else
			cmd->args[j++] = ft_strdup(tokens[i++]);
	}
	cmd->args[j] = NULL;
	free_args(tokens);
	return (cmd);
}

void	execute_command(t_cmd *cmd, char **envp)
{
	__pid_t	pid;
	char	*path;
	int		fd;
	int		flag;

	path = get_command_path(cmd->args[0], envp);
	if (!path)
	{
		ft_printf("minishell: %s, command not found\n", cmd->args[0]);
		free_args(cmd->args);
		return ;
	}
	pid = fork();
	if (pid == 0)
	{
		if (cmd->infile)
		{
			fd = open(cmd->infile, O_RDONLY);
			if (fd < 0)
				perror("open error1");
			dup2(fd, STDIN_FILENO);
			close(fd);
		}
		if (cmd->outfile)
		{
			flag = O_WRONLY | O_CREAT;
			if (cmd->append == 1)
				flag |= O_APPEND;
			else
				flag |= O_TRUNC;
			fd = open(cmd->outfile, flag, 0644);
			if (fd < 0)
				perror("open error2");
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		execve(path, cmd->args, envp);
		perror("minishell");
		exit (1);
	}
	else if (pid > 0)
		waitpid(pid, NULL, 0);
	else
		perror("fork");
	free_args(cmd->args);
}

void	execute_pipeline(char *line, char **envp)
{
	char	**cmds;
	int		fd[2];
	int		in_fd;
	__pid_t	pid;
	int		i;
	t_cmd	*cmd;

	cmds = ft_split((const char*)line, '|');
	in_fd = 0;
	i = 0;
	while (cmds[i])
	{
		pipe(fd);
		pid = fork();
		if (pid == 0)
		{
			dup2(in_fd, STDIN_FILENO);
			if (cmds[i + 1])
				dup2(fd[1], STDOUT_FILENO);
			close(fd[0]);
			cmd = parse_command(cmds[i]);
			execve(get_command_path((cmd->args[0]), envp), cmd->args, envp);
			perror("execve error");
			exit (1);
		}
		else
		{
			waitpid(pid, NULL, 0);
			close(fd[1]);
			in_fd = fd[0];
			i++;
		}
	}
	free_args(cmds);
}