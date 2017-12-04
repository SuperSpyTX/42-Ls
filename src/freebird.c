/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freebird.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkrause <jkrause@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/03 19:52:50 by jkrause           #+#    #+#             */
/*   Updated: 2017/12/04 01:36:10 by jkrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
** Mandatory puns included - there were so many memory leaks.
** Approved by @anazar.
*/

void						freebird_entry(t_entry *entry)
{
	t_freebird_entry		fbentry;
	int						i;

	fbentry.entry = *entry;
	i = -1;
	while (++i < 7)
		if (fbentry.addresses[i] != 0)
			free(fbentry.addresses[i]);
	free(entry);
}

void						freebird_entries(t_entry **entries)
{
	int						g;

	g = -1;
	while (entries[++g] != 0)
		freebird_entry(entries[g]);
	free(entries);
}

void						freebird_chararray(char **arg)
{
	int						g;

	g = -1;
	while (arg[++g] != 0)
		free(arg[g]);
	free(arg);
}
