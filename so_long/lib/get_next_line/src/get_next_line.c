/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mi■■■■■ <mi■■■■■@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 18:55:34 by minakim           #+#    #+#             */
/*   Updated: 2023/04/20 16:15:14 by mi■■■■■          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static t_list	*stash;
	char			*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = NULL;
	if (read_to_stash(fd, &stash) != CODE_OK)
	{
		free_stash(stash);
		stash = NULL;
		return (NULL);
	}
	if (extract_stash(stash, &line) != CODE_OK)
		return (NULL);
	clean_stash(&stash);
	if (line[0] == '\0')
	{
		free_stash(stash);
		stash = NULL;
		free(line);
		return (NULL);
	}
	return (line);
}

int	read_to_stash(int fd, t_list **stash)
{
	char	*buf;
	int		fd_readed;

	fd_readed = 1;
	while (!found_newline(*stash) && fd_readed != 0)
	{
		buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (buf == NULL)
			return (CODE_ERROR);
		fd_readed = read(fd, buf, BUFFER_SIZE);
		if (fd_readed == -1 || (*stash == NULL && fd_readed == 0))
		{
			free(buf);
			return (CODE_ERROR);
		}
		buf[fd_readed] = '\0';
		add_to_stash(stash, buf, fd_readed);
		free(buf);
	}
	return (CODE_OK);
}

void	add_to_stash(t_list **stash, char *buf, int fd_readed)
{
	t_list	*new_node;
	t_list	*last;
	int		i;

	new_node = malloc(sizeof(t_list));
	if (new_node == NULL)
		return ;
	new_node->next = NULL;
	new_node->content = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!new_node->content)
	{
		free(new_node);
		return ;
	}
	i = -1;
	while (i++ < fd_readed && buf[i])
		new_node->content[i] = buf[i];
	new_node->content[i] = '\0';
	if (*stash == NULL)
	{
		*stash = new_node;
		return ;
	}
	last = ft_lstlast(*stash);
	last->next = new_node;
}

int	extract_stash(t_list *stash, char **line)
{
	int	i;
	int	j;

	if (as_much_newline(stash, line) != CODE_OK)
		return (CODE_ERROR);
	if (*line == NULL)
		return (CODE_ERROR);
	j = 0;
	while (stash)
	{
		i = 0;
		while (stash->content[i])
		{
			if (stash->content[i] == '\n')
			{
				(*line)[j++] = stash->content[i];
				break ;
			}
			(*line)[j++] = stash->content[i++];
		}
		stash = stash->next;
	}
	(*line)[j] = '\0';
	return (CODE_OK);
}

void	clean_stash(t_list **stash)
{
	t_list	*last;
	t_list	*clean_node;
	int		i;
	int		j;

	clean_node = malloc(sizeof(t_list));
	if (stash == NULL || clean_node == NULL)
		return ;
	clean_node->next = NULL;
	last = ft_lstlast(*stash);
	i = 0;
	while (last->content[i] && last->content[i] != '\n')
		i++;
	if (last->content && last->content[i] == '\n')
		i++;
	clean_node->content = malloc(sizeof(char) \
		* ((ft_strlen(last->content) - i) + 1));
	if (clean_node->content == NULL)
		return ;
	j = 0;
	while (last->content[i])
		clean_node->content[j++] = last->content[i++];
	clean_node->content[j] = '\0';
	free_stash(*stash);
	*stash = clean_node;
}
