/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkrause <jkrause@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 23:29:50 by jkrause           #+#    #+#             */
/*   Updated: 2017/12/03 22:12:12 by jkrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

size_t					get_numwidth(int t)
{
	int					width;

	width = 0;
	while (t > 0)
	{
		t = t / 10;
		width++;
	}
	return (width);
}

size_t					*get_maxwidths(t_entry **entries, t_flags *flags)
{
	size_t				g;
	size_t				*longest;

	g = -1;
	longest = (size_t*)ft_memalloc(sizeof(size_t) * 7);
	while (entries[++g] != 0)
	{
		if (entries[g]->skip || (flags->hidden_files == 0
					&& entries[g]->name[0] == '.'))
			continue;
		longest[0] = (longest[0] < ft_strlen(entries[g]->perms)
				? ft_strlen(entries[g]->perms) : longest[0]);
		longest[1] = (longest[1] < get_numwidth(entries[g]->links)
				? get_numwidth(entries[g]->links) : longest[1]);
		longest[2] = (longest[2] < ft_strlen(entries[g]->username)
				? ft_strlen(entries[g]->username) : longest[2]);
		longest[3] = (longest[3] < ft_strlen(entries[g]->groupname)
				? ft_strlen(entries[g]->groupname) : longest[3]);
		longest[4] = (longest[4] < get_numwidth(entries[g]->bsize)
				? get_numwidth(entries[g]->bsize) : longest[4]);
		longest[5] = (longest[5] < ft_strlen(entries[g]->date)
				? ft_strlen(entries[g]->date) : longest[5]);
	}
	return (longest);
}

void					get_full_date_str(t_entry *entry,
							time_t mtime, struct timespec spec)
{
	char			*dateorig;

	dateorig = ctime(&mtime);
	if (time(NULL) - spec.tv_sec >= 15724800)
		entry->date = ft_sprintf("%2.3s %2.2s % 4.5s", dateorig + 4,
				dateorig + 8, dateorig + 19);
	else
		entry->date = ft_sprintf("%.12s", dateorig + 4);
}

void					print_entry(t_entry *entry, t_flags *flags,
							size_t *widths)
{
	if (flags->detailed && widths)
	{
		ft_printf("%-*s %*d %-*s %-*s %*d %-*s %-s", widths[0],
				entry->perms, widths[1],
				entry->links, widths[2] + 1, entry->username,
				widths[3] + 1, entry->groupname, widths[4],
				entry->bsize, 12, entry->date,
				entry->name);
		if (entry->perms[0] == 'l')
			ft_printf(" -> %s", entry->filelink);
	}
	else
		ft_printf("%s", entry->name);
}

void					print_entries(t_entry **entries, t_flags *flags)
{
	int					i;
	size_t				*widths;

	i = -1;
	widths = (flags->detailed ? get_maxwidths(entries, flags) : 0);
	while (entries[++i] != 0)
	{
		if (entries[i]->skip || (entries[i]->name[0] == '.'
					&& !flags->hidden_files))
			continue;
		print_entry(entries[i], flags, widths);
		ft_printf("\n");
	}
	free(widths);
}
