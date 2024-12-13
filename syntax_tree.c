/* ************************************************************************** */
/*				                                                              */
/*				                                          :::      ::::::::   */
/*	 syntax_tree.c                                      :+:      :+:    :+:   */
/*				                                      +:+ +:+         +:+     */
/*	 By: sanoor <marvin@42.fr>			          +#+  +:+       +#+        */
/*				                                  +#+#+#+#+#+   +#+           */
/*	 Created: 2024/04/19 13:12:17 by sanoor			#+#    #+#             */
/*	 Updated: 2024/07/18 16:54:41 by mpihur           ###   ########.fr       */
/*				                                                              */
/* ************************************************************************** */

#include "minishell.h"

static void	open_redir_helper(t_node **node, t_node **cmd_node)
{
	if ((*node)->redir->mode < 0)
	{
		if ((*cmd_node)->inred)
			free((*cmd_node)->inred);
		(*cmd_node)->inred = (*node)->redir;
	}
	else
	{
		if ((*cmd_node)->outred)
			free((*cmd_node)->outred);
		(*cmd_node)->outred = (*node)->redir;
	}
}

void	open_redir(t_node **start_ptr, t_node *node,
		t_node *cmd_node, t_minish **msh_ptr)
{
	while (*start_ptr != NULL || (*start_ptr)->type != PIPE_NODE)
	{
		if ((*start_ptr)->type == CMD_NODE)
		{
			cmd_node = *start_ptr;
			break ;
		}
		*start_ptr = (*start_ptr)->next;
	}
	if (cmd_node == NULL)
	{
		ft_no_exit(msh_ptr, 0, NULL, "cmd_node is NULL");
		return ;
	}
	open_redir_helper(&node, &cmd_node);
}

void	remove_redir(t_node **node_ptr, t_node *red_node)
{
	t_node	*temp;

	temp = *node_ptr;
	if (temp == red_node)
	{
		*node_ptr = (*node_ptr)->next;
		return ;
	}
	while (temp->next != red_node)
		temp = temp->next;
	if (temp && temp->next->next == NULL)
	{
		temp->next = NULL;
		return ;
	}
	if (temp && temp->next != NULL && temp->next->next != NULL)
		temp->next = temp->next->next;
}

void	syntax_tree(t_node **node_ptr, t_node *start, t_minish **msh_ptr)
{
	t_node	*node;
	int		count;

	(void)start;
	count = 20;
	node = *node_ptr;
	while (node != NULL)
	{
		if (node->type == REDIR_NODE)
		{
			open_redir(&start, node, NULL, msh_ptr);
			remove_redir(node_ptr, node);
			free(node);
			node = *node_ptr;
		}
		else if (node->type == CMD_NODE)
		{
			remove_arg_quotes(&(node->cmd->av), node->cmd->ac, NULL, 1);
			node = node->next;
		}
		else
			node = node->next;
	}
}
