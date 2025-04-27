/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   messages.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymauk <ymauk@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 18:23:41 by ymauk             #+#    #+#             */
/*   Updated: 2025/04/27 16:27:20 by ymauk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	thinking(void *arg)
{
	t_philos	*philo;

	philo = arg;
	if (check_mutex_var(philo, 1) != 1 && check_mutex_var(philo, 2) == 0)
		print_message(philo, "is thinking");
	usleep(500);
}

void	take_forks(void *arg)
{
	t_philos	*philo;
	int			left_fork;
	int			right_fork;
	int			first_fork;
	int			second_fork;

	philo = arg;
	left_fork = philo->id_philo - 1;
	right_fork = philo->id_philo % check_mutex_var(philo, 4);
	if (left_fork > right_fork)
	{
		first_fork = left_fork;
		second_fork = right_fork;
	}
	else
	{
		first_fork = right_fork;
		second_fork = left_fork;
	}
	pthread_mutex_lock(&philo->data->forks[first_fork]);
	if (check_mutex_var(philo, 1) != 1 && check_mutex_var(philo, 2) == 0)
		print_message(philo, "has taken a fork");
	pthread_mutex_lock(&philo->data->forks[second_fork]);
	if (check_mutex_var(philo, 1) != 1 && check_mutex_var(philo, 2) == 0)
		print_message(philo, "has taken a fork");
}

void	eating(void *arg)
{
	t_philos	*philo;
	size_t		current_time;

	philo = (t_philos *)arg;
	current_time = get_current_time();
	pthread_mutex_lock(&philo->meal);
	philo->last_meal = current_time;
	pthread_mutex_unlock(&philo->meal);
	if (check_mutex_var(philo, 1) != 1 && check_mutex_var(philo, 2) == 0)
	{
		print_message(philo, "is eating");
		ft_usleep(philo->data->time_to_eat);
	}
	pthread_mutex_lock(&philo->meal);
	philo->has_eaten++;
	pthread_mutex_unlock(&philo->meal);
}

void	putdown_forks(void *arg)
{
	t_philos	*philo;
	int			left_fork;
	int			right_fork;

	philo = arg;
	left_fork = philo->id_philo - 1;
	right_fork = philo->id_philo % check_mutex_var(philo, 4);
	pthread_mutex_unlock(&philo->data->forks[left_fork]);
	pthread_mutex_unlock(&philo->data->forks[right_fork]);
}

void	go_sleep(void *arg)
{
	t_philos	*philo;

	philo = arg;
	if (check_mutex_var(philo, 1) != 1 && check_mutex_var(philo, 2) == 0)
	{
		print_message(philo, "is sleeping");
		ft_usleep(philo->data->time_to_sleep);
	}
}
