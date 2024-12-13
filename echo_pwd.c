/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_pwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpihur <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 18:20:27 by mpihur            #+#    #+#             */
/*   Updated: 2024/07/26 12:27:22 by mpihur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_and_exit(char *str, int ret)
{
	perror(str);
	return (ret);
}

void	ft_pwd(void)
{
	char	*buff;

	buff = (char *)malloc(PATH_MAX);
	if (!buff)
		exit(check_and_exit("Pwd error\n", MALL_ERR));
	if (getcwd(buff, PATH_MAX) == NULL)
	{
		perror("getcwd failed");
		free(buff);
		exit(EXIT_FAILURE);
	}
	printf("%s\n", buff);
	free(buff);
}

/*Executes "cd" with relative or absolute path, as well as ., ..i
 *
 * A child process created via fork(2) inherits its parent's current
 * working directory.  The current working directory is left
 * unchanged by execve(2).
*/

int	ft_cd(char *path)
{
	if (chdir(path) < 0)
		check_and_exit("Cd execution error\n", EXECVE_ERROR);
	return (SUCS);
}

static int	exec_echo(bool newline, char **str, int i, int j)
{
	while (str[i] && ft_strncmp(str[i], "", 1) != 0)
	{
		if (ft_strncmp(str[i], "#\0", 2) == 0)
		{
			i++;
			continue ;
		}
		if (str[i][j] == '"' || str[i][j] == '\'')
		{
			j++;
			while (str[i][j] && (str[i][j] != '\'' && str[i][j] != '"'))
				printf("%c", str[i][j++]);
			i++;
		}
		else
			printf("%s", str[i++]);
		if (str[i])
			printf(" ");
	}
	if (newline == true)
		printf("\n");
	return (SUCS);
}

int	ft_echo(char **cmd)
{
	bool	newline;
	int		i;
	int		j;

	i = 1;
	j = 0;
	if (cmd[i] && ft_strncmp(cmd[i], "-n", 2) == 0)
	{
		newline = false;
		while (cmd[i] && ft_strncmp(cmd[i], "-n", 2) == 0)
		{
			i++;
		}
	}
	else
		newline = true;
	if (newline == true)
		return (exec_echo(newline, cmd, 1, 0));
	else
		return (exec_echo(newline, cmd, i, 0));
}
