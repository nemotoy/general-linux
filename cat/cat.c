// rf. '$ man 2 read'
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
// rf. '$ man 2 close'
#include <unistd.h>
// rf. '$ man 2 open'
#include <fcntl.h>

static void do_cat(const char *path);
static void die(const char *s);

int
main(int argc, char *argv[])
{
  int i;
  if (argc < 2) {
    fprintf(stderr, "%s: file name not given\n", argv[0]);
    exit(1);
  }
  for (i = 1; i < argc; i++) {
    do_cat(argv[i]);
  }
  exit(0);
}

#define BUFFER_SIZE 2048

static void
do_cat(const char *path)
{
  int fb;
  unsigned char buf[BUFFER_SIZE];
  int n;

  fb = open(path, O_RDONLY);
  if (fb < 0 ) die(path);
  for (;;) {
    n = read(fb, buf, sizeof buf);
    if (n < 0) die(path);
    if (n == 0) break;
    if (write(STDOUT_FILENO, buf, n) < 0) die(path);
  }
  if (close(fb) < 0) die(path);
}

static void
die(const char *s)
{
  perror(s);
  exit(1);
}

