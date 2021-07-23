//#define EIGENLIB			// uncomment to use Eigen linear algebra library
//#define NO_POINTER_INIT	// uncomment to disable pointer checking

#include "fun_head_fast.h"

// do not add Equations in this area

MODELBEGIN

/*****EQUATION FILES*****/


#include "fun_time_step.h"          // Time Step Variable

#include "fun_functions.h"          // Macro Functions
#include "fun_macro.h"              // Macro Object Variables and Functions
#include "fun_macro_sfc.h"          // Macro Object Variables for Stock-Flow Consistency
#include "fun_macro_analysis.h"     // Macro Object Variables for Analysis
#include "fun_sectors.h"            // Sector Object Variables and Aggregates (including additonal files)
#include "fun_firms.h"              // Firm Object Variables (including additional files)
#include "fun_inputs.h"             // Input Object Variables
#include "fun_capital_goods.h"      // Capital Goods Object Variables
#include "fun_classes.h"            // Income Classes Object Variables
#include "fun_government.h"         // Government Object Variables
#include "fun_external_sector.h"    // External Sector Object Variables
#include "fun_entry_exit.h"         // Entry and Exit Variables (inside Sector Object)


MODELEND

// do not add Equations in this area

void close_sim( void )
{
// close simulation special commands go here
}
