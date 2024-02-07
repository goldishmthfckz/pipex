/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: estegana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 17:27:06 by estegana          #+#    #+#             */
/*   Updated: 2024/01/24 17:27:09 by estegana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*find_path(char *cmd, char **env)
{
	char	**allpaths;
	char	**split_cmd;
	char	*path;
	char	*exec;
	int		i;

	i = 0;
	while (ft_strnstr(env[i], "PATH", 4) == 0)
		i++;
	return (cmd);
}

void	execute_cmd(char *cmd, char **env)
{
	char	**split_cmd;
	char	*path;
	int	i;

	**split_cmd = ft_split(cmd, ' ');
	path = find_path(cmd, env);
	if (execve(path, split_cmd, env) == -1)
	{
		ft_putstr_fd("Pipex: command not found: ", 2);
		ft_putendl_fd(split_cmd[0], 2);
		ft_freelist(split_cmd[i]);
		exit(1);
	}
}

void	child(char **av, int *tube, char **env)
{
	int	infile;

	ft_printf("entree ds le child\n");
	infile = open(av[1], 0);
	dup2(infile, 0);
	dup2(tube[1], 1);
	close(tube[0]);
	execute_cmd(av[2], env);
}

//ouvre
void	parent(char **av, int *tube, char **env)
{
	int	outfile;

	ft_printf("entree ds le parent\n");
	outfile = open(av[4], 0);
	dup2(outfile, 1);
	dup2(tube[0], 0);
	close(tube[1]);
	execute_cmd(av[3], env);
}

//si y a pas 4 argv, affichier pas bn nb d'arg
//si y a bien 4 argv ;
//> pipe
//> si ya erreur de pipe, exit tt le programme
//> fork
//> si ya erreur de fork, exit tt le programme
//> sinon rentre ds processus parent puis enfant
int	main(int ac, char **av, char **env)
{
	int	tube[2];
	pid_t	pid;

	if (ac == 5)
	{
		ft_printf("Bon nombre d'arguments (4)\n");
		ft_printf("entree dans le processus de pipe\n");
		if (pipe(tube) == -1)
			exit(1);
		pid = fork();
		if (pid == -1)
			exit(1);
		else if (pid == 0)
			child(av, tube, env);
		else
			parent(av, tube, env);
	}
	else
		ft_printf("madatory : Pas le bon nombre d'arguments\n");
	return (0);
}
