/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ret_freetab.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwan-nan <bwan-nan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/01 16:21:55 by bwan-nan          #+#    #+#             */
/*   Updated: 2019/07/01 16:22:26 by bwan-nan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void		free_tab(char **tab)
{
	int i;

	i = -1;
	while(tab[++i])
		free(tab[i]);
	free(tab);
}

int				ret_freetab(int ret, char **tab)
{
	free_tab(tab);
	return (ret);
}
