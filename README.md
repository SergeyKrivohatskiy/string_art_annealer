Image as string art
===============
This is a small C++ tool for recreating an input image as string art.

The tool searches for a path of string around the nails. 

Example:

![bjorn_input](http://s10.postimg.org/6tdq69tcl/bjorn.png)
![bjorn_output](http://s10.postimg.org/5fm3ayu39/bjorn_out.png)

The solution is based on simulated annealing metod and very straightforward. But is's easy to modify the metric and apply limitations to the solution.

There is a much faster solution based on solving a linear system. Like [here](https://github.com/danielvarga/string-art) for example.


License
---------------
The project uses MIT license. See LICENSE file for the details.


Compatibility
---------------
The project is tested with
- Visual Studio 14(2015)
