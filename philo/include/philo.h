/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonnard <abonnard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 12:00:54 by abonnard          #+#    #+#             */
/*   Updated: 2025/03/17 20:04:19 by abonnard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define MSG_FORK "%lld %d has taken a fork\n"
# define MSG_EAT "%lld %d is eating\n"
# define MSG_SLEEP "%lld %d is sleeping\n"
# define MSG_THINK "%lld %d is thinking\n"
# define MSG_DEAD "%lld %d died\n"

typedef struct s_tools
{
	int				nb_phil;
	long long		start;
	long long		time_to_die;
	long long		time_to_eat;
	long long		time_to_sleep;
	int				nb_must_eat;
	pthread_mutex_t	print;
	pthread_mutex_t	*forks;
	struct s_phil	*phils;
	pthread_t		check;
	pthread_t		check_death;
}					t_tools;

typedef struct s_phil
{
	pthread_t		thread;
	int				stop;
	int				id;
	int				eat_count;
	long long		last_eat;
	pthread_mutex_t	m_stop;
	pthread_mutex_t	m_eat_count;
	pthread_mutex_t	m_last_eat;
	pthread_mutex_t	*fork_left;
	pthread_mutex_t	*fork_right;

	t_tools			*tools;
}					t_phil;

int					ft_usleep(long long time, t_phil *phil);
int					print_msg(t_phil *phil, char *msg, int dead);
int					choose_fork(t_phil *phil);
int					my_fork(t_phil *phil);
void				*check_dead(void *ptr);
void				*check_thread(void *ptr);
long long			get_time(void);
int					ft_atoi(const char *nptr);
void				*ft_calloc(size_t nmemb, size_t size);
int					init_thread_check(t_tools *tools);
int					phil_init(int ac, char **av, t_tools *tools);
int					phil_create(t_tools *tools);
void				phil_free(t_tools *tools);
void				*update_death(t_tools *tools);

#endif
