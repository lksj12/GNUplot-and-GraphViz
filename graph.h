#include <string>
#include <fstream>
#include <vector>
#include "windows.h"

using std::string;
using std::vector;
using std::pair;
using std::ofstream;

class GNUplot
{
private:
	string p = "";
	string set = "";
	vector<string> pl;
	vector<vector<pair<double, double>>> dat;
	int cnt = 0;

	string leg = "";

public:
	void plot(vector<double> x, vector<double> y, string color = "", string label = "",\
	 string style = "lp", string point_type = "7", string line_width = "1")
	{
		if(cnt == 0){ p += "plot \"-\" "; }
		else{ p += "\"-\" "; }
		if (color != ""){ p += "lc rgb \"" + color + "\" ";}
		p += "pt " + point_type + " lw " + line_width + " w " + style + ", ";

		dat.emplace_back(vector<pair<double, double>>());
		dat[cnt].assign(x.capacity(), pair<double, double> (0.0, 0.0));

		for(int i = 0; i < x.capacity(); i++)
		{
			dat[cnt][i].first = x[i];
			dat[cnt][i].second = y[i];
		}

		pl.emplace_back(p);
		p = "";

		cnt += 1;
	}

	void xyaxis(bool x_ax = true, bool y_ax = true)
	{
		string axis = "";

		if(x_ax && y_ax) { axis = "set zeroaxis lc rgb \"black\" lt 1\n"; }
		else if(x_ax == false && y_ax) { axis = "set yzeroaxis lc rgb \"black\" lt 1\n"; }
		else if(x_ax && y_ax == false) { axis = "set xzeroaxis lc rgb \"black\" lt 1\n"; }

		set = axis + set;
	}

	void grid()
	{
		string grid = "set grid\n";
		set = grid + set;
	}
	
	void title(string title)
	{
		string tit = "set title \"" + title + "\"\n";
		set = set + tit;
	}

	void legend()
	{
		leg = "on";
	}

	void show()
	{
		ofstream fout;
		fout.open("a.plt");

		fout << set;
		if (leg == "") { fout << "set key off\n"; }

		for(int i = 0; i < pl.capacity(); i++){	fout << pl[i]; }
		fout << "\n";

		for (int i = 0; i < dat.capacity(); i++)
		{
			for (int j = 0; j < dat[i].capacity(); j++)
			{
				fout << dat[i][j].first << " " << dat[i][j].second << "\n";
			}
			fout << "e\n";
		}

		fout << "pause mouse";

		fout.close();

		system("gnuplot a.plt");
		system("del a.plt");
	}
	
	void savefig(string fn)
	{
		ofstream fout;
		fout.open("a.plt");

		string type = "";

		for (int i = fn.length()-3; i < fn.length(); i++)
		{
			type += fn[i];
		}

		if (type == "png"){	fout << "set term png\n"; }
		else if(type == "eps"){ fout << "set term postscript color enhance eps\n"; }

		fout << "set output \"" << fn << "\"\n";

		fout << set;
		if (leg == "") { fout << "set key off\n"; }

		for(int i = 0; i < pl.capacity(); i++){	fout << pl[i]; }
		fout << "\n";

		for (int i = 0; i < dat.capacity(); i++)
		{
			for (int j = 0; j < dat[i].capacity(); j++)
			{
				fout << dat[i][j].first << " " << dat[i][j].second << "\n";
			}
			fout << "e\n";
		}

		fout.close();

		system("gnuplot a.plt");
		system("del a.plt");
	}
};

class GraphViz
{
private:
	vector<string> nodes;
	vector<pair<string, string>> edges;
	string set = "";
public:
	void add_node(string node){ nodes.emplace_back(node); }
	void add_edge(pair<string, string> edge){ edges.emplace_back(edge); }
	void add_nodes_from(vector<string> n)
	{
		for(int i = 0; i < n.capacity(); i++)
		{
			nodes.emplace_back(n[i]);
		}
	}
	void add_edges_from(vector<pair<string, string>> e)
	{
		for(int i = 0; i<e.capacity(); i++)
		{
			edges.emplace_back(e[i]);
		}
	}
	void remove_node(string node)
	{
		int ind = -1;
		for (int i = 0; i < nodes.capacity(); i++)
		{
			if (nodes[i] == node)
			{
				ind = i;
				break;
			}
		}
		if (ind == -1)
		{
			throw std::runtime_error("Your graph does not have node \"" + node + "\"!");
		}
		else
		{
			nodes.erase(ind);
			nodes.shrink_to_fit();
		}
	}

	void remove_edge(pair<string, string> edge)
	{
		int ind = -1;
		for(int i = 0; i < edges.capacity(); i++)
		{
			if(edges[i].first == edge.first && edges[i].second == edge.second)
			{
				ind = i;
				break;
			}
		}

		if(ind == -1)
		{
			throw std::runtime_error("Your graph does not have node \"(" + edge.first + ", " + edge.second + ")\"!");
		}
		else
		{
			edes.erase(ind);
			edes.shrink_to_fit();
		}
	}

	void setting(bool Di = false, string rankdir = "LR")
	{
		if(Di == false){set += "graph G{\n";}
		else{set += "digraph DG{\n";}

		if (rankdir != "LR" && rankdir != "RL" && rankdir != "BT" && rankdir != "TB")
		{
			throw std::runtime_error("The rankdir \"" + rankdir + "\" is not exist in GraphViz!");
		}

		set += "rankdir = " + rankdir + ";\n";
	}

	void show()
	{
		ofstream fout;
		fout.open("a.dot");
		fout.close();
		system("gvedit a.dot");
		system("del a.dot");
	}
	void savefig(){}

};