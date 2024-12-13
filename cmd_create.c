/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_create.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpihur <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 17:51:58 by mpihur            #+#    #+#             */
/*   Updated: 2024/07/25 19:03:04 by mpihur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**split_path(t_minish *msh)
{
	char	*path_env;

	path_env = find_envv_value(msh->env, "PATH\0");
	if (path_env == NULL)
		return (NULL);
	return (ft_split(path_env, ':'));
}

int	is_valid_cmd(char *token, char **full_line, t_minish *msh)
{
	char	**path;
	int		is_valid;
	int		i;

	if (is_builtin(token) == 1)
		return (true);
	if (token[0] == '/')
	{
		if (access(token, F_OK) == 0)
		{
			*full_line = ft_strdup(token);
			return (true);
		}
	}
	i = 0;
	is_valid = 0;
	path = split_path(msh);
	if (!path)
		return (-1);
	is_valid = check_command(path, token, full_line);
	while (path[i])
		free(path[i++]);
	free(path);
	return (is_valid);
}

int	check_command(char **path, char *token, char **full_line)
{
	int		i;
	char	*ptemp;
	char	*full_path;

	i = 0;
	while (path && path[i++])
	{
		ptemp = ft_strjoin(path[i], "/\0");
		full_path = ft_strjoin(ptemp, token);
		free(ptemp);
		if (!full_path)
			return (printf("MALL_ERR, check_command, cmd_create.c\n"),
				MALL_ERR);
		if (access(full_path, F_OK) == 0)
		{
			*full_line = full_path;
			return (true);
		}
		free(full_path);
	}
	return (false);
}

t_cmd	*create_cmd_node(char ***tokens_ptr)
{
	char	**tokens;
	t_cmd	*cmd;
	int		j;

	tokens = *tokens_ptr;
	cmd = malloc(sizeof(t_cmd));
	cmd->ac = 0;
	while (tokens[cmd->ac] && ft_strncmp(tokens[cmd->ac], "|", 1) != 0
		&& ft_strncmp(tokens[cmd->ac], ">", 1) != 0
		&& ft_strncmp(tokens[cmd->ac], "<", 1))
		cmd->ac++;
	j = -1;
	cmd->av = malloc(sizeof(char *) * (cmd->ac + 1));
	if (cmd->av == NULL)
		return (printf("MALLOC_ERR, create_cmd_node\n"), NULL);
	while (++j < cmd->ac)
		cmd->av[j] = ft_strdup(tokens[j]);
	cmd->av[cmd->ac] = NULL;
	if (cmd->ac == 1)
		++(*tokens_ptr);
	else
		*tokens_ptr += (cmd->ac);
	return (cmd);
}

t_node	*wrap_cmd_in_node(t_cmd *cmd, char **full_line)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	if (node == NULL)
		return (NULL);
	node->type = CMD_NODE;
	cmd->infd = -128;
	cmd->outfd = -128;
	node->cmd = cmd;
	node->cmd->full_line = ft_strdup(*full_line);
	if (*full_line != NULL)
	{
		free(*full_line);
		*full_line = NULL;
	}
	node->redir = NULL;
	node->inred = NULL;
	node->outred = NULL;
	node->pipe = NULL;
	node->next = NULL;
	return (node);
}
