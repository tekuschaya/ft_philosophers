/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   states.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odhazzar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 13:13:55 by odhazzar          #+#    #+#             */
/*   Updated: 2020/11/19 21:38:31 by odhazzar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

int			write_message(t_phil *state, char *s)
{
	if (state->phil->end)
		return (1);
	if (sem_wait(state->phil->sem_write))
		return (1);
	ft_putnbr(get_time() - state->start);
	ft_putchar('\t');
	if (state->id >= 0)
		ft_putnbr(state->id + 1);
	ft_putstr(s);
	if (sem_post(state->phil->sem_write))
		return (1);
	return (0);
}

static int	check_eat(t_phil *state)
{
	if (state->flag)
	{
		if (state->count_eat == state->phil->time)
		{
			state->flag = 0;
			state->phil->check_time++;
			if (state->phil->check_time == state->phil->amount)
			{
				state->phil->end = 1;
				sem_wait(state->phil->sem_write);
				ft_putstr("All the philosophers have eaten\n");
				sem_post(state->phil->sem_end);
				return (1);
			}
		}
	}
	return (0);
}

int			to_eat(t_phil *state)
{
	uint64_t	stop;

	stop = get_time() + state->phil->eat;
	if (state->phil->end)
		return (1);
	sem_wait(state->phil->sem_protect[state->id]);
	write_message(state, " is eating\n");
	state->last_eat = get_time();
	state->count_eat++;
	if (check_eat(state))
		return (1);
	while (get_time() < stop)
		usleep(100);
	sem_post(state->phil->sem_protect[state->id]);
	if (sem_post(state->phil->sem_forks))
		return (1);
	if (sem_post(state->phil->sem_forks))
		return (1);
	return (0);
}

int			to_sleep_and_think(t_phil *state)
{
	uint64_t	stop;

	stop = get_time() + state->phil->sleep;
	if (state->phil->end)
		return (1);
	if (write_message(state, " is sleeping\n"))
		return (1);
	while (get_time() < stop)
		usleep(100);
	if (state->phil->end)
		return (1);
	if (write_message(state, " is thinking\n"))
		return (1);
	return (0);
}

int			take_fork(t_phil *state)
{
	if (state->phil->end)
		return (1);
	if (sem_wait(state->phil->sem_forks))
		return (1);
	if (write_message(state, " has taking a fork\n"))
		return (1);
	if (state->phil->end)
		return (1);
	if (sem_wait(state->phil->sem_forks))
		return (1);
	if (write_message(state, " has taking a fork\n"))
		return (1);
	return (0);
}
