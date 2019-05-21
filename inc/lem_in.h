/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pimichau <pimichau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 16:14:17 by pimichau          #+#    #+#             */
/*   Updated: 2019/05/21 15:17:20 by pimichau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

typedef struct			s_tunnel
{
	t_room				*room;
}						t_tunnel;

typedef struct			s_room
{
	char				*name;
	int					id;
	int					x;
	int					y;
	int					population;
	t_list				*tunnels;
}						t_room;

typedef struct			s_anthill
{
	unsigned long long	ant_qty;
	int					room_qty;
	t_list				*rooms;
}						t_anthill;

int		create_anthill(t_anthill *anthill);
int		add_tunnel(char *line, t_anthill *anthill);

//tools :
int		ret_freetab(int ret, char **tab);
int		ret_print(int ret, char *msg);
void	free_tab(char **tab);

#endif
