/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/14 01:57:32 by vmormont          #+#    #+#             */
/*   Updated: 2020/01/04 16:16:08 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dasm.h"

int				main(int argc, char **argv)
{
	t_bool		error;
	int			index;

	error = FALSE;
	index = 1;
	while (index < argc)
	{
		if (is_filename_extension(argv[index], ".cor"))
			disassemble(argv[index]);
		else
		{
			error = TRUE;
			ft_printf("{red}ERROR: invalid filename extension: %s{eoc}\n",\
						argv[index]);
		}
		++index;
	}
	if (error || argc == 1)
		print_usage();
	return (EXIT_SUCCESS);
}
