/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pimichau <pimichau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 14:38:19 by pimichau          #+#    #+#             */
/*   Updated: 2019/07/02 11:03:14 by bwan-nan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	get_option(t_anthill *anthill, int ac, char **av)
{
	if (ac == 2)
	{
		if (ft_strequ(av[1], "--paths"))
			anthill->option |= DISPLAY_PATHS;
		else if (ft_strequ(av[1], "--solution"))
			anthill->option |= ONLY_DISPLAY_SOLUTION;
	}
}

int		main(int ac, char **av)
{
	t_anthill	anthill;
	t_list		*input;
	t_list		*paths;

	paths = NULL;
	input = NULL;
	if (!get_input(&input))
		return (free_input(&input, -1));
	if (!create_anthill(&anthill, input))
		return (print_and_free(&anthill, &input, &paths, "ERROR"));
	get_option(&anthill, ac, av);
	if (!(get_paths(&anthill, anthill.start, anthill.end, &paths)))
		return (print_and_free(&anthill, &input, &paths, "ERROR"));
	init_ants(&anthill);
	if (!anthill.option)
		print_input(input);
	print_output(&anthill, paths);
	return (print_and_free(&anthill, &input, &paths, NULL));
}
