/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwan-nan <bwan-nan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 19:12:54 by bwan-nan          #+#    #+#             */
/*   Updated: 2019/06/12 23:48:22 by bwan-nan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		del_steps(void *content, size_t size)
{
	if (content && size)
		;
}
/*
void			del_path(void *content, size_t size)
{
	t_path	*path;
	t_list	*steps;

	path = (t_path *)content;
	steps = path->steps;
	if (content && size)
		ft_lstdel(&steps, del_steps);
}
*/
