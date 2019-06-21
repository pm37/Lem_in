#include "lem_in.h"

static void 	move_ants_from_start(t_anthill *anthill, t_list *paths)
{
	t_list	*path;
	t_room	*dest_room;

	path = paths;
	while (path)
	{
		dest_room = ((t_path *)paths->content)->room->content;
		if (((t_path *)path->content)->sent-- >= 0)
		{
			((t_room *)anthill->start->content)->population--;
			dest_room->population++;
			dest_room->ant_id = ((t_room *)anthill->start->content)->ant_id++;
			ft_printf("L%d-%s ", dest_room->ant_id,
			dest_room->name);
		}
		path = path->next;
	}
	ft_putendl("\nla");
	ft_putchar('\n');
}

static void 	move_ants_forward(t_anthill *anthill, t_list *paths)
{
	t_list	*ant;
	t_room	*position;

	ant = anthill->ants;
	while (((t_ant *)ant->content)->position->end != 0)
	{
		position = ((t_ant *)ant->content)->position;
		if (position->next)
		{
			ft_putendl("ici");
			position->population--;
			((t_room *)position->next->content)->population++;
			((t_room *)position->next->content)->ant_id = position->ant_id;
			ft_printf("L%d-%s ", position->ant_id,
			((t_room *)position->next->content)->name);
			position->ant_id = 0;
		}
		ant = ant->next;
	}
	move_ants_from_start(anthill, paths);
}

void       		print_output(t_anthill *anthill, t_list *paths)
{
  ((t_room *)anthill->start->content)->population = anthill->ant_qty;
  ((t_room *)anthill->start->content)->ant_id = 1;
  while (((t_room *)anthill->end->content)->population < anthill->ant_qty)
  {
	ft_putendl("there");
	ft_printf("ant_qty = %d | end_ant_qty = %d",
	anthill->ant_qty,
	((t_room *)anthill->end->content)->population);
    move_ants_forward(anthill, paths);
  }
}
