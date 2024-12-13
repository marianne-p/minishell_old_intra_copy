/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_verify.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpihur <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 14:49:55 by mpihur            #+#    #+#             */
/*   Updated: 2024/07/22 10:11:20 by mpihur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_white_space(char c)
{
	if (c == ' ' || (c > 8 && c < 14))
		return (true);
	return (false);
}

char	**ret_and_free(char *str, char **tokens)
{
	write(1, &str, ft_strlen(str));
	free(tokens);
	return (NULL);
}

int	verify_quotes(char *str, int i, int db_q, int sing_q)
{
	while (str[i])
	{
		if (str[i] == 34)
			db_q++;
		if (str[i] == 39)
			sing_q++;
		i++;
	}
	if (sing_q % 2 == 1)
		return (-1);
	if (db_q % 2 == 1)
		return (-2);
	return (false);
}
