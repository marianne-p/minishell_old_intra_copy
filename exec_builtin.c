/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpihur <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 17:59:32 by mpihur            #+#    #+#             */
/*   Updated: 2024/07/18 15:46:49 by mpihur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_exit(t_node *node, t_minish **msh_ptr)
{
	int		ret;

	ret = 0;
	if (ft_strncmp(node->cmd->av[0], "exit\0", 5) == 0
		&& node->cmd->av[1] != NULL)
	{
		if (ft_is_all_num(node->cmd->av[1]) == true)
		{
			ret = ft_atoi(node->cmd->av[1]);
			ft_exit(node->cmd->av[1], msh_ptr, ret, NULL);
		}
		else
		{
			printf("exit: %s: numeric argument required\n", node->cmd->av[1]);
			ft_exit(NULL, msh_ptr, 0, NULL);
		}
		return (ret & 0xFF);
	}
	else if (ft_strncmp(node->cmd->av[0], "exit\0", 5) == 0)
	{
		ft_exit(NULL, msh_ptr, 0, NULL);
	}
	return (ret & 0xFF);
}

void	exec_builtin(t_node *node, t_minish **msh_ptr)
{
	if (ft_strncmp(node->cmd->av[0], "echo\0", 5) == 0)
		ft_echo(node->cmd->av);
	if (ft_strncmp(node->cmd->av[0], "pwd\0", 4) == 0)
		ft_pwd();
	if (ft_strncmp(node->cmd->av[0], "export\0", 7) == 0)
		return ;
	if (ft_strncmp(node->cmd->av[0], "unset\0", 6) == 0)
		return ;
	if (ft_strncmp(node->cmd->av[0], "env\0", 4) == 0)
		ft_env(*msh_ptr);
	exec_exit(node, msh_ptr);
	exit(0);
}

int	is_exp_env_uns(char *cmd)
{
	if (!ft_strncmp(cmd, "env\0", 4) || !ft_strncmp(cmd, "export\0", 7)
		|| !ft_strncmp(cmd, "unset\0", 6))
		return (true);
	return (false);
}

int	single_cmd_in_parent(t_minish **msh_ptr, t_node *node)
{
	if (ft_strncmp(node->cmd->av[0], "export\0", 7) == 0)
		ft_export(node->cmd->av, &((*msh_ptr)->env));
	if (ft_strncmp(node->cmd->av[0], "unset\0", 6) == 0)
		ft_unset(node->cmd->av[1], &((*msh_ptr)->env));
	if (ft_strncmp(node->cmd->av[0], "env\0", 4) == 0)
		ft_env(*msh_ptr);
	return (0);
}
