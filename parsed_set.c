/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsed_set.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpihur <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 17:13:31 by mpihur            #+#    #+#             */
/*   Updated: 2024/07/18 17:14:25 by mpihur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node	*link_nodes(t_node *current, t_node *new_node)
{
	if (current != NULL)
		current->next = new_node;
	return (new_node);
}

void	set_redir(char ***tokens, t_node **current, t_node **root)
{
	if (*current == NULL)
	{
		*current = link_nodes(*current,
				wrap_redir_in_node(create_redir_node(tokens)));
		*root = *current;
	}
	else
		*current = link_nodes(*current,
				wrap_redir_in_node(create_redir_node(tokens)));
}

void	set_pipe(t_node **current, t_node **root)
{
	if (*current == NULL)
	{
		*current = link_nodes(*current,
				wrap_pipe_in_node(create_pipe_node()));
		*root = *current;
	}
	else
		*current = link_nodes(*current,
				wrap_pipe_in_node(create_pipe_node()));
}

void	set_cmd(char ***tokens, t_node **current,
		t_node **root, char **full_line)
{
	if (*current == NULL)
	{
		*current = link_nodes(*current,
				wrap_cmd_in_node(create_cmd_node(tokens), full_line));
		*root = *current;
	}
	else
		*current = link_nodes(*current,
				wrap_cmd_in_node(create_cmd_node(tokens), full_line));
}
