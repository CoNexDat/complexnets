#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sstream>
#include <algorithm>
#include <string>
#include "cmdUtils.h"

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

    std::string dir_name = RESULTS_DIR;

    dir_name += std::string(graph_name);

    if (!(dir = opendir(dir_name.c_str())))
        return;

    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type != DT_DIR) {
            std::stringstream plot_cmd;
            std::string d_name = std::string(entry->d_name);
            std::string d_name_with_space = d_name;
            std::replace(d_name_with_space.begin(), d_name_with_space.end(), '_', ' ');
            plot_cmd << "./complexnetspp --view " << std::string(graph_name) << " " << d_name << " | gnuplot -p -e \" set title '" << d_name_with_space << "'; set logscale; plot '-' w linespoints;\"";
            const std::string aux = plot_cmd.str();
            const int sys_err = system(aux.c_str());
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
    std::stringstream dir;
    dir << RESULTS_DIR << std::string(graph_name) << "/" << std::string(analysis_name);
    FILE *f;
    const std::string dir_aux = dir.str();
    f = fopen(dir_aux.c_str(), "r");
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

