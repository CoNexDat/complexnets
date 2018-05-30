#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void listdir(const char *name, int indent)
{
    DIR *dir;
    struct dirent *entry;

    if (!(dir = opendir(name)))
        return;

    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_DIR) {
            char path[1024];
            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
                continue;
            snprintf(path, sizeof(path), "%s/%s", name, entry->d_name);
            printf("%*s[%s]\n", indent, "", entry->d_name);
            listdir(path, indent + 2);
        } else {
            printf("%*s- %s\n", indent, "", entry->d_name);
        }
    }
    closedir(dir);
}

char * stringcat(char *out, const char *in)
{
  char *anchor = out;
  size_t olen;

  if(out == NULL || in == NULL)
    return NULL;

  olen = strlen(out);
  out += olen;
  while((*out++ = *in++))
    ;
  return anchor;
}

void printFile(char *graph_name, char *analysis_name)
{
    char c;
    char dir[100] = "./results/";
    stringcat(dir, graph_name);
    stringcat(dir, "/");
    stringcat(dir, analysis_name);
    FILE *f;
    f = fopen(dir, "r");
    if (f == NULL)
    {
      printf("Result file not found for graph %s and analysis %s \n", graph_name, analysis_name);
      exit(0);
    }
    printf("Reading file from %s\n", dir);
    c = fgetc(f);
    while (c != EOF)
    {
      printf ("%c", c);
      c = fgetc(f);
    }
    fclose(f);
}

