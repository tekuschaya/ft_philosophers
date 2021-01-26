/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odhazzar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 19:18:43 by odhazzar          #+#    #+#             */
/*   Updated: 2020/11/19 21:30:47 by odhazzar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
# define PHILO_ONE_H

# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdlib.h>

typedef struct		s_param
{
	uint64_t		die;
	uint64_t		eat;
	uint64_t		sleep;
	uint64_t		start;
	int				amount;
	int				time;
	int				id;
	int				check_time;
	int				end;
	pthread_mutex_t	*mutex_forks;
	pthread_mutex_t	mutex_write;
	pthread_mutex_t	*mutex_protect;
}					t_param;

typedef struct		s_phil
{
	int				id;
	int				fork_r;
	int				fork_l;
	int				count_eat;
	uint64_t		last_eat;
	t_param			*phil;
}					t_phil;

int					parse_param(int i, char *s, t_param *phil);
int					init_struct(t_param *phil, int arg, int i);
int					clear_struct(t_param *phil);
int					print_error(char *s);
int					ft_strlen(char *s);
int					take_fork(t_phil *state);
int					to_sleep_and_think(t_phil *state);
int					to_eat(t_phil *state);
int					write_message(t_phil *state, char *s);
void				ft_putstr(char *s);
void				ft_putnbr(int n);
void				ft_putchar(char c);
uint64_t			get_time(void);

#endif
