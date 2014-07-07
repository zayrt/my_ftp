/*
** cmd.c for cmd in /home/zellou_i/rendu/PSU_2013_myftp
** 
** Made by ilyas zelloufi
** Login   <zellou_i@epitech.net>
** 
** Started on  Sun Apr 13 19:11:49 2014 ilyas zelloufi
** Last update Sun Apr 13 21:17:03 2014 ilyas zelloufi
*/

#include		<sys/types.h>
#include		<unistd.h>
#include		<stdio.h>
#include		<stdlib.h>
#include		<string.h>
#include		<fcntl.h>
#include		<sys/stat.h>
#include		<dirent.h>
#include		"serveur.h"

char			*my_concat(char *fd_name)
{
  int			i;
  char			*path_fd;

  i = 0;
  path_fd = malloc(sizeof(char) * strlen(fd_name) + 11);
  if (path_fd == NULL)
    my_exit("Malloc() fail");
  sprintf(path_fd, "./ftp_data/%s", fd_name);
  path_fd[strlen(path_fd) - 1] = '\0';
  return (path_fd);
}

int			my_put(int s, char *file_name)
{
  t_file		t;
  int			fd;

  t.sent = 0;
  fd = open(my_concat(file_name), O_WRONLY | O_CREAT | O_TRUNC, 0644);
  if (fd == -1)
    my_exit("Open() fail");
  t.ret = read(s, t.buff, SIZE);
  t.buff[t.ret] = '\0';
  t.size_file = atol(t.buff);
  while (t.sent != t.size_file)
    {
      bzero(t.buff, SIZE);
      t.ret = read(s, t.buff, SIZE);
      if (t.ret > 0)
	{
	  t.buff[t.ret] = '\0';
	  t.ret = write(fd, t.buff, t.ret);
	  t.sent += t.ret;
	  printf("%d/%d octects sent.\n", t.sent, t.size_file);
	}
    }
  close(fd);
  return (TRUE);
}

int			my_get(int s, char *file_name)
{
  t_file		t;

  t.sent = 0;
  if ((t.fd = fopen(my_concat(file_name), "rb")) == NULL)
    my_exit("Fopen() fail");
  if ((t.f = open(my_concat(file_name), O_RDONLY)) == -1)
    my_exit("Open() fail");
  t.size_file = lseek(t.f, 0, SEEK_END);
  sprintf(t.size, "%d", t.size_file);
  write(s, t.size, strlen(t.size));
  usleep(20000);
  while (t.sent != t.size_file)
    {
      bzero(t.buff, SIZE);
      if ((t.ret = fread(t.buff, 1, SIZE, t.fd)) > 0)
	{
	  t.buff[t.ret] = '\0';
	  t.ret = write(s, t.buff, t.ret);
	  t.sent += t.ret;
	  usleep(20000);
	  printf("%d/%d octects sent.\n", t.sent, t.size_file);
	}
    }
  return (TRUE);
}

int		my_ls(int s, char *str)
{
  DIR		*dir;
  struct dirent	*ent;

  (void)s;
  (void)str;
  dir = opendir("./ftp_data/");
  if (!dir)
    my_exit("Opendir() fail");
  while ((ent = readdir(dir)) != NULL)
    puts(ent->d_name);
  puts("");
  closedir(dir);
  return (TRUE);
}

int		my_pwd(int s, char *str)
{
  char		*pwd;

  (void)s;
  (void)str;
  pwd = malloc(sizeof(char) * SIZE);
  if (pwd == NULL)
    my_exit("Malloc() fail");
  pwd = getcwd(pwd, SIZE);
  if (pwd != NULL)
    puts(pwd);
  puts("");
  return (TRUE);
}
