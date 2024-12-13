/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpihur <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 17:16:26 by mpihur            #+#    #+#             */
/*   Updated: 2024/07/18 17:17:14 by mpihur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_cmd_node(t_node **node_ptr, int i)
{
	if ((*node_ptr)->cmd != NULL)
	{
		while ((*node_ptr)->cmd->av[i])
		{
			free((*node_ptr)->cmd->av[i]);
			(*node_ptr)->cmd->av[i++] = NULL;
		}
		free((*node_ptr)->cmd->av);
		(*node_ptr)->cmd->av = NULL;
		if ((*node_ptr)->cmd->full_line)
		{
			free((*node_ptr)->cmd->full_line);
			(*node_ptr)->cmd->full_line = NULL;
		}
		free((*node_ptr)->cmd);
		(*node_ptr)->cmd = NULL;
	}
}

void	free_env(t_minish **msh_ptr, void *temp)
{
	if (msh_ptr && (*msh_ptr)->env != NULL)
	{
		temp = (*msh_ptr)->env;
		while (temp != NULL)
		{
			(*msh_ptr)->env = (*msh_ptr)->env->next;
			free(((t_envv *)temp)->value);
			free(((t_envv *)temp)->key);
			free(((t_envv *)temp));
			temp = (*msh_ptr)->env;
		}
	}
}

void	free_tokens(t_minish **msh_ptr, int i)
{
	char	**temp;
	char	*t;

	(void)i;
	temp = (*msh_ptr)->tokens;
	if ((*msh_ptr)->tokens)
	{
		while (*((*msh_ptr)->tokens) != NULL)
		{
			t = *((*msh_ptr)->tokens);
			(*msh_ptr)->tokens++;
			if (t != NULL)
				free(t);
			*((*msh_ptr)->tokens - 1) = NULL;
		}
		free(temp);
	}
	(*msh_ptr)->tokens = NULL;
}

void	ft_exit(char *str, t_minish **msh_ptr, int ret, void *temp)
{
	int	ret_bit;

	ret_bit = ret & 0xFF;
	(void)str;
	(void)temp;
	free_env(msh_ptr, temp);
	if (msh_ptr && *msh_ptr)
	{
		if ((*msh_ptr)->tokens)
			free_tokens(msh_ptr, 0);
		if ((*msh_ptr)->node != NULL)
			free_t_node(&((*msh_ptr)->node), NULL);
	}
	free(*msh_ptr);
	rl_clear_history();
	printf("exit\n");
	kill(0, SIGTERM);
	exit (ret_bit);
}
