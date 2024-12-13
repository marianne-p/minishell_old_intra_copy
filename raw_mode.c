/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raw_mode.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpihur <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 16:00:30 by mpihur            #+#    #+#             */
/*   Updated: 2024/07/18 16:22:02 by mpihur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*
#include "minishell.h"
#include <termios.h>

struct termios orig_termios;

void	disable_raw_mode(void)
{
    if (isatty(STDIN_FILENO))
	{
        tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
    }
}

void	enable_raw_mode(void)
{
	struct termios raw; 
    
	if (isatty(STDIN_FILENO)) 
	{
        tcgetattr(STDIN_FILENO, &orig_termios);

        raw = orig_termios;
        raw.c_lflag &= ~(ICANON);
        tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
    }
}*/
