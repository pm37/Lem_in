#include "lem_in.h"

bool		start_linked_to_end(t_list *start, t_list *end)
{
	t_list	*tunnel;
	t_list	*dest_room;

	tunnel = ((t_room *)start->content)->tunnels;
	while (tunnel)
	{
		dest_room = ((t_tunnel *)tunnel->content)->room;
		if (dest_room == end)
			return (true);
		tunnel = tunnel->next;
	}
	return (false);
}

bool		init_the_only_path(t_list **paths, t_anthill *anthill)
{
	t_path	path;
	t_list	*new_path;

	path.room = anthill->end;
	path.len = 1;
	path.sent = anthill->ant_qty;
	path.id = 1;
	path.complete = true;
	if (!(new_path = ft_lstnew(&path, sizeof(t_path))))
		return (false);
	ft_lstprepend(paths, new_path);
	return (true);
}
