/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_extra.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpihur <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 16:39:49 by mpihur            #+#    #+#             */
/*   Updated: 2024/07/22 10:16:37 by mpihur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	token_exec(char **input, char **tokens, t_minish **msh, t_node *node)
{
	remove_useless_quotes(input, *input, 0);
	tokens = ft_split_minish(*input, 0, msh);
	if (tokens == NULL)
		return (1);
	(*msh)->tokens = tokens;
	node = parser(tokens, msh, NULL, NULL);
	if (node == NULL)
		return (VALID_ERR);
	if (check_redir_cmd(node, false, false) == false)
		return (ft_no_exit(msh, VALID_ERR, NULL, "INVALID INPUT"));
	syntax_tree(&node, node, msh);
	(*msh)->node = node;
	if (check_validity(node, *msh) == false)
		return (ft_no_exit(msh, VALID_ERR, NULL, "INVALID INPUT"));
	if (!ft_strncmp(node->cmd->av[0], "exit\0", 5))
		return (exec_exit(node, msh));
	execute(msh, &node, node);
	free(*input);
	*input = NULL;
	ft_no_err_no_exit(msh, 0, NULL);
	return (SUCS);
}

static int	run_child(int (*fd)[], t_minish **msh_ptr, t_node *node, pid_t *pid)
{
	if (pipe(*fd) == -1)
		return (ft_no_exit(msh_ptr, PIPE_ERROR, NULL,
				"Single Cmd. Pipe creation err\n"));
	*pid = fork();
	if (*pid == -1)
		return (ft_no_exit(msh_ptr, FORK_ERROR, NULL,
				"Single Cmd. Fork error\n"));
	if (!*pid)
		child_process(node, *fd, *msh_ptr);
	return (0);
}

int	single_cmd(t_node *node, t_minish **msh_ptr)
{
	int		fd[2];
	pid_t	pid;
	int		status;

	if (node && node->cmd && node->cmd->infd && node->cmd->infd != -128)
	{
		if (dup2(node->cmd->infd, STDIN_FILENO) == -1)
			return (ft_no_exit(msh_ptr, DUP2_ERROR, NULL,
					"Single Cmd. Input fd dup2 error\n"));
		close(node->cmd->infd);
	}
	if (!ft_strncmp("cd\0", node->cmd->av[0], 3))
		ft_cd(node->cmd->av[1]);
	if (is_exp_env_uns(node->cmd->av[0]))
		return (single_cmd_in_parent(msh_ptr, node));
	if (run_child(&fd, msh_ptr, node, &pid) < 0)
		return (1);
	waitpid(pid, &status, 0);
	((*msh_ptr)->status) = WEXITSTATUS(status);
	close(fd[0]);
	return (SUCS);
}

/*Handle errors not just with FT_EXIT
How to make sure HereDoc Child exits and no hangs? */

int	handle_cmd_redir(t_minish **msh_ptr, t_redir *inrd,
	t_redir *outrd, t_node **node)
{
	if (inrd)
	{
		if (inrd->mode == -1)
			(*node)->cmd->infd = open(inrd->filename, O_RDONLY);
		if (inrd->mode == -2)
			(*node)->cmd->infd = handle_input_heredoc(*msh_ptr, *node,
					get_str(inrd->delim, NULL, NULL));
		if ((*node)->cmd->infd != -128 && (*node)->cmd->infd < 0)
			return (ft_no_exit(msh_ptr, REDIR_ERR, NULL, "Input REDIR ERR\n"));
	}
	if (outrd)
	{
		if (outrd->mode == 0)
			(*node)->cmd->outfd = open(outrd->filename,
					O_TRUNC | O_WRONLY | O_CREAT, 0666);
		if (outrd->mode == 1)
			(*node)->cmd->outfd = open(outrd->filename,
					O_APPEND | O_WRONLY | O_CREAT, 0666);
		if ((*node)->cmd->outfd != -128 && (*node)->cmd->outfd < 0)
			return (ft_no_exit(msh_ptr, REDIR_ERR, NULL, "Output REDIR ERR\n"));
	}
	return (0);
}

void	child_process(t_node *node, int fd[2], t_minish *msh)
{
	close(fd[0]);
	if (node->next && dup2(fd[1], STDOUT_FILENO) == -1)
		ft_no_exit(&msh, DUP2_ERROR, NULL,
			"Child process. Dup2 fd[1] to STDOUT ERR\n");
	if (node->cmd->outfd && node->cmd->outfd != -128)
		if (dup2(node->cmd->outfd, STDOUT_FILENO) == -1)
			ft_no_exit(&msh, DUP2_ERROR, NULL,
				"Child. Dup2 ERR, outfd to STDOUT\n");
	if (node->cmd->infd != -128)
		close(node->cmd->infd);
	if (node->cmd->outfd != -128)
		close(node->cmd->outfd);
	close(fd[1]);
	if (is_builtin(node->cmd->av[0]))
		exec_builtin(node, &msh);
	else
	{
		execve(node->cmd->full_line, node->cmd->av, NULL);
		ft_no_exit(&msh, EXECVE_ERROR, NULL, "Child Execve ERR\n");
	}
	return ;
}
