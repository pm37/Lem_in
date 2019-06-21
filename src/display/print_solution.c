#include "lem_in.h"

static void 	move_ants_from_start(t_list *ant, t_anthill *anthill, t_list *paths)
{
	t_list	*path;
	t_room	*dest_room;
	int		is_nexted;

	path = paths;
	is_nexted = 1;
	while (ant && path && ((t_path *)path->content)->sent > 0)
	{
		dest_room = ((t_path *)path->content)->room->content;
		((t_room *)anthill->start->content)->population--;
		dest_room->population++;
		dest_room->ant_id = ((t_room *)anthill->start->content)->ant_id++;
		if (!path->next || ((t_path *)path->next->content)->sent == 0)
			is_nexted = 0;
		ft_printf("L%d-%s%s", dest_room->ant_id,
		dest_room->name, is_nexted ? " " : "");
		((t_ant *)ant->content)->position = dest_room;
		((t_path *)path->content)->sent--;
		path = path->next;
		ant = ant->next;
	}
	ft_putchar('\n');
}

static void 	move_ants_forward(t_anthill *anthill, t_list *paths)
{
	t_list	*ant;
	t_room	*position;
	int		is_nexted;

	ant = anthill->ants;
	position = ((t_ant *)ant->content)->position;
	while (ant && ((t_ant *)ant->content)->position->end != 0)
	{
		position = ((t_ant *)ant->content)->position;
		if (position && position->next && (is_nexted = 1))
		{
			position->population--;
			((t_room *)position->next->content)->population++;
			((t_room *)position->next->content)->ant_id = position->ant_id;
			if (!ant->next || (((t_ant *)ant->next->content)->position->end == 0
			&& ((t_room *)anthill->start->content)->population == 0))
				is_nexted = 0;
			ft_printf("L%d-%s%s", position->ant_id,
			((t_room *)position->next->content)->name, is_nexted ? " " : "");
			position->ant_id = 0;
			((t_ant *)ant->content)->position = position->next->content;
		}
		ant = ant->next;
	}
	move_ants_from_start(ant, anthill, paths);
}

void       		print_output(t_anthill *anthill, t_list *paths)
{
  ((t_room *)anthill->start->content)->population = anthill->ant_qty;
  ((t_room *)anthill->start->content)->ant_id = 1;
  while (((t_room *)anthill->end->content)->population < anthill->ant_qty)
	  move_ants_forward(anthill, paths);
}
