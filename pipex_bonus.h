/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmalaval <jmalaval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 13:06:45 by jmalaval          #+#    #+#             */
/*   Updated: 2025/07/28 16:26:57 by jmalaval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "ft_printf/ft_printf.h"
# include "libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_pipex_b
{
	int		infile;			//initialisé
	int		outfile;		//init
	char	**cmd;			//init
	char	**directories;	//init
	char	*path;			// init
	char	*pathname_cmd;	//init
	int		**pipefd;
	int		outfile_error;	//init
	int		last_cmd;		// init
	int		first_cmd;		// init
	int		prev_fd;		
	char	*path_outfile;	// init
	int		cmd_count;		// init
	pid_t	*pid;			// init
}			t_pipex_b;


///////////////////////////// utils.c ///////////////////////////////////
char		*get_env_value(char *value, char **env);
void		get_pathname(char **cmd, t_pipex_b *pipex);
void		init_cmd(t_pipex_b *pipex, char *av);
void		init_struct(t_pipex_b *pipex, char **av, char **env);

///////////////////////////// free_errors.c ///////////////////////////////////
void		exit_with_message(char *str, const char *str2, int n);
void		exit_with_message_and_free(char *str, t_pipex_b *pipex, int n);
void		free_tab(void **tab);
void		free_struct(t_pipex_b *pipex);
void	free_cmd(t_pipex_b *pipex);

///////////////////////////// pipex.c ///////////////////////////////////
//int			ft_pipex(t_pipex_b *pipex, char **env);
void		cmd_process(t_pipex_b *pipex, char **env, int index);
void		init_outfile(t_pipex_b *pipex);

#endif