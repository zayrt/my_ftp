/*
** client.c for client in /home/zellou_i/rendu/PSU_2013_myftp
**
** Made by ilyas zelloufi
** Login   <zellou_i@epitech.net>
**
** Started on  Fri Apr 11 16:01:50 2014 ilyas zelloufi
** Last update Sun Apr 13 20:42:41 2014 ilyas zelloufi
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
#include		<fcntl.h>
#include		<sys/stat.h>
#include		"client.h"
#include		"file.h"

int			my_client(int s)
{
  char			**cmd;
  t_file		t;

  while (42)
    {
      write(1, "$> ", 3);
      t.ret = read(0, t.buff, SIZE);
      if (t.ret <= 0 || strcmp(t.buff, "quit\n") == 0)
	exit (0);
      t.buff[t.ret] = '\0';
      if (t.buff[0] != '\n')
	{
	  write(s, t.buff, t.ret);
	  usleep(20000);
	  cmd = my_str_to_wordtab(t.buff, ' ');
	  t.i = 0;
	  while (cmd[t.i])
	    t.i++;
	  if (strcmp(cmd[0], "put") == 0 && t.i == 2)
	    send_file(s, cmd[1]);
	  else if (strcmp(cmd[0], "get") == 0 && t.i == 2)
	    receive_file(s, cmd[1]);
	}
    }
}

int			send_file(int s, char *file_name)
{
  t_file		t;

  file_name[strlen(file_name) - 1] = '\0';
  if ((t.f = open(file_name, O_RDONLY)) == -1)
    my_exit("Open() fail");
  t.fd = fopen(file_name, "rb");
  t.sent = 0;
  t.size_file = lseek(t.f, 0, SEEK_END);
  sprintf(t.size, "%d\n", t.size_file);
  write(s, t.size, strlen(t.size));
  usleep(20000);
  while (t.sent != t.size_file)
    {
      t.ret = fread(t.buff, 1, SIZE, t.fd);
      t.buff[t.ret] = '\0';
      if (t.ret > 0)
	{
	  t.i = write(s, t.buff, t.ret);
	  usleep(20000);
	  t.sent += t.i;
	  printf("%d/%d octects sent.\n", t.sent, t.size_file);
	}
    }
}

int			receive_file(int s, char *file_name)
{
  t_file		t;

  file_name[strlen(file_name) - 1] = '\0';
  if ((t.f = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644)) == -1)
    my_exit("Open() fail");
  t.ret = read(s, t.buff, SIZE);
  t.sent = 0;
  t.buff[t.ret] = '\0';
  t.size_file = atol(t.buff);
  while (t.sent != t.size_file)
    {
      bzero(t.buff, SIZE);
      t.ret = read(s, t.buff, SIZE);
      if (t.ret > 0)
	{
	  t.buff[t.ret] = '\0';
	  t.ret = write(t.f, t.buff, t.ret);
	  t.sent += t.ret;
	  printf("%d/%d octects sent.\n", t.sent, t.size_file);
	}
    }
  close (t.f);
}

int			main(int ac, char **av)
{
  struct protoent	*pe;
  struct sockaddr_in	sin;
  int			s;
  int			port;
  char			*str;

  if (ac != 3)
    my_exit("Usage : ./client machine port");
  port = atoi(av[2]);
  pe = getprotobyname("TCP");
  if (pe == NULL)
    my_exit("Getprotobyname() fail");
  s = socket(AF_INET, SOCK_STREAM, pe->p_proto);
  if (s == -1)
    my_exit("socket() fail.\n");
  sin.sin_family = AF_INET;
  sin.sin_port = htons(port);
  sin.sin_addr.s_addr = inet_addr(av[1]);
  if (connect(s, (const struct sockaddr *)&sin, sizeof(sin)) == -1)
    my_exit("Connect() fail");
  if (my_client(s) == 0)
    return (0);
}
