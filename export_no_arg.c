/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_no_arg.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpihur <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 15:58:51 by mpihur            #+#    #+#             */
/*   Updated: 2024/07/22 10:22:40 by mpihur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	swap(t_envv *a, t_envv *b)
{
	char	*temp_key;
	char	*temp_value;

	temp_key = a->key;
	temp_value = a->value;
	a->key = b->key;
	a->value = b->value;
	b->key = temp_key;
	b->value = temp_value;
}

void	sort_list(t_envv **start_ptr, t_envv *lptr)
{
	int		swapped;
	t_envv	*start;
	t_envv	*ptr1;

	start = *start_ptr;
	if (start == NULL)
		return ;
	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		ptr1 = start;
		while (ptr1->next != lptr)
		{
			if (ft_strncmp(ptr1->key, ptr1->next->key, 3) > 0)
			{
				swap(ptr1, ptr1->next);
				swapped = 1;
			}
			ptr1 = ptr1->next;
		}
		lptr = ptr1;
	}
}

t_envv	*copy_node(t_envv *node)
{
	t_envv	*new_node;

	new_node = malloc(sizeof(t_envv));
	new_node->key = ft_strdup(node->key);
	new_node->value = ft_strdup(node->value);
	new_node->next = NULL;
	return (new_node);
}

t_envv	*copy_list(t_envv *head)
{
	t_envv	*new_head;
	t_envv	*current;

	if (head == NULL)
		return (NULL);
	new_head = copy_node(head);
	current = new_head;
	while (head->next)
	{
		head = head->next;
		current->next = copy_node(head);
		current = current->next;
	}
	return (new_head);
}
/*
void print_all_envv(t_envv *head) {
	t_envv *copy = copy_list(head);
	sort_list(&copy, NULL);
	t_envv *temp = copy;
	while (temp) {
		printf("declare -x %s = \"%s\"\n", temp->key, temp->value);
		temp = temp->next;
	}
	// Don't forget to free the copied list
	free_list(copy);
}*/

void	print_all_envv(t_envv *head)
{
	t_envv	*copy;
	t_envv	*temp;

	copy = copy_list(head);
	sort_list(&copy, NULL);
	temp = copy;
	while (temp)
	{
		printf("declare -x %s = \"%s\"\n", temp->key, temp->value);
		copy = temp;
		temp = temp->next;
		free_envv(&copy);
	}
}

/* #include <stdio.h>
#include "./Libft/libft.h"
#include <stdlib.h>

extern char **environ;

static void	ft_swap(char **arr, int l, int r)
{
	char	*temp;

	temp = arr[l];
	arr[l] = arr[r];
	arr[r] = temp;
}

static int	partition(char **arr, int l, int r, char *pivot)
{
	while (l <= r)
	{
		while (ft_strncmp(arr[l], pivot, 32) < 0)
			l++;
		while (ft_strncmp(arr[r], pivot, 32) > 0)
			r--;
		if (l <= r)
		{
			ft_swap(arr, l, r);
			l++;
			r--;
		}
	}
	return (l);
}

void	quick_sort(char **arr, int l, int r)
{
	char	*pivot;
	int		index;

	if (l >= r)
		return ;
	pivot = arr[(l + r) / 2];
	index = partition(arr, l, r, pivot);
	quick_sort(arr, l, index - 1);
	quick_sort(arr, index, r);
}

void print_exported_vars() {
    for (char **env = environ; *env != 0; env++) {
        char *thisEnv = *env;
        printf("declare -x %s\n", thisEnv);
    }
}

int	ft_env(void) 
{
	char			**sort;
	unsigned int	i;

	i = 0;
	while (environ[i])
		i++;
	sort = malloc(sizeof(char *) * (i + 2));
	i = 0;
	if (!sort)
		return (-1);
	while (environ[i])
	{
		sort[i] = ft_strdup(environ[i]);
		i++;
	}
	sort[i] = NULL;		
	quick_sort(sort, 0, i);
    print_exported_vars();
	printf("\n");
	i = 0;
	while (sort[i])
		printf("declare -x %s\n", sort[i++]);
	free(sort);
    return (0);
}*/
