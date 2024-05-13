/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mi■■■■■ <mi■■■■■@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 12:53:35 by minakim           #+#    #+#             */
/*   Updated: 2023/03/13 20:39:22 by mi■■■■■          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <stdlib.h>

/* t_list	*ft_lstlast(t_list *stash)
{
	t_list	*current;

	current = stash;
	while (current->next != NULL && current->next)
		current = current->next;
	return (current);
} */

/* if find new line, make `read to stash` function stoped */
int	found_newline(t_list *stash)
{
	t_list	*current;
	int		i;

	if (stash == NULL)
		return (0);
	current = ft_lstlast(stash);
	i = 0;
	while (current->content[i])
	{
		if (current->content[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

int	as_much_newline(t_list *stash, char **line)
{
	int	len;
	int	i;

	len = 0;
	while (stash)
	{
		i = 0;
		while (stash->content[i])
		{
			if (stash->content[i] == '\n')
			{
				len++;
				break ;
			}
			i++;
			len++;
		}
		stash = stash->next;
	}
	*line = (char *)malloc(sizeof(char) * (len + 1));
	if (!(*line))
		return (CODE_ERROR);
	return (CODE_OK);
}

void	free_stash(t_list *stash)
{
	t_list	*current;
	t_list	*next;

	current = stash;
	while (current)
	{
		free(current->content);
		next = current->next;
		free(current);
		current = next;
	}
}
/* 
size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}
 */