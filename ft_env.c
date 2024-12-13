/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpihur <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 16:07:25 by mpihur            #+#    #+#             */
/*   Updated: 2024/07/25 19:06:10 by mpihur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	busy_wait(void)
{
	volatile int	dummy;

	dummy = 0;
	while (dummy != 10000000)
	{
		dummy++;
	}
}

void	ft_env(t_minish *minish)
{
	t_envv	*env;

	env = minish->env;
	while (env != NULL)
	{
		printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
}
