
/******MACRO FUNCTIONS******/


EQUATION("Intermediate_Demand_Function")
/*
Calculates the domestic demand for inputs.
Must be called by the sectors.
*/
	v[0]=VS(c, "id_intermediate_goods_sector");                    //identifies the intermediate goods sector
	v[1]=VS(c, "id_sector_number");                                //identifies the number of the sector                                  
	if (v[0]==1)                                                   //if it is a intermediate good sector
		{
		v[2]=0;                                                      //initializes the value for thr CYCLE
		CYCLE(cur, "SECTORS")                                        //CYCLE trought all sectors
		{
			v[3]=0;                                                    //initializes the value for the CYCLE
			CYCLES(cur, cur1, "FIRMS")                                 //CYCLE trought all firms inside the sectors
			{
				cur2 = SEARCH_CNDS(cur1, "id_input_sector", v[1]);       //search the imput equivalent to that sector, id_3 identifies th imputs like id_1      
				v[4]=VS(cur2, "Input_Demand_Next_Period");               //gives the demand for imputs of each firm
				v[3]=v[3]+v[4];                                          //sums up the demand for imputs of all firms
			} 
		v[2]=v[2]+v[3];                                              //sums up the demand for imputs of all setors
		}
		}
	else                                                           //if it is not intermediate goods sector
	v[2]=0;                                                        //the demand for imputs is zero
RESULT(v[2])


EQUATION("Domestic_Consumption_Demand_Function")
/*
Calculates the domestic demand for consumption goods.
Must be called by the sector.
*/
	v[0]=0;                                                 //initializes the CYCLE
	CYCLE(cur, "CLASSES")                                   //CYCLE trought all income classes
	{
		v[1]=VS(cur, "Class_Real_Domestic_Consumption");      //class' income lagged 1                                      //class consumption
  	v[0]=v[0]+v[1];                                       //sums up all classes consumption
	}
	v[9]=VLS(c, "Avg_Price",1);                             //sector average price in the last period
	v[10]=V("Government_Consumption");                      //government consumption
	v[11]=v[10]/v[9];                                       //real government consumption in the sector
	v[12]=v[0]+v[11];                                       //total consumption demand is the sum of classes induced consumption, calsses autonomous consumption and government consumption
RESULT(v[12])


EQUATION("Capital_Goods_Demand_Function")
/*
The demand for capital goods is calculated by summing up the demand for capital goods from all sectors with government spending on investment.
Must be called by the sectors.
*/
	v[0]=VS(c, "id_sector_number");                         //identifies the number of the sector
	v[1]=0;                                                 //initializes the CYCLE
	CYCLE(cur, "SECTORS")                                   //CYCLE trought the sectors
	{	
		v[2]=0;                                               //initializes the second CYCLE
		CYCLES(cur, cur1, "FIRMS")                            //CYCLE trought the firms
		{
			cur2 = SEARCH_CNDS(cur1, "id_input_sector", v[0]);  //search the capital good equivalent to that sector, id_3 identifies th capital good like id_1
    	v[3]=VS(cur2, "Demand_Capital_Goods");              //gives the demand for capital goods of each firm
   		v[2]=v[2]+v[3];                                     //sums up all capital goods demand
		}
		v[1]=v[1]+v[2];                                       //sums up all firm's capital goods demand
	}                                      
	v[4]=VLS(c, "Avg_Price",1);                             //sector average price in the last period
	v[5]=V("Government_Investment");                        //government investment in nominal values
	v[6]=v[5]/v[4];                                         //government investment in real values
	v[7]=v[1]+v[6];
RESULT(v[7])


EQUATION("Effective_Productive_Capacity_Variation_Function")
/*

*/
v[0]=VS(c, "id_firm_number");
v[1]=fmod((double) t,6); 
	if(v[0]==v[1]||v[0]==(v[1]+6)||v[0]==(v[1]+12)||v[0]==(v[1]+18))
	{
	v[2]=VLS(c, "Productive_Capacity_Variation", 6);
	v[3]=1;
	v[4]=1;
	v[5]=1;
	v[6]=1;
	v[7]=1;
	v[8]=1;
	v[9]=0;
	CYCLE(cur, "SECTORS")
	{
		v[10]=VS(cur,"id_capital_goods_sector");
		if (v[10]==1) //capital goods sector
			{
			v[11]=VLS(cur,"Demand_Met",5);
    	v[12]=VLS(cur,"Demand_Met",4);
    	v[13]=VLS(cur,"Demand_Met",3);
    	v[14]=VLS(cur,"Demand_Met",2);
    	v[15]=VLS(cur,"Demand_Met",1);
    	v[16]=VLS(cur,"Demand_Met",6);                 //Modificado por Jo�o
    	v[17]=VLS(cur,"Demand_Met_By_Imports",5);
    	v[18]=VLS(cur,"Demand_Met_By_Imports",4);
    	v[19]=VLS(cur,"Demand_Met_By_Imports",3);
    	v[20]=VLS(cur,"Demand_Met_By_Imports",2);
    	v[21]=VLS(cur,"Demand_Met_By_Imports",1);
    	v[22]=VLS(cur,"Demand_Met_By_Imports",6);			//Modificado por Jo�o
    	
    	v[23]=v[11]+(1-v[11])*v[17];
    	v[24]=v[12]+(1-v[12])*v[18];
    	v[25]=v[13]+(1-v[13])*v[19];
    	v[26]=v[14]+(1-v[14])*v[20];
    	v[27]=v[15]+(1-v[15])*v[21];
    	v[28]=v[16]+(1-v[16])*v[22];
    	v[29]=VS(cur, "propensity_to_import_capital_goods");
    	}
    else
    	{
    	v[23]=1;
    	v[24]=1;
    	v[25]=1;
    	v[26]=1;
    	v[27]=1;
    	v[28]=1;
    	v[29]=0;
    	}
    v[3]=min(v[3],v[23]);
		v[4]=min(v[4],v[24]);
		v[5]=min(v[5],v[25]);
		v[6]=min(v[6],v[26]);
		v[7]=min(v[7],v[27]);
		v[8]=min(v[8],v[28]);
		v[9]=max(v[9],v[29]);
	}
	v[30]=v[2]*(1-v[9])*((v[3]+v[4]+v[5]+v[6]+v[7]+v[8])/6)+v[2]*v[9];
	}
else
	v[30]=0;
RESULT(v[30])


EQUATION("Class_Expenses_Function")
/*
Must be called by the classes
*/
	v[0]=VS(c,"Class_Real_Domestic_Consumption");                                                     // class real icnome lagged 1
	v[1]=VS(c,"Class_Real_External_Consumption");                                                     // class real icnome lagged 2
	v[2]=V("Exchange_Rate");                                                                //exchange rate
	
	v[3]=0;                                                                                 //initializes the CYCLE                                                                                //initializes the CYCLE
	CYCLE(cur, "SECTORS")                                                                   //CYCLE trought the sectors
	{
		v[4]=VS(cur, "id_consumption_goods_sector");
		if(v[4]==1)		
			{
			v[6]=VS(cur, "Avg_Price");                                                           //sector average price
			v[7]=VS(cur, "Foreign_Price");                                                       //sector external price
			v[8]=v[0]*v[6]+v[1]*v[2]*v[7];                       
			}
		else
			v[8]=0;
		v[3]=v[3]+v[8];	
	}
RESULT(v[3])


EQUATION("Income_Taxes_Function")
/*
Calculates income taxes of the classes and must be called by the government variable
Must be called by Government.
*/
	v[0]=V("Total_Wages");
	v[10]=V("Total_Salaries");                                 //total wages          
	v[11]=v[0]-v[10];
	v[1]=V("Distributed_Profits");                         //distributed profits for the classes
	v[2]=0;                                                //initializes the CYCLE
	CYCLE(cur, "CLASSES")                                  //CYCLE trought all classes
	{
		v[3]=VS(cur,"class_direct_tax");                     //income tax percentage of each class
		v[4]=VS(cur,"class_profit_distribution");                   //class profit share
		v[5]=VS(cur,"class_wage_distribution");                     //class wage share
		v[6]=VS(cur,"class_salary_distribution");    //interest payment from the government to the class
		v[7]=(v[11]*v[5]+v[10]*v[6]+v[1]*v[4])*v[3];                     //income tax of each class is the tax percentage multiplyed by class total income
		v[2]=v[2]+v[7];                                      //sums up income taxes of all classes
	}
RESULT(v[2])


EQUATION("Indirect_Taxes_Function")
/*
Calculates indirect taxes of all firms. Must be called by the government variable
Must be called by Government.
*/
	v[0]=0;                                //initializes the CYCLE
	CYCLE(cur, "SECTORS")                  //CYCLE trought all sectors
	{              
		v[1]=0;                              //initializes the second CYCLE
		CYCLES(cur, cur1, "FIRMS")           //CYCLE trought all firms in the sector
		{
			v[2]=VS(cur1, "Indirect_Tax");     //firm's indirect tax
			v[1]=v[1]+v[2];                    //sums up all firm's indirect tax of the sector
		}
	v[0]=v[0]+v[1];                        //sums up all sectors indirect tax
	}
RESULT(v[0])


EQUATION("Intermediate_Imports_Function")
/*
The imported total of each type of input is determined by the sum for all sectors of the economy of the import of the respective input.
*/
v[0]=VS(c, "id_intermediate_goods_sector");
if (v[0]==1)
	{
	v[1]=VS(c, "id_sector_number");
	v[2]=0;
	CYCLE(cur, "SECTORS")
	{
		v[3]=0;
		CYCLES(cur, cur1, "FIRMS")
		{
			cur2 = SEARCH_CND("id_input_sector", v[1]);
			v[4]=VS(cur2, "Input_Imports");
			v[3]=v[3]+v[4];
		}
		v[2]=v[2]+v[3];
	}
	}
else
	v[2]=0;
RESULT(v[2])


EQUATION("Consumption_Imports")
/*
Sums up the demand for imports of each income class.
*/
	v[0]=SUM("Class_Real_External_Consumption");
RESULT(v[0])
