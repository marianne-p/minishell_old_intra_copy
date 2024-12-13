/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpihur <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 16:30:09 by mpihur            #+#    #+#             */
/*   Updated: 2024/07/25 19:02:53 by mpihur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_cmd(t_minish **msh_ptr, t_node **node, t_node *start)
{
	int		saved_stdin;
	int		saved_stdout;
	t_node	**begin;

	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	if (saved_stdin < 0 || saved_stdout < 0)
		ft_no_exit(msh_ptr, 1, NULL, "Dup StdIn ERR\n");
	if (!start->next)
		single_cmd(start, msh_ptr);
	else
	{
		begin = clean_pipes(node, msh_ptr, 0);
		if (begin == NULL)
			return ;
		handle_cmd_pipe(*begin, msh_ptr);
	}
	if (dup2(saved_stdin, STDIN_FILENO) < 0
		|| dup2(saved_stdout, STDOUT_FILENO) < 0)
		ft_no_exit(msh_ptr, 1, NULL, "Error restoring STDIN to STDIN\n");
}

void	execute(t_minish **msh_ptr, t_node **node, t_node *unode)
{
	t_node	*start;
	int		result;

	start = unode;
	while (unode)
	{
		if ((unode)->type == CMD_NODE)
		{
			if (unode->inred || unode->outred)
			{
				result = handle_cmd_redir(msh_ptr, unode->inred,
						unode->outred, &unode);
				if (result != 0)
					return ;
			}
		}
		unode = unode->next;
	}
	exec_cmd(msh_ptr, node, start);
}

static int	handle_cmd_pipe_helper(int (*fd)[], t_node **node,
t_minish **msh_ptr, pid_t *pid)
{
	if ((*node)->cmd->infd && (*node)->cmd->infd != -128)
	{
		if (dup2((*node)->cmd->infd, STDIN_FILENO) == -1)
			return (ft_no_exit(msh_ptr, 1, NULL,
					"Handle_cmd_pipe. Dup2 ERR, infd to StdIn\n"));
		close((*node)->cmd->infd);
	}
	if (pipe(*fd) == -1)
		return (ft_no_exit(msh_ptr, 1, NULL, "Handle_cmd_pipe. Pipe error\n"));
	*pid = fork();
	return (SUCS);
}

static int	handle_dup2(t_minish **msh_ptr, t_node *node, int (*fd)[])
{
	if (node->next)
	{
		if (dup2((*fd)[0], STDIN_FILENO) == -1)
			return (ft_no_exit(msh_ptr, DUP2_ERROR, NULL,
					"Handle_cmd_pipe. Dup2 ERR, fd[0] to STDIN\n"));
	}
	else
		close((*fd)[0]);
	return (0);
}

int	handle_cmd_pipe(t_node *node, t_minish **msh_ptr)
{
	int		fd[2];
	pid_t	pid;
	int		status;

	while (node)
	{
		if (handle_cmd_pipe_helper(&fd, &node, msh_ptr, &pid) < 0)
			return (-1);
		if (pid == -1)
			return (ft_no_exit(msh_ptr, FORK_ERROR, NULL,
					"Handle_cmd_pipe. Fork error\n"));
		if (!pid)
			child_process(node, fd, *msh_ptr);
		waitpid(pid, &status, WNOHANG);
		busy_wait();
		((*msh_ptr)->status) = WEXITSTATUS(status);
		close(fd[1]);
		if (handle_dup2(msh_ptr, node, &fd) < 0)
			return (DUP2_ERROR);
		node = node->next;
	}
	return (1);
}
