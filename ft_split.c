/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpihur <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 14:49:47 by mpihur            #+#    #+#             */
/*   Updated: 2024/07/18 17:59:17 by mpihur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	copy_quote(char **tokens, char **str)
{
	char	quote;
	char	*start;
	int		len;

	len = 0;
	quote = **str;
	start = *str;
	(*str)++;
	while (*str && **str != quote)
		(*str)++;
	len = *str - start + 1;
	tokens[0] = malloc(len + 1);
	if (tokens[0])
	{
		if (len > 0)
			ft_strncpy(tokens[0], start, len);
		tokens[0][len] = '\0';
	}
	if (*str && **str == quote)
		(*str)++;
}

void	copy_regtoken(char **tokens, char **str, t_envv *env, t_minish *msh)
{
	char	*start;
	int		len;

	(void)msh;
	(void)env;
	len = 0;
	start = *str;
	while (*str && **str != '\0' && **str && **str != ' '
		&& !(**str > 8 && **str < 14) && **str != '"' && **str != '\'')
		(*str)++;
	len = *str - start;
	*tokens = malloc(len + 1);
	if (!*tokens)
		return ;
	if (*tokens)
	{
		ft_strncpy(*tokens, start, len);
		(*tokens)[len] = '\0';
	}
	if (ft_strchr(*tokens, '$') != NULL)
		*tokens = expand(0, *tokens, msh);
}

static char	**create_tokens(char *str, int i, t_minish **msh_ptr, char **tokens)
{
	while (*str && *str != '\0')
	{
		while (str && *str && (*str == ' ' || (*str > 8 && *str < 14)))
			str++;
		if (!*str)
			break ;
		if (str && *str && *str == '|')
		{
			tokens[i++] = ft_strdup("|\0");
			str++;
		}
		else if (str && *str && *str == '\'')
			copy_quote(&tokens[i++], &str);
		else if (str && *str && *str == '"')
			copy_quote_expand(&tokens[i++], &str, msh_ptr);
		else if (str && *str)
			copy_regtoken(&tokens[i++], &str, (*msh_ptr)->env, *msh_ptr);
	}
	tokens[i] = NULL;
	return (tokens);
}

char	**ft_split_minish(char *str, int i, t_minish **msh_ptr)
{
	char	**tokens;
	int		count_tokens;

	count_tokens = len(str, 0);
	if (!count_tokens)
		return (NULL);
	tokens = malloc((count_tokens + 1) * (sizeof(char *)));
	if (tokens == NULL)
		return (NULL);
	if (verify_quotes(str, 0, 0, 0) < 0)
		return (ret_and_free("Quotes number not even, try again\n", tokens));
	tokens = create_tokens(str, i, msh_ptr, tokens);
	return (tokens);
}
