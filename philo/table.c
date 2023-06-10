/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjukmong <tjukmong@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 03:26:50 by tjukmong          #+#    #+#             */
/*   Updated: 2023/06/10 16:45:40 by tjukmong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
		update_timestamp(ph, &time);
	}
	philo_died(ph);
	return (NULL);
}
