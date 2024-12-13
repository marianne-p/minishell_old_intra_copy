/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_redir_handler.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpihur <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 17:47:36 by mpihur            #+#    #+#             */
/*   Updated: 2024/06/23 17:52:44 by mpihur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_str(char *delim, char *buff, char *ret)
{
	char	c[2];
	char	*temp;

	c[1] = '\0';
	while (!buff || ft_strlen(buff) - 1 != ft_strlen(delim)
		|| ft_strncmp(delim, buff, ft_strlen(buff) - 1))
	{
		temp = ret;
		ret = ft_strjoinc(ret, buff);
		free(temp);
		free(buff);
		buff = NULL;
		*c = '\0';
		write(STDOUT_FILENO, "> ", 2);
		while (*c != '\n')
		{
			read(0, c, 1);
			temp = buff;
			buff = ft_strjoinc(buff, c);
			free(temp);
		}
	}
	free(buff);
	return (ret);
}

int	handle_input_heredoc(t_minish *msh, t_node *node, char *str)
{
	int		fd[2];
	pid_t	pid;

	if (pipe(fd) == -1)
		return (ft_no_exit(&msh, 1, NULL,
				"Handle_input_heredoc (cmd_redir_handler.c). Pipe ERR\n"));
	pid = fork();
	if (pid == -1)
		return (ft_no_exit(&msh, 1, NULL,
				"Handle_input_heredoc (cmd_redir_handler.c). Fork ERR\n"));
	if (!pid)
	{
		close(fd[0]);
		write(fd[1], str, ft_strlen(str));
		close(fd[1]);
		exit (0);
	}
	node->cmd->infd = fd[0];
	close(fd[1]);
	free(str);
	return (fd[0]);
}
