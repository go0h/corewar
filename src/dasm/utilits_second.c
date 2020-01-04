/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilits_second.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/14 01:36:53 by vmormont          #+#    #+#             */
/*   Updated: 2020/01/04 16:14:13 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dasm.h"

void				ft_exit_dasm(int err)
{
	if (err == MALLOC_FAILURE)
		ft_fprintf(STDERR_FILENO, "Error: Can not allocate memory.\n");
	else if (err == READ_ERROR)
		ft_fprintf(STDERR_FILENO, "Error: Can not read file.\n");
	else if (err == ERROR_PROG_SIZE)
		ft_fprintf(STDERR_FILENO, "Error: Too big size for a champion.\n");
	else if (err == MAGIC_ERROR)
		ft_fprintf(STDERR_FILENO, "Error: No equal magic.\n");
	else
		perror("Error");
	exit(err);
}

void				print_usage(void)
{
	ft_printf("{eoc}Welcome to Disassembler!\n");
	ft_printf("Start the program correctly:\n\n");
	ft_printf("./dasm [filename.cor]\n\n");
	ft_printf("Have a nice day, My Friend!\n");
}
