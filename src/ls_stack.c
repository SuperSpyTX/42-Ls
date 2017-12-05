/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_stack.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkrause <jkrause@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 17:27:52 by jkrause           #+#    #+#             */
/*   Updated: 2017/12/04 12:05:00 by jkrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
** "Found the PHP Programmer"
*/

void				add_ls_stack(t_entry *arg,
						t_entry ***ls_stack, int *ls_stacksize)
{
	if (*ls_stacksize > 0)
	{
		finish_ls_stack(ls_stack, ls_stacksize);
		(*ls_stack)[((*ls_stacksize / sizeof(t_entry*)) - 1)] = arg;
	}
	else
		*ls_stack = expand_write(&arg, sizeof(t_entry*),
						*ls_stack, ls_stacksize);
}

void				finish_ls_stack(t_entry ***ls_stack, int *ls_stacksize)
{
	long			empty;

	empty = 0;
	*ls_stack = expand_write(&empty, sizeof(long), *ls_stack, ls_stacksize);
}
