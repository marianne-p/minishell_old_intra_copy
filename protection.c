/* ************************************************************************** */
/*				                                                              */
/*				                                          :::      ::::::::   */
/*	 protection.c			                           :+:      :+:    :+:   */
/*				                                      +:+ +:+         +:+     */
/*	 By: mpihur <marvin@42.fr>			          +#+  +:+       +#+        */
/*				                                  +#+#+#+#+#+   +#+           */
/*	 Created: 2024/07/22 10:02:09 by mpihur			#+#    #+#             */
/*	 Updated: 2024/07/22 10:02:09 by mpihur		   ###   ########.fr	   */
/*				                                                              */
/* ************************************************************************** */

#include "minishell.h"

/*
*	 Protection from "" infinite loop
*	 Loop though input received from the readline, if there is match looking like
*	 <white_space>""<white_space>
*	 Remove the "" before parsing
*/

char	*copy_without_quote(char *input, int i, int len, char *new_input)
{
	int	k;

	k = 0;
	if (len <= 2)
		return (NULL);
	new_input = malloc((len - 1) * sizeof(char));
	if (new_input == NULL)
		return (NULL);
	while (input[k] && i != k)
	{
		new_input[k] = input[k];
		k++;
	}
	k += 2;
	while (input[k])
		new_input[i++] = input[k++];
	new_input[i] = '\0';
	return (new_input);
}

char	*remove_one_quotemark(char *input, int i, char *new_input, int j)
{
	int		k;
	char	*the_quote;

	new_input = malloc(sizeof(char) * (ft_strlen(input) - 1));
	if (new_input == NULL)
		return (NULL);
	while (++j != i)
		new_input[j] = input[j];
	k = j;
	j++;
	the_quote = ft_strrchr(input + i, '"');
	while (input[j] && input + j != the_quote)
		new_input[k++] = input[j++];
	j++;
	while (input[j])
		new_input[k++] = input[j++];
	new_input[k] = '\0';
	return (new_input);
}

int	find_the_quote(char *input, int i)
{
	while (input[i] && input[i + 1])
	{
		if (ft_strncmp(input + i, "\"\"", 2) == 0)
			return (true);
		i++;
	}
	return (false);
}

void	remove_dbl_quote(char **input_ptr, char *input, int *i)
{
	if (ft_strncmp(input + *i, "\"\"", 2) == 0)
	{
		if ((*i - 1 < 0 || (*i - 1 >= 0
					&& is_white_space(input[*i - 1]) == true))
			&& (!input[*i + 2] || (input[*i + 2]
					&& is_white_space(input[*i + 2]) == true)))
		{
			input = copy_without_quote(input, *i, ft_strlen(input), NULL);
			free(*input_ptr);
			*input_ptr = input;
			*i = 0;
		}
	}
}

void	remove_useless_quotes(char **input_ptr, char *input, int i)
{
	while (input[i] && input[i + 1])
	{
		remove_dbl_quote(input_ptr, input, &i);
		input = *input_ptr;
		if (input == NULL)
			break ;
		if (input && input[i] && ft_strncmp(input + i, "\"\"", 2) == 0
			&& (input[i + 2]
				&& find_the_quote(input, i + 2) == true))
		{
			input = remove_one_quotemark(input, i, NULL, -1);
			free(*input_ptr);
			*input_ptr = input;
			i = 0;
		}
		if (input == NULL)
			break ;
		i++;
	}
}
