/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjukmong <tjukmong@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 03:26:50 by tjukmong          #+#    #+#             */
/*   Updated: 2023/06/16 18:32:07 by tjukmong         ###   ########.fr       */
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
	pthread_mutex_init(&table->mutx, NULL);
}

void	*philo_routine(void *ph)
{
	t_philo	*philo;
	size_t	time;

	philo = (t_philo *)ph;
	time = 0;
	while (philo->state.eaten < philo->table->rules.times_to_eat)
	{
		usleep(50);
		if (pthread_mutex_lock(&philo->table->mutx))
			return (NULL);
		printf("%ld%8d is ideling\n", time, philo->id);
		philo->state.eaten++;
		update_timestamp(philo, &time);
		pthread_mutex_unlock(&philo->table->mutx);
		if (philo->state.eaten == philo->table->rules.times_to_eat)
			philo_died(ph);
		msleep(philo, &time, 100);
	}
	return (NULL);
}
