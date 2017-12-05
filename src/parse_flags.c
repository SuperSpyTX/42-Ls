/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_flags.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkrause <jkrause@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 18:20:34 by jkrause           #+#    #+#             */
/*   Updated: 2017/12/04 19:58:53 by jkrause          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void					write_err(char *str)
{
	char				*error;

	error = ft_sprintf("ft_ls: %s\nusage: ft_ls [-lartR] [file ...]", str);
	write(2, error, ft_strlen(error));
	free(error);
}

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

int						parse(char ltr, t_flags *flags)
{
	char				*error;

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
	else if (ltr == '1')
		return (1);
	else
	{
		error = ft_sprintf("illegal option -- %c", ltr);
		write_err(error);
		free(error);
		return (0);
	}
	return (1);
}

int						parse_arg(char *arg, t_flags *flags)
{
	arg = arg + 1;
	while (*arg != 0)
		if (!parse(*arg++, flags))
			return (0);
	return (1);
}
