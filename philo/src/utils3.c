/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymauk <ymauk@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 20:01:52 by ymauk             #+#    #+#             */
/*   Updated: 2025/04/28 13:35:48 by ymauk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	one_philo(void *arg)
{
	t_philos	*philo;
	int			left_fork;

	philo = arg;
	left_fork = philo->id_philo - 1;
	pthread_mutex_lock(&philo->data->forks[left_fork]);
	print_message(philo, "has taken a fork");
	ft_usleep(philo->data->time_to_die);
	pthread_mutex_unlock(&philo->data->forks[left_fork]);
}
