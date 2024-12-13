/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpihur <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 17:15:17 by mpihur            #+#    #+#             */
/*   Updated: 2024/07/18 17:15:29 by mpihur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	create_cmd_node(char **tokens, t_node *node)
{
	t_cmd	*cmd;
	int		i;
	int		j;

	j = 0;
	i = 0;
	cmd = malloc(sizeof(t_cmd));
	cmd->ac = 0;
	while (tokens[i] && ft_strncmp(tokens[i], "|", 1) != 0
		&& ft_strncmp(tokens[i], ">", 1) != 0
		&& ft_strncmp(tokens[i], "<", 1) != 0)
	{
		i++;
		cmd->ac++;
	}
	cmd->av = malloc(sizeof(char *) * (cmd->ac + 1));
	while (j < cmd->ac)
	{
		cmd->av[j] = ft_strdup(tokens[j]);
		j++;
	}
	cmd->av[cmd->ac] = NULL;
	node->cmd = cmd;
}
