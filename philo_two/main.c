/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odhazzar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 13:05:29 by odhazzar          #+#    #+#             */
/*   Updated: 2020/11/19 22:02:57 by odhazzar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

static void	*check_state(void *arg)
{
	t_phil *state;

	state = (t_phil*)arg;
	while (!state->phil->end)
	{
		sem_wait(state->phil->sem_protect[state->id]);
		if (get_time() > state->last_eat + state->phil->die)
		{
			sem_wait(state->phil->sem_write);
			ft_putnbr(get_time() - state->start);
			ft_putchar('\t');
			ft_putnbr(state->id + 1);
			ft_putstr(" died\n");
			state->phil->end = 1;
			sem_post(state->phil->sem_end);
			break ;
		}
		sem_post(state->phil->sem_protect[state->id]);
	}
	return (NULL);
}

static void	state_init(t_param *phil, t_phil *state)
{
	state->id = phil->number;
	state->last_eat = phil->start;
	state->phil = phil;
	state->count_eat = 0;
	state->start = phil->start;
	state->flag = 0;
	if (phil->time)
		state->flag = 1;
}

static void	*doing_things(void *arg)
{
	t_phil		state;
	t_param		*phil;
	pthread_t	thread;

	phil = (t_param*)arg;
	state_init(phil, &state);
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

static void	create_thread(t_param *phil)
{
	int			i;
	pthread_t	thread;

	i = 0;
	while (i < phil->amount)
	{
		phil->number = i;
		if (pthread_create(&thread, NULL, doing_things, phil) < 0)
			print_error("Error. Can't create thread\n");
		pthread_detach(thread);
		usleep(100);
		i++;
	}
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
			return (0);
		i++;
	}
	init_struct(&phil, argc);
	create_thread(&phil);
	sem_wait(phil.sem_end);
	free(phil.sem_protect);
	return (0);
}
