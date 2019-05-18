/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwan-nan <bwan-nan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 11:56:09 by bwan-nan          #+#    #+#             */
/*   Updated: 2019/01/08 00:26:47 by bwan-nan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "get_next_line.h"

static int		update_line(t_lst *elem, char **line)
{
	char	*tmp;
	int		i;

	i = 0;
	tmp = elem->str;
	while (elem->str[i] && elem->str[i] != '\n')
		i++;
	if (i == 0)
		*line = ft_strnew(0);
	else
		*line = ft_strsub(elem->str, 0, i);
	if (ft_strchr(elem->str, '\n'))
		elem->str = ft_strdup(ft_strchr(elem->str, '\n') + 1);
	else
		elem->str = ft_strnew(0);
	free(tmp);
	return (1);
}

static t_lst	*ft_lstcreate(const int fd, t_lst **list)
{
	t_lst *tmp;

	if (!(tmp = (t_lst *)malloc(sizeof(t_lst))))
		return (NULL);
	tmp->fd = fd;
	tmp->str = NULL;
	tmp->next = *list;
	return (tmp);
}

static void		update_str(const int fd, char **str)
{
	int		ret;
	char	buffer[BUFF_SIZE + 1];
	char	*tmp;

	while ((ret = read(fd, buffer, BUFF_SIZE)) > 0)
	{
		buffer[ret] = '\0';
		tmp = *str;
		*str = ft_strjoin(*str, buffer);
		free(tmp);
		if (ft_strchr(*str, '\n'))
			break ;
	}
}

int				get_next_line(const int fd, char **line)
{
	static t_lst	*list = NULL;
	t_lst			*elem;

	if (read(fd, 0, 0) == -1 || BUFF_SIZE <= 0)
		return (-1);
	elem = list;
	while (elem)
	{
		if (elem->fd == fd)
			break ;
		elem = elem->next;
	}
	if (elem == NULL)
	{
		if (!(elem = ft_lstcreate(fd, &list)))
			return (-1);
		list = elem;
	}
	if (elem->str == NULL)
		elem->str = ft_strnew(0);
	if (!ft_strchr(elem->str, '\n'))
		update_str(fd, &(elem->str));
	if (elem->str[0])
		return (update_line(elem, line));
	return (0);
}
