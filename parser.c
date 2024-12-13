/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpihur <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 14:50:29 by mpihur            #+#    #+#             */
/*   Updated: 2024/07/18 17:13:58 by mpihur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	this(char ***tokens, t_minish **msh_ptr,
		t_node **root_ptr, t_node **curr_ptr)
{
	if (is_redirection(**tokens))
	{
		set_redir(tokens, curr_ptr, root_ptr);
		(*msh_ptr)->node = *root_ptr;
	}
	else if (is_pipe(**tokens))
	{
		set_pipe(curr_ptr, root_ptr);
		++(*tokens);
		(*msh_ptr)->node = *root_ptr;
	}
}

t_node	*parser(char **tokens, t_minish **msh_ptr,
		t_node *root, t_node *current)
{
	char	*full_line;

	full_line = NULL;
	while (tokens && *tokens)
	{
		if (is_redirection(*tokens) || is_pipe(*tokens))
		{
			this(&tokens, msh_ptr, &root, &current);
			root = (*msh_ptr)->node;
		}
		else if (is_valid_cmd(*tokens, &full_line, *msh_ptr) == true)
		{
			set_cmd(&tokens, &current, &root, &full_line);
			(*msh_ptr)->node = root;
		}
		else
		{
			ft_no_exit(msh_ptr, VALID_ERR, NULL, "INVALID CMD");
			return (NULL);
		}
	}
	return (root);
}
