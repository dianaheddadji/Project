This file summarizes the same content from "Heddadji-Project-LIEC.pdf"

It's a mini racket compiler interpreting the language python to mips


Requirements :
	- Python
		Command line installation : sudo apt-get install python
		or consult and follow the instructions in graphical mode on the link bellow : 
		https://www.python.org/downloads/

	- Spim
		Command line installation : sudo apt-get install spim
		or consult and follow the instructions in graphical mode on the link bellow : 
		https://sourceforge.net/projects/spimsimulator/files/

	- Dr. Racket
		Command line installation : sudo apt-get install racket
		or consult and follow the instructions in graphical mode on the link bellow : 
		https://download.racket-lang.org/


Compilation :
	Open a terminal on the Racket folder and type the following line : /Racket$ liec ../test-Python/*.py
	- "*" must be replaced with the name of one of the .py files in the folder "test-Python"
	This will generate a file with the extension .s compilable and executable on the SPIM simulator.
	
	Then, in the test-Python directory, open a terminal and launch spim by simply typing the command :
	- spim

	load the generated .s file with the load command, for example:
	- load "test1.py.s"

	Finally, for the execution :
	- run

There are some error tests in the "errors" folder
	
	


