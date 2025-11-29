/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohaker <ohaker@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 20:51:15 by ohaker            #+#    #+#             */
/*   Updated: 2025/11/29 15:57:19 by ohaker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"
#include <stdlib.h>

int	init_input(int argc, char **argv, t_rules *rules)
{
	int	x;

	x = 0;
	rules->philo_count = ft_atoi(argv[1]);
	rules->time_to_die = ft_atoi(argv[2]);
	rules->time_to_eat = ft_atoi(argv[3]);
	rules->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		rules->must_eat_count = ft_atoi(argv[5]);
	else if (argc == 5)
		rules->must_eat_count = -1;
	rules->forks = malloc(sizeof(pthread_mutex_t) * rules->philo_count);
	if (!rules->forks)
		error_msg("Memory allocation for forks failed.\n");
	while (x < ft_atoi(argv[1]))
		pthread_mutex_init(&rules->forks[x++], NULL);
	pthread_mutex_init(&rules->alive_lock, NULL);
	pthread_mutex_init(&rules->meal_lock, NULL);
	pthread_mutex_init(&rules->print_lock, NULL);
	pthread_mutex_init(&rules->simulation_lock, NULL);
	return (0);
}

int	init_philos(t_rules *rules)
{
	int	x;

	rules->philos = malloc(sizeof(t_philo) * rules->philo_count);
	if (!rules->philos)
		return (error_msg("Memory allocation of philos failed.\n"), 1);
	memset(rules->philos, 0, sizeof(t_philo) * rules->philo_count);
	gettimeofday(&rules->start_time, NULL);
	x = 0;
	while (x < rules->philo_count)
	{
		rules->philos[x].id = x;
		rules->philos[x].alive = 1;
		rules->philos[x].meals_eaten = 0;
		rules->philos[x].rules = rules;
		rules->philos[x].last_meal = rules->start_time;
		rules->philos[x].left_fork = &rules->forks[x];
		rules->philos[x].right_fork = &rules->forks[(x + 1)
			% rules->philo_count];
		pthread_mutex_init(&rules->philos[x].philo_lock, NULL);
		x++;
	}
	return (0);
}

int	eat_helper(t_rules *rules)
{
	int	x;

	x = 0;
	while (x < rules->philo_count)
	{
		printf("Philo %d has eaten %d meals\n", rules->philos[x].id,
			rules->philos[x].meals_eaten);
		x++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_rules	*rules;

	if (check_input(argc, argv))
		return (1);
	rules = malloc(sizeof(t_rules));
	if (!rules)
		return (error_msg("Initial rules allocation failed.\n"), 1);
	memset(rules, 0, sizeof(t_rules));
	if (init_input(argc, argv, rules) || init_philos(rules))
		return (1);
	if (thread_create(rules) != 0)
		return (1);
	check_end(rules);
	thread_join(rules);
	eat_helper(rules);
	clean_up(rules);
	return (0);
}
