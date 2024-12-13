/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpihur <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 15:57:22 by mpihur            #+#    #+#             */
/*   Updated: 2024/07/18 15:57:51 by mpihur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_t_node(t_node **node_ptr, t_node *temp)
{
	while (node_ptr && *node_ptr)
	{
		if ((*node_ptr)->cmd)
			free_cmd_node(node_ptr, 0);
		if ((*node_ptr)->pipe)
			free((*node_ptr)->pipe);
		if ((*node_ptr)->redir)
			free((*node_ptr)->redir);
		if ((*node_ptr)->inred)
			free((*node_ptr)->inred);
		if ((*node_ptr)->outred)
			free((*node_ptr)->outred);
		temp = (*node_ptr)->next;
		free(*node_ptr);
		*node_ptr = temp;
	}
}

void	ft_no_err_no_exit(t_minish **msh_ptr, int i, void *temp)
{
	(void)temp;
	(void)i;
	if (msh_ptr && *msh_ptr)
	{
		if ((*msh_ptr)->tokens)
			free_tokens(msh_ptr, -1);
		i = 0;
		if ((*msh_ptr)->node != NULL)
			free_t_node(&((*msh_ptr)->node), NULL);
	}
}

int	ft_no_exit(t_minish **msh_ptr, int ret, void *temp, char *str)
{
	(void)temp;
	ft_no_err_no_exit(msh_ptr, 0, NULL);
	perror (str);
	(*msh_ptr)->status = ret;
	return (ret);
}

int	ft_cust_err_no_exit(t_minish **msh_ptr, void *temp, char *str)
{
	(void)temp;
	ft_no_err_no_exit(msh_ptr, 0, NULL);
	if (str != NULL)
		write(STDERR_FILENO, str, ft_strlen(str));
	return (-12);
}
