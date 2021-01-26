/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odhazzar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 22:26:37 by odhazzar          #+#    #+#             */
/*   Updated: 2020/11/19 22:02:35 by odhazzar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

static void	*monitor(void *arg)
{
	t_param *phil;

	phil = (t_param*)arg;
	while (!phil->end)
		usleep(1000);
	return (NULL);
}

static void	*check_state(void *arg)
{
	t_phil *state;

	state = (t_phil*)arg;
	while (!state->phil->end)
	{
		pthread_mutex_lock(&(state->phil->mutex_protect[state->id]));
		if (get_time() > state->last_eat + state->phil->die)
		{
			pthread_mutex_lock(&(state->phil->mutex_write));
			ft_putnbr(get_time() - state->phil->start);
			ft_putchar('\t');
			ft_putnbr(state->id + 1);
			ft_putstr(" died\n");
			state->phil->end = 1;
			pthread_mutex_unlock(&(state->phil->mutex_protect[state->id]));
			break ;
		}
		pthread_mutex_unlock(&(state->phil->mutex_protect[state->id]));
	}
	return (NULL);
}

void		*doing_things(void *arg)
{
	t_phil		state;
	t_param		*phil;
	pthread_t	thread;

	phil = (t_param*)arg;
	state.id = phil->id;
	state.phil = phil;
	state.fork_l = state.id;
	state.fork_r = (state.id + 1) % phil->amount;
	state.count_eat = 0;
	state.last_eat = phil->start;
	if (pthread_create(&thread, NULL, check_state, &state) != 0)
		print_error("Error. Can't create thread\n");
	pthread_detach(thread);
	while (1)
	{
		if (take_fork(&state))
			break ;
		if (to_eat(&state))
			break ;
		if (to_sleep_and_think(&state))
			break ;
	}
	return (NULL);
}

void		create_thread(t_param *phil)
{
	int			i;
	pthread_t	thread;

	i = 0;
	phil->start = get_time();
	while (i < phil->amount)
	{
		phil->id = i;
		if (pthread_create(&thread, NULL, doing_things, phil) < 0)
			print_error("Error. Can't create thread\n");
		pthread_detach(thread);
		usleep(100);
		i++;
	}
	if (pthread_create(&thread, NULL, &monitor, phil) < 0)
		print_error("Error. Can't create thread\n");
	pthread_join(thread, NULL);
}

int			main(int argc, char **argv)
{
	int		i;
	t_param	phil;

	i = 1;
	if (argc < 5 || argc > 6)
		return (print_error("Incorrect number of arguments\n"));
	while (i < argc)
	{
		if (parse_param(i, argv[i], &phil))
			return (1);
		i++;
	}
	if (init_struct(&phil, argc, 0))
		return (1);
	create_thread(&phil);
	if (phil.time && phil.check_time == phil.amount)
		ft_putstr("All the philosophers have eaten\n");
	clear_struct(&phil);
	return (0);
}
