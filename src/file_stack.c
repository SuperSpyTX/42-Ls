/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_stack.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkrause <jkrause@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 17:27:52 by jkrause           #+#    #+#             */
/*   Updated: 2017/12/03 11:41:29 by jkrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
** "Found the PHP Programmer"
*/

t_entry				**g_file_stack;
int					g_file_stacksize;

void				add_filestack(t_entry *arg)
{
	g_file_stack = expand_write(&arg, sizeof(t_entry*),
						g_file_stack, &g_file_stacksize);
}

t_entry				**get_filestack(void)
{
	long			empty;

	empty = 0L;
	g_file_stack = expand_write(&empty, sizeof(long),
						g_file_stack, &g_file_stacksize);
	g_file_stack[(g_file_stacksize / sizeof(t_entry*)) - 1] = 0;
	return (g_file_stack);
}

void				free_filestack(void)
{
	freebird_entries(g_file_stack);
	g_file_stack = 0;
	g_file_stacksize = 0;
}

int					get_filestack_count(void)
{
	return (g_file_stacksize / sizeof(char*));
}
