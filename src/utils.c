#include "../include/minishell.h"

int	ft_strlen_2(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_strcmp(char *str1, char *str2)
{
	int	i;

	i = 0;
	if (!str1 || !str2)
		return (0);
	while (str1[i] && str2[i])
	{
		if (str1[i] != str2[i])
			return ((unsigned char) (str1[i]) - (unsigned char) (str2[i]));
		i++;
	}
	return ((unsigned char) (str1[i]) - (unsigned char) (str2[i]));
}

int	ft_isspace(int a)
{
	return (a == '\f' || a == '\n' || a == '\r' || a == '\t' || a == '\v');
}