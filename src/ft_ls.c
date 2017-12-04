/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkrause <jkrause@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 15:36:50 by jkrause           #+#    #+#             */
/*   Updated: 2017/12/04 01:51:40 by jkrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char			**g_dirstack;
int				g_dirstack_size;

void			read_arg(char *arg, t_flags *flags)
{
	int			result;

	result = read_ls_arg(arg, flags);
	if (result < 1)
		return ;
	else if (result == 1)
		add_filestack(get_entry(arg, flags));
	else if (result == 2)
		add_ls_stack(ft_strdup(arg), &g_dirstack, &g_dirstack_size);
}

void			process_filestack(t_flags *flags)
{
	t_entry		**filestack;
	int			count;

	count = get_filestack_count();
	filestack = get_filestack();
	if (!filestack || count < 1)
		return ;
	if (count > 1)
		sort_entries((void**)filestack, 0, count, getcmp(flags));
	print_entries(filestack, flags);
	free_filestack();
}

int				main(int argc, char **argv)
{
	t_flags		*flags;
	int			i;

	flags = init_flags();
	i = 0;
	while (++i < argc)
	{
		if (argv[i][0] == '-')
			parse_arg(argv[i], flags);
		else
			read_arg(argv[i], flags);
	}
	i--;
	process_filestack(flags);
	process_clusterfuck(g_dirstack, g_dirstack_size, flags, argc);
	free(flags);
	return (0);
}
