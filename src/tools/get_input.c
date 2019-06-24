/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwan-nan <bwan-nan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 12:46:37 by bwan-nan          #+#    #+#             */
/*   Updated: 2019/06/24 12:59:28 by bwan-nan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int	get_input(t_list **input)
{
	char	*line;
	t_list	*node;
	t_input	new;

	while (get_next_line(0, &line))
	{
		if (!(new.line = ft_strdup(line)))
			return (0);
		if (!(node = ft_lstnew(&new, sizeof(t_input))))
			return (0);
		ft_lstappend(input, node);
		ft_strdel(&line);
	}
	return (1);
}
