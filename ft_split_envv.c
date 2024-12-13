/* ************************************************************************** */
/*			                                                                */
/*			                                            :::      ::::::::   */
/*   ft_split_envv.c                                    :+:      :+:    :+:   */
/*			                                        +:+ +:+         +:+     */
/*   By: mpihur <marvin@42.fr>			          +#+  +:+       +#+        */
/*			                                    +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 16:23:37 by mpihur			#+#    #+#             */
/*   Updated: 2024/07/18 16:26:41 by mpihur           ###   ########.fr       */
/*			                                                                */
/* ************************************************************************** */

#include "minishell.h"

static char	*create_key(char *key, char *sngl_env, int i)
{
	int	len;

	len = ft_strlen(sngl_env);
	while (i < len && sngl_env[i] != '=')
		i++;
	key = malloc(sizeof(char) * (i + 1));
	if (!key)
		return (NULL);
	i = 0;
	while (i < len && sngl_env[i] != '=')
	{
		key[i] = sngl_env[i];
		i++;
	}
	key[i] = '\0';
	return (key);
}

static char	*create_value(char *value, char *sngl, int i, int k)
{
	int	len;

	len = ft_strlen(sngl);
	while (i < len && sngl[i] != '=')
		i++;
	if (i == len)
		return (NULL);
	k = len - i;
	value = malloc(sizeof(char) * k);
	if (value == NULL)
		return (NULL);
	k = 0;
	while (sngl[++i] != '\0')
		value[k++] = sngl[i];
	value[k] = '\0';
	return (value);
}

static t_envv	*ft_newenv(t_envv *new, char *sngl)
{
	new = malloc(sizeof(t_envv));
	if (!new)
		return (NULL);
	new->key = create_key(NULL, sngl, 0);
	if (new->key == NULL)
		return (free_new(&new, NULL));
	new->value = create_value(NULL, sngl, 0, 0);
	if (new->value == NULL)
		return (free_new(&new, &(new->key)));
	new->next = NULL;
	return (new);
}

void	create_new_envv(t_envv **env_ptr, char **key, t_envv *new, char *sngl)
{
	t_envv	*temp;

	temp = *env_ptr;
	free(*key);
	new = ft_newenv(new, sngl);
	if (!*env_ptr)
		*env_ptr = new;
	else
	{
		temp = *env_ptr;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new;
	}
}

void	ft_addenvv(t_envv **env_ptr, char *sngl, t_envv *new)
{
	t_envv	*temp;
	char	*key;
	bool	envv_exist;

	envv_exist = false;
	key = create_key(NULL, sngl, 0);
	if (key == NULL)
		return ;
	temp = *env_ptr;
	while (temp)
	{
		if (key && ft_strncmp(temp->key, key, ft_strlen(key) + 1) == 0)
		{
			envv_exist = true;
			free(temp->value);
			free (key);
			key = NULL;
			temp->value = create_value(NULL, sngl, 0, 0);
			break ;
		}
		temp = temp->next;
	}
	if (envv_exist == false)
		create_new_envv(env_ptr, &key, new, sngl);
}
/*
static void	 print_envv(t_envv *env, t_envv *temp)
{
	temp = env;

	while (temp != NULL && temp->key && temp->value)
	{
		printf("%s = %s\n", temp->key, temp->value);
		temp = temp->next;
	}
	printf("HEAD after printf_envv: %s\n", env->key);
}*/
