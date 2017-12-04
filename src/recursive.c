/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recursive.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkrause <jkrause@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/03 17:10:48 by jkrause           #+#    #+#             */
/*   Updated: 2017/12/04 01:52:42 by jkrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void			write_error(char *name)
{
	char		*error;

	error = ft_sprintf("ft_ls: %s: %s\n", name, strerror(errno));
	write(2, error, ft_strlen(error));
	free(error);
}

void			process_directory(char *dir, t_flags *flags)
{
	t_entry		**entries;
	int			blksize;

	entries = get_entries(dir, flags);
	sort_entries((void**)entries, 0, -1, getcmp(flags));
	blksize = get_total_blksize(entries, flags);
	if (flags->detailed == 1 && blksize > 0)
		ft_printf("total %d\n", blksize);
	print_entries(entries, flags);
	if (flags->recursion)
		process_ls_stack_entries(entries, flags);
	freebird_entries(entries);
}

void			process_ls_stack_entries(t_entry **entries, t_flags *flags)
{
	int			i;
	char		*join;

	i = -1;
	while ((entries[++i] != 0))
	{
		if (entries[i]->skip == 0 && entries[i]->perms[0] == 'd'
				&& !ft_strequ(entries[i]->name, ".")
				&& !ft_strequ(entries[i]->name, "..")
				&& ft_strlen(entries[i]->name) > 0)
		{
			if (entries[i]->name[0] == '.' && !flags->hidden_files)
				continue;
			join = path_join(entries[i]->directory, entries[i]->name);
			if (read_ls_arg(join, flags) == 2)
			{
				ft_printf("\n%s:\n", join);
				if (count_dir(join) == 0)
					write_error(entries[i]->name);
				else
					process_directory(join, flags);
			}
			free(join);
		}
	}
}

void			process_clusterfuck(char **ls_stack, int ls_stack_size,
					t_flags *flags, int argc)
{
	int			count;
	int			i;
	int			first;

	i = -1;
	first = (get_filestack_count() > 1 ? 1 : 0);
	count = (ls_stack_size / sizeof(char*));
	finish_ls_stack(&ls_stack, &ls_stack_size);
	if (!ls_stack || count < 1)
		return ;
	// TODO: Port over generic version of qsort!
	sort_ls_stack_alpha(ls_stack, ls_stack_size);
	while (++i < count)
	{
		if (first != 0)
			ft_printf("\n");
		first = 1;
		if (get_filestack_count() > 1 || count > 1 || argc > 3)
			ft_printf("%s:\n", ls_stack[i]);
		if (count_dir(ls_stack[i]) == 0)
			write_error("");
		else
			process_directory(ls_stack[i], flags);
	}
}
