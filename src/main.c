#include "../include/minishell.h"
#include "../libft/libft.h"

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	t_cmd	*cmd;

	(void)argc;
	(void)argv;
	setup_signals();
	while (1)
	{
		line = readline("minishell$");
		if (!line)
			break;
		if (*line)
			add_history(line);
		if (ft_strchr(line, '|'))
				execute_pipeline(line, envp);
		else
		{
			cmd = parse_command(line);
			if (cmd && cmd->args && cmd->args[0])
					execute_command(cmd, envp);
			if (cmd)
				free(cmd);
		}
		free(line);
	}
	return (0);
}