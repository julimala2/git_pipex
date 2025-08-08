/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmalaval <jmalaval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 13:06:45 by jmalaval          #+#    #+#             */
/*   Updated: 2025/08/08 16:06:35 by jmalaval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "ft_printf/ft_printf.h"
# include "libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_pipex
{
	int		infile;
	int		outfile;
	char	**cmd1;
	char	**cmd2;
	char	**directories;
	char	*path;
	char	*pathname_cmd1;
	char	*pathname_cmd2;
	int		pipefd[2];
	int		outfile_error;
}			t_pipex;

///////////////////////////// utils.c ///////////////////////////////////
void		init_pipex(t_pipex *pipex, char **av, char **env);
void		init_struct(t_pipex *pipex);
void		init_outfile(t_pipex *pipex, char **av);
void		init_infile(t_pipex *pipex, char **av);

///////////////////////////// free_errors.c //////////////////////////////
void		exit_with_message(char *str, int n);
void		exit_with_message_and_free(char *str, t_pipex *pipex, int n);
void		free_tab(char **tab);
void		free_struct(t_pipex *pipex);
void		ft_free(void *ptr);

///////////////////////////// pipex.c ///////////////////////////////////
int			ft_pipex(t_pipex *pipex, char **av, char **env);
void		cmd1_process(t_pipex *pipex, char **env);
void		cmd2_process(t_pipex *pipex, char **env);

///////////////////////////// main.c ///////////////////////////////////
char		*get_env_value(char *value, char **env);
void		get_pathname(char **cmd, t_pipex *pipex, int j);

#endif