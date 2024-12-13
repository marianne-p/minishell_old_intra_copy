/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_unset.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpihur <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 17:18:29 by mpihur            #+#    #+#             */
/*   Updated: 2024/07/18 17:18:43 by mpihur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Adds EnvVar to the list*/
int	ft_export(char **envvar, t_envv **head)
{
	char	*str;

	if (envvar[1] == NULL)
		print_all_envv(*head);
	else
	{
		if (envvar[2] == NULL)
			ft_addenvv(head, envvar[1], NULL);
		else
		{
			str = ft_strjoin(envvar[1], envvar[2]);
			ft_addenvv(head, str, NULL);
			free (str);
		}
	}
	return (SUCS);
}

void	free_envv(t_envv **node)
{
	free((*node)->key);
	free((*node)->value);
	free(*node);
	*node = NULL;
}

/*Checks list of EnvVar and removes node from the list*/
int	ft_unset(char *key, t_envv **head)
{
	t_envv	*temp;
	t_envv	*prev;

	temp = *head;
	prev = temp;
	while (temp)
	{
		if (ft_strncmp(temp->key, key, ft_strlen(key)) == 0)
		{
			if (*head == temp)
			{
				*head = (*head)->next;
				free_envv(&temp);
			}
			else
			{
				prev->next = temp->next;
				free_envv(&temp);
			}
		}
		prev = temp;
		if (temp)
			temp = temp->next;
	}
	return (SUCS);
}
