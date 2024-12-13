/* ************************************************************************** */
/*			                                                                */
/*			                                            :::      ::::::::   */
/*   ft_utils_2.c                                       :+:      :+:    :+:   */
/*			                                        +:+ +:+         +:+     */
/*   By: mpihur <marvin@42.fr>			          +#+  +:+       +#+        */
/*			                                    +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 14:46:22 by mpihur			#+#    #+#             */
/*   Updated: 2024/07/22 10:09:17 by mpihur           ###   ########.fr       */
/*			                                                                */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_all_num(char *str)
{
	while (*str && ((*str > 8 && *str < 14) || *str == ' '))
		str++;
	if (*str && *str == '-')
		str++;
	while (*str && ft_isdigit((int)*str) == true)
		str++;
	while (*str && ((*str > 8 && *str < 14) || *str == ' '))
		str++;
	if (*str != '\0')
	{
		return (false);
	}
	return (true);
}

int	is_pipe(char *token)
{
	if (*token == '|')
		return (true);
	return (false);
}

void	copy_quote_expand(char **tokens, char **str, t_minish **msh_ptr)
{
	copy_quote(tokens, str);
	*tokens = expand(0, *tokens, *msh_ptr);
}

int	isvalidquote(char **str)
{
	char	quote;

	quote = **str;
	(*str)++;
	while (**str && quote != **str)
		(*str)++;
	if (**str == '\0')
		return (false);
	else
	{
		(*str)++;
		return (true);
	}
	return (false);
}

int	len(char *str, int count)
{
	while (str && *str != '\0')
	{
		while (*str && (*str == ' ' || *str == '\t' || *str == '\n'))
			str++;
		if (*str && *str == '|')
		{
			count++;
			str++;
		}
		else if (*str && (*str == '"' || *str == '\''))
		{
			if (!isvalidquote(&str))
				return (false);
			count++;
		}
		else if (*str)
		{
			while (*str && !(*str == ' ' || *str == '\t'
					|| *str == '\n' || *str == '"' || *str == '\''))
				str++;
			count++;
		}
	}
	return (count);
}
