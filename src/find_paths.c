int 					get_next_step(t_list *queue)
{
	t_list	*tunnel;
	t_list	*room;

	room = queue->content;
	tunnel = ((t_room *)room->content)->tunnels;
	while (tunnel)
	{
		room = tunnel->content;
		((t_room *)room->content)->next = room;
		if (!add_to_queue(&queue, room))
			return (0);
		tunnel = tunnel->next;
	}
	return (1);
}

int				bfs(t_anthill *anthill, t_list *queue)
{
	if (!queue || end_found(queue))
		return (1);
	get_next_step(queue);

	return (bfs(anthill, queue));
}

int				find_paths(t_anthill *anthill)
{
	t_list	*queue;

	init_paths(anthill, queue);
	if (!bfs(anthill, queue))
		return (0);
}
