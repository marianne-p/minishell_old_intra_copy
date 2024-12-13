/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_tree_extra.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpihur <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 19:03:29 by mpihur            #+#    #+#             */
/*   Updated: 2024/07/25 19:03:31 by mpihur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*copy_inside_quote(char *res, char *str)
{
	char	quote;
	char	*start;
	int		len;

	len = 0;
	quote = *str;
	str++;
	start = str;
	while (str && *str && *str != quote)
		(str)++;
	len = str - start;
	res = malloc(len + 1);
	if (res)
	{
		if (len > 0)
			ft_strncpy(res, start, len);
		res[len] = '\0';
	}
	return (res);
}

void	remove_arg_quotes(char ***av_ptr, int ac, char **av, int i)
{
	char	*temp;

	av = *av_ptr;
	if (ac == 1)
		return ;
	while (av[i])
	{
		if (*av[i] == '"' || *av[i] == '\'')
		{
			temp = (*av_ptr)[i];
			(*av_ptr)[i] = copy_inside_quote(NULL, av[i]);
			free (temp);
		}
		i++;
	}
}
