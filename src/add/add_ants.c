#include "lem_in.h"

int		add_ant(int id, t_anthill *anthill)
{
	t_ant	ant;
	t_list	*new_ant;

	ant.id = id;
	ant.position = anthill->start->content;
	if (!(new_ant = ft_lstnew(&ant, sizeof(t_ant))))
		return (0);
	ft_lstprepend(&anthill->ants, new_ant);
	return (1);
}
