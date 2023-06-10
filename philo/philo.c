/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjukmong <tjukmong@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 05:44:49 by tjukmong          #+#    #+#             */
/*   Updated: 2023/06/10 17:09:26 by tjukmong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	parse_args(int argc, char **argv, int *ac, int **av)
{
	*av = argv_getint(ac, argv);
	if ((!*av && argc > 1) || (*ac > 0 && (*av)[0] <= 0))
	{
		printf("Invalid argument passed.\n");
		return (1);
	}
	if (*ac == 0)
	{
		free(*av);
		printf("No argument passed.\n Usage: ");
		printf("./philo nbr_philo time_to_live time_to_eat time_to_sleep\n");
		return (1);
	}
	if (*ac < 4 || *ac > 5)
	{
		printf("Too few / too much arguments.\n");
		free(*av);
		return (1);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	int				ac;
	int				*av;
	t_table			table;

	av = NULL;
	table.nbr_philo = 0;
	if (parse_args(argc, argv, &ac, &av))
		return (1);
	if (ac == 5)
		table.rules.times_to_eat = av[4];
	else
		table.rules.times_to_eat = INT_MAX;
	while (av[0]--)
	{
		if (!philo_spawn(&table, philo_routine))
		{
			philo_purge(table.philo, 1);
			return (-1);
		}
	}
	if (table.philo)
		philo_join(&table);
	philo_purge(table.philo, 0);
	free(av);
}
