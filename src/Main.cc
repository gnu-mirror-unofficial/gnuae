// 
//   Copyright (C) 2003, 2004, 2005, 2006, 2007, 2008,
//              2009 Free Software Foundation, Inc.
// 
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

// This is generated by autoconf
#include "config.h"

#include <string>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <getopt.h>
#include <iostream>

#include "Database.h"
#include "Battery.h"
#include "Centers.h"
#include "Chargers.h"
#include "Combiners.h"
#include "Inverters.h"
#include "Loads.h"
#include "PVPanel.h"
#include "Pumps.h"
#include "Wire.h"
#include "log.h"
#include "tcpip.h"
#include "gnuae.h"

using namespace std;
using namespace gnuae;

static void usage (const char *);

static LogFile& dbglogfile = LogFile::getDefaultInstance();
static GnuAE& gdata = GnuAE::getDefaultInstance();

int
main(int argc, char **argv) {
    int c, status, result;
    bool logopen = false;
    const char *errmsg;
    char buf[30];
    bool dump = false;
    string mod_filespec, search;
    PVPanels pv;
    pvpanel_t *entry;
    
    string      hostname;
    string      user;
    string      passwd;
    
    // scan for the two main standard GNU options
    for (c=0; c<argc; c++) {
	if (strcmp("--help", argv[c]) == 0) {
	    usage(argv[0]);
	    exit(0);
	}
	if (strcmp("--version", argv[c]) == 0) {
	    cerr << "GnuAE version: " << VERSION << endl;
	    // fprintf (stderr, "GnuAE version: %s\n", VERSION);
	    exit(0);
	}
    }
    
    while ((c = getopt (argc, argv, "dhvs:l:m:r:u:p:xc")) != -1) {
	switch (c) {
	  case 'd':
	      dump = true;        
	      break;
	      
	  case 'l':
	      logopen = true;
	      dbglogfile.Open (optarg);
	      break;
	      
	  case 'm':
	      mod_filespec = optarg;
	      break;
	      
	  case 's':
	      search = optarg;
	      break;
	      
	  case 'h':
	      usage (argv[0]);
	      break;
	      
	  case 'v':
	      dbglogfile.set_verbosity();
	      break;
	      
	  case 'r':
	      hostname = optarg;
	      gdata.dbHostSet(hostname);
	      break;
	      
	      // Specify database user name.
	  case 'u': 
	      user = optarg;
	      gdata.dbUserSet(user);
	      break;
	      
	      // Specify database user password.
	  case 'p':
	      passwd = optarg;
	      gdata.dbPasswdSet(passwd);
	      break;
	      
	  case 'x':
	      gdata.useSQL(true);
	      dbglogfile << "Will use SQL queries instead of memory resident" << endl;
	      break;
	      
	  case 'c':
	      gdata.useCSV(true);
	      dbglogfile << "Will use CSV files to load memory resident" << endl;
	      break;
	      
	  default:
	      usage (argv[0]);
	      exit(0);
	}
    }
    
    if (!logopen) {
	dbglogfile.Open (DEFAULT_LOGFILE);
    }
#if 0
    if (mod_filespec.size() == 0) {
	mod_filespec = "/home/rob/projects/gnu/gnuae/data/Modules.csv";
    }
#endif
    
    // cout << "Using " << mod_filespec << " for PV Modules data file" << endl;
    
    //  if (optind + 1 != argc)
    //  usage (argv[0]);
    
    // if (pv.readModuleDataCSV(mod_filespec)) {
    
    // } else {
    // 	cerr << "Couldn't open PV module data file " << mod_filespec << endl;
    // }  
    
    gdata.openDB();
    gdata.loadData();
    
    // Dump the data in the data base
    if (dump) {
	gdata.dump();
    }

#if 0
    // Search the database for all entries that match the search string
    if (search.size()) {
	vector<pvpanel_t *>::iterator it;
	vector<pvpanel_t *> *pvary;
	pvary = pv.search(search);
	
	for (it = pvary->begin(); it != pvary->end(); it++) {
	    entry = *it;
	    pv.dump(entry);
	}
    }
#endif
    
}

static void
usage (const char *prog)
{
    cerr << "Usage: " << prog << "[dlhvrup]" << endl;
    cerr << "-h\tHelp" << endl;
    cerr << "-m\tPV Modules data file name" << endl;
    cerr << "-l\tLogfile name" << endl;
    cerr << "-d\tDump PV Modules data" << endl;
    cerr << "-s\tDump a specific model's data" << endl;
    cerr << "-v\tVerbose mode" << endl;
    cerr << "-r\tRemote Machine (localhost)" << endl;
    cerr << "-u\tRemote Machine user" << endl;
    cerr << "-p\tRemote Machine password" << endl;
    exit (-1);
}

// local Variables:
// mode: C++
// indent-tabs-mode: t
// End:
