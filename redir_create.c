/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_create.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpihur <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 18:12:02 by mpihur            #+#    #+#             */
/*   Updated: 2024/07/18 17:15:45 by mpihur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_redirection(char *token)
{
	if (ft_strncmp(token, ">", 1) == 0
		|| ft_strncmp(token, "<", 1) == 0)
		return (1);
	return (0);
}

t_node	*wrap_redir_in_node(t_redir *redir)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	node->type = REDIR_NODE;
	node->redir = redir;
	node->inred = NULL;
	node->outred = NULL;
	node->cmd = NULL;
	node->pipe = NULL;
	node->next = NULL;
	return (node);
}

static t_redir	*input_dir(char ***tokens, t_redir *redir)
{
	redir->filename = NULL;
	redir->delim = NULL;
	if (ft_strncmp(**tokens, "<", 1) == 0)
	{
		redir->mode = -1;
		if (ft_strncmp(**tokens, "<<", 2) == 0)
		{
			redir->mode = -2;
			if (ft_strlen(**tokens) > 2)
				redir->delim = ((**tokens) + 2);
			else
				redir->delim = *(++(*tokens));
			return (redir);
		}
		if (ft_strlen(**tokens) > 1)
			redir->filename = ((**tokens) + 1);
		else
			redir->filename = *(++(*tokens));
		return (redir);
	}
	return (redir);
}

static t_redir	*mini_create_red_nd(char ***tokens, t_redir *redir)
{
	redir->mode = 1;
	if (ft_strlen(**tokens) > 2)
		redir->filename = ((**tokens) + 2);
	else
		redir->filename = *(++(*tokens));
	(*tokens)++;
	return (redir);
}

t_redir	*create_redir_node(char ***tokens)
{
	t_redir	*redir;

	redir = malloc(sizeof(t_redir));
	if (!redir)
		return (NULL);
	redir->mode = -1;
	redir->delim = NULL;
	if (ft_strncmp(**tokens, "<", 1) == 0)
		redir = input_dir(tokens, redir);
	if (ft_strncmp(**tokens, ">", 1) == 0)
	{
		redir->delim = NULL;
		redir->mode = 0;
		if (ft_strncmp(**tokens, ">>", 2) == 0)
			return (mini_create_red_nd(tokens, redir));
		if (ft_strlen(**tokens) > 1)
			redir->filename = ((**tokens) + 1);
		else
			redir->filename = *(++(*tokens));
		(*tokens)++;
		return (redir);
	}
	(*tokens)++;
	return (redir);
}
