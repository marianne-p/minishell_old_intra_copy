/* ************************************************************************** */
/*			                                                                */
/*			                                            :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*			                                        +:+ +:+         +:+     */
/*   By: mpihur <marvin@42.fr>			          +#+  +:+       +#+        */
/*			                                    +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 14:50:16 by mpihur			#+#    #+#             */
/*   Updated: 2024/07/25 19:28:21 by mpihur           ###   ########.fr       */
/*			                                                                */
/* ************************************************************************** */

#include "minishell.h"

volatile short	g_signals[2];

/*
void	printf_nodes(t_node *node)
{
	while (node)
	{
		if (node->type == 0)
		{
			printf("CMD_NODE, ");
			printf("%s\n", node->cmd->av[0]);
		}
		if (node->type == 1)
			printf("REDIR_NODE\n");
		if (node->type == 2)
			printf("PIPE_NODE\n");
		node = node->next;
	}
}*/

int	handle_input(char **input, t_minish **msh_ptr)
{
	if (*input == NULL)
	{
		free(*input);
		return (ft_exit(NULL, msh_ptr, 1, NULL), 1);
	}
	if (*input && **input)
		add_history(*input);
	return (SUCS);
}

static int	is_pipe_end(char *input)
{
	int	len;

	len = ft_strlen(input) - 1;
	if (!input || input[0] == '\0' || input[len] == '\004')
		return (0);
	while (len > -1 && input[len]
		&& ((input[len] > 8 && input[len] < 14) || input[len] == ' '))
		len--;
	if (len > 0 && input[len] && input[len] == '|'
		&& ((input[len - 1] > 8 && input[len - 1] < 14)
			|| input[len - 1] == ' '))
		return (true);
	return (0);
}

static char	*add_input(char *input, char *temp, char *remove)
{
	while (is_pipe_end(input) == true)
	{
		rl_on_new_line();
		temp = input;
		input = ft_strjoin(input, " ");
		free (temp);
		temp = readline(" > ");
		remove = input;
		input = ft_strjoin(remove, temp);
		free (remove);
		free (temp);
		rl_replace_line(input, 0);
	}
	return (input);
}

void	main_loop(t_minish **msh_ptr, char *input, char *temp, char *remove)
{
	while (true)
	{
		if (g_signals[0] == 128 + SIGSEGV)
			ft_exit(NULL, msh_ptr, 128 + SIGSEGV, NULL);
		if (g_signals[1] == true)
			continue ;
		g_signals[1] = false;
		rl_on_new_line();
		input = readline("minishell> ");
		if (is_pipe_end(input) == true)
			input = add_input(input, temp, remove);
		if (g_signals[0] > 0)
			(*msh_ptr)->status = g_signals[0];
		if (handle_input(&input, msh_ptr) > 0
			|| token_exec(&input, (*msh_ptr)->tokens,
				msh_ptr, (*msh_ptr)->node) > 0)
		{
			if (input != NULL)
				free(input);
			continue ;
		}
		if (input != NULL)
			free(input);
	}
}

int	main(int argc, char **argv, char **envv)
{
	t_minish		*msh;

	(void)argc;
	(void)argv;
	setup_signal_handlers();
	msh = malloc(sizeof(t_minish));
	if (!msh)
		return (ft_no_exit(NULL, MALL_ERR, NULL,
				"Failed memory alloc for MINISH structure"));
	msh->env = NULL;
	msh->envv = envv;
	msh->node = NULL;
	msh->env = split_envv(&msh, &(msh->env), msh->envv, 0);
	msh->status = 0;
	msh->tokens = NULL;
	main_loop(&msh, NULL, NULL, NULL);
	return (0);
}
