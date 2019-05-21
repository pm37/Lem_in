/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversions.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bwan-nan <bwan-nan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/01 22:21:01 by bwan-nan          #+#    #+#             */
/*   Updated: 2019/05/21 17:16:47 by bwan-nan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONVERSIONS_H
# define CONVERSIONS_H

int					ft_atoi(const char *nptr);
unsigned long long 	ft_atoull(const char *nptr);
int					ft_binatoi(char *str);
char				*ft_itoa(int n);
char				*ft_itoa_base(int value, int base);
char				*ft_llitoa(long long nb);
char				*ft_llitoa_base(long long nb, int base);
char				*ft_ullitoa(unsigned long long nb);
char				*ft_ullitoa_base(unsigned long long nb, int base);

#endif
