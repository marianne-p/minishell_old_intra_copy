/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_create.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpihur <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 17:03:11 by mpihur            #+#    #+#             */
/*   Updated: 2024/07/18 17:06:47 by mpihur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_pipes(int pipes_count, int i, t_node **begin)
{
	t_node	*current;

	current = *begin;
	while (current)
	{
		if (current->type == PIPE_NODE)
			return (-1);
		if (current->type == CMD_NODE)
			i++;
		current = current->next;
	}
	if (pipes_count + 1 == i)
		return (true);
	return (false);
}

t_node	**clean_pipes(t_node **node, t_minish **msh_ptr, int pipe_count)
{
	t_node	**begin;
	t_node	*temp;
	t_node	*current;

	begin = node;
	current = *node;
	while (current)
	{
		while (current->type == CMD_NODE && current->next
			&& current->next->type == PIPE_NODE)
		{
			temp = current->next;
			current->next = current->next->next;
			free(temp->pipe);
			free(temp);
			pipe_count++;
		}
		current = current->next;
	}
	if (check_pipes(pipe_count, 0, begin) == false)
	{
		ft_cust_err_no_exit(msh_ptr, NULL, "Pipes number is wrong\n\0");
		return (NULL);
	}
	return (begin);
}

t_pipe	*create_pipe_node(void)
{
	t_pipe	*pipe;

	pipe = malloc(sizeof(t_pipe));
	pipe->left = NULL;
	pipe->right = NULL;
	return (pipe);
}

t_node	*wrap_pipe_in_node(t_pipe *pipe)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	node->type = PIPE_NODE;
	node->pipe = pipe;
	node->cmd = NULL;
	node->redir = NULL;
	node->inred = NULL;
	node->outred = NULL;
	node->next = NULL;
	return (node);
}
