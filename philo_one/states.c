/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   states.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odhazzar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 22:29:03 by odhazzar          #+#    #+#             */
/*   Updated: 2020/11/19 21:26:58 by odhazzar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int			write_message(t_phil *state, char *s)
{
	if (state->phil->end)
		return (1);
	pthread_mutex_lock(&(state->phil->mutex_write));
	ft_putnbr(get_time() - state->phil->start);
	ft_putchar('\t');
	if (state->id >= 0)
		ft_putnbr(state->id + 1);
	ft_putstr(s);
	pthread_mutex_unlock(&(state->phil->mutex_write));
	return (0);
}

int			to_eat(t_phil *state)
{
	uint64_t	stop;

	stop = get_time() + state->phil->eat;
	if (state->phil->end)
		return (1);
	pthread_mutex_lock(&(state->phil->mutex_protect[state->id]));
	write_message(state, " is eating\n");
	state->last_eat = get_time();
	if (++state->count_eat == state->phil->time)
	{
		state->phil->check_time++;
		if (state->phil->check_time == state->phil->amount)
		{
			state->phil->end = 1;
			return (1);
		}
	}
	while (get_time() < stop)
		usleep(100);
	if (state->phil->end)
		return (1);
	pthread_mutex_unlock(&(state->phil->mutex_protect[state->id]));
	pthread_mutex_unlock(&(state->phil->mutex_forks[state->fork_r]));
	pthread_mutex_unlock(&(state->phil->mutex_forks[state->fork_l]));
	return (0);
}

int			to_sleep_and_think(t_phil *state)
{
	uint64_t	stop;

	stop = get_time() + state->phil->sleep;
	if (state->phil->end)
		return (1);
	write_message(state, " is sleeping\n");
	while (get_time() < stop)
		usleep(100);
	if (state->phil->end)
		return (1);
	write_message(state, " is thinking\n");
	return (0);
}

int			take_fork(t_phil *state)
{
	if (state->phil->end)
		return (1);
	pthread_mutex_lock(&(state->phil->mutex_forks[state->fork_l]));
	write_message(state, " has taking a fork\n");
	if (state->phil->end)
		return (1);
	pthread_mutex_lock(&(state->phil->mutex_forks[state->fork_r]));
	write_message(state, " has taking a fork\n");
	return (0);
}
