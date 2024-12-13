/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpihur <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 16:04:01 by mpihur            #+#    #+#             */
/*   Updated: 2024/07/18 16:19:26 by mpihur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_envv_value(t_envv *env, char *key)
{
	while (env != NULL)
	{
		if (!ft_strncmp(key, env->key, ft_strlen(env->key)))
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

static char	*alloc_ret(char *value, int j, char *cpy, char *ret)
{
	if (value)
	{
		ret = malloc(ft_strlen(cpy) - j + ft_strlen(value) + 1);
		if (!ret)
			return (NULL);
		ft_bzero(ret, ft_strlen(cpy) - j + ft_strlen(value) + 1);
	}
	else
	{
		ret = malloc(ft_strlen(cpy) - j + 1);
		if (!ret)
			return (NULL);
		ft_bzero(ret, ft_strlen(cpy) - j + 1);
	}
	return (ret);
}

static char	*create_new_str(char *value, int j, char *cpy, int *start)
{
	int		k;
	char	*ret;

	ret = alloc_ret(value, j, cpy, NULL);
	k = 0;
	j = 0;
	while (cpy[j] != '$')
		ret[k++] = cpy[j++];
	if (value)
	{
		while (*value)
			ret[k++] = *value++;
	}
	*start = k;
	while (cpy[j] != '\0' && cpy[j] != ' ' && !(cpy[j] > 8 && cpy[j] < 14))
		j++;
	*start = k;
	while (cpy[j])
		ret[k++] = cpy[j++];
	ret[k] = '\0';
	return (ret);
}

static char	*create_return(int i, char *cpy, t_minish *msh, int *start)
{
	char	*free_value;
	char	key[1024];
	int		j;
	char	*value;
	char	*ret;

	ft_bzero(key, 1024);
	free_value = NULL;
	j = 0;
	while (cpy[i] != '\0' && cpy[i] != ' '
		&& !(cpy[i] > 8 && cpy[i] < 14))
		key[j++] = cpy[i++];
	key[j] = '\0';
	value = find_envv_value(msh->env, key);
	if (!value && !ft_strncmp(key, "?\0", 2))
		free_value = ft_itoa(msh->status);
	if (free_value)
		ret = create_new_str(free_value, j, cpy, start);
	else
		ret = create_new_str(value, j, cpy, start);
	free(cpy);
	if (free_value)
		free(free_value);
	return (ret);
}

char	*expand(int i, char *cpy, t_minish *msh)
{
	char	*ret;
	int		start;

	start = 0;
	if (cpy && cpy[i] && ft_strchr(cpy, '$') == NULL)
		return (cpy);
	while (cpy && cpy[i] != '\0' && ft_strrchr(cpy, '$') != NULL)
	{
		while (cpy[i] != '\0' && cpy[i] != '$')
			i++;
		if (cpy[i++] == '$')
		{
			ret = create_return(i, cpy, msh, &start);
			cpy = ret;
		}
		i = start;
	}
	return (ret);
}
