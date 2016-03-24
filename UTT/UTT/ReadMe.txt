========================================================================
    CONSOLE APPLICATION : UTT Project Overview
========================================================================

AppWizard has created this UTT application for you.

This file contains a summary of what you will find in each of the files that
make up your UTT application.


UTT.vcxproj
    This is the main project file for VC++ projects generated using an Application Wizard.
    It contains information about the version of Visual C++ that generated the file, and
    information about the platforms, configurations, and project features selected with the
    Application Wizard.

UTT.vcxproj.filters
    This is the filters file for VC++ projects generated using an Application Wizard. 
    It contains information about the association between the files in your project 
    and the filters. This association is used in the IDE to show grouping of files with
    similar extensions under a specific node (for e.g. ".cpp" files are associated with the
    "Source Files" filter).

UTT.cpp
    This is the main application source file.

/////////////////////////////////////////////////////////////////////////////
Other standard files:

StdAfx.h, StdAfx.cpp
    These files are used to build a precompiled header (PCH) file
    named UTT.pch and a precompiled types file named StdAfx.obj.

/////////////////////////////////////////////////////////////////////////////
Other notes:

AppWizard uses "TODO:" comments to indicate parts of the source code you
should add to or customize.

/////////////////////////////////////////////////////////////////////////////

In Position am implementat urmatoarele functii:

	-int get_position(int board, int i, int j) const;
	(primeste ca parametrii un joc si pozitiile; intoarce elementul din pozitia cautata)

	-void set_position(std::string &s, int board, int i, int j, int player);
	(primeste ca parametrii un vector(tabla), jocul, pozitiile i si j si payerul ( 1 - X; 2 - zero) si seteaza 
	payerul pe pozitia respectiva)

In Board am implementat functiile:

	-bool is_empty_board(std::string &s, int board);
	(primeste ca parametrii tabla si un joc si verifica daca tot board-ul e gol)
	
	-bool board_to_close(std::string &s, int board, int player);
	(verifica daca se poate inchide board-ul dintr-o mutare)

	-int position_to_board(int value);
	(invers ca la get_position)

	-std::vector<int> empty_positions(std::string &s, int board);
	(returneaza setul de valori din vetcor care sunt libere in board-ul de 3x3)