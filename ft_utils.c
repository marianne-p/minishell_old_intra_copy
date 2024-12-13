/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*													+:+ +:+		 +:+	 */
/*   By: mpihur <marvin@42.fr>					  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/04/26 14:50:06 by mpihur			#+#	#+#			 */
/*   Updated: 2024/07/22 10:14:50 by mpihur           ###   ########.fr       */
/*																			*/
/* ************************************************************************** */

#include "minishell.h"

/*t_node	*find_last_node(t_node *node)
{
	while (node->next != NULL)
		node = node->next;
	return (&node);
}*/

char	*ft_strncpy(char *dest, const char *src, size_t n)
{
	size_t	i;

	i = 0;
	while (src[i] != '\0' && i < n)
	{
		dest[i] = src[i];
		++i;
	}
	while (i < n)
	{
		dest[i] = '\0';
		i++;
	}
	return (dest);
}

t_envv	*free_new(t_envv **new, char **str)
{
	if (str != NULL && *str != NULL)
		free(*str);
	free(*new);
	return (NULL);
}

t_envv	*split_envv(t_minish **msh_ptr, t_envv **env, char **envv, int i)
{
	while (envv[i])
	{
		ft_addenvv(env, envv[i], NULL);
		i++;
	}
	if (*env == NULL)
		ft_no_exit(msh_ptr, GEN_ERR, NULL,
			"Error copying EnvV, unable to start the shell\n");
	return (*env);
}

char	*ft_strjoinc(char const *s1, char const *s2)
{
	int		len_s1;
	int		len_s2;
	char	*s3;
	int		i;

	if (s1 == NULL && s2 == NULL)
		return (NULL);
	i = 0;
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	s3 = (char *)malloc(len_s1 + len_s2 + 1);
	if (s3 == NULL)
		return (NULL);
	while (i < len_s1 || i < len_s2)
	{
		if (i < len_s1)
			s3[i] = s1[i];
		if (i < len_s2)
			s3[i + len_s1] = s2[i];
		i++;
	}
	s3[len_s1 + len_s2] = '\0';
	return (s3);
}

int	check_validity(t_node *node, t_minish *msh)
{
	char	*fl;

	fl = NULL;
	if (node == NULL || node->cmd == NULL)
		return (false);
	while (node)
	{
		if (node->type != PIPE_NODE
			&& !is_valid_cmd(node->cmd->av[0], &fl, msh)
			&& !is_builtin(node->cmd->av[0]))
		{
			if (fl)
				free(fl);
			return (false);
		}
		if (fl != NULL)
			free(fl);
		fl = NULL;
		node = node->next;
	}
	return (true);
}
