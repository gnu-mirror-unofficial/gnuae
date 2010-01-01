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

#include <iostream>
#include <string>
#include <vector>
#include <memory>

#include "log.h"
#include "gnuae.h"
#include "Wire.h"

using namespace std;

namespace gnuae {

static LogFile& dbglogfile = LogFile::getDefaultInstance();
static GnuAE& gdata = GnuAE::getDefaultInstance();

// From table 8, Conductor Properties, NEC code
wire_t wire_table[] = {
    {"18",    0.823,   1620,   1, 0,    0,      1.02,   0.040, 0.823,  0.001, 25.5,   7.77, 26.5,     8.08,  42.0,   12.8,  0},
    {"18",    0.823,   1620,   7, 0.39, 0.015,  1.16,  0.046,  1.06,   0.002, 26.1,   7.95, 27.7,     8.45,  42.8,   13.1,  0},
    {"16",    1.31,    2580,   1, 0,    0,      1.29,   0.051, 1.31,   0.002, 16.0,   4.89, 16.7,     5.08,  26.4,    8.05,  0},
    {"16",    1.31,    2580,   7, 0.49, 0.019,  1.46,  0.058,  1.68,   0.003, 16.4,   4.99, 17.3,     5.29,  26.9,    8.21,  0},
    {"14",    2.08,    4110,   1, 0,    0,      1.63,   0.064, 2.08,   0.003, 10.1,   3.07, 10.4,     3.19,  16.6,    5.06,  0},
    {"14",    2.08,    4110,   7, 0.62, 0.024,  1.85,  0.073,  2.68,   0.004, 10.3,   3.14, 10.7,     3.26,  16.9,    5.17,  0},
    {"12",    3.31,    6530,   1, 0,    0,      2.05,   0.081, 3.31,   0.005,  6.34,  1.93,   6.57,   2.01,  10.45,   3.18,  0},
    {"12",    3.31,    6530,   7, 0.78, 0.030,  2.32,  0.092,  4.25,   0.006, 6.50,   1.98,   6.73,   2.05,  10.69,   3.25,  0},
    {"10",    5.261,  10380,   1, 0,    0,      2.588,  0.102, 5.26,   0.008,  3.984, 1.21,   4.148,  1.26,   6.561,  2.00,  0},
    {"10",    5.261,  10380,   7, 0.98, 0.038,  2.95,  0.116,  6.76,   0.011, 4.070,  1.24,   4.226,  1.29,   6.679,  2.04,  0},
    {"8",     8.367,  16510,   1, 0,    0,      3.264,  0.128, 8.37,   0.013,  2.506, 0.764,  2.579,  0.786,  4.125,  1.26,  0},
    {"8",     8.367,  16510,   7, 1.23, 0.049,  3.71,  0.146, 10.76,   0.017, 2.551,  0.778,  2.653,  0.809,  4.204,  1.28,  0},
    {"6",     13.30,  26240,   7, 1.56, 0.061,  4.67,  0.184, 17.09,   0.027, 1.608,  0.491,  1.671,  0.510,  2.652,  0.808,  0},
    {"4",     21.15,  41740,   7, 1.96, 0.077,  5.89,  0.232, 27.19,   0.042, 1.010,  0.308,  1.053,  0.321,  1.666,  0.508,  0},
    {"3",     26.67,  52620,   7, 2.20, 0.087,  6.60,  0.260, 34.28,   0.053, 0.802,  0.245,  0.833,  0.254,  1.320,  0.403,  0},
    {"2",     33.62,  66360,   7, 2.47, 0.097,  7.42,  0.292, 43.23,   0.067, 0.634,  0.194,  0.661,  0.201,  1.045,  0.319,  0},
    {"1",     42.41,  83690,  19, 1.69, 0.066,  8.43,  0.332, 55.80,   0.087, 0.505,  0.154,  0.524,  0.160,  0.829,  0.253,  0},
    {"1/0",   53.49, 105600,  19, 1.89, 0.074,  9.45,  0.372, 70.41,   0.109, 0.399,  0.122,  0.415,  0.127,  0.660,  0.201,  0},
    {"2/0",   67.43, 133100,  19, 2.13, 0.084, 10.62,  0.418, 88.74,   0.137, 0.3170, 0.0967, 0.329,  0.101,  0.523,  0.159,  0},
    {"3/0",   85.01, 167800,  19, 2.39, 0.094, 11.94,  0.470, 111.9,   0.173, 0.2512, 0.0766, 0.2610, 0.0797, 0.413,  0.126,  0},
    {"4/0",   107.2, 211600,  19, 2.68, 0.106, 13.41,  0.528, 141.1,   0.219, 0.1996, 0.0608, 0.2050, 0.0626, 0.328,  0.100,  0},
    {"250",   127,        0,  37, 2.09, 0.082, 14.61,  0.575, 168,     0.260, 0.1687, 0.0515, 0.1753, 0.0535, 0.2778, 0.0847, 0},
    {"300",   152,        0,  37, 2.29, 0.090, 16.00,  0.630, 201,     0.312, 0.1409, 0.0429, 0.1463, 0.0446, 0.2318, 0.0707, 0},
    {"350",   177,        0,  37, 2.47, 0.097, 17.30,  0.681, 235,     0.364, 0.1205, 0.0367, 0.1252, 0.0382, 0.1984, 0.0605, 0},
    {"400",   203,        0,  37, 2.64, 0.104, 18.49,  0.728, 268,     0.416, 0.1053, 0.0321, 0.1084, 0.0331, 0.1737, 0.0529, 0},
    {"500",   253,        0,  37, 2.95, 0.116, 20.65,  0.813, 336,     0.519, 0.0845, 0.0258, 0.0869, 0.0265, 0.1391, 0.0424, 0},
    {"600",   304,        0,  61, 2.52, 0.099, 22.68,  0.893, 404,     0.626, 0.0704, 0.0214, 0.0732, 0.0223, 0.1159, 0.0353, 0},
    {"700",   355,        0,  61, 2.72, 0.107, 24.49,  0.964, 471,     0.730, 0.0603, 0.0184, 0.0622, 0.0189, 0.0994, 0.0303, 0},
    {"750",   380,        0,  61, 2.82, 0.111, 25.35,  0.998, 505,     0.782, 0.0563, 0.0171, 0.0579, 0.0176, 0.0927, 0.0282, 0},
    {"800",   405,        0,  61, 2.91, 0.114, 26.16,  1.030, 538,     0.834, 0.0528, 0.0161, 0.0544, 0.0166, 0.0868, 0.0265, 0},
    {"900",   456,        0,  61, 3.09, 0.122, 27.79,  1.094, 606,     0.940, 0.0470, 0.0143, 0.0481, 0.0147, 0.0770, 0.0235, 0},
    {"1000",  507,        0,  61, 3.25, 0.128, 29.26,  1.152, 673,     1.042, 0.0423, 0.0129, 0.0434, 0.0132, 0.0695, 0.0212, 0},
    {"1250",  633,        0,  91, 2.98, 0.117, 32.74,  1.289, 842,     1.305, 0.0338, 0.0103, 0.0347, 0.0106, 0.0554, 0.0169, 0},
    {"1500",  760,        0,  91, 3.26, 0.128, 35.86,  1.412, 1011,    1.566, 0.02814, 0.00858, 0.02814, 0.00883, 0.0464, 0.0141, 0},
    {"1750",  887,        0, 127, 2.98, 0.117, 38.76,  1.526, 1180,    1.829, 0.02410, 0.00735, 0.02410, 0.00756, 0.0397, 0.0121, 0},
    {"2000", 1013,        0, 127, 3.19, 0.126, 41.45,  1.632, 1349,    2.092, 0.02109, 0.00643, 0.02109, 0.00662, 0.0348, 0.0106, 0},
    {0,         0,        0,   0,    0,     0,     0,      0,    0,      0,        0,      0,       0,       0,      0,      0, 0} // terminate the table
};

struct tempfactor
{
  int high;
  int low;
  float factor;
};

Wire::Wire()
{
    // DEBUGLOG_REPORT_FUNCTION;

    // All the other tables are loaded from an SQL database, but the
    // wire data is static, as it's defined in the NEC Code. As the
    // template wants to delete all the entries when deleted, we fake
    // it out by allocating memory for the wire data, so it behaves
    // like everything else.
    for (int i=0; wire_table[i].name!=0; i++) {
	// wire_t *wire = new wire_t;
	// memcpy(wire, &wire_table[i], sizeof(wire_t));
     	// addEntry(wire);
    }
}

Wire::~Wire()
{
    // DEBUGLOG_REPORT_FUNCTION;
}

void
Wire::dump()
{
    // DEBUGLOG_REPORT_FUNCTION;
    if (!dataSize()) {
    	cerr << "No Wire data in memory." << endl;
    } else {
    	vector<string>::iterator it;
    	auto_ptr<vector<string> > loadnames = dataNames();
    	for (it = loadnames->begin(); it != loadnames->end(); ++it) {
    	    dump(findEntry(*it));
    	}
    }
}

void
Wire::dump(wire_t *wire)
{
    // DEBUGLOG_REPORT_FUNCTION;
    cerr << "Wire gauge is: " << wire->name << endl;

    cerr << "\tArea mm: " << wire->area_mm;		// Area in mm
    cerr << ", Area mils: " << wire->area_mils;		// Area in circular mils
    cerr << ", Strands: " << wire->strand_qty << endl;	// conductors
    // Conductors
    cerr << "\tStranding mm: " << wire->strand_mm;
    cerr << ", inches: " << wire->strans_in << endl;
    cerr << "\tDiameter mm: " << wire->dia_mm;
    cerr << ", inches: " << wire->dia_in << endl;
    cerr << "\tStranding Area mm: " << wire->sarea_mm; // Stranding in mm
    cerr << ", in: " << wire->sarea_in << endl;	       // Stranding in in
    // Direct-Current Resistance at 75°C (167°F)
    // UnCoated Copper wire
    cerr << "\tUncoated Copper km: " << wire->uncoated_km;
    cerr << ", in kft: " << wire->uncoated_kft << endl;
    // Coated Copper wire
    cerr << "\tCoated Copper km: " << wire->coated_km;
    cerr << ", in kft: " << wire->coated_kft << endl;
    // Aluminum wire
    cerr << "\tAluminum km: " << wire->alum_km;
    cerr << ", in kft: " << wire->alum_kft << endl;
}

//  Drop = Current in Amps x resistance per foot x length			
//	Voltage drop= Amp x ohms		

} // end of gnuae namespace

// local Variables:
// mode: C++
// indent-tabs-mode: t
// End:
