/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szverhov <szverhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 18:54:24 by szverhov          #+#    #+#             */
/*   Updated: 2017/10/30 12:15:13 by szverhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_H
# define CLIENT_H

# include <string.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <string.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <netdb.h>
# include <arpa/inet.h>
# include <netinet/in.h>
# include <stdlib.h>
# include <unistd.h>
# include "get_next_line.h"

typedef struct	s_m
{
	int				status;
	struct addrinfo	hints;
	struct addrinfo	*res;
	int				sockfd;
	char			*res_str;
	char			*tmp;
	char			*ip_for_serv;
	char			*ip_of_serv;
	char			*data;
	int				fd;
	char			**files;
}				t_m;

typedef struct	s_rdfs
{
	struct sockaddr_storage	their_addr;
	socklen_t				addr_size;
	struct addrinfo			hints;
	struct addrinfo			*res;
	int						sockfd;
	int						new_fd;
	char					*buff;
	fd_set					set;
	struct timeval			timeout;
	int						rv;
}				t_rdfs;

void			ft_asmsz(char **files);
void			ft_execute_asm_and_startsz(char **files);
int				ft_check_argssz(int argc, char **argv, char **res_str);
int				ft_atoisz(char *str);
char			*ft_sub_strsz(char *str, char end);
int				ft_slsz(char *str);
int				ft_return_namesz(char *argv);
char			*ft_get_ipsz();
void			inner_rdfssz(t_rdfs *v, char *my_ip);
char			*ft_recive_data_from_serversz(char *my_ip);
char			*ft_strsubbsz(char *s, unsigned int start, size_t len);
int				count_of_wordssz(char *s, char c);
int				ft_strcmpsz(const char *s1, const char *s2);
int				ft_check_name(char *name);
void			ft_add_numsz(char *ip, char **res, int *adds);
char			*ft_free_return_zerosz(char **str);
char			*ft_make_serv_ipsz(char *ip);
char			**ft_strsplitsz(char *s, char c);
void			ft_reallsz(char **str, char *tmp);
void			ft_creat_filesz(char *buf);
int				ft_remove_namesz(char *buf);
void			ft_start_warsz(char **files);
void			ft_realsz(char **str, char *tmp);
void			ft_rm_rf_cors(char **names);
int				ft_return_0(char **str);

#endif
