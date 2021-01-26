/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odhazzar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 12:56:51 by odhazzar          #+#    #+#             */
/*   Updated: 2020/11/19 21:40:33 by odhazzar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

int		clear_struct(t_param *phil)
{
	int i;

	i = 0;
	while (i < phil->amount)
	{
		kill(phil->pid[i], 9);
		i++;
	}
	free(phil->pid);
	free(phil->sem_protect);
	free(phil->sem_eat);
	return (0);
}

sem_t	*sem_create(char *name, int value)
{
	sem_unlink(name);
	return (sem_open(name, O_CREAT, 0666, value));
}

int		create_semaphores(t_param *phil, int i)
{
	if (!(phil->pid = (pid_t*)malloc(sizeof(pid_t) * phil->amount)))
		return (print_error("Memory is not allocated\n"));
	if (!(phil->sem_protect = (sem_t**)malloc(sizeof(sem_t*) * phil->amount)))
	{
		free(phil->pid);
		return (print_error("Memory is not allocated\n"));
	}
	while (i < phil->amount)
		phil->sem_protect[i++] = sem_create("protect", 1);
	if (phil->time)
	{
		if (!(phil->sem_eat = (sem_t**)malloc(sizeof(sem_t*) * phil->amount)))
		{
			free(phil->pid);
			free(phil->sem_protect);
			return (print_error("Memory is not allocated\n"));
		}
		i = 0;
		while (i < phil->amount)
			phil->sem_eat[i++] = sem_create("check_eat", 0);
	}
	return (1);
}

int		init_struct(t_param *phil, int arg)
{
	phil->sem_forks = sem_create("fork", phil->amount);
	phil->sem_write = sem_create("write", 1);
	phil->sem_check_die = sem_create("die", 0);
	phil->sem_check_eat = sem_create("eat", 1);
	phil->sem_eat = NULL;
	if (arg == 5)
		phil->time = 0;
	phil->end = 0;
	phil->count_eat = 0;
	if (!create_semaphores(phil, 0))
		return (1);
	return (0);
}
