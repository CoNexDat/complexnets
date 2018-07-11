#pragma once

void listdir(const char *name, int indent);
void plotResults(const char *graph_name);
void printFile(char *graph_name, char *analysis_name);
int findIndex(char *analysis_name);

static const int ANALYSIS_CANT = 7;
static const char *RESULTS_DIR = "./results";
static const char *analysis_names[] = {
	"betweenness",
	"degree_distribution",
	"clustering_coefficient",
	"nearest_neighbors_degree",
	"shellIndex",
	"max_clique_distribution",
	"max_clique_distribution_aproximation"
};

static const char *header_name[] = {
	"#Betweenness Degree",
	"#Node p(d)",
	"#Clustering Degree",
	"#NearestNeighborsDegree Degree",
	"#ShellIndex Degree",
	"#Cliques Nodes",
	"#Cliques Nodes"
};