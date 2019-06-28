/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pimichau <pimichau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 16:14:17 by pimichau          #+#    #+#             */
/*   Updated: 2019/06/28 12:41:27 by pimichau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "libft.h"
# include <stdbool.h>

# define ONLY_DISPLAY_SOLUTION	2
# define DISPLAY_PATHS		4

typedef struct			s_room
{
	char				*name;
	int					x;
	int					y;
	int					end;
	int 				path_id;
	int 				ant_id;
	unsigned int	 		population;
	int 				new_path_id;
	bool 				deviation;
	bool				visited;
	bool 				dead_end;
	t_list			*next;
	t_list			*new_next;
	t_list			*previous;
	t_list			*tunnels;
}						t_room;

typedef struct			s_anthill
{
	unsigned int			ant_qty;
	int				room_qty;
	int 			rounds;
	unsigned int		option;
	int 			id;
	t_list				*rooms;
	t_list				*start;
	t_list				*end;
	t_list				*ants;
}						t_anthill;

typedef struct			s_tunnel
{
	int			usage;
	t_list			*room;
}				t_tunnel;

typedef struct			s_path
{
	int 							id;
	int 							sent;
	int 							len;
	bool 							complete;
	t_list						*room;
}										t_path;

typedef struct 			s_ant
{
	int 							id;
	t_room 						*position;
} 									t_ant;

typedef struct			s_input
{
	char			*line;
}				t_input;

/*
** ----------------------------- INIT ------------------------------------------
*/
int		create_anthill(t_anthill *anthill, t_list *input);
int		init_paths(t_list **paths, t_list *start, unsigned int option);
int		init_ants(t_anthill *anthill);
/*
** ------------------------------ ADD ------------------------------------------
*/
int		add_room(t_anthill *anthill, t_list **input);
int		add_tunnel(t_anthill *anthill, char *line);
int		add_step(t_list **steps, t_list *room);
int		add_path(t_list **paths);
int		add_ant(int id, t_anthill *anthill);
/*
** ----------------------------- ALGO -----------------------------------------
*/
bool	get_paths(t_anthill *anthill, t_list *start
		, t_list *end, t_list **paths);
bool	bfs(t_list *start, t_list *end, t_list **queue);
int	test_solution(t_anthill *anthill, t_list *paths
	, unsigned int ant_qty);
void	update_data(t_anthill *anthill, int rounds, t_list **paths);
void	complete_paths(t_list **paths);
void	set_tunnels_usage(t_list *end);
int	init_queue(t_list **queue, t_list *start);
int	complete_queue(t_list *queue, t_list *end);
bool	going_to_deviate(t_list *current, t_list *room);
bool	deviation_reaches_end(t_list *deviation_room, t_list *end);
bool	start_linked_to_end(t_list *start, t_list *end);
bool	init_the_only_path(t_list **paths, t_anthill *anthill);
/*
** ---------------------------- DISPLAY ----------------------------------------
*/
void	print_paths(t_list *paths);
void	print_steps(t_list *steps);
void    print_output(t_anthill *anthill, t_list *paths);
void	print_input(t_list *input);
/*
** ----------------------------- CLEAN -----------------------------------------
*/
void	clean_paths(t_anthill *anthill);
int		check_dead_end(t_anthill *anthill);
void 	del_steps(void *content, size_t size);
/*
** ---------------------------- TOOLS ------------------------------------------
*/
int		ret_freetab(int ret, char **tab);
int		ret_freeline(int ret, char **line);
int		ret_print(int ret, char *msg);
void	free_tab(char **tab);
int		copy_path(void *dest, void *src);
int		copy_steps(void *dest, void *src);
t_list	*compare_steps(t_list *l1, t_list *l2);
void	del_path(void *content, size_t size);
int	get_input(t_list **input);
int	ret_free_input(t_list **input);
int	is_a_comment(char *line);
int	is_an_end_room(char *line);
int	ret_print_free_all(t_anthill *ath, t_list **input, t_list **paths, char *msg);


#endif
