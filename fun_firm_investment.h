
EQUATION("Expected_Sales_Long_Term")
/*
Firm Variable.
The sectors update their productive capacity from year to year, time it takes for new capacity to be produced and to be available for use. The variation in the desired productive capacity is then defined according to the expected orders for the following year. Expected orders are calculated from the average of actual orders for the last six periods and the growth projection for six periods thereafter. This projection is determined on the basis of the difference between the averages of orders for the last six periods and the six periods prior to them, on which a doubling annual extrapolation factor applies.
*/
	v[0]=V("Effective_Orders");                           //firm's effective orders in the current period
	v[1]=VL("Effective_Orders",1);                        //firm's effective orders lagged 1
	v[2]=VL("Effective_Orders",2);                        //firm's effective orders lagged 2
	v[3]=VL("Effective_Orders",3);                        //firm's effective orders lagged 3
	v[4]=VL("Effective_Orders",4);                        //firm's effective orders lagged 4
	v[5]=VL("Effective_Orders",5);                        //firm's effective orders lagged 5
	v[6]=VL("Effective_Orders",6);                        //firm's effective orders lagged 6
	v[7]=VL("Effective_Orders",7);                        //firm's effective orders lagged 7
	v[8]=VL("Effective_Orders",8);                        //firm's effective orders lagged 8
	v[9]=VL("Effective_Orders",9);                        //firm's effective orders lagged 9
	v[10]=VL("Effective_Orders",10);                      //firm's effective orders lagged 10
	v[11]=VL("Effective_Orders",11);                      //firm's effective orders lagged 11
   
	v[12]=(v[0]+v[1]+v[2]+v[3]+v[4]+v[5])/6;              //average effective orders of the last six periods
	v[13]=(v[6]+v[7]+v[8]+v[9]+v[10]+v[11])/6;            //average effective orders of the six periods prior to the last six
   		
	v[14]=V("Gama");                                      //expectations parameter
	if (v[13]!=0)                                         //if the average effective orders of the six periods prior to the last six is not zero
		{
		v[15]=v[12]*(1+2*v[14]*((v[12]-v[13])/v[13]));      //expected orders for the next six periods will be the average effective orders of the last six periods multiplied by the growth rate between the averages and the double of the expectation parameter
		v[16]=max(0,v[15]);                                 //expected orders for the next six periods can never be negative
		}
	else                                                  //if the average effective orders of the six periods prior to the last six is zero
		v[16]=0;                                            //expected orders for the next six periods will be zero
RESULT(v[16])


EQUATION("Desired_Productive_Capacity_Variation")
/*
Firm Variable
The desired change in productive capacity is calculated from the expected sales minus the existing productive capacity, considering the margin over sales to be kept in stock and the desired degree of utilization of the productive capacity (1 / ALFA). To ensure that the desired capacity variation generates a demand for an entire number of capital goods, the desired variation is divided by the coefficient of indivisibility and the integer is taken, which is then multiplied by the coefficient. The observed lags distribute uniformly the demand for capital goods from the different sectors over time.
*/
	v[6]=V("id_firm_number");                                                                                                                                             
	v[10]=V("investment_period");
	v[7]= fmod((double) t,v[10]); 
   	if(v[6]==v[7]||v[6]==(v[7]+v[10])||v[6]==(v[7]+2*v[10])||v[6]==(v[7]+3*v[10]))
   	{
   		v[0]=V("Expected_Sales_Long_Term");
   		v[1]=V("Productive_Capacity"); 
   		v[2]=V("desired_inventories_proportion");
   		v[3]=V("desired_degree_capacity_utilization");
   		v[9]=V("Depreciation_Productive_Capacity");
   		//v[4]=((1+v[2])/v[3])*v[0]-(v[1]-v[9]);
   		v[4]=(v[0]/v[3])-(v[1]-v[9]);
   		v[8]=max(0,v[4]);
   		cur = SEARCH_CND("id_input_sector", 2);
   		v[5]=VS(cur, "capital_output_ratio");
   		v[11]=v[8]*v[5];
   		modf(v[11],&v[12]);
   		v[13]=v[12]/v[5];
   		}
   	else
   		v[13]=0;
RESULT(v[13])


EQUATION("Depreciation_Productive_Capacity")
/*
Firm Variable
*/
v[0]=V("id_firm_number");
v[1]=V("investment_period");
v[2]= fmod((double) t,v[1]); 

if(v[0]==v[2]||v[0]==(v[2]+v[1])||v[0]==(v[2]+2*v[1])||v[0]==(v[2]+3*v[1]))
	{
	v[3]=V("depreciation");
	v[4]=0;
	CYCLE(cur, "CAPITAL")
		{
			v[5]=VS(cur,"capital_good_date_birth");
			v[6]=VS(cur,"capital_good_productive_capacity");
			if((double)t==v[5]+v[3]-6)
				v[4]=v[4]+v[6];
			else
				v[4]=v[4];
		}
	}
else
v[4]=0;
RESULT(v[4])


EQUATION("Desired_Investment_Expenses")
/*
Firm Variable
Demand for capital goods of the sector. Capacity variation plus autonomous investment.
*/
v[0]=V("id_firm_number");
v[1]=V("investment_period");
v[2]= fmod((double) t,v[1]); 

if(v[0]==v[2]||v[0]==(v[2]+v[1])||v[0]==(v[2]+2*v[1])||v[0]==(v[2]+3*v[1]))
	{
	v[3]=V("Desired_Productive_Capacity_Variation");
	v[4]=V("Desired_Autonomous_Investment");
	v[5]=V("Price_Capital_Goods");
	
	cur = SEARCH_CND("id_input_sector", 2);
	v[6]=VS(cur, "capital_output_ratio");
	v[7]=(v[3]+v[4])*v[6]*v[5];
	}
else
	v[7]=0;
RESULT(v[7])


EQUATION("Desired_Autonomous_Investment")
/*
Firm Variable
Demand for capital goods of the sector. Capacity variation plus autonomous investment.
*/
v[0]=V("switch_autonomous_investment");
if (v[0]==1)
	{
	if((double) t<15)
  	v[1]=V("desired_autonomous_investment_parameter");
  if((double) t>=15 &&(double) t<35)
  	{
   	v[2]=V("desired_autonomous_investment_parameter");
   	v[3]=(double) t;
   	v[1]=(1-((v[3]-15)/40))*v[2];
   	}
  if((double) t>=35)
   	{
   	v[2]=V("desired_autonomous_investment_parameter");
   	v[1]=v[2]*0.5;
   	}
  }
else
	v[1]=V("desired_autonomous_investment_parameter");
RESULT(v[1])


EQUATION("Productive_Capacity_Variation")
/*
Firm Variable
*/
v[0]=V("Desired_Productive_Capacity_Variation");
v[1]=V("Investment_Expenses");
v[2]=V("Price_Capital_Goods");
	
cur = SEARCH_CND("id_input_sector", 2);
v[3]=VS(cur, "capital_output_ratio");

v[4]=v[1]/v[2];
v[5]=v[4]*v[3];

modf(v[5],&v[6]);
if (v[6]>0)
	{
	v[7]=V("Frontier_Productivity");
	v[8]=V("Max_Capital_Goods_Productivity");
		if (v[7]>=v[8])
		WRITE("id_a_3", 1);
		else
		WRITE("id_a_3", 2);
	}
else
	WRITE("id_a_3", 0);
v[9]=min(v[6],v[0]);
RESULT(v[9])


EQUATION("Demand_Productive_Capacity")
/*
Firm Variable
*/
v[0]=V("Investment_Expenses");
v[1]=V("Price_Capital_Goods");
cur = SEARCH_CND("id_input_sector", 2);
v[2]=VS(cur, "capital_output_ratio");

v[3]=v[0]/v[1];
v[4]=v[3]/v[2];

modf(v[4],&v[5]);
v[6]=v[0]-v[5]*v[2]*v[1];
WRITE("rest", v[6]);
RESULT(v[4])


EQUATION("Effective_Orders_Capital_Goods_Firm")
/*
Firm Variable
It is settled in a way that there will be no excess demand while there is still productive capacity in the sector. This distribution is done in this variable.
*/
V("Effective_Orders_Capital_Firm");
v[0]=V("capital_goods_effective_orders_firm_temporary");
WRITE("capital_goods_production_temporary", 0);
WRITE("capital_goods_effective_orders_firm_temporary", 0);
RESULT(v[0])


EQUATION("Productive_Capacity")
/*
Firm Variable
In this variable, new capital goods are created and old ones are deleted.
*/
v[0]=V("Effective_Productive_Capacity_Variation");
v[1]=VL("Frontier_Productivity",6);//Available technology when the capital good was ordered. 
v[2]=VL("Max_Capital_Goods_Productivity",6);//Best technology in use when the capital good was ordered
v[3]=VL("Sum_Id_A_3",6);
v[4]=VL("Sum_Id_A_3",7);
v[5]=V("depreciation");
cur2 = SEARCH_CND("id_input_sector", 2);
v[6]=VS(cur2,"capital_output_ratio");
v[7]=round(v[0]*v[6]);//The amount of Capital Goods bought
v[8]=fmod((double) t,6);
v[9]=V("id_firm_number");
v[14]=V("Max_Capital_Goods_Productivity");

if(v[9]==v[8]||v[9]==(v[8]+6)||v[9]==(v[8]+12)||v[9]==(v[8]+18))//OBSOLECENSE
	{
	v[10]=0;
	CYCLE(cur, "CAPITAL")
	{
		v[11]=VS(cur, "id_a_2");
		v[12]=VS(cur, "capital_good_productive_capacity");
			if (v[11]>0)//the capital good is obsolete and it will be replaced by a modern one
				{
				WRITES(cur, "capital_good_productivity_initial", v[1]);
				WRITES(cur, "id_a_2", 0);
				WRITES(cur, "capital_good_date_birth", (double)t);
				WRITES(cur, "to_die_capital_good", 0);
				v[10]=v[10]+v[12];
			}
     	else
     		v[10]=v[10];
   }
   
	if (v[0]>0) //Productive Capacity Expansion
	{
		if (v[3]==(v[4]+1)) //technological frontier
		{
		for(v[13]=0; v[13]<v[7]; v[13]=v[13]+1)
        {
        cur=ADDOBJ("CAPITAL");
        WRITES(cur, "capital_good_productivity_initial", v[1]);
				WRITES(cur, "capital_good_productive_capacity", v[6]);
				WRITES(cur, "capital_good_date_birth", (double)t);
				WRITES(cur, "to_die_capital_good", 0);
				}
		}
		if (v[3]==(v[4]+2)) 
		{
		cur = SEARCH_CND("Capital_Good_Productivity", v[14]);
		for(v[13]=0; v[13]<v[7]; v[13]=v[13]+1)
        {
        if ( cur != NULL )				
        	cur = ADDOBJ_EX( "CAPITAL", cur );
        else
        	cur = ADDOBJ( "CAPITAL" );
        WRITES(cur, "capital_good_date_birth",(double)t);
        WRITES(cur, "to_die_capital_good",0);
        }
     }
	}
	WRITE("Productive_Capacity_Scrapped", v[10]); //amount of prod. cap. scrapped	
	}
v[15] = SUM("capital_good_productive_capacity");
RESULT(v[15])


EQUATION("Effective_Productive_Capacity_Variation")
/*
Stores the value of the Function
*/
	v[0]=V("Effective_Productive_Capacity_Variation_Function");
RESULT(v[0])


EQUATION("Desired_Autonomous_Investment_Quality")
/*
Desired Autonomous Investment to obtain the gains of quality increase
*/
v[0]= fmod((double) t,6); 
v[1]=V("id_firm_number"); 
if(v[1]==v[0]||v[1]==(v[0]+6)||v[1]==(v[0]+12)||v[1]==(v[0]+18))
  {
  v[2]=V("Available_Funds_Replacement");
  v[3]=V("Pay_Test_Quality");
     if(v[2]>0&&v[3]==1)
     	{
     	v[4]=V("quality_investment_parameter");
     	v[5]=V("Productive_Capacity");
     	cur = SEARCH_CND("id_input_sector", 2);
     	v[6]=VS(cur,"capital_output_ratio");
     	v[7]=V("Price_Capital_Goods");
     	v[8]=v[4]*v[5]*v[6]*v[7];
    	}
     else
    	v[8]=0;
  }
else
  v[8]=0;
RESULT(v[8])


EQUATION("Autonomous_Investment_Quality")
/*
Autonomous Investment to obtain the gains of quality increase
*/
v[0]= fmod((double) t,6);
v[1]=V("id_firm_number");  
if(v[1]==v[0]||v[1]==(v[0]+6)||v[1]==(v[0]+12)||v[1]==(v[0]+18))
  {
  v[2]=V("Available_Funds_Replacement");
  v[3]=V("Desired_Autonomous_Investment_Quality");
  v[4]=min(v[2],v[3]);
  }
else
  v[4]=0;
RESULT(v[4])


EQUATION("Available_Funds_Replacement_Rest")
/*
Autonomous Investment to obtain the gains of quality increase
*/
v[0]= fmod((double) t,6);
v[1]=V("id_firm_number"); 
v[2]=V("Available_Funds_Replacement");
if(v[1]==v[0]||v[1]==(v[0]+6)||v[1]==(v[0]+12)||v[1]==(v[0]+18))
  {
  v[3]=V("Autonomous_Investment_Quality");
  v[4]=v[2]-v[3];
  }
else
  v[4]=v[2];
RESULT(v[4])


EQUATION("Demand_Productive_Capacity_Quality")
/*
Autonomous Investment to obtain the gains of quality increase
*/
v[0]= fmod((double) t,6);
v[1]=V("id_firm_number"); 
if(v[1]==v[0]||v[1]==(v[0]+6)||v[1]==(v[0]+12)||v[1]==(v[0]+18))
  {
  v[2]=V("Autonomous_Investment_Quality");
  v[3]=V("Price_Capital_Goods");
  cur = SEARCH_CND("id_input_sector", 2);
  v[4]=VS(cur,"capital_output_ratio");
  v[5]=round(v[2]/(v[3]*v[4]));
  }
else
  v[5]=0;
RESULT(v[5])


EQUATION("Replecement")
/*
Firm Variable
*/
	v[0]=0;
	CYCLE(cur, "CAPITAL")
		{
		v[1]=VS(cur,"Capital_Good_Replacement");
		v[0]=v[0]+v[1];
		}
RESULT(v[0])


EQUATION("Replecement_2")
/*
Expenses in aquisition of new equipment to replace obsolete ones.
*/
V("Productive_Capacity");
V("Investment_Expenses_1");
v[0]=V("Available_Funds_Replacement_Rest");
v[2]=V("Pool_Financial_Assets");
v[3]=V("Pool_Debt");
v[4]=V("Desired_Investment_Expenses");
v[5]=V("Funds");     
v[6]=VL("Debt",1);
v[7]=V("depreciation");
v[8]=V("payback");
v[9]=V("Frontier_Productivity");
v[10]=V("Wage");
v[11]=V("Price_Capital_Goods");
cur1 = SEARCH_CND("id_input_sector", 2);
v[24]=VS(cur1, "capital_output_ratio");
v[12]=V("Max_Capital_Goods_Productivity");
v[31]=V("bonus");
v[32]=V("antecipation");
v[13]=max(v[9]*(1+v[32]*v[31]),v[12]);
v[14]=V("id_firm_number");
v[15]= fmod((double) t,6); 
  if(v[14]==v[15]||v[14]==(v[15]+6)||v[14]==(v[15]+12)||v[14]==(v[15]+18))
  {
  v[16]=0;
  v[21]=v[0];
  SORT("CAPITAL","Capital_Good_Productivity","UP");  
   CYCLE(cur, "CAPITAL")
   {
     v[19]=VS(cur, "capital_good_date_birth");
     if((double)t!=v[19])
     {
     v[17]=VS(cur, "Capital_Good_Productivity");
     v[18]=VS(cur, "capital_good_productive_capacity");     
     v[20]=v[18]*v[24]*v[11];
     v[21]=v[0]-v[16];
         if(v[13]>v[17])
         { 
         v[22]=(1/(v[17]))-(1/(v[13]));
         v[23]=v[11]/(v[10]*v[22]); 
         }
         else
         {
         v[22]=0;
         v[23]=0;
         } 
      WRITES(cur, "pay_test", v[22]);
      WRITES(cur, "pay_test_2", v[23]);
         if(v[22]!=0 && v[20]<=v[21]&& v[23]<=v[8]  && (double)t < v[7]+v[19]-6)
         {
         WRITES(cur, "id_a_2",1);
         v[16]=v[16]+v[20];
         WRITES(cur, "Capital_Good_Replacement",v[18]);         
         }
         else
         {
         WRITES(cur, "Capital_Good_Replacement",0);
         v[16]=v[16];
         }
      }
      else
      {
      WRITES(cur, "id_a_2",0);
      WRITES(cur, "Capital_Good_Replacement",0);
      }   
   }
  }
  else
  {
  v[16]=v[0];      
  v[21]=v[0];  
  }
   /*END OF THE CYCLE*/
     
  if(v[0]>0)//if there were resources for modernization 
  {
  if(v[14]==v[15]||v[14]==(v[15]+6)||v[14]==(v[15]+12)||v[14]==(v[15]+18))
  v[1]=v[21];// what is left after pay-back period calculus
  else
  v[1]=v[0];//It was not an investment period, therefore the extra amount was not expended

    if(v[3]>=0)//May increase debt
     {
       if(v[1]>=v[3])
       {
         v[25]=0;
         v[26]=v[2]+(v[1]-v[3]);
       }
       else
       {
         v[25]=v[3]-v[1];
         v[26]=v[2];
       }
    
     }
    else //v[3]<0
    {
     if(v[6]+v[3]-v[1]>=0)
      {
      v[25]=v[3]-v[1];
      v[26]=v[2];
      }
      else
      {
     v[25]=-v[6];
     v[26]=v[2]+v[1]-v[3]-v[6];
     } 
    } 
    WRITE("financial_asset_3",v[26]);
    WRITE("debt_3",v[25]);
   	}
	else 
	{
 	WRITE("financial_asset_3",0);
 	WRITE("debt_3",0);
	}

	if(v[14]==v[15]||v[14]==(v[15]+6)||v[14]==(v[15]+12)||v[14]==(v[15]+18))
		v[50]=v[16];
	else
		v[50]=0;
		
RESULT(v[50])
