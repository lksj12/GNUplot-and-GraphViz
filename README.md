# GNUplot-and-GraphViz
plotting mathematic graph and network graph header file for c++

I am just amateur programmer!

But I tried to make library(header file) for visualize mathematical function graph and network graph with c++

If you want to this file, first you need to install [Gnuplot](http://www.gnuplot.info/download.html) and [Graphviz](https://www.graphviz.org/download/).

Gnuplot is plotting program for mathematical function and Graphviz is one for network graph.

Graphviz part is incomplete. So this is not working now.

Gnuplot part can plot only 2D graph, but this can plot multiple graphs.

I tried to make this similar python's working process with my best.
Thank you.

# GNUPlot Part
## Simple Examples of GNUplot Part
The name of class for using Gnuplot is GNUplot.

~~~
#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include "graph.h"

using std::cout;
using std::vector;

using std::exp;

int main()
{
    GNUplot plt; //GNUplot class in graph.h
    vector<double> x(20);
    vector<double> y(20);
    
    for (int i = 0; i<x.capacity(); i++)
    {
        x[i] = i*0.1;
        y[i] = exp(x[i]);
    }
    
    plt.plot(x,y);
    plt.show();
}
~~~

This is end!
If you want to save the figure, you can use savefig().
~~~
#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include "graph.h"

using std::cout;
using std::vector;

using std::exp;

int main()
{
    GNUplot plt; //GNUplot class in graph.h
    vector<double> x(20);
    vector<double> y(20);
    
    for (int i = 0; i<x.capacity(); i++)
    {
        x[i] = i*0.1;
        y[i] = exp(x[i]);
    }
    
    plt.plot(x,y);
    plt.savefig("Exponential.png"); //or plt.savefig("Exponential.esp");
}
~~~

You can only extract figure to png and eps now.

## GNUplot's functions
    plot(x, y, color = "", label = "", style = "lp", point_type = "7", line_width = "1")

x and y are vector<double> type.

color, label, style, point_type, and line_width are string type.

You can use color with rgb color name e.g. red black green etc.

The label is graph's name. If you want to use legend, I recommend write the graph's label.
    
The style is line's style. Default option is "lp". Gnuplot support l, p, and lp called line, points, and line points respectively.
    
The point_type is literally the points' shape. The list of point shape is showed [here](https://livebook.manning.com/book/gnuplot-in-action-second-edition/chapter-9/158)
    
The line_width is literally line's width. The value is larger, figure's line's width will be larger.
    
    xyaxis(xaxis = true, yaxis = true)

xaxis and yaxis are bool type.
    
The xaxis represents y = 0 line, and yaxis represents x = 0 line.
    
    grid()

This fuction just plot grid line, when you call this.
    
    title(string title)
    
This function just show the figure's title, when you call this function.
    
    lengend()
    
If you call this function, Gnuplot will show the legend.

    show()

You should call this function or savefig, after all graphs are plotted, if you want to check your graph.
    
    savefig(fn)
    
You should call this function or show, after all graphs are plotted, if you want to check your graph.
    
fn is file name. e.g. "Exponential.png", "Exponential.eps" etc.
    
# GraphViz Part
## Simple Examples of GraphViz Part
I will update this part.
