/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pimichau <pimichau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 14:38:19 by pimichau          #+#    #+#             */
/*   Updated: 2019/05/21 15:07:18 by pimichau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static void	init_anthill(t_anthill *anthill)
{
	anthill->rooms = NULL;
	anthill->room_qty = 0;
}

int			main(void)
{
	t_anthill	anthill;

	init_anthill(&anthill);
	if (!create_anthill(&anthill))
		return (ret_print(0, "ERROR"));
	return (0);
}
