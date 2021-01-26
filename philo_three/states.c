/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   states.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odhazzar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 13:13:55 by odhazzar          #+#    #+#             */
/*   Updated: 2020/11/19 21:41:18 by odhazzar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

int		write_message(t_param *phil, char *s)
{
	if (phil->end)
		return (1);
	sem_wait(phil->sem_write);
	ft_putnbr(get_time() - phil->start);
	ft_putchar('\t');
	if (phil->id >= 0)
		ft_putnbr(phil->id + 1);
	ft_putstr(s);
	sem_post(phil->sem_write);
	return (0);
}

int		to_eat(t_param *phil)
{
	uint64_t stop;

	stop = get_time() + phil->eat;
	if (phil->end)
		return (1);
	sem_wait(phil->sem_protect[phil->id]);
	write_message(phil, " is eating\n");
	phil->last_eat = get_time();
	if (phil->count_eat < phil->time)
	{
		phil->count_eat++;
		if (phil->count_eat == phil->time)
			sem_post(phil->sem_eat[phil->id]);
	}
	while (get_time() < stop)
		usleep(100);
	sem_post(phil->sem_protect[phil->id]);
	sem_post(phil->sem_forks);
	sem_post(phil->sem_forks);
	return (0);
}

int		to_sleep_and_think(t_param *phil)
{
	uint64_t stop;

	stop = get_time() + phil->sleep;
	write_message(phil, " is sleeping\n");
	while (get_time() < stop)
		usleep(100);
	write_message(phil, " is thinking\n");
	return (0);
}

int		take_fork(t_param *phil)
{
	if (sem_wait(phil->sem_forks))
		return (1);
	write_message(phil, " has taking a fork\n");
	if (sem_wait(phil->sem_forks))
		return (1);
	write_message(phil, " has taking a fork\n");
	return (0);
}
