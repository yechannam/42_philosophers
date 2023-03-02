/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yecnam <yecnam@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 15:03:03 by yecnam            #+#    #+#             */
/*   Updated: 2023/03/02 14:37:57 by yecnam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>

typedef struct s_info
{
	int				philo_num;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				must_eat;
	long long		start_time;
}	t_info;

typedef struct s_data
{
	int				end;
	int				end_eat;
	pthread_mutex_t	flag;
	pthread_mutex_t	*fork;
	pthread_mutex_t	*philo;
	pthread_mutex_t	print;
}	t_data;

typedef struct s_philo
{
	int				num;
	int				right;
	int				left;
	int				count_eat;
	int				finish_eat;
	long long		last_eat;
	struct s_info	info;
	struct s_data	*data;
	pthread_t		thread;
}	t_philo;

int			free_fork(t_data *data, int max, t_info info);
int			data_init_start(t_data *data);
int			free_philo_mutex(t_data *data);
int			free_philo(t_data *data, int max);
void		thread_init(t_philo *philo);
int			fork_init(t_data *data, t_info info);
int			info_init(int argc, char **argv, t_info *info);
int			philo_init(t_philo **philo, t_info info, t_data *data);
void		*thread_ing(void *data);
long long	ft_gettime(void);
void		print_state(t_philo philo, char *msg);
void		ft_sleep(long long wait_time);
void		odd_fork(t_philo *philo, t_data *data);
void		even_fork(t_philo *philo, t_data *data);
void		check_finish(t_philo **philo);
long long	ft_atoll(const char *str);
int			data_init(t_data *data, t_info info);
void		sleep_think(t_philo *philo);
int			check_enough_eat(t_philo **philo, int *i);
int			check_die(t_philo **philo, int *idx);

#endif