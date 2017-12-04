/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_flags.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkrause <jkrause@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 18:20:34 by jkrause           #+#    #+#             */
/*   Updated: 2017/12/02 21:19:18 by jkrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_flags					*init_flags(void)
{
	t_flags				*flags;

	flags = (t_flags*)ft_memalloc(sizeof(t_flags));
	flags->detailed = 0;
	flags->hidden_files = 0;
	flags->time_sort = 0;
	flags->recursion = 0;
	flags->reverse = 0;
	return (flags);
}

void					parse(char ltr, t_flags *flags)
{
	if (ltr == 'l')
		flags->detailed = 1;
	else if (ltr == 'a')
		flags->hidden_files = 1;
	else if (ltr == 'u')
		flags->time_sort = 1;
	else if (ltr == 'R')
		flags->recursion = 1;
	else if (ltr == 't')
		flags->time_sort = 1;
	else if (ltr == 'r')
		flags->reverse = 1;
}

void					parse_arg(char *arg, t_flags *flags)
{
	while (*arg != 0)
		parse(*arg++, flags);
}
