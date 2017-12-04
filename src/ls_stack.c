/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_stack.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkrause <jkrause@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 17:27:52 by jkrause           #+#    #+#             */
/*   Updated: 2017/12/03 17:07:01 by jkrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
** "Found the PHP Programmer"
*/

void				add_ls_stack(char *arg, char ***ls_stack, int *ls_stacksize)
{
	if (*ls_stacksize > 0)
	{
		(*ls_stack)[((*ls_stacksize / sizeof(char*)) - 1)] = arg;
		finish_ls_stack(ls_stack, ls_stacksize);
	}
	else
		*ls_stack = expand_write(&arg, sizeof(char*), *ls_stack, ls_stacksize);
}

void				finish_ls_stack(char ***ls_stack, int *ls_stacksize)
{
	long			empty;

	empty = 0;
	*ls_stack = expand_write(&empty, sizeof(long), *ls_stack, ls_stacksize);
}

void				sort_ls_stack_alpha(char **ls_stack, int ls_stacksize)
{
	int				sorted;
	int				i;

	i = -1;
	sorted = 0;
	while (ls_stack[++i] != 0)
	{
		if (ls_stack[i + 1] != 0 && ls_stack[i] != 0 &&
				ft_strcmp(ls_stack[i + 1], ls_stack[i]) < 0)
		{
			ft_swap((void**)&ls_stack[i], (void**)&ls_stack[i + 1]);
			sorted = 1;
		}
	}
	if (sorted)
		return (sort_ls_stack_alpha(ls_stack, ls_stacksize));
}
