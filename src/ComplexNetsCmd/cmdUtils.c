#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "cmdUtils.h"

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

char* strreplace(char s[], char chr, char repl_chr)
{
     int i=0;
     while(s[i]!='\0')
     {
           if(s[i]==chr)
           {
               s[i]=repl_chr;
           }  
           i++; 
     }
    return s;
}

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

void plotResults(const char *graph_name) 
{
    DIR *dir;
    struct dirent *entry;

    char dir_name[100] = "./results/";

    stringcat(dir_name, graph_name);

    if (!(dir = opendir(dir_name)))
        return;

    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type != DT_DIR) {
            char plot_cmd[200] = "./complexnetspp --view ";
            stringcat(plot_cmd, graph_name);
            stringcat(plot_cmd, " ");
            stringcat(plot_cmd, entry->d_name);
            stringcat(plot_cmd, " | gnuplot -p -e \" set title '");
            stringcat(plot_cmd, strreplace(entry->d_name, '_', ' '));
            stringcat(plot_cmd, "'; set logscale; plot '-' w linespoints;\"");

            const int sys_err = system(plot_cmd);
            if (sys_err == -1 || sys_err == 256) {
                printf("An error ocurred\n");
            }
        }
    }
}

int findIndex(char *analysis_name)
{
    int index = 0;
    while (index < ANALYSIS_CANT)
    {
        if (strcmp(analysis_names[index], analysis_name) == 0) {
            return index;
        }
        index++;
    } 
    return -1;
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
    int header_index = findIndex(analysis_name);
    printf("%s\n", header_name[header_index]);
    c = fgetc(f);
    while (c != EOF)
    {
      printf ("%c", c);
      c = fgetc(f);
    }
    fclose(f);
}

