/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_unc_unstr.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlutsyk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/09 16:10:33 by tlutsyk           #+#    #+#             */
/*   Updated: 2018/01/09 16:10:35 by tlutsyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

/*
*** check MB_CUR_MAX in %C(UNICODE)
*/

int					ft_cur_max(unsigned int *a, t_struct *flags)
{
	if (MB_CUR_MAX == 1 && (*a > 127 && *a < 256))
	{
		write(1, a, 1);
		flags->write_count += 1;
		return (-1);
	}
	if (MB_CUR_MAX == 1 && *a > 255)
	{
		flags->un_costil = -1;
		return (-1);
	}
	return (1);
}

/*
*** there i find min_size of output
*/

int					ft_min_pole_s(t_struct *flags, int length)
{
	if (flags->min_size == -1)
		return (0);
	if (flags->min_size <= length)
		return (0);
	return (flags->min_size - length);
}

/*
*** find print size malloc char * and free and write res when size 0
*/

void				ft_presizion_memory(t_struct *flags, char **a, uint64_t b)
{
	char			*src;

	src = NULL;
	flags->count_nb = ft_strlen(*a);
	if (flags->presizion > flags->count_nb)
	{
		src = ft_strnew(flags->presizion);
		ft_memset(src, '0', flags->presizion - flags->count_nb);
		src = ft_strcat(src, *a);
		ft_strdel(a);
		*a = src;
	}
	if (b == 0 && flags->presizion == 0)
	{
		ft_strdel(&src);
		*a = ft_strnew(0);
	}
}
