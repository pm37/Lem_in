/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compare_steps.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwan-nan <bwan-nan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 16:55:59 by bwan-nan          #+#    #+#             */
/*   Updated: 2019/06/04 16:59:25 by bwan-nan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_list		*compare_steps(t_list *l1, t_list *l2)
{
	t_list	*a;
	t_list	*b;

	while (l1 && l2)
	{
		a = l1->content;
		b = l2->content;
		if (((t_room *)a->content) != ((t_room *)b->content))
			return (l1);
		l1 = l1->next;
		l2 = l2->next;
	}
	return (NULL);
}
