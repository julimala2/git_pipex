/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmalaval <jmalaval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 13:06:45 by jmalaval          #+#    #+#             */
/*   Updated: 2025/07/04 16:26:45 by jmalaval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"
# include "ft_printf/ft_printf.h"

# include <sys/types.h>
# include <unistd.h>

#include <stdio.h>
#include <errno.h>

typedef struct s_pipex
{
	char	*infile;
	char	*outfile;
	char	*cmd1;
	char	*cmd2;
	char	**directories;
}			t_pipex;

// changer le wildcard du makefile

int			main(int argc, char **argv, char **env);

///////////////////////////// parse.c ///////////////////////////////////
char		*get_env_value(char *value, char **env);
int			existing_cmd(char *cmd, char **dir);

///////////////////////////// free_errors.c ///////////////////////////////////
void		exit_with_message(char *str);

#endif