/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwan-nan <bwan-nan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 11:59:01 by bwan-nan          #+#    #+#             */
/*   Updated: 2019/01/08 17:38:54 by bwan-nan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include "libft.h"
# define BUFF_SIZE 100

typedef struct		s_lst
{
	int				fd;
	char			*str;
	struct s_lst	*next;
}					t_lst;
int					get_next_line(const int fd, char **line);

#endif
