/* ************************************************************************** */
/*			                                                                */
/*			                                            :::      ::::::::   */
/*   cmd_crt_builtin.c                                  :+:      :+:    :+:   */
/*			                                        +:+ +:+         +:+     */
/*   By: mpihur <marvin@42.fr>			          +#+  +:+       +#+        */
/*			                                    +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 19:00:00 by mpihur			#+#    #+#             */
/*   Updated: 2024/07/18 15:56:55 by mpihur           ###   ########.fr       */
/*			                                                                */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char *token)
{
	if (!ft_strncmp(token, "pwd\0", 4) || !ft_strncmp(token, "echo\0", 5)
		|| !ft_strncmp(token, "export\0", 7) || !ft_strncmp(token, "unset\0", 6)
		|| !ft_strncmp(token, "env\0", 4) || !ft_strncmp(token, "exit\0", 5)
		|| !ft_strncmp(token, "cd\0", 3))
		return (true);
	return (false);
}
