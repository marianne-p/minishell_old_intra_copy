/* ************************************************************************** */
/*			                                                                */
/*			                                            :::      ::::::::   */
/*   check_redir_cmd.c                                  :+:      :+:    :+:   */
/*			                                        +:+ +:+         +:+     */
/*   By: mpihur <marvin@42.fr>			          +#+  +:+       +#+        */
/*			                                    +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 10:22:59 by mpihur			#+#    #+#             */
/*   Updated: 2024/07/22 10:24:59 by mpihur           ###   ########.fr       */
/*			                                                                */
/* ************************************************************************** */

#include "minishell.h"

int	check_redir_cmd(t_node *node, bool cmd, bool redir)
{
	while (node)
	{
		if (node->type == REDIR_NODE)
			redir = true;
		if (node->type == CMD_NODE)
			cmd = true;
		node = node->next;
		if (!node || (node && node->type == PIPE_NODE))
		{
			if ((redir == true && cmd != true)
				|| (node && node->type == PIPE_NODE && cmd == false))
				return (false);
			cmd = false;
			redir = false;
		}
	}
	return (true);
}
