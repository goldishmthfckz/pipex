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

//fd[1] = child, ecrit, execute cmd1
//fd[0] = parent, lit, execute cmd2

void	exec(char *cmd, char **env)
{

}

//infile devient stdin (dc input) de cmd1
//execute cmd1
//cmd1 output -> write in fd[1] = cmd1 stdout
void	child(int *end, char **av, char **env)
{
	int	fd;

	fd = openfile(av[1], 0);
	dup2(fd, 0);
	dup2(end[1], 1);
	close(end[0]);
	exec(av[2], env);
}

//read from fd[0], write in outfile = stdout iliyana
//fd[0] reads fd[1], cmd1 output -> cmd2, fd[0] = cmd2 stdin
void	parent(int *end, char **av, char **env)
{
	int	fd;

	fd = openfile(av[4], 1);
	dup2(fd, 1);
	dup2(end[1], 0);
	close(end[1]);
	exec(av[3], env);
}

int main(int ac, char **av, char **env)
{
	int end[2];
	long int pid;

	if (ac == 5)
	{
		if (pipe(end) == -1)
			exit(1);
		pid = fork();
		if (pid < 0)
			printf("erreur de fork");
		if (pid == 0)
			child(end[1], end, env);
		else
			parent(end[0], end, env);
	}
	return (0);
}
