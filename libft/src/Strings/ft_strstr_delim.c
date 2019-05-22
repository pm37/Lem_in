/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr_delim.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwan-nan <bwan-nan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 19:36:45 by bwan-nan          #+#    #+#             */
/*   Updated: 2019/05/22 19:54:59 by bwan-nan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strstr_delim(const char *haystack, const char *needle, char delim)
{
	char	*found;
	int		len;

	if (haystack && needle)
	{
		if (!(found = ft_strstr(haystack, needle)))
			return (0);
		len = ft_strlen(needle);
		if (found == haystack)
		{
			if (!haystack[len] || haystack[len] == delim)
				return (1);
		}
		else
		{
			if (*(found - 1) == delim && (!found[len] || found[len] == delim))
				return (1);
		}
	}
	return (0);
}
