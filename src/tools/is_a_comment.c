/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_a_comment.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwan-nan <bwan-nan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 13:05:53 by bwan-nan          #+#    #+#             */
/*   Updated: 2019/06/24 13:09:54 by bwan-nan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int	is_a_comment(char *line)
{
	return (line[0] == '#');
}

int	is_an_end_room(char *line)
{
	return (ft_strequ("##start", line) || ft_strequ("##end", line));
}
