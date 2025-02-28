/*****INPUTS VARIABLES*****/


EQUATION("Required_Inputs")
/*
Input variable.
The demand for inputs for each period depends on programed production for that period and the tecnical relationship.
*/
	v[0]=V("Planned_Production");                      //amount of production the firm wants
	v[1]=V("input_technical_relationship");            //gives the amount of imputs necessary to product
	v[2]=V("input_techinal_relationship_imports");     //gives the amount of imported imputs necessary to product
	v[3]=v[0]*(v[1]+v[2]);                             //gives the total amount of imputs required for that planned production
RESULT(v[3])


EQUATION("Available_Inputs_Ratio")
/*
Input variable
This variable defines the ratio between available inputs and inputs demanded for each sector in order to fulfil desired production.
*/
	v[0]=V("Required_Inputs");                         //total amount of imputs to required to fulfil planned production
	v[1]=VL("Remaining_Inputs",1);                     //stock of remaining imputs from the last period	
	if(v[0]>0)                                         //if required imputs is a positive value
		v[2]=v[1]/v[0];                                  //gives the ratio between necessary imputs and available imputs
	else                                               //if required imputs is not a positive value
		v[2]=1;                                          //the ratio between necessary imputs and available imputs equals 1
	v[3]=min(1,v[2]);                                  //the ratio can never be smaller then 1
RESULT(v[3])


EQUATION("Input_Demand_Production_Period")
/*
Firm Variable
The stock of inputs for each sector, before the demand for inputs to be utilized in the next period, is determined subtracting the amount to be used in production from the total inputs available. Then amount to be used is calculated multiplying the necessary inputs for programed production with the minimum ratio between vailable inputs and necessary inputs.
*/
	v[0]=VL("Remaining_Inputs",1);                    //gives the stock of imputs remaining from the last period
	v[1]=V("Min_Available_Inputs_Ratio");             //gives the minimium available imput ratio
	v[2]=V("Required_Inputs");                        //gives the required imputs necessary to fulfil planned production
	v[3]=v[0]-(v[1]*v[2]);                            //subtracts from the current stock of imputs the total amount necessary to produce, determined by the required amount multiplied by the minimum available ratio.
	v[4]=max(v[3], 0);                                //the stock of imputs can never be negative
RESULT(v[4])


EQUATION("Input_Demand_Next_Period")
/*
Input Variable
The demand for inputs of each sector of intermediate goods, which should be produced during current period and to be used in the next period, is calculated based on the necessity of programed production, in which a expected growth rate is applied and the remaing stock is discounted. 

The expected growth rate is defined by the average of effective orders of the last two periods, extrapolated by a expectation parameter.

The intermediate goods sectors demand exactly the amount they will need to produce in the next period, without discouting the initial stock, which is now know, since the intermediate goods production in the current period will be defined by the demand for inputs of all sectors and not the programed production of the intermediate sector.
*/
	v[0]=V("Planned_Production");                     //firm's planned production for the current period
	v[1]=V("input_technical_relationship");           //gives the amount of imputs necessary to product
	v[2]=V("id_intermediate_goods_sector");           //identifies intermediate good sectors
	v[3]=V("id_capital_goods_sector");                //identifies capital good sectors
	v[4]=V("Input_Demand_Production_Period");         //current stock of imputs before production

	v[5]=VL("Effective_Orders", 1);                   //firm's effective orders lagged 1 (testar diferen�a trimestral e n�o semestral)
	v[6]=VL("Effective_Orders", 2);                   //firm's effective orders lagged 1
	v[7]=VL("Effective_Orders", 3);                   //firm's effective orders lagged 1
	v[8]=VL("Effective_Orders", 4);                   //firm's effective orders lagged 1
	v[9]=V("Gama");                                   //expectation parameter
	v[10]=(v[5]+v[6]);                                //sum of effective orders of the last two periods 
	v[11]=(v[7]+v[8]);                                //sum of effective orders of the two periods before the last two periods 
	if(v[11]!=0)                                      //if the sum of effective orders is not 0
		v[12]=1+(v[9]*((v[10]-v[11])/v[11]));           //gives an expected growth rate, based on the effective orders
	else                                              //if the sum of effective orders is 0
		v[12]=1;                                        //the expected growth rate is 1

	if (v[2]==0)                                      //if it is not intermediate goods sector
		{
		if (v[3]==1)                                    //if it is capital goods sector
			{
			v[13]=V("desired_inventories_proportion");    //gives the desired amount of inventories as a proportion of sales
			v[14]=(v[0]*(1+v[13])*v[1])*(v[12])-v[4];     //gives the amount of imputs necessary for the next period, multiplying the current planned production plus the desired amount of investories by the exptected growth rate and by the imput techinical relanshionship, and subtracting the current stock of imputs
			}
		else                                            //if it is consumption goods sector
			v[14]=(v[0]*v[1])*(v[12])-v[4];               //gives the amount of imputs necessary for the next period, multiplying the current planned production by the exptected growth rate and by the imput techinical relanshionship, and subtracting the current stock of imputs  
		}
	else                                              //if it is intermediate goods sector
	v[14]=(v[0]*v[1])*(v[12]);                        //gives the amount of imputs necessary for the next period, multiplying the current planned production by the exptected growth rate and by the imput techinical relanshionship
	
	v[15]=max(v[14],0);                               //the demand of imputs for the next period can never be negative
RESULT(v[15])


EQUATION("Required_Inputs_Intermediate_Sector")          
/*
Imput Variable 
The amount of inputs to be used by the sectors of intermediate goods in their production is calculated by multiplying the desired production of inputs by the technical coefficient.
*/
	v[0]=V("Intermediate_Production_Firm");             //gives the production of each firm of intermediate goods based on the other sector's demand
	v[1]=V("input_technical_relationship");             //gives the amount of imputs necessary to product
	v[2]=V("input_techinal_relationship_imports");      //gives the amount of imported imputs necessary to product
	v[3]=v[0]*(v[1]+v[2]);                              //gives the total amount of imputs required for that intermediate production
RESULT(v[3])


EQUATION("Available_Inputs_Ratio_Intermediate_Sector")
/*
Imput Variable 
Relation between available inputs and inputs needed for the intermediate goods sectors to achieve their desired output.
*/
	v[0]=V("Required_Inputs_Intermediate_Sector");       //total amount of imputs to required to taht intermediate production
	v[1]=VL("Remaining_Inputs", 1);                      //stock of remaining imputs from the last period	
		if (v[0]>0)                                        //if required imputs is positive
			v[2]=v[1]/v[0];                                  //gives the ratio between necessary imputs and available imputs
		if (v[0]==0)                                       //if required imputs is zero
			v[2]=1;                                          //the ratio between necessary imputs and available imputs is 1
	v[3]=min(1,v[2]);                                    //the available ratio can never be smaller then 1
RESULT(v[3])


EQUATION("Remaining_Inputs")
/*
Input Variable
The stock of inputs of each sector at the end of the period is calculated by summing the input inventories that were not used in the current production with the demand for inputs of the period.
*/
	v[0]=V("id_intermediate_goods_sector");                         //identifies the intermediate good sector
	v[1]=V("Input_Demand_Next_Period");                             //gives the value of the demand for imputs for the next period
	v[2]=V("Demand_Met_Input");                                     //gives how much of the demand was met by the imputs
	v[3]=V("Demand_Met_By_Imports_Input");                          //gives how much of the demand was met by imput imports
	v[4]=v[2]+(1-v[2])*v[3];                                        //gives the total amount of imputs used
	v[5]=V("Input_Demand_Production_Period");                       //gives the demand for imputs before production
	v[6]=V("Input_Imports");                                        //gives the import of imputs
		if(v[0]==0)                                                   //if it is not intermediate goods sector
			v[7]=v[1]*v[4]+v[5]+v[6];                                   //remaing inputs is calculated multiplying the imputs for the next period by the total used and adding the initial stock and the imports
		if(v[0]==1)                                                   //if it is intermediate good sector
			{
			v[8]=V("Required_Inputs_Intermediate_Sector");              //gives the required imputs for intermediate production
			v[9]=VL("Remaining_Inputs",1);                              //gives the stock of imputs from the last period
			v[10]=V("Min_Available_Inputs_Ratio_Intermediate_Sector");  //gives the minimum available ratio
			v[7]=v[1]*v[4]+(v[9]-(v[10]*v[8]))+v[6];                    //remaing inputs is calculated multiplying the imputs for the next period by the total used and adding the initial stock and the imports and subtracting the internal production within the sector
			}
	v[11]=max(v[7],0);
RESULT(v[11])


EQUATION("Demand_Capital_Goods")
/*
Input Variable
The demand for capital goods in each period will be determined by the sum of the autonomous investment with 1/4 of the variation of the productive capacity desired by each sector multiplied by the capital coefficient (to transform it into units of capital goods demanded).
*/

v[0]=V("id_firm_number");
v[1]=V("investment_period");
v[2]=V("capital_output_ratio");
v[3]=fmod((double) t,6);

if(v[0]==(v[3]-1)||v[0]==(v[3]+5)||v[0]==(v[3]+11)||v[0]==(v[3]+17))
	{
	v[4]=VL("Replecement",1);
	v[5]=VL("Demand_Productive_Capacity_Quality",1); 
	v[6]=VL("Demand_Productive_Capacity", 1);
	v[7]=(v[6]+v[4]+v[5])/6;
	}
if(v[0]==(v[3]-2)||v[0]==(v[3]+4)||v[0]==(v[3]+10)||v[0]==(v[3]+16))
	{
	v[4]=VL("Replecement",2);
	v[5]=VL("Demand_Productive_Capacity_Quality",2); 
	v[6]=VL("Demand_Productive_Capacity", 2);
	v[7]=(v[6]+v[4]+v[5])/6;
	}
if(v[0]==(v[3]-3)||v[0]==(v[3]+3)||v[0]==(v[3]+9)||v[0]==(v[3]+15))
	{
	v[4]=VL("Replecement",3);
	v[5]=VL("Demand_Productive_Capacity_Quality",3); 
	v[6]=VL("Demand_Productive_Capacity", 3);
	v[7]=(v[6]+v[4]+v[5])/6;
	}
if(v[0]==(v[3]-4)||v[0]==(v[3]+2)||v[0]==(v[3]+8)||v[0]==(v[3]+14))	
	{
	v[4]=VL("Replecement",4);
	v[5]=VL("Demand_Productive_Capacity_Quality",4); 
	v[6]=VL("Demand_Productive_Capacity", 4);
	v[7]=(v[6]+v[4]+v[5])/6;
	}
if(v[0]==(v[3]-5)||v[0]==(v[3]+1)||v[0]==(v[3]+7)||v[0]==(v[3]+13))
	{
	v[4]=VL("Replecement",5);
	v[5]=VL("Demand_Productive_Capacity_Quality",5); 
	v[6]=VL("Demand_Productive_Capacity", 5);
	v[7]=(v[6]+v[4]+v[5])/6;
	}
if(v[0]==(v[3])||v[0]==(v[3]+6)||v[0]==(v[3]+12)||v[0]==(v[3]+18))
	{
	v[4]=VL("Replecement",6);
	v[5]=VL("Demand_Productive_Capacity_Quality",6); 
	v[6]=VL("Demand_Productive_Capacity", 6);
	v[7]=(v[6]+v[4]+v[5])/6;
	}
v[8]=v[7]*v[2];
RESULT(v[8])


EQUATION("Demand_Met_By_Imports_Input")
/*
Input Variable
*/
	v[0]=V("id_input_sector");
	cur=SEARCH_CND("id_sector_number",v[0]);
	v[1]=VS(cur,"Demand_Met_By_Imports");
RESULT(v[1])


EQUATION("Demand_Met_Input")
/*
Input Variable
*/
	v[0]=V("id_input_sector");
	cur=SEARCH_CND("id_sector_number",v[0]);
	v[1]=VS(cur,"Demand_Met");
RESULT(v[1])


EQUATION("Input_Cost")
/*
Input Variable
Costs of the inputs
*/
	v[0]=V("id_input_sector");                                                //identifies the sectors(?)
	cur=SEARCH_CND("id_sector_number",v[0]);                                  //search the inputs for the one from the intermediate sector
	v[1]=VLS(cur,"Avg_Price",1);                                              //intermediate sector average price
	v[2]=VS(cur,"Foreign_Price");                                             //sector external price
	v[3]=V("input_technical_relationship");                                   //input technical relationship
	v[4]=V("input_techinal_relationship_imports");                            //imported input technical relationship 
	v[5]=V("Exchange_Rate");                                                  //exchange rate
	v[6]=VL("Demand_Met_Input",1);                                            //demand for inputs met by the domestic production in the last period
	v[7]=VL("Demand_Met_By_Imports_Input",1);                                 //demand for inputs met y external production in the last period
RESULT(v[1]*v[3]*v[6]+v[2]*v[5]*v[4]+1.1*(1-v[6])*v[7]*v[3]*v[2]*v[5])      //input cost will be the amount demanded domesticaly multiplied by domestic price plus the amount demanded externally miltiplied by the external price
//estranhamente, alterar o RESULT para v[8] e chamar o novo RESULT(v[8]) altera o resultado. 


EQUATION("Input_Imports")
/*
Input Variable 
The importation of inputs is determined based on the planned production of each sector and its technical coefficient of import of intermediate goods.
*/
	v[0]=V("Planned_Production");
	v[1]=V("input_techinal_relationship_imports");
	v[2]=V("Gama"); 
	v[3]=VL("Effective_Orders", 1);
	v[4]=VL("Effective_Orders", 2);
	v[5]=VL("Effective_Orders", 3);
	v[6]=VL("Effective_Orders", 4);
	v[7]=(v[3]+v[4]);
	v[8]=(v[5]+v[6]);
	if(v[8]!=0)
	  v[9]=1+(v[2]*((v[7]-v[8])/v[8]));
	else
	  v[9]=1;	
	v[10]=v[0]*v[1]*v[9];  
	v[11]=max(v[10],0);
RESULT(v[11])
