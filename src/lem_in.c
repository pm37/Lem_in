/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pimichau <pimichau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 14:38:19 by pimichau          #+#    #+#             */
/*   Updated: 2019/06/28 12:46:35 by pimichau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	get_option(t_anthill *anthill, int ac, char **av)
{
	if (ac == 2)
	{
		if (ft_strequ(av[1], "--paths"))
			anthill->option |= DISPLAY_PATHS;
		else if (ft_strequ(av[1], "--solution"))
			anthill->option |= ONLY_DISPLAY_SOLUTION;
	}
}

int			main(int ac, char **av)
{
	t_anthill	anthill;
	t_list		*input;
	t_list		*paths;

	paths = NULL;
	input = NULL;
	if (!get_input(&input))
		return (ret_free_input(&input));
	if (!create_anthill(&anthill, input))
		return (ret_print_free_all(&anthill, &input, &paths, "ERROR")); // free everything
	get_option(&anthill, ac, av);
	if (!(get_paths(&anthill, anthill.start, anthill.end, &paths)))
		return (ret_print(0, "ERROR"));
	init_ants(&anthill);
	if (!anthill.option)
		print_input(input);
	print_output(&anthill, paths);
	//ft_putnbrendl(anthill.rounds);
	return (ret_print_free_all(&anthill, &input, &paths, NULL));
}
