/*
** serveur.c for server in /home/zellou_i/rendu/PSU_2013_myftp
**
** Made by ilyas zelloufi
** Login   <zellou_i@epitech.net>
**
** Started on  Fri Apr 11 16:01:31 2014 ilyas zelloufi
** Last update Sun Apr 13 21:13:32 2014 ilyas zelloufi
*/

#include		<sys/types.h>
#include		<sys/socket.h>
#include		<unistd.h>
#include		<stdlib.h>
#include		<stdio.h>
#include		<netdb.h>
#include		<string.h>
#include		<netinet/in.h>
#include		<arpa/inet.h>
#include		<sys/stat.h>
#include		<fcntl.h>
#include		"serveur.h"

t_cmd			tab[] =
  {
    {"put", &my_put},
    {"get", &my_get},
    {"ls\n", &my_ls},
    {"pwd\n", &my_pwd},
    {NULL, NULL},
  };

void			get_cmd(t_file *t, int s)
{
  char			**cmd;
  int			i;

  i = 0;
  cmd = my_str_to_wordtab(t->buff, ' ');
  while (cmd[i])
    i++;
  if (i > 2)
    perror("Error : command not found.");
  else
    {
      i = -1;
      while (tab[++i].cmd != NULL && strcmp(cmd[0], tab[i].cmd) != 0);
      if (tab[i].cmd == NULL)
	{
	  puts(cmd[0]);
	  perror("Error : command not found.");
	}
      else
	tab[i].fptr(s, cmd[1]);
    }
}

int			my_server(int s, char *ip)
{
  t_file		t;

  while (42)
    {
      bzero(t.buff, SIZE);
      t.ret = read(s, t.buff, SIZE);
      if (strcmp(t.buff, "quit\n") == 0)
	printf("Connection closed with %s.\n", ip);
      else if (t.buff[0] != '\n')
	get_cmd(&t, s);
    }
}

void			init_server(char *port, int *s)
{
  int			p;
  struct protoent	*pe;
  struct sockaddr_in	sin;

  p = atoi(port);
  pe = getprotobyname("TCP");
  if ((*s = socket(AF_INET, SOCK_STREAM, pe->p_proto)) == -1)
    my_exit("socket() fail.\n");
  sin.sin_family = AF_INET;
  sin.sin_port = htons(p);
  sin.sin_addr.s_addr = INADDR_ANY;
  if (bind(*s, (const struct sockaddr *)&sin, sizeof(sin)) == -1)
    {
      close (*s);
      my_exit("bind() fail.\n");
    }
  if (listen(*s, 42) == -1)
    {
      close (*s);
      my_exit("listen() fail.\n");
    }
}

int			main(int ac, char **av)
{
  char			*ip;
  int			cs;
  int			len;
  struct sockaddr_in	sin_client;
  int			s;

  if (ac != 2)
    my_exit("USAGE : ./serveur port");
  init_server(av[1], &s);
  while (2)
    {
      len = sizeof(sin_client);
      if ((cs = accept(s, (struct sockaddr *) &sin_client, &len)) == -1)
	my_exit("accept() fail.\n");
      ip = inet_ntoa(sin_client.sin_addr);
      if (!fork())
	{
	printf("Connect with %s.\n", ip);
	my_server(cs, ip);
	exit (0);
      }
      while (waitpid(-1, NULL, WNOHANG) > 0);
    }
}
