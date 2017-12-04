/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkrause <jkrause@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 17:42:51 by jkrause           #+#    #+#             */
/*   Updated: 2017/12/04 01:40:19 by jkrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int				qsort_part(void **entries, int low,
					int high, t_cmp qsort_cmp)
{
	int			pivot;
	int			s;
	int			e;

	pivot = high;
	s = low;
	e = high;
	while (s < e)
	{
		while (s < high
			&& qsort_cmp(entries[s], entries[pivot]) <= 0)
			s++;
		while (e > low
				&& qsort_cmp(entries[e], entries[pivot]) > 0)
			e--;
		if (s < e)
			ft_swap((void**)&entries[s], (void**)&entries[e]);
	}
	return (e);
}

void			sort_entries(void **entries, int low,
					int high, t_cmp qsort_cmp)
{
	int			pivot;

	if (high == -1)
		high = count_entries((t_entry**)entries) - 1;
	if (low < high)
	{
		pivot = qsort_part((void*)entries, low, high, qsort_cmp);
		sort_entries(entries, low, pivot - 1, qsort_cmp);
		sort_entries(entries, pivot, high, qsort_cmp);
	}
}
