/*****PRODUCTION AND DEMAND*****/


EQUATION("Domestic_Intermediate_Demand")
/*
This stores the value of the "Dom_Intermediate_Demand_Function" for each sector.
*/
	v[0]=V("id_intermediate_goods_sector");
	if(v[0]==1)
		v[1]=V("Intermediate_Demand_Function");
	else
		v[1]=0;
RESULT(v[1])


EQUATION("Domestic_Consumption_Demand") 
/*
Stores the value of the Demand Function if it is a consumption goods sector
*/
	v[0]=V("id_consumption_goods_sector");                  //identifies consumption goods sector
	if(v[0]==1)                                             //if it is a consumption good sector
    v[1]=V("Domestic_Consumption_Demand_Function");       //stores the value of the function  
  else                                                    //if it is not a consumption good sector 
		v[1]=0;                                               //domestic consumption is zero
RESULT(v[1])


EQUATION("Domestic_Capital_Demand")
/*
Calls the Capital_Goods_Demand Function and calculates the demand of other sectors.
*/
v[0]=V("id_capital_goods_sector");
if(v[0]==1)
	{
	v[1]=V("Capital_Goods_Demand_Function");
	v[2]=V("propensity_to_import_capital_goods");
	v[3]=v[1]*(1-v[2]);
	}
else
	v[3]=0;
RESULT(v[3])


EQUATION("Effective_Orders_Sector")
/*
Sector Variable
Effective orders are determined from total demand for the products in the sector. In the sum of consumption goods, capital goods and intermediate goods, only the factor referring to the sector that is calling this variable will asume positive values. In the case of the agricultural sector, effective orders also include exports.
*/
	v[0]=V("Domestic_Consumption_Demand");                                                       //domestic demand of consumption goods
	v[1]=V("Domestic_Capital_Demand");                                                           //domestic demand of capital goods
	v[2]=V("Domestic_Intermediate_Demand");                                                      //domestic demand of intermediate goods
	v[3]=v[0]+v[1]+v[2];                                                                         //sums up the domestic demands. For each sector, only the relevant demand will have a value and the others will be zero.
	v[4]=V("Exports");                                                                           //external demand, exports of the sector (zero for the non-agricultural sector)
	v[5]=v[3]+v[4];                                                                              //sums up domestic and external demand
RESULT(v[5])


EQUATION("Effective_Orders_Capital_Firm")
/*
Sector Variable
*/
	v[0]=V("id_capital_goods_sector");                                                        //identifies capital goods sectors
	v[1]=V("Sum_Market_Share");                                                               //
	if (v[0]==1)                                                                              //if it is capital goods sector
		{
		v[2]=V("Effective_Orders_Sector");                                               //value of effective orders of capital goods 
		for(v[3]=0,v[4]=v[2],v[5]=0; (v[2]-v[3])>0&&v[5]<v[1]; v[4]=(v[2]-v[3]),v[5]=v[6])      //??
 			{	
			v[7]=v[5];                                                                            //initializes v[7] for the CYCLE
			v[8]=0;    														                                                //initializes v[8] for the CYCLE                                                       
			v[9]=0;                                                                               //initializes v[9] for the CYCLE
			v[10]=0;                                                                              //initializes v[10] for the CYCLE
			CYCLE(cur, "FIRMS")                                                                   //begin CYCLE trought firms
			{
				v[11]=VS(cur, "Market_Share");                                                      //firm's market share
				v[12]=VLS(cur, "Productive_Capacity", 1);                                           //firm's productive capacity in the last period
				v[13]=VS(cur, "productive_capacity_overuse");                                       //firm's productive capacity oversuse parameter
				v[14]=v[12]*v[13];                                                                  //firm's maximum capacity
				v[15]=VS(cur, "capital_goods_production_temporary");                                //firm's capital goods production
					if (v[15]<v[14])                                                                  //if firm's capital goods production is lower then the firm's maximum capacity
					{
					v[16]=VS(cur, "capital_goods_effective_orders_firm_temporary");                   //firm's effective orders temporary
					v[17]=v[16]+v[4]*v[11]/(1-v[7]);                                                  //firm effective orders will be the temporary value plus the total value of effective orders multiplied by firm's market share, divided by 
					v[18]=max((min(v[17],v[14])),0);                                                  //firm's effective production can never be more then the maximum capacity nor negative
					}
					else                                                                              //if firm's capital goods production is higher then the firm's maximum capacity             
					{
					v[17]=VS(cur, "capital_goods_effective_orders_firm_temporary");                   //firm's effective orders temporary      
					v[18]=v[14];                                                                      //firm's effective production will be the maximum capacity
					}
				WRITES(cur, "capital_goods_effective_orders_firm_temporary", v[17]);                //writes the firm's capital goods effective orders
				WRITES(cur, "capital_goods_production_temporary", v[18]);                           //writes the firm's capital goods production
				v[10]=v[10]+v[18];                                                                  //sums up the production of each firm
				v[19]=min(v[17],v[14]);                                                             //determines the firm's effecive orders, that can not be higher then the maximum capacity
				v[9]=v[9]+v[19];                                                                    //sums up the effective orders of each firm
					if (v[18]==v[14])                                                                 //if firm's production is equal to maximum capacity	
						v[20]=v[11];                                                                    //effective orders will be equal to firm's market share
					else                                                                              //if firm's production is not equal to maximum capacity
						v[20]=0;                                                                        //effective orders will be equal to zero  
				v[8]=v[8]+v[20];                                                                    //sums up the effective orders of each firm
			}
			v[3]=v[9];                                                                            //new value for v[3]
			v[6]=v[8];                                                                            //new value for v[6]
			}
		}
	else                                                                                      //if it is not capital goods sector
		v[20]=0;                                                                                //result equals zero
RESULT(v[20])


EQUATION("Intermediate_Production")
/*
Sector Variable
Intermediate goods sector produces on demand. This variable calculates how much was demanded to the industries in this period in order to determine the effective production of the input producing sectors.
*/
v[0]=V("id_intermediate_goods_sector");
v[1]=V("Sum_Market_Share");
if (v[0]==1) //intermediate goods sector
	{
	v[2]=V("Effective_Orders_Sector");
	for(v[3]=0,v[4]=v[2],v[5]=0; (v[2]-v[3])>0&&v[5]<v[1]; v[4]=(v[2]-v[3]),v[5]=v[6])
 		{	
		v[7]=v[5];
		v[8]=0;
		v[9]=0;
		v[10]=0;
		CYCLE(cur, "FIRMS")
		{
			v[11]=VS(cur, "Market_Share");
			v[21]=VS(cur, "desired_inventories_proportion");
			v[22]=VLS(cur, "Inventories", 1);
			v[12]=VLS(cur, "Productive_Capacity", 1);
			v[13]=VS(cur, "productive_capacity_overuse");
			v[14]=v[12]*v[13];
			v[15]=VS(cur, "intermediate_production_firm_temporary");
			if (v[15]<v[14])
				{
				v[16]=VS(cur, "intermediate_effective_orders_firm_temporary");
				v[17]=v[16]+v[4]*v[11]/(1-v[7]);
				v[18]=max((min(v[17]*(1+v[21])-v[22],v[14])),0);
				}
				else
				{
				v[17]=VS(cur, "intermediate_effective_orders_firm_temporary");
				v[18]=v[14];
				}
			WRITES(cur, "intermediate_effective_orders_firm_temporary", v[17]);
			WRITES(cur, "intermediate_production_firm_temporary", v[18]);
			v[10]=v[10]+v[18];
			v[19]=min(v[17],v[14]+v[22]);
			v[9]=v[9]+v[19];
				if (v[18]==v[14])
					v[20]=v[11];
				else
					v[20]=0;
			v[8]=v[8]+v[20];
		}
		v[3]=v[9];
		v[6]=v[8];
		}
	}
else
	v[20]=0;
RESULT(v[20])


EQUATION("Effective_Orders_Consumption_Firm")
/*
Sector Variable
*/
v[0]=V("id_consumption_goods_sector");
v[1]=V("Sum_Market_Share");
if (v[0]==1) //capital goods sector
	{
	v[2]=V("Effective_Orders_Sector");
	for(v[3]=0,v[4]=v[2],v[5]=0; (v[2]-v[3])>0&&v[5]<v[1]; v[4]=(v[2]-v[3]),v[5]=v[6])
 		{	
		v[7]=v[5];
		v[8]=0;
		v[9]=0;
		CYCLE(cur, "FIRMS")
		{
			v[11]=VS(cur, "Market_Share");
			v[12]=VS(cur, "Effective_Production");
			v[13]=VLS(cur, "Inventories", 1);
			v[14]=v[12]+v[13];
			v[15]=VS(cur, "consumption_effective_orders_firm_temporary");
				if (v[15]<v[14])
					v[17]=v[15]+v[4]*v[11]/(1-v[7]);
				else
					v[17]=v[15];
			WRITES(cur, "consumption_effective_orders_firm_temporary", v[17]);
			v[19]=min(v[17],v[14]);
			v[9]=v[9]+v[19];
				if (v[19]==v[14])
					v[20]=v[11];
				else
					v[20]=0;
			v[8]=v[8]+v[20];
		}
		v[3]=v[9];
		v[6]=v[8];
		}
	}
else
	v[3]=0;
RESULT(v[3])