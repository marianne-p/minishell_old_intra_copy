/* ************************************************************************** */
/*	                                                                        */
/*	                                                    :::      ::::::::   */
/*   is_pipe_redir.c                                    :+:      :+:    :+:   */
/*	                                                +:+ +:+         +:+     */
/*   By: mpihur <marvin@42.fr>	                  +#+  +:+       +#+        */
/*	                                            +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 15:54:04 by mpihur	        #+#    #+#             */
/*   Updated: 2024/07/22 10:16:49 by mpihur           ###   ########.fr       */
/*	                                                                        */
/* ************************************************************************** */

#include "minishell.h"

int	is_space(char c)
{
	if ((c > 8 && c < 14) || c == 32)
		return (false);
	return (true);
}

int	is_redirection(char *tokens)
{
	if (is_space(*tokens))
		tokens++;
	if (*tokens == '<' || *tokens == '>')
		return (false);
	return (true);
}

int	is_pipe(char *tokens)
{
	if (is_space(*tokens))
		tokens++;
	if (*tokens == '|')
		return (false);
	return (true);
}

int	is_valid_cmd(char *tokens)
{
	if (access(tokens, F_OK | R_OK))
		return (false);
	return (true);
}
