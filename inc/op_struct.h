/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_struct.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcredibl <pcredibl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 10:19:34 by astripeb          #+#    #+#             */
/*   Updated: 2019/12/23 17:11:57 by pcredibl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OP_STRUCT_H
# define OP_STRUCT_H

/*
**	ДОПУСТИМЫЙ ТИП АРГУМЕНТОВ ДЛЯ ИНСТРУКЦИИ
**				   T_REG  T_DIR T_IND
**	DIR			00	 00     10	  00	-> 8
**	REG			00	 01  	00	  00	-> 16
**	DIR/IND		00	 00  	10	  11	-> 11
**	REG/DIR		00	 01  	10	  00	-> 24
**	REG/IND		00	 01  	00	  11	-> 19
**	REG/DIR/IND	00	 01		10	  11	-> 27
**
** СТРУКТУРА ИНСТРУКЦИИ
** name			- имя инструкции
** num_args		- количество небходимых аргументов
** args[1-3]	- аргументы
** code			- код инструкции
** cycles2go	- циклов до исполнения
** comment		- комментарий
** code_args	- код типов аргументов (1 - есть, 0 - нет)
** tdir_size	- размер аргумента T_DIR
*/

# define NUMBER_OF_INSTR	16
# define D					8
# define R					16
# define DI					11
# define RD					24
# define RI					19
# define RDI				27

typedef enum	e_bool
{
	FALSE,
	TRUE
}				t_bool;

enum			e_args
{
	FIRST,
	SECOND,
	THIRD
};

enum			e_op
{
	UNDEFINED,
	LIVE,
	LD,
	ST,
	ADD,
	SUB,
	AND,
	OR,
	XOR,
	ZJMP,
	LDI,
	STI,
	FORK,
	LLD,
	LLDI,
	LFORK,
	AFF
};

typedef struct	s_op
{
	char			name[6];
	int				num_args;
	char			args[3];
	int				code;
	int				cycles2go;
	char			code_args;
	char			tdir_size;
}				t_op;

t_bool			possible_arg(short op_code, short num_arg, t_arg_type type);

char			get_dir_size(short op_code);

t_op			get_op_struct(short op_code);

char			*get_op_name(short op_code);

int				get_instruct_code(char *name);

#endif
