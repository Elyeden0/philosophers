/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonnard <abonnard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 14:18:54 by abonnard          #+#    #+#             */
/*   Updated: 2025/03/17 02:25:02 by abonnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	ft_usleep(long long time, t_phil *phil)
{
	long long	wait;
	long long	tmp;

	wait = get_time() + time;
	tmp = get_time();
	while (tmp < wait)
	{
		pthread_mutex_lock(&phil->m_last_eat);
		if (tmp - phil->last_eat - phil->tools->time_to_die > 0)
		{
			pthread_mutex_unlock(&phil->m_last_eat);
			print_msg(phil, MSG_DEAD, 1);
			return (1);
		}
		pthread_mutex_unlock(&phil->m_last_eat);
		pthread_mutex_lock(&phil->m_stop);
		if (phil->stop)
			return (pthread_mutex_unlock(&phil->m_stop) + 1);
		pthread_mutex_unlock(&phil->m_stop);
		usleep(1000);
		tmp = get_time();
	}
	return (0);
}

static void	*phil_life(void *ptr)
{
	t_phil	*phil;

	phil = (t_phil *)ptr;
	pthread_mutex_lock(&phil->m_stop);
	while (!phil->stop)
	{
		pthread_mutex_unlock(&phil->m_stop);
		print_msg(phil, MSG_THINK, 0);
		if (phil->id % 2 == 0)
			usleep(150);
		if (my_fork(phil))
			return (NULL);
		pthread_mutex_lock(&phil->m_eat_count);
		phil->eat_count++;
		pthread_mutex_unlock(&phil->m_eat_count);
		print_msg(phil, MSG_SLEEP, 0);
		if (ft_usleep(phil->tools->time_to_sleep, phil))
			return (NULL);
		pthread_mutex_lock(&phil->m_stop);
	}
	pthread_mutex_unlock(&phil->m_stop);
	return (NULL);
}

static void	create_threads(t_tools *tools, int tmp)
{
	int	i;

	i = tmp;
	while (i < tools->nb_phil)
	{
		if (pthread_create(&tools->phils[i].thread, NULL, phil_life,
				&tools->phils[i]) != 0)
		{
			printf("Problem when creating threads\n");
			return ;
		}
		i += 2;
	}
	if (tmp == 0)
		create_threads(tools, 1);
}

int	main(int ac, char **av)
{
	t_tools	tools;
	int		i;

	i = phil_init(ac, av, &tools);
	if (i)
	{
		if (i == 1)
			printf("Problem when initialising philosophers\n");
		phil_free(&tools);
		return (1);
	}
	tools.start = get_time();
	create_threads(&tools, 0);
	if (init_thread_check(&tools))
		return (1);
	i = -1;
	while (++i < tools.nb_phil)
		pthread_join(tools.phils[i].thread, NULL);
	if (tools.nb_must_eat > 0)
		pthread_join(tools.check, NULL);
	pthread_join(tools.check_death, NULL);
	phil_free(&tools);
	return (0);
}
