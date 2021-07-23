
EQUATION("Depreciation_Expenses")
/*
Firm Variable 
*/
	v[0]=VL("Productive_Capacity",1);                    //firm's productive capacity in the last period
	v[1]=V("depreciation_rate");                         //depereciation rate of capital goods
	v[2]=V("Price_Capital_Goods");                       //price of capital goods
	cur = SEARCH_CND("id_input_sector", 2);              //search the inputs for the capital good sector one
	v[3]=VS(cur,"capital_output_ratio");                 //capital outpur ratio            
	v[4]=v[0]*(v[1]/6)*v[3]*v[2];                        //depeciation expenses is the total productive capacity times 1 sixth of the depreciation rate multiplied by the price and by the capital outrput ratio
RESULT(v[4])


EQUATION("Capital")
/*
Firm Variable
*/
	v[0]=V("Productive_Capacity");                       //firm's productive capacity in the last period   
	v[1]=V("Price_Capital_Goods");                       //price of capital goods
	cur = SEARCH_CND("id_input_sector", 2);              //search the inputs for the capital good sector one
	v[2]=VS(cur,"capital_output_ratio");                 //capital output ratio 
	v[3]=v[0]*v[1]*v[2];                                 //nominal value of firm's total capital
RESULT(v[3])


EQUATION("Firm_Avg_Productivity")
/*
Firm's productivity will be an average of each capital good productivity weighted by their repective production	
*/
	v[0]=V("Effective_Production");                                //firm's effective production
	v[1]=VL("Firm_Avg_Productivity", 1);                           //firm's average productivity in the last period
	v[2]=0;                                                        //initializes the CYCLE
	v[3]=0;                                                        //initializes the CYCLE
	CYCLE(cur, "CAPITAL")                                          //CYCLE trought firm's capital goods
	{
		v[4]=VS(cur, "Capital_Good_Productivity");                   //capital good productivity
		v[5]=VS(cur, "Capital_Good_Production");                     //capital good production
		v[2]=v[2]+v[4]*v[5];                                         //sums up the product of each capital good productivity and production
		v[3]=v[3]+v[5];                                              //sums up the production of each capital good
	}
	if (v[3]!=0)                                                   //if the sum of the production is not zero
		v[6]=v[2]/v[3];                                              //firm's average productivity will be the average of each capital good productivity weighted by its respective production
	else                                                           //if the sum of the production is zero
		{
		v[6]=v[1];                                                   //firm's average production will be the last period's 
		plog("\nERROR: total capital production equals zero");       //report the error in the log window
  	}
RESULT(v[6])


EQUATION("Firm_Productivity_Growth")
/*
Firm Variable
*/
	v[0]=V("Firm_Avg_Productivity");
	v[1]=VL("Firm_Avg_Productivity",1);
	v[2]=(v[0]-v[1])/v[1];
RESULT(v[2])


EQUATION("Productive_Capacity_Scrapped") 
/*
Firm Variable
*/
	V("Productive_Capacity"); 
RESULT(CURRENT)


EQUATION("Productive_Capacity_Depreciated")
/*
Firm Variable
*/
	V("Productive_Capacity_Appendix");
RESULT(CURRENT)


EQUATION("Max_Capital_Goods_Productivity");
/*
Calls the maximum productivity among firm's capital goods
*/
STAT("Capital_Good_Productivity");
RESULT(v[3])


EQUATION("Sum_Id_A_3")
/*
Firm Variable
*/
v[0]=V("id_a_3");
v[1]=VL("Sum_Id_A_3",1);
v[2]=v[1]+v[0];
RESULT(v[2])






