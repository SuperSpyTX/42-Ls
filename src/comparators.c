/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comparators.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkrause <jkrause@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/04 01:33:38 by jkrause           #+#    #+#             */
/*   Updated: 2017/12/04 01:56:37 by jkrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int				cmp_alpha(t_entry *a, t_entry *b)
{
	return (ft_strcmp(a->name, b->name));
}

int				cmp_time(t_entry *a, t_entry *b)
{
	return (b->mtim - a->mtim);
}

int				cmp_alpha_r(t_entry *a, t_entry *b)
{
	return (cmp_alpha(a, b) * -1);
}

int				cmp_time_r(t_entry *a, t_entry *b)
{
	return (cmp_time(a, b) * -1);
}

t_cmp			getcmp(t_flags *flags)
{
	if (flags->time_sort)
		return (flags->reverse == 1 ? (t_cmp)cmp_time_r : (t_cmp)cmp_time);
	else
		return (flags->reverse == 1 ? (t_cmp)cmp_alpha_r : (t_cmp)cmp_alpha);
}
