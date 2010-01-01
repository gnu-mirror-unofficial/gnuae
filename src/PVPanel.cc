// 
//   Copyright (C) 2003, 2004, 2005, 2006, 2007, 2008,
//              2009, 2010 Free Software Foundation, Inc.
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

#include <sys/types.h>
#include <sys/stat.h>
#include <vector>
#include <string>
#include <cstring>
#include <iostream>
#include <fstream>
#include <iterator>
#include <cstdlib>
#include <memory>
#include <map>
#include <algorithm>

#include "DataType.h"
#include "Database.h"
#include "PVPanel.h"
#include "log.h"
#include "gnuae.h"

#ifdef __STDC_HOSTED__
#include <sstream>
#else
#include <strstream>
#endif

using namespace std;

namespace gnuae {

const int LINELEN = 1024;
const int FIELDLEN = 512;

static LogFile& dbglogfile = LogFile::getDefaultInstance();
static GnuAE& gdata = GnuAE::getDefaultInstance();

PVPanels::PVPanels(void)
{
    _debug = false;
    _enhanced = true;
}

PVPanels::~PVPanels(void)
{
    if (_data.size()) {
	std::map<std::string, pvpanel_t *>::const_iterator it;
 	for (it = _data.begin(); it != _data.end(); it++) {
 	    pvpanel_t *entry = it->second;
 	    if (entry) {
 		if (entry->Description) {
 		    free(entry->Description);
 		}
 		if (entry->Material) {
 		    free(entry->Material);
 		}
#if 0
 		if (entry->Picture) {
 		    free(entry->Picture);
 		}
#endif
 	    }
 	}
    }
}

void
PVPanels::dump(void)
{
    // DEBUGLOG_REPORT_FUNCTION;
    if (!dataSize()) {
	cerr << "No PVPanel data in memory." << endl;
    } else {
	vector<string>::iterator it;
	auto_ptr<vector<string> > loadnames = dataNames();
	for (it = loadnames->begin(); it != loadnames->end(); ++it) {
	    dump(findEntry(*it));
	}
    }
}

void
PVPanels::dump(pvpanel_t *pv)
{
    dump(pv, _enhanced);
}

void
PVPanels::dump(pvpanel_t *pv, bool enhanced)
{
    if (pv->name != 0) {
	if (*pv->name != 0) {
	    cerr << "PVPanel name is " << pv->name << endl;
	} else {
	    cerr << "No name specified" << endl;
	}
    }
    
    if (pv->Vintage != 0) {
	if (pv->Vintage != 0) {
	    cerr << "Vintage is " << pv->Vintage << endl;
	} else {
	    cerr << "No Vintage specified" << endl;
	}
    }
    
    cerr << "Area is " << pv->Area << endl;
    
    if (pv->Material != 0) {
	if (*pv->Material != 0) {
	    cerr << "Material is " << pv->Material << endl;
	} else {
	    cerr << "No Material specified" << endl;
	}
    }
    
    cerr << "Series Cells is " << pv->Series_Cells << endl;
    cerr << "Parallel_C-S is " << pv->Parallel_C_S << endl;
    cerr << "Isco is " << pv->Isco << endl;
    cerr << "Voco is " << pv->Voco << endl;
    cerr << "Impo is " << pv->Impo << endl;
    cerr << "Vmpo is " << pv->Vmpo << endl;
    cerr << "aIsc is " << pv->aIsc << endl;
    cerr << "aImp is " << pv->aImp << endl;
    cerr << "C0 is " << pv->C0 << endl;
    cerr << "C1 is " << pv->C1 << endl;
    cerr << "BVoco is " << pv->BVoco << endl;
    cerr << "mBVoc is " << pv->mBVoc << endl;
    cerr << "BVmpo is " << pv->BVmpo << endl;
    cerr << "mBVmp is " << pv->mBVmp << endl;
    cerr << "n is " << pv->n << endl;
    cerr << "C2 is " << pv->C2 << endl;
    cerr << "C3 is " << pv->C3 << endl;
    cerr << "A0 is " << pv->A0 << endl;
    cerr << "A1 is " << pv->A1 << endl;
    cerr << "A2 is " << pv->A2 << endl;
    cerr << "A3 is " << pv->A3 << endl;
    cerr << "A4 is " << pv->A4 << endl;
    cerr << "B0 is " << pv->B0 << endl;
    cerr << "B1 is " << pv->B1 << endl;
    cerr << "B2 is " << pv->B2 << endl;
    cerr << "B3 is " << pv->B3 << endl;
    cerr << "B4 is " << pv->B4 << endl;
    cerr << "B5 is " << pv->B5 << endl;
    cerr << "d(Tc) is " << pv->d_Tc << endl;
    cerr << "fd is " << pv->fd << endl;
    cerr << "a is " << pv->a << endl;
    cerr << "b is " << pv->b << endl;
    cerr << "C4 is " << pv->C4 << endl;
    cerr << "C5 is " << pv->C5 << endl;
    cerr << "Ixo is " << pv->Ixo << endl;
    cerr << "Ixxo is " << pv->Ixxo << endl;
    cerr << "C6 is " << pv->C6 << endl;
    cerr << "C7 is " << pv->C7 << endl;
    
    if (pv->Picture) {
	cerr << "Picture is " << pv->Picture << endl;
    }
    
    if (pv->Description != 0) {
	cerr << "Description is " << pv->Description << endl;
    }
    
    if (pv->manufacturer) {
	cerr << "manufacturer is " << pv->manufacturer << endl;
    }
}

// This reads a Comma delimited text file that is exported from the
// Sandia Module data base.
int
PVPanels::readModuleDataCSV(std::string filespec)
{
    pvpanel_t *pv;
    char buf[LINELEN];
    char *ptr, *token, *home;
    float val;
    int i;
    ifstream in;
    string tmpbuf, loadfile, field;
    struct stat stats;
    int lines = -1;
    string::size_type pos1;
    
    
    if (filespec.size() == 0) {
	home = getenv("HOME");
	
	if (home) {
	    loadfile = home;
	    loadfile += "/.gnuae/modules.csv";
	    if (stat(loadfile.c_str(), &stats) == 0) {
		filespec = loadfile;
	    } else {
		loadfile = "/etc/gnuae/modules.csv";
		if (stat(loadfile.c_str(), &stats) == 0) {
		    filespec = loadfile;
		}
	    }
	}
    }
    
    in.open(filespec.c_str());
    dbglogfile << "Reading PV Module data from: " << filespec.c_str() << endl;
    
    if (!in)
	{
	    dbglogfile << "Couldn't open file " << filespec.c_str() << endl;
	    return -1;
	}
    
    // Read in but ignore the first line, which are the headers in the
    // data file.
    in.getline(buf, LINELEN);
    ptr = buf;
    
    while (!in.eof()) {
	lines++;
	// Get memory to hold the data
	pv = new pvpanel_t;
	
#if 0
	// Get memory for the strings in the data structure
	pv->name = new char[FIELDLEN];
	pv->Vintage = new char[FIELDLEN];
	pv->Material = new char[FIELDLEN];
	pv->Picture = new char[FIELDLEN];
	pv->Description = new char[FIELDLEN];
#endif
	
	in.getline(buf, LINELEN, ','); // Get a token from the line
	tmpbuf = buf;
	if (tmpbuf.size()) {
	    // The string has double quote marks on each end, which is used by
	    // the CSV format. So we drop them to have just the plain string left.
	    tmpbuf.erase(0, 1);
	    tmpbuf.erase(tmpbuf.size()-1, 1);
	    pv->name = new char[strlen(buf)+1];
	    strcpy(pv->name, tmpbuf.c_str());
	}
	else {
	    return lines;
	}
	
	in.getline(buf, LINELEN, ','); // Get a token from the line
	tmpbuf = buf;
	if (tmpbuf.size()) {
	    // The string has double quote marks on each end, which is used by
	    // the CSV format. So we drop them to have just the plain string left.
	    tmpbuf.erase(0, 1);
	    tmpbuf.erase(tmpbuf.size()-1, 1);
	    pv->Vintage;// = new char[strlen(buf)+1];
	    pv->Vintage, strtol(tmpbuf.c_str(), NULL, 0);
	}
	
	in.getline(buf, LINELEN, ','); // Get a token from the line
	pv->Area = atof(buf);
	
	in.getline(buf, LINELEN, ','); // Get a token from the line
	tmpbuf = buf;
	if (tmpbuf.size()) {
	    // The string has double quote marks on each end, which is used by
	    // the CSV format. So we drop them to have just the plain string left.
	    tmpbuf.erase(0, 1);
	    tmpbuf.erase(tmpbuf.size()-1, 1);
	    pv->Material = new char[strlen(buf)+1];
	    strcpy(pv->Material, tmpbuf.c_str());
	}
	
	in.getline(buf, LINELEN, ','); // Get a token from the line
	pv->Series_Cells = atoi(buf);
	
	in.getline(buf, LINELEN, ','); // Get a token from the line
	pv->Parallel_C_S = atoi(buf);
	
	in.getline(buf, LINELEN, ','); // Get a token from the line
	pv->Isco = atof(buf);
	
	in.getline(buf, LINELEN, ','); // Get a token from the line
	pv->Voco = atof(buf);
	
	in.getline(buf, LINELEN, ','); // Get a token from the line
	pv->Impo = atof(buf);
	
	in.getline(buf, LINELEN, ','); // Get a token from the line
	pv->Vmpo = atof(buf);
	
	in.getline(buf, LINELEN, ','); // Get a token from the line
	pv->aIsc = atof(buf);
	
	in.getline(buf, LINELEN, ','); // Get a token from the line
	pv->aImp = atof(buf);
	
	in.getline(buf, LINELEN, ','); // Get a token from the line
	pv->C0 = atof(buf);
	
	in.getline(buf, LINELEN, ','); // Get a token from the line
	pv->C1 = atof(buf);
	
	in.getline(buf, LINELEN, ','); // Get a token from the line
	pv->BVoco = atof(buf);
	
	in.getline(buf, LINELEN, ','); // Get a token from the line
	pv->mBVoc = atof(buf);
	
	in.getline(buf, LINELEN, ','); // Get a token from the line
	pv->BVmpo = atof(buf);
	
	in.getline(buf, LINELEN, ','); // Get a token from the line
	pv->mBVmp = atof(buf);
	
	in.getline(buf, LINELEN, ','); // Get a token from the line
	pv->n = atof(buf);
	
	in.getline(buf, LINELEN, ','); // Get a token from the line
	pv->C2 = atof(buf);
	
	in.getline(buf, LINELEN, ','); // Get a token from the line
	pv->C3 = atof(buf);
	
	in.getline(buf, LINELEN, ','); // Get a token from the line
	pv->A0 = atof(buf);
	
	in.getline(buf, LINELEN, ','); // Get a token from the line
	pv->A1 = atof(buf);
	
	in.getline(buf, LINELEN, ','); // Get a token from the line
	pv->A2 = atof(buf);
	
	in.getline(buf, LINELEN, ','); // Get a token from the line
	pv->A3 = atof(buf);
	
	in.getline(buf, LINELEN, ','); // Get a token from the line
	pv->A4 = atof(buf);
	
	in.getline(buf, LINELEN, ','); // Get a token from the line
	pv->B0 = atof(buf);
	
	in.getline(buf, LINELEN, ','); // Get a token from the line
	pv->B1 = atof(buf);
	
	in.getline(buf, LINELEN, ','); // Get a token from the line
	pv->B2 = atof(buf);
	
	in.getline(buf, LINELEN, ','); // Get a token from the line
	pv->B3 = atof(buf);
	
	in.getline(buf, LINELEN, ','); // Get a token from the line
	pv->B4 = atof(buf);
	
	in.getline(buf, LINELEN, ','); // Get a token from the line
	pv->B5 = atof(buf);
	
	in.getline(buf, LINELEN, ','); // Get a token from the line
	pv->d_Tc = atof(buf);
	
	in.getline(buf, LINELEN, ','); // Get a token from the line
	pv->fd = atof(buf);
	
	in.getline(buf, LINELEN, ','); // Get a token from the line
	pv->a = atof(buf);
	
	in.getline(buf, LINELEN, ','); // Get a token from the line
	pv->b = atof(buf);
	
	in.getline(buf, LINELEN, ','); // Get a token from the line
	pv->C4 = atof(buf);
	
	in.getline(buf, LINELEN, ','); // Get a token from the line
	pv->C5 = atof(buf);
	
	in.getline(buf, LINELEN, ','); // Get a token from the line
	pv->Ixo = atof(buf);
	
	in.getline(buf, LINELEN, ','); // Get a token from the line
	pv->Ixxo = atof(buf);
	
	in.getline(buf, LINELEN, ','); // Get a token from the line
	pv->C6 = atof(buf);
	
	in.getline(buf, LINELEN, ','); // Get a token from the line
	pv->C7 = atof(buf);
	
	in.getline(buf, LINELEN, ','); // Get a token from the line
	tmpbuf = buf;
	if (tmpbuf.size()) {
	    // The string has double quote marks on each end, which is used by
	    // the CSV format. So we drop them to have just the plain string left.
	    tmpbuf.erase(0, 1);
	    tmpbuf.erase(tmpbuf.size()-1, 1);
	    //pv->Picture = new char[strlen(buf)+1];
	    // strcpy(pv->Picture, tmpbuf.c_str());
	    //std::copy(tmpbuf.begin(), tmpbuf.end(), pv->Picture);
	    pv->Picture = strdup(tmpbuf.c_str());
	} else {
	    pv->Picture = 0;
	}
	
	// This gets messy, as the description string itself may include
	// commas and/or quotes. So we read to the end of the line, and
	// for the remaining fields, we work our way backward.
	in.getline(buf, LINELEN, '\n'); // Get a token from the line
	tmpbuf = buf;
	if (tmpbuf.size()) {
	    if (_enhanced) {
		// in.getline(buf, LINELEN, ','); // Get a token from the line
		pos1 = tmpbuf.rfind(",", string::npos);
		if (pos1 == string::npos) {
		    cerr << "Comma not found!" << endl;
		} else {
		    field = tmpbuf.substr(pos1, string::npos);
		    field.erase(0, 1);    // erase the comma
		    if (field.substr(0, 1) == "\"") {
			field.erase(0, 1);    // erase the double quote
		    }
		    if (field.size() > 0) {
			field.erase(field.size(), 1); // erase last double quote
			if (field.size() == 1) {
			    pv->manufacturer = 0;
			} else {
			    pv->manufacturer = new char[field.size()+1];
			    strcpy(pv->manufacturer, field.c_str());
			    tmpbuf.erase(pos1, string::npos); // erase this part from
			    // the string
			}
		    }
		}
		
		pos1 = tmpbuf.rfind(",", pos1-1);
		if (pos1 == string::npos) {
		    cerr << "Comma not found!" << endl;
		} else {
		    field = tmpbuf.substr(pos1, string::npos);
		    field.erase(0, 1);    // erase the comma
		    if (field.size() > 0) {
			field.erase(field.size(), string::npos);
			// pv->Price = atof(field.c_str());
			tmpbuf.erase(pos1, string::npos); // erase this part from
			// the string
		    }
		}
		tmpbuf.erase(0, 1);   // erase the first double quote
		// Now erase the trailing double quote
		if (tmpbuf.substr(tmpbuf.size()-1, 1) == "\"") {
		    tmpbuf.erase(tmpbuf.size()-1, 2);
		}
		if (tmpbuf.substr(tmpbuf.size()-2, 1) == "\"") {
		    tmpbuf.erase(tmpbuf.size()-2, 2);
		}
		
		pv->Description = new char[tmpbuf.size()+1];
		// strcpy(pv->Description, tmpbuf.c_str());
		//std::copy(tmpbuf.begin(), tmpbuf.end(), pv->Description);
		pv->Description = strdup(tmpbuf.c_str());
	    }
	} // if _enhanced
	
	addEntry(pv);
    }
    
    in.close();
    return lines;
}

int
PVPanels::readModuleDataXML(std::string filespec)
{
    
}

vector<string> *
PVPanels::names(void)
{
    vector<pvpanel_t *>::iterator it;
    vector<string> *pvnames;
    pvpanel_t *entry;
    pvnames = new vector<string>;  
    
    if (_data.size() == 0) {
	dbglogfile << "No PV Panel data in memory" << endl;
	return pvnames;
    }
    
    for (it = _pvdata.begin(); it != _pvdata.end(); it++) {
	entry = *it;
	pvnames->push_back(entry->name);
    }
    
    return pvnames;
}

#if 0
vector<pvpanel_t *> *
PVPanels::search(std::string search)
{
    std::vector<pvpanel_t *>::iterator it;
    vector<pvpanel_t *> *pv;
    pvpanel_t *entry;
    pv = new vector<pvpanel_t *>;
    
    if (_data.size() == 0) {
	dbglogfile << "No PV Panel data in memory" << endl;
	return pv;
    }
    
    for (it = _data.begin(); it != _data.end(); it++) {
	if (strstr((*it)->name, search.c_str())) {
	    entry = *it;
	    pv->push_back(entry);
	}
    }
    
    return pv;
}
#endif

int
PVPanels::readSQL(Database &db)
{
    // DEBUGLOG_REPORT_FUNCTION;
    if (db.getState() == Database::DBOPENED) {
	string query = "SELECT * from modules";
	vector<vector<string> > *result = db.queryResults(query);
	vector<vector<string> >::iterator it;
	for (it=result->begin(); it!=result->end(); ++it) {
	    pvpanel_t *thispv = new pvpanel_t;
	    vector<string> &row = *it;
	    if (!row[1].empty()) {
		thispv->name = strdup(row[1].c_str());
	    }
	    if (!row[2].empty()) {
		thispv->manufacturer = strdup(row[2].c_str());
	    }
	    thispv->Vintage = strtol(row[3].c_str(), NULL, 0);
	    thispv->Area = strtof(row[4].c_str(), NULL);
	    if (!row[5].empty()) {
		thispv->Material = strdup(row[5].c_str());
	    }
	    thispv->Series_Cells = strtol(row[5].c_str(), NULL, 0);
	    thispv->Parallel_C_S = strtol(row[6].c_str(), NULL, 0);
	    thispv->Isco = strtof(row[7].c_str(), NULL);
	    thispv->Voco = strtof(row[8].c_str(), NULL);
	    thispv->Impo = strtof(row[9].c_str(), NULL);
	    thispv->Vmpo = strtof(row[10].c_str(), NULL);
	    thispv->aIsc = strtof(row[11].c_str(), NULL);
	    thispv->aImp = strtof(row[12].c_str(), NULL);
	    thispv->C0 = strtof(row[13].c_str(), NULL);
	    thispv->C1 = strtof(row[14].c_str(), NULL);
	    thispv->BVoco = strtof(row[15].c_str(), NULL);
	    thispv->mBVoc = strtof(row[16].c_str(), NULL);
	    thispv->BVmpo = strtof(row[17].c_str(), NULL);
	    thispv->BVmpo = strtof(row[18].c_str(), NULL);
	    thispv->n = strtof(row[19].c_str(), NULL);
	    thispv->C2 = strtof(row[20].c_str(), NULL);
	    thispv->C3 = strtof(row[21].c_str(), NULL);
	    thispv->A0 = strtof(row[22].c_str(), NULL);
	    thispv->A1 = strtof(row[23].c_str(), NULL);
	    thispv->A2 = strtof(row[24].c_str(), NULL);
	    thispv->A3 = strtof(row[25].c_str(), NULL);
	    thispv->A4 = strtof(row[26].c_str(), NULL);
	    thispv->B0 = strtof(row[27].c_str(), NULL);
	    thispv->B1 = strtof(row[28].c_str(), NULL);
	    thispv->B2 = strtof(row[29].c_str(), NULL);
	    thispv->B3 = strtof(row[30].c_str(), NULL);
	    thispv->B4 = strtof(row[31].c_str(), NULL);
	    thispv->B5 = strtof(row[32].c_str(), NULL);
	    thispv->d_Tc = strtof(row[33].c_str(), NULL);
	    thispv->fd = strtof(row[34].c_str(), NULL);
	    thispv->a = strtof(row[35].c_str(), NULL);
	    thispv->b = strtof(row[36].c_str(), NULL);
	    thispv->C4 = strtof(row[37].c_str(), NULL);
	    thispv->C5 = strtof(row[38].c_str(), NULL);
	    thispv->Ixo = strtof(row[39].c_str(), NULL);
	    thispv->Ixxo = strtof(row[40].c_str(), NULL);
	    thispv->C6 = strtof(row[42].c_str(), NULL);
	    thispv->C7 = strtof(row[43].c_str(), NULL);
	    if (!row[44].empty()) {
		if (row[44] != "0") {
		    thispv->Picture = strdup(row[44].c_str());
		} else {
		    thispv->Picture = 0;
		}
	    }
	    if (!row[45].empty()) {
		if (row[44] != "0") {
		    thispv->Description = strdup(row[45].c_str());
		} else {
		    thispv->Description = 0;
		}
	    }

	    addEntry(thispv);
	}
	delete result;
    }

    dbglogfile << "Loaded " << dataSize() << " records from pvpanels table." << endl;

    return dataSize();
}

void
PVPanels::add(pvpanel_t *pv)
{
    addEntry(pv);
}

void
PVPanels::writeDatabase(string filespec)
{
    ofstream os;
    ostringstream tmpstr;
    int lines = -1;
    vector<pvpanel_t *>::iterator it;
    pvpanel_t *pv;
    int i;
    char *home;
    string loadfile;
    struct stat stats;
    
    if (_data.size() == 0) {
	cerr << "No PV data in memory" << endl;
	return;
    }
    
    if (filespec.size() == 0) {
	home = getenv("HOME");
	
	if (home) {
	    loadfile = home;
	    loadfile += "/.gnuae/modules.csv";
	    if (stat(loadfile.c_str(), &stats) == 0) {
		filespec = loadfile;
	    } else {
		loadfile = "/etc/gnuae/modules.csv";
		if (stat(loadfile.c_str(), &stats) == 0) {
		    filespec = loadfile;
		}
	    }
	}
    }
    
    os.open(filespec.c_str(), ios::out);
    
    cerr << "Opening modules file for writing: " << filespec << endl;
    
    // Write the headers so this can be imported easier into other programs,
    // like spreadsheets.
    os << "name,Vintage,Area,Material,Series_Cells,Parallel_C-S,Isco,Voco,Impo,Vmpo,aIsc,aImp,C0,C1,BVoco,mBVoc,BVmpo,mBVmp,n,C2,C3,A0,A1,A2,A3,A4,B0,B1,B2,B3,B4,B5,d(Tc),fd,a,b,C4,C5,Ixo,Ixxo,C6,C7,Picture,Description";
    
    if (_enhanced) {
	os << ",Price,manufacturer";
    }
    
    os << endl;
    
    for (it = _pvdata.begin(); it != _pvdata.end(); it++) {
	pv = *it;
	if (pv->name == 0) {
	    break;
	}
	
	if (pv->name)
	    os << "\"" << pv->name << "\",";
	else
	    os << "\"\",";
	if (pv->Vintage)
	    os << "\"" << pv->Vintage << "\",";
	else
	    os << "\"\",";
	os << pv->Area << ",";
	if (pv->Material)
	    os << "\"" << pv->Material << "\",";
	else
	    os << "\"\",";
	os << pv->Series_Cells << ",";
	os << pv->Parallel_C_S << ",";
	os << pv->Isco << ",";
	os << pv->Voco << ",";
	os << pv->Impo << ",";
	os << pv->Vmpo << ",";
	os << pv->aIsc << ",";
	os << pv->aImp << ",";
	os << pv->C0 << ",";
	os << pv->C1 << ",";
	os << pv->BVoco << ",";
	os << pv->mBVoc << ",";
	os << pv->BVmpo << ",";
	os << pv->mBVmp << ",";
	os << pv->n << ",";
	os << pv->C2 << ",";
	os << pv->C3 << ",";
	os << pv->A0 << ",";
	os << pv->A1 << ",";
	os << pv->A2 << ",";
	os << pv->A3 << ",";
	os << pv->A4 << ",";
	os << pv->B0 << ",";
	os << pv->B1 << ",";
	os << pv->B2 << ",";
	os << pv->B3 << ",";
	os << pv->B4 << ",";
	os << pv->B5 << ",";
	os << pv->d_Tc << ",";
	os << pv->fd << ",";
	os << pv->a << ",";
	os << pv->b << ",";
	os << pv->C4 << ",";
	os << pv->C5 << ",";
	os << pv->Ixo << ",";
	os << pv->Ixxo << ",";
	os << pv->C6 << ",";
	os << pv->C7 << ",";
	if (pv->Picture)
	    os << "\"" << pv->Picture << "\",";
	else
	    os << "\"\",";
	
	if (pv->Description)
	    os << "\"" << pv->Description << "\",";
	else
	    os << "\"no description\",";
	
	if (_enhanced) {
	    /* Enhanced fields */
	    if (pv->manufacturer)
		os << "\"" << pv->manufacturer << "\""; 
	    else
		os << "\"\"";
	}
	os << endl;
	os.flush();
    }
    
    os.close(); 
}

} // end of gnuae namespace

#if 0
// This is for the C API. We have to instantiate a class for the C API
// code to operate on.
static PVPanels _pv;

extern "C" {

  int pv_data_size(void)
  {
    return _pv.dataSize();
  }

  int
  read_module_data_csv(const char *filespec)
  {
    return _pv.readModuleDataCSV(filespec);
  }
  
  int
  read_module_data_xml(const char *filespec)
  {
    return _pv.readModuleDataXML(filespec);
  }
  
  pvpanel_t **
  getPVPanels(void)
  {
    static pvpanel_t **pvd;
    
    // getPVPanels();
    return pvd;
  }
  
  void
  pv_dump(pvpanel_t *pv)
  {
    _pv.dump(pv);
  }
  
  void
  pv_write(const char *filespec)
  {
    _pv.writeDatabase(filespec);
  }
  
  void
  pv_add(pvpanel_t *pv)
  {
    _pv.add(pv);
  }
  
  pvpanel_t **search(const char *str)
  {
    static pvpanel_t **pvd;
    
    _pv.search(str);
    return pvd;
  }

  pvpanel_t *
  get_pvpanel(int x)
  {
    return _pv[x];
  }

  int
  module_names(const char **namelist) {
    vector<string>::iterator it;
    vector<string> *pvnames;
    string entry;
    int i = 0;

    pvnames = _pv.names();
    
    if (pvnames->size() == 0) {
      dbglogfile << "No PV Panel data in memory" << endl;
      return 0;
    }
                
    namelist[i++] = strdup("Hey Now");
    for (it = pvnames->begin(); it != pvnames->end(); it++) {
      entry = *it;
      namelist[i++] = strdup(entry.c_str());
      //      dbglogfile << "NAMELIST " << namelist[i-1] << endl;
    }
    
    
    namelist[i++] = "eof";
    dbglogfile << "EOF" << endl;

    return pvnames->size();
}

#if 0
float
PVPanels::ampacity(pvpanel_t *pv, int parallel)
{
  return pv->Isco * parallel * NEC::ampacity();
}

float
PVPanels::maxCurrent(pvpanel_t *pv, int parallel)
{
  return pv->Isco * parallel * NEC::maxCurrent();
}

float
PVPanels::crystalCompensation(pvpanel_t *pv, float temp)
{
  float nvolts;
  
  nvolts = NEC::crystalCompensation(temp) * pv->Voco;
  
  if (_debug)
    cerr << "The temperature adjusted voltage is: " << nvolts << endl;
      
  return nvolts;
}

std::vector<pvpanel_t *>
PVPanels::getPVPanels(void)
{
  return _data;
}

void
PVPanels::setPVPanels(std::vector<pvpanel_t *> ptr)
{
  _data = ptr;
}
#endif
#endif
    
// local Variables:
// mode: C++
// indent-tabs-mode: t
// End:
