/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohaker <ohaker@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 20:28:20 by ohaker            #+#    #+#             */
/*   Updated: 2025/07/23 03:00:37 by ohaker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void error_msg(char *err_str)
{
	printf("Error: %s", err_str);
	exit (1);
}

int ft_isdigit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ft_atoi(const char *str)
{
	int	x;
	int	res;

	x = 0;
	res = 0;
	while (ft_isdigit(str[x]))
	{
		res = (res * 10) + (str[x] - '0');
		x++;
	}
	return (res);
}

long get_time_diff(struct timeval start)
{
	struct timeval	now;
	long			time_diff;

	gettimeofday(&now, NULL);
	time_diff = (now.tv_sec - start.tv_sec) * 1000;
	time_diff += (now.tv_usec - start.tv_usec) / 1000;
	return (time_diff);
}

void ft_usleep(long sleep)
{
	long temp;

	temp = sleep / 100;
	while (temp <= sleep && philo.alive)
	{
		usleep(temp);
		temp += sleep / 100;
	}
}
