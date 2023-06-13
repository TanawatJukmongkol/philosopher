/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjukmong <tjukmong@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 03:26:50 by tjukmong          #+#    #+#             */
/*   Updated: 2023/06/13 14:05:37 by tjukmong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	table_init(t_table *table, int ac, int *av)
{
	table->nbr_philo = 0;
	table->rules.time_to_live = av[1];
	table->rules.time_to_eat = av[2];
	table->rules.time_to_sleep = av[3];
	if (ac == 5)
		table->rules.times_to_eat = av[4];
	else
		table->rules.times_to_eat = INT_MAX;
}

void	*philo_routine(void *ph)
{
	t_philo	*philo;
	size_t	time;

	philo = (t_philo *)ph;
	time = 0;
	while (philo->state.eaten < philo->table->rules.times_to_eat)
	{
		update_timestamp(philo, &time);
		if (pthread_mutex_lock(&philo->mutx) != 0)
			return (NULL);
		printf("%ld%8d is ideling\n", time, philo->id);
		msleep(philo, &time, 100);
		philo->state.eaten++;
		pthread_mutex_unlock(&philo->mutx);
		philo_detatch(ph);
		// if (philo->state.agenda == _think || philo->state.agenda == _waiting)
		// {
		// 	pthread_mutex_lock(&philo->mutx);
		// 	if (philo->state.agenda != _waiting)
		// 	{
		// 		printf("%ld%8d is thinking\n", time, philo->id);
		// 		philo->state.agenda = _waiting;
		// 	}
		// 	philo_take_fork(ph, time);
		// 	pthread_mutex_unlock(&philo->mutx);
		// }
		// else if (philo->state.agenda == _eat)
		// {
		// 	printf("%ld%8d is eating\n", time, philo->id);
		// 	msleep(philo, &time, philo->table->rules.time_to_eat);
		// 	philo->state.eaten++;
		// 	philo->state.agenda = _sleep;
		// 	philo_free_fork(ph);
		// }
		// else if (philo->state.agenda == _sleep)
		// {
		// 	printf("%ld%8d is sleeping\n", time, philo->id);
		// 	msleep(philo, &time, philo->table->rules.time_to_sleep);
		// 	philo->state.agenda = _think;
		// }
	}
	philo_died(ph);
	return (NULL);
}
