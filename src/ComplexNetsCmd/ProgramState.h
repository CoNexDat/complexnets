class ProgramState {

private:
	bool isWeighted;
    WeightedGraph *weightedGraph;
    Graph *graph;

public:
	void setIsWeighted(bool isWeighted);
	void setWeightedGraph(WeightedGraph *weightedGraph);
	void setGraph(Graph *weightedGraph);
}