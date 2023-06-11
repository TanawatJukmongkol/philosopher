/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjukmong <tjukmong@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 05:46:35 by tjukmong          #+#    #+#             */
/*   Updated: 2023/06/11 20:08:40 by tjukmong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# define DEBUG_MODE 0

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include "lib/miniutils/miniutils.h"

# if DEBUG_MODE == 1
# endif

enum	e_state
{
	_think	= 0,
	_hungry	= 1,
	_eat	= 2,
	_sleep	= 3
};

// Define struct types
typedef struct timeval	t_timeval;
typedef struct s_table	t_table;

typedef struct s_rules
{
	t_timeval	t_start;
	int			time_to_live;
	int			time_to_eat;
	int			time_to_sleep;
	int			times_to_eat;
}				t_rules;

typedef struct s_state
{
	int				eaten;
	int				holding;
	enum e_state	agenda;
}				t_state;

typedef struct s_philo
{
	pthread_t		thread;
	pthread_mutex_t	mutx;
	t_state			state;
	struct s_philo	*right;
	struct s_philo	*left;
	int				id;
	t_timeval		timer;
	t_table			*table;
}				t_philo;

typedef struct s_table
{
	pthread_mutex_t	global_lock;
	t_philo			*philo;
	t_rules			rules;
	int				nbr_philo;
}				t_table;

// Philosopher utils
t_philo	*philo_spawn(t_table *t, void *(*routine)(void *));
void	philo_join(t_table *t);
void	philo_died(t_philo *ph);
void	philo_detatch(t_philo *ph);
void	philo_purge(t_philo *ph);

// Utils
void	update_timestamp(t_philo *ph, size_t *time);
void	msleep(t_philo *ph, size_t *time_output, int msec);

// At the diner's table
void	table_init(t_table *table, int ac, int *av);
void	*philo_routine(void *ph);

#endif
