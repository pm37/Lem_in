/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwan-nan <bwan-nan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 12:46:37 by bwan-nan          #+#    #+#             */
/*   Updated: 2019/07/03 14:36:53 by pimichau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int		check_input(t_list *input)
{
	char	*line;

	if (!input)
		return (0);
	while (input)
	{
		line = ((t_input *)input->content)->line;
		if (!line || ft_strequ(line, "\0"))
			return (0);
		input = input->next;
	}
	return (1);
}

int				get_input(t_list **input)
{
	char	*line;
	t_list	*node;
	t_input	new;
	int		len;

	while ((len = get_next_line(0, &line)) > 0)
	{
		if (!(new.line = ft_strdup(line))
		|| !(node = ft_lstnew(&new, sizeof(t_input))))
		{
			ft_strdel(&new.line);
			ft_strdel(&line);
			return (0);
		}
		ft_lstappend(input, node);
		ft_strdel(&line);
	}
	return (check_input(*input));
}
