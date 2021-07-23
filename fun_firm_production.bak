
EQUATION("Min_Available_Inputs_Ratio")
/*
This variable defines the minimum ratio between available inputs and necessary inputs to fulfill programed production, for each sector.
*/
  v[0]=MIN("Available_Inputs_Ratio");            
RESULT(v[0])


EQUATION("Input_Demand_Production_Period")
/*
The stock of inputs for each sector, before the demand for inputs to be utilized in the next period, is determined subtracting the amount to be used in production from the total inputs available. Then amount to be used is calculated multiplying the necessary inputs for programed production with the minimum ratio between vailable inputs and necessary inputs.
*/
	v[0]=VL("Remaining_Inputs",1);                    //gives the stock of imputs remaining from the last period
	v[1]=V("Min_Available_Inputs_Ratio");             //gives the minimium available imput ratio
	v[2]=V("Required_Inputs");                        //gives the required imputs necessary to fulfil planned production
	v[3]=v[0]-(v[1]*v[2]);                            //subtracts from the current stock of imputs the total amount necessary to produce, determined by the required amount multiplied by the minimum available ratio.
	v[4]=max(v[3], 0);                                //the stock of imputs can never be negative
RESULT(v[4])


EQUATION("Min_Available_Inputs_Ratio_Intermediate_Sector")
/*
This variable determines the lowest ratio between the total of inputs available and the inputs needed for the desired production of the intermediate goods sectors.
*/
	v[0]=MIN("Available_Inputs_Ratio_Intermediate_Sector");
RESULT(v[0])


EQUATION("Expected_Sales")
/*
Firm's expected sales are calculated from an average of effective sales from the two previos periods, applying a expected growth rate. This expected growth rate is obtained from comparing the average of the two previous periods with the average of the two before that, adjusted by an expectation parameter.
*/
	v[1]=VL("Effective_Orders", 1);                       //firm's effective orders lagged 1
	v[2]=VL("Effective_Orders", 2);                       //firm's effective orders lagged 2
	v[3]=V("Gama");                                       //expectations parameter

	if(v[2]!=0)                                           //if firm's effective orders lagged 2 is not zero
		{
		v[4]=v[1]*(1+v[3]*((v[1]-v[2])/v[2]));              //expected sales will be the effective orders in the last period multiplied by the growth rate between the two periods adjusted by the expectations parameter
		v[5]=max(0,v[4]);                                   //expected sales can never be negative
		}
	else                                                  //if firm's effective orders lagged 2 is zero 
		v[5]=v[1];                                          //expected sales will be equal to effective orders of the last period
RESULT(v[5])


EQUATION("Planned_Production")
/*
It's calculated from expected sales for the period, considering the proportion of sales that is desired to be kept as inventories and discounting the acumulated stock of inventories in the last period. 
For the capital goods sector, program production is defined by effective orders.
Programed Production is subjected to a existing capactity restriction, but it is possible to increase production by incrising extra hours of labor, in any sector.
*/
	v[0]=V("id_capital_goods_sector");                    //identifies the capital goods sector      
	v[1]=V("Expected_Sales");                             //calls the firm's expected sales
	v[2]=V("Productive_Capacity");                 			  //ALTERADO POR JOÃO! calls the firm's productive capacity of the last period
	v[3]=V("productive_capacity_overuse");                //calls the firm's productive capacity overuse parameter
	v[4]=v[3]*v[2];                                       //giver the maximum productive capacity
	v[5]=V("desired_inventories_proportion");             //calls the firm's desired inventories ratio as a proportion of sales
	v[6]=VL("Inventories",1);                             //calls the firm's stock of inventories in the last period

	if(v[0]==0)                                           //if it is not capital goods sector
		v[7]=v[1]*(1+v[5])-v[6];                            //planned production will be expected sales plus the desired proportion of investories minus the existing stock of inventories
	else                                                  //if it is a capital goods sector
		v[7]=V("Effective_Orders_Capital_Goods_Firm");      //planned production will be the firm's effective orders (received in the beginning of the period)

	v[8]=max(0, min(v[4],v[7]));                          //planned production can never be more then the maximum productive capacity and can never be negative
RESULT(v[8])


EQUATION("Intermediate_Production_Firm")
/*
Firm Variable
*/
V("Intermediate_Production");
v[0]=V("intermediate_production_firm_temporary");
WRITE("intermediate_production_firm_temporary", 0);
RESULT(v[0])


EQUATION("Effective_Production")
/*
The actual production of each sector will be determined by the constraint imposed by the availability of inputs to the realization of the programmed production (or production of inputs desired, in the case of intermediate sectors). Such constraint is defined by the lower ratio between available inputs and the inputs required for production.
*/
	v[0]=V("Planned_Production");                                                                //firm's planned production
	v[1]=V("id_intermediate_goods_sector");                                                      //identifies intermediate goods sectors
	v[2]=V("Intermediate_Production_Firm");                                                      //intermediate goods production for the firm of intermediate goods sectors

	if (v[1]==0)                                                                                 //if it is not intermediate goods sector
		{
		v[3]=V("Min_Available_Inputs_Ratio");                                                      //minimum available imputs ratio for production
		v[4]=v[3]*v[0];                                                                            //effective planned production, constrained by the ratio of available inputs
		}
	else                                                                                         //if it is intermediate goods sector
		{
		v[3]=V("Min_Available_Inputs_Ratio_Intermediate_Sector");                                  //minimum available imputs ratio for production of intermediate goods firns
		v[4]=v[3]*v[2];                                                                            //effective planned production, constrained by the ratio of available inputs
		}
	
	SORT("CAPITAL", "Capital_Good_Productivity", "DOWN");                                        //rule for the use of capital goods, sorts firm's capital goods by productivity in a decreasing order
	v[5]=0;                                                                                      //initializes the CYCLE
	CYCLE(cur, "CAPITAL")                                                                        //CYCLE trought the capital goods of the firm
	{
		v[6]=VS(cur, "capital_good_productive_capacity");                                          //capital productivity capacity
		v[7]=V("productive_capacity_overuse");                                                     //firm's capacity oversuse parameter
		v[8]=max(0,(min(v[6]*v[7], v[4])));                                                        //maximum capacity of each capital goods, constrained by effective planned production, and it can not be negative
		WRITES(cur, "Capital_Good_Production", v[8]);                                              //the capacity of each capital goods is in fact its production
		v[4]=v[4]-v[8];                                                                            //it subracts the production of the first capital good from the effective planned production before going to the next capital good
		v[5]=v[5]+v[8];                                                                            //sums up the production of each capital good to determine firm's effective production
	}
RESULT(max(v[5],0.01))


EQUATION("Input_Imports_Firm")
/*

*/
	v[0]=SUM("Input_Imports");
RESULT(v[0])


EQUATION("Capacity_Utilization_Firm")
/*

*/
	v[0]=V("Productive_Capacity");       								 //productive capacity in the last period
 	v[1]=V("Effective_Production");          						 //effective production
 	v[2]=v[1]/v[0];
RESULT(v[2])


EQUATION("Firm_Employment")
/*

*/
	v[0]=V("Firm_Avg_Productivity");       								 
 	v[1]=V("Effective_Production");          						 
 	v[2]=v[1]/v[0];
RESULT(v[2])


