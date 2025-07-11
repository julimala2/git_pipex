/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juliette-malaval <juliette-malaval@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 13:06:45 by jmalaval          #+#    #+#             */
/*   Updated: 2025/07/11 17:16:27 by juliette-ma      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"
# include "ft_printf/ft_printf.h"

# include <sys/types.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <errno.h>
# include <sys/wait.h>
# include <stdio.h>

typedef struct s_pipex
{
	int	infile;
	int	outfile;
	char	**cmd1;
	char	**cmd2;
	char	**directories;
	char	*path;
	char	*pathname_cmd1;
	char	*pathname_cmd2;
	int		pipefd[2];
}			t_pipex;

// changer le wildcard du makefile

int			main(int argc, char **argv, char **env);

///////////////////////////// utils.c ///////////////////////////////////
char		*get_env_value(char *value, char **env);
void	get_pathname(char **cmd, t_pipex *pipex, int j);
void    init_pipex(t_pipex *pipex, char **av, char **env);
void init_struct(t_pipex *pipex);

///////////////////////////// free_errors.c ///////////////////////////////////
void		exit_with_message(char *str);
void	exit_with_message_and_free(char *str, t_pipex *pipex);
void	free_tab(char **tab);
void	free_struct(t_pipex *pipex);

///////////////////////////// pipex.c ///////////////////////////////////
void    ft_pipex(t_pipex *pipex, char **env);
void    cmd1_process(t_pipex *pipex, char **env);
void    cmd2_process(t_pipex *pipex, char **env);


#endif