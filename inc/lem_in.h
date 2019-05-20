/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pimichau <pimichau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 16:14:17 by pimichau          #+#    #+#             */
/*   Updated: 2019/05/20 17:00:01 by pimichau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

typedef struct			t_room
{
	char				*name;
	int					id;
	int					x;
	int					y;
	t_room				*tunnels[];
	int					ant_nbr;
}						s_room;

typedef struct			t_anthill
{
	unsigned long long	ant_nbr;
	t_room				*rooms;
	int					room_nbr;
}						s_anthill;

int		init_anthill(t_anthill *anthill);
int		add_tunnel(char *line, t_anthill *anthill);

//tools :
int		ret_freetab(int ret, char **tab);
int		ret_print(int ret, char *msg);
void	free_tab(char **tab);

#endif
