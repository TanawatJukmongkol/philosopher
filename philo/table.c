/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjukmong <tjukmong@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 03:26:50 by tjukmong          #+#    #+#             */
/*   Updated: 2023/06/11 20:05:11 by tjukmong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	table_init(t_table *table, int ac, int *av)
{
	if (ac == 5)
		table->rules.times_to_eat = av[4];
	else
		table->rules.times_to_eat = INT_MAX;
	table->nbr_philo = 0;
	pthread_mutex_init(&table->global_lock, NULL);
}

void	*philo_routine(void *ph)
{
	t_philo	*philo;
	size_t	time;

	philo = (t_philo *)ph;
	time = 0;
	while (philo->state.eaten < philo->table->rules.times_to_eat)
	{
		printf("[%ldms] Philosopher #%d\n", time, philo->id);
		msleep(ph, &time, 100);
		philo->state.eaten++;
	}
	philo_died(ph);
	return (NULL);
}
