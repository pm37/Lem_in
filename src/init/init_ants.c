#include "lem_in.h"

int		init_ants(t_anthill *anthill)
{
	int		i;

	anthill->ants = NULL;
	i = anthill->ant_qty + 1;
	while (--i)
	{
		if (!add_ant(i, anthill))
			return (0);
	}
	return (1);
}
