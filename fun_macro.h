/*****MACRO VARIABLES******/


/********************************* INCOME (GDP) ************************************************/


EQUATION("Distributed_Profits")
/*
Total amount of distributed profits by the firms. Will be used to determine the income of the income classes and to calculate GDP.
*/
	v[0]=0;                                            //initializes the CYCLE
	CYCLE(cur, "SECTORS")                              //CYCLE trought all sectors
	{
		v[1]=0;                                          //initializes the second CYCLE
		CYCLES(cur, cur1, "FIRMS")                       //CYCLE trought all firms
		{
			VS(cur1, "Retained_Profits");                  //make sure Retained_Profits was calculated before
			v[2]=VS(cur1, "Profits_Distribution");         //value of distributed profits of each firm
			v[1]=v[1]+v[2];                                //sums up the value of all firms in the sector
		}
		v[0]=v[0]+v[1];                                  //sums up the value of distributed profits of all sectors
	}
RESULT(v[0])


EQUATION("Total_Retained_Profits")
/*
Total amount of retained profits by the firms. Will be used to calculate GDP
*/
	v[0]=0;                                                    //initializes the CYCLE
	CYCLE(cur, "SECTORS")                                      //CYCLE trought all sectors
	{ 
		v[1]=0;                                                  //initializes the second CYCLE
		CYCLES(cur, cur1, "FIRMS")                               //CYCLE trought all firms of the sector
		{
			v[2]=VS(cur1, "Retained_Profits");                     //firm's retained profits
			v[1]=v[1]+v[2];                                        //sums up all firms' surplus of the sector
		}
		v[0]=v[0]+v[1];                                          //sums up the surplus of all sectors
	}
RESULT(v[0])


EQUATION("Total_Profits")
/*
Comment
*/
	v[0]=V("Total_Retained_Profits");
	v[1]=V("Distributed_Profits");
	v[2]=v[0]+v[1];
RESULT(v[2])


EQUATION("Total_Real_Profits")
/*
Comment
*/
	v[0]=V("Total_Profits");
	v[1]=V("Price_Index");
	v[2]=v[0]/v[1];
RESULT(v[2])



//EQUATION("Total_Interest_Paid")
/*
Total amount of retained profits by the firms. Will be used to calculate GDP
*/
//	v[0]=0;                                                    //initializes the CYCLE
//	CYCLE(cur, "SECTORS")                                      //CYCLE trought all sectors
//	{ 
//		v[1]=0;                                                  //initializes the second CYCLE
//		CYCLES(cur, cur1, "FIRMS")                               //CYCLE trought all firms of the sector
//		{
//			v[2]=VLS(cur1,"Debt",1);                               //firm's stock of debt in the last period
//			v[3]=VS(cur1,"Interest_Rate_Firm");                    //interest rate paid by the firm
//			v[1]=v[1]+v[2]*v[3];                                   
//		}
//		v[0]=v[0]+v[1];  																				//Total interest paid by firms                                        
//	}
//	v[4]=VL("Public_Debt",1);
//	v[5]=V("Interest_Rate");
//	v[6]=v[4]*v[5];																						//Total interest paid by Government
//	v[7]=0;
//	CYCLE(cur, "CLASSES")                                     //CYCLE trought Classes
//	{
//		v[8]=VL("Class_Debt",1);
//		v[7]=v[7]+v[8]*v[5];																		//Total interest paid by classes
//	}
//	v[9]=v[0]+v[6]+v[7];
//RESULT(v[9])


EQUATION("Total_Surplus")
/*
Total Surplus of the Economy. Will be used to calculate GDP
*/
	v[0]=0;                                                    //initializes the CYCLE
	CYCLE(cur, "SECTORS")                                      //CYCLE trought all sectors
	{ 
		v[1]=0;                                                  //initializes the second CYCLE
		CYCLES(cur, cur1, "FIRMS")                               //CYCLE trought all firms of the sector
		{
			v[2]=VS(cur1, "Surplus");                              //firm's surplus
			v[1]=v[1]+v[2];                                        //sums up all firms' surplus of the sector
		}
		v[0]=v[0]+v[1];                                          //sums up the surplus of all sectors
	}
RESULT(v[0])


EQUATION("Total_Wages")
/*
The total wage is calculated by the sum of the wages paid in the agricultural sector with the wages paid in the other sectors and the salaries paid by the government. The wage per unit of production is a predetermined parameter, and the total salary is calculated by multiplying this unit wage by the actual production of each sector (the hiring of workers is performed only after it has been verified how much is available to be able to produce). In the case of the agricultural sector, the total wage is calculated by multiplying the unitary wage by the programmed production restricted by the available inputs. 
*/
	v[0]=0;                                                    //initializes the CYCLE
	CYCLE(cur, "SECTORS")                                      //CYCLE trought all sectors
	{
		v[1]=0;								                                   
		CYCLES(cur, cur1, "FIRMS")                                //initializes the second CYCLE
		{
			v[2]=VS(cur1, "Wage_Bill");               					   //firm's wage bill
			v[1]=v[1]+v[2];
		}
		v[0]=v[0]+v[1];                                          
	}
	v[3]=V("Government_Wages");                                //wages paid by the government
	v[4]=v[0]+v[3];                                            //sums up productive sectors wages with government wages
RESULT(v[4])


EQUATION("Total_Real_Wages")
/*
Comment
*/
	v[0]=V("Total_Wages");
	v[1]=V("Price_Index");
	v[2]=v[0]/v[1];
RESULT(v[2])


EQUATION("Total_Direct_Wages")
/*
Total remuneration of direct labour and government labour
*/
	v[0]=0;                                                    //initializes the CYCLE
	CYCLE(cur, "SECTORS")                                      //CYCLE trought all sectors
	{
		v[1]=VS(cur, "Wage");                                    //sector wage
		v[2]=0;                                                  //initializes the second CYCLE
		CYCLES(cur, cur1, "FIRMS")                               //CYCLE trought all firms of the sector
		{
			v[3]=VS(cur1, "Effective_Production");                 //firm's effective production
			v[4]=VLS(cur1, "Firm_Avg_Productivity", 1);            //firm's productivity in the last period
			v[2]=v[2]+v[3]*(v[1]/v[4]);                            //sums up all firms' wage, determined by a unitary wage (sectorial wage divided by firm's productivity) multiplied by firm's effective production
		}
		v[0]=v[0]+v[2];                                          //sums up all wages of all sectors
	}
	v[5]=V("Government_Wages");                                //wages paid by the government
	v[6]=v[0]+v[5];                                            //sums up productive sectors wages with government wages
RESULT(v[6])

EQUATION("Total_Salaries")
/*
Comment
*/
	v[0]=V("Total_Wages");
	v[1]=V("Total_Direct_Wages");
	v[2]=v[0]-v[1];
RESULT(v[3])



EQUATION("Profit_Share")
/*
Profit Share
*/
	v[0]=V("Total_Wages");
	v[1]=V("Total_Retained_Profits");
	v[2]=V("Distributed_Profits");
	v[3]=v[0]+v[1]+v[2];
	v[4]=(v[1]+v[2])/v[3];
RESULT(v[4])


EQUATION("Wage_Share")
/*
Wage Share
*/
	v[0]=V("Total_Wages");
	v[1]=V("Total_Retained_Profits");
	v[2]=V("Distributed_Profits");
	v[3]=v[0]+v[1]+v[2];
	v[4]=v[0]/v[3];
RESULT(v[4])


EQUATION("Avg_Markup")
/*
Agregated average markup 
*/
	v[0]=WHTAVE("Avg_Markup_Sector", "Sales_Sector");
	v[1]=SUM("Sales_Sector");
	v[2]=v[0]/v[1];
RESULT(v[2])		


EQUATION("Avg_M")
/*
Agregated average markup 
*/
	v[0]=WHTAVE("Avg_M_Sector", "Sales_Sector");
	v[1]=SUM("Sales_Sector");
	v[2]=v[0]/v[1];
RESULT(v[2])


EQUATION("Avg_Profit_Margin")
/*
Agregated average markup 
*/
	v[0]=WHTAVE("Avg_Profit_Margin_Sector", "Sales_Sector");
	v[1]=SUM("Sales_Sector");
	v[2]=v[0]/v[1];
RESULT(v[2])


EQUATION("Q_GDP")
/*
Calculated summing up profits, wages and indirect taxes
*/
	v[0]=V("Total_Retained_Profits");
	v[1]=V("Distributed_Profits");                     
	v[2]=V("Total_Wages");
	v[3]=V("Indirect_Taxes");
	//v[4]=V("Total_Interest_Paid");
	v[5]=v[0]+v[1]+v[2]+v[3];
RESULT(v[5])


EQUATION ("Old_Q_GDP")
	v[0]=V("Total_Surplus");
	v[1]=V("Total_Direct_Wages");
	v[2]=V("Indirect_Taxes");
	v[3]=v[0]+v[1]+v[2];
RESULT(v[3])


EQUATION("GDP")
/*
Annual GDP. Sums up quarterly GDP
*/
	v[0]=V("Q_GDP");
	v[1]=VL("Q_GDP",1);
	v[2]=VL("Q_GDP",2);
	v[3]=VL("Q_GDP",3);
	v[4]=(v[0]+v[1]+v[2]+v[3]);
RESULT(v[4])


EQUATION("Real_Q_GDP")
/*
Nominal GDP over the price index.
*/
	v[0]=V("Q_GDP");                 //nominal GDP
	v[1]=V("Price_Index");           //current price index
	if(v[1]!=0)                      //if the price index is not zero
		v[2]=v[0]/v[1];                //real GDP is the nominal GDP devided by the price index
	else                             //if the price index is zero
		v[2]=v[0];                     //real GDP equals nominal GDP
RESULT(v[2])


EQUATION("Growth_rate")
/*
Annual GDP growth rate.
*/
	v[0]=VL("Q_GDP",7);              //GDP lagged 7
	v[1]=VL("Q_GDP",6);              //GDP lagged 6
	v[2]=VL("Q_GDP",5);              //GDP lagged 5
	v[3]=VL("Q_GDP",4);              //GDP lagged 4
	v[4]=(v[0]+v[1]+v[2]+v[3]);      //annual GDP of the year before last
	v[5]=VL("Q_GDP",3);              //GDP lagged 3
	v[6]=VL("Q_GDP",2);              //GDP lagged 2
	v[7]=VL("Q_GDP",1);              //GDP lagged 1
	v[8]=V("Q_GDP");                 //current GDP
	v[9]=(v[5]+v[6]+v[7]+v[8]);      //annual GDP of the last year
	v[10]=(v[9]-v[4])/v[4];          //growth rate between the annual GDP
RESULT(v[10])


EQUATION("Real_Growth_Rate")
/*
Annual Real GDP Growth rate.
*/
		v[0]=VL("Real_Q_GDP",7);       //real GDP lagged 7
		v[1]=VL("Real_Q_GDP",6);       //real GDP lagged 6 
		v[2]=VL("Real_Q_GDP",5);       //real GDP lagged 5
		v[3]=VL("Real_Q_GDP",4);       //real GDP lagged 4
		v[4]=(v[0]+v[1]+v[2]+v[3]);    //annual real GDP of the year before last
		v[5]=VL("Real_Q_GDP",3);       //real GDP lagged 3    
		v[6]=VL("Real_Q_GDP",2);       //real GDP lagged 2
		v[7]=VL("Real_Q_GDP",1);       //real GDP lagged 1
		v[8]=V("Real_Q_GDP");          //current real GDP
		v[9]=(v[5]+v[6]+v[7]+v[8]);    //annual real GDP of the last year
		v[10]=(v[9]-v[4])/v[4];        //growth rate between the annual real GDP
RESULT(v[10])

/*************************** EXPENSES (GDP)*****************************************************/


EQUATION("Aggregate_Investment_Expenses")
/*
Aggeregate Investment Expenses is calculated summing up the demand of capital goods of all firms and multiplying by the average price of the capital goods sector
*/
	cur = SEARCH_CND("id_capital_goods_sector", 1);
	v[4]=VS(cur, "Avg_Price");
	v[0]=0;
	CYCLE(cur, "SECTORS")
	{
		v[1]=0;
		CYCLES(cur, cur1, "FIRMS")
		{
			v[2]=0;
			CYCLES(cur1, cur2, "INPUTS")
			{
			v[3]=VS(cur2, "Demand_Capital_Goods");
			v[2]=v[2]+v[4]*v[3];
			}
		v[1]=v[1]+v[2];
		}
	v[0]=v[0]+v[1];
	}
RESULT(v[0])



EQUATION("Real_Q_Investment")
/*
Quarterly aggregate investment.
*/
	v[0]=V("Aggregate_Investment_Expenses");          
	v[1]=V("Price_Index");
	v[2]=v[0]/v[1];
RESULT(v[2])


EQUATION("Aggregate_Inventories")
	v[0]=0;                                                //initializes the CYCLE
	CYCLE(cur, "SECTORS")                                  //CYCLE trough all sectors 
	{
		v[1]=VS(cur,"Avg_Price");                            //sector average price    
  	v[2]=VS(cur,"Inventories_Sector");                   //sector stock of inventories
  	v[0]=v[0]+v[1]*v[2];                                 //calculates and sums up nominal value of inventories of all sectors
	}
RESULT(v[0])


EQUATION("Aggregate_Inventories_Variation")
v[0]=0;
CYCLE(cur, "SECTORS")
{
	v[1]=0;
	CYCLES(cur, cur1, "FIRMS")
	{
		v[2]=VS(cur1, "Inventories_Variation");
		v[1]=v[1]+v[2];
	}
	v[0]=v[0]+v[1];
}
RESULT(v[0])


EQUATION("Real_Aggregate_Inventories_Variation")
/*
Quarterly aggregate investment.
*/
	v[0]=V("Aggregate_Inventories_Variation");          
	v[1]=V("Price_Index");
	v[2]=v[0]/v[1];
RESULT(v[2])



EQUATION("Autonomous_Consumption_Variation_Rate")

	v[0]=V("switch_autonomous_consumption");                     //switch, changes how the rate is determined
	v[1]=VL("Autonomous_Consumption_Variation_Rate",1);          //rate of change of the autonomous consumption in the last period

	if(v[0]==0)                                                  //if the value of the switch is zero                                      
		v[8]=0;                                                    //rate of change of the autonomous consumption is zero
	else                                                         //if the value of the switch is not zero, one
  	{
  	v[2]=fmod((double) t,10);                                  //divides the time period by ten
   	 if(v[2]==0)                                               //if the rest of the above division is zero
     	 {
      	v[3]=VL("Avg_Quality_Sector",10);                      //calls the average quality of the sector lagged 10
      	v[4]=VL("Avg_Quality_Sector",1);                       //calls the average quality of the sector lagged 1
      	v[5]=(v[4]-v[3])/v[3];                                 //gives a growth rate of the average quality
      	v[6]=V("min_autonomous_consummption_variation_rate");  //calls the minimum rate of change possible
      	v[7]=V("max_autonomous_consummption_variation_rate");  //calls the maximum rate of change possible
   
        	if(v[5]<=0)                                          //if the quality growth rate was negative
        		v[8]=0;                                            //autonomous consumption rate of change is zero
        	else                                                 //if the quality growth was not negative
          	{
          	v[9]=v[5]/0.0001;                                  //
          	modf(v[9],&v[10]);                                 //
          	v[11]=v[10]*0.0001;                                //
          	v[8]=min(v[7],v[11]);                              //(TESTAR TIRAR DEPOIS)
          	}   
       	}
  	 else                                                      //if the division is not zero (it is not time period to adjust autonomous consumption)
    		v[8]=v[1];                                             //autonomous consumption rate of change will be the same from the last period
 		}
RESULT(v[8])


EQUATION("Q_Consumption")
/*
Quarterly aggregate nominal consumption, given by the nominal value of the consumption good sector sales
*/
	v[0]=SUM("Class_Real_Domestic_Consumption");                                              //initializes the CYCLE  
	v[1]=SUM("Class_Real_External_Consumption");
	v[2]=V("Consumer_Price_Index");
	cur = SEARCH_CND("id_consumption_goods_sector", 1);
	v[3]=VS(cur, "Foreign_Price");
	v[4]=V("Exchange_Rate");
	v[5]=v[0]*v[2]+v[1]*v[3]*v[4];
RESULT(v[5])


EQUATION("Real_Q_Consumption")
/*
Quarterly aggregate consumption.
*/
	v[0]=V("Q_Consumption");
	v[1]=V("Price_Index");
	v[2]=v[0]/v[1];
RESULT(v[2])


EQUATION("Real_Government_Expenses")
/*
Quarterly aggregate consumption.
*/
	v[0]=V("Government_Expenses");
	v[1]=V("Price_Index");
	v[2]=v[0]/v[1];
RESULT(v[2])



EQUATION("Total_Exports")
/*
The total exports of the economy in value are defined by the sum of the exports of each sector multiplied by the price charged in the period.
*/
v[0]=0;
CYCLE(cur, "SECTORS")
{
	v[1]=VS(cur, "Exports");
	v[2]=VS(cur, "Avg_Price");
	v[3]=VS(cur, "Demand_Met");
	v[4]=v[1]*v[2]*v[3];
	v[0]=v[0]+v[4];
}
RESULT(v[0])


EQUATION("Real_Exports")
/*
Quarterly aggregate consumption.
*/
	v[0]=V("Total_Exports");
	v[1]=V("Price_Index");
	v[2]=v[0]/v[1];
RESULT(v[2])


EQUATION("Total_Imports")
/*
Total imports (Local Currency)
*/

	v[0]=V("Exchange_Rate");
	v[1]=SUM("Input_Imports_Sector");
	cur1=SEARCH_CND("id_intermediate_goods_sector",1);
	v[2]=VS(cur1,"Foreign_Price");
	v[3]=SUM("Class_Real_External_Consumption");
	cur2=SEARCH_CND("id_consumption_goods_sector",1);
	v[4]=VS(cur2,"Foreign_Price");
	v[5]=v[3]*v[4]*v[0];
	v[6]=v[1]*v[2]*v[0];																	//Total imports of intermediate goods
	v[7]=0;																								//Total Extra Imports
	CYCLE(cur, "SECTORS")
		{
		v[8]=V("Extra_Imports");
		v[9]=V("Foreign_Price");
		v[7]=v[7]+v[8]*v[9]*v[0];
		}
	v[8]=v[5]+v[6]+v[7];																			
RESULT(v[8])


EQUATION("Real_Imports")
/*
Quarterly aggregate consumption.
*/
	v[0]=V("Total_Imports");
	v[1]=V("Price_Index");
	v[2]=v[0]/v[1];
RESULT(v[2])



EQUATION("Aggregate_Depreciation_Expenses")
/*
Sums up the employment of each sector.
*/
	v[0]=SUM("Depreciation_Expenses_Sector");
RESULT(v[0])


EQUATION("Q_GDP_Demand")
/*
GDP calculated by the demand perspective
*/
v[0]=V("Total_Classes_Expenses");
v[1]=V("Government_Expenses");
v[2]=V("Total_Exports");
v[3]=V("Total_Imports");
v[4]=V("Aggregate_Inventories_Variation");
v[5]=V("Aggregate_Depreciation_Expenses");
v[6]=V("Aggregate_Investment_Expenses");
//v[7]=v[0]+v[1]+v[2]-v[3]+v[4]-v[5]+v[6];
v[7]=v[0]+v[1]+v[2]-v[3]+v[4]+v[6];
RESULT(v[7])


EQUATION("Real_Q_GDP_Demand")
/*
GDP calculated by the demand perspective
*/
v[0]=V("Real_Q_Consumption");
v[1]=V("Real_Government_Expenses");
v[2]=V("Real_Exports");
v[3]=V("Real_Imports");
v[4]=V("Real_Aggregate_Inventories_Variation");
v[6]=V("Real_Q_Investment");
v[7]=v[0]+v[1]+v[2]-v[3]+v[4]+v[6];
RESULT(v[7])



/***************************** PRICE AND EMPLOYMENT ******************************************/

EQUATION("Price_Index")
/*
Paasche price index of all sector. GDP deflator
*/
	v[0]=v[1]=0;                                         //initializes the CYCLE  
	CYCLE(cur, "SECTORS")                                //CYCLE trough all sectors 
	{
		v[2]=VS(cur, "Sales_Sector");                      //sector sales
		v[3]=VS(cur, "Avg_Price");                         //sector average price
		v[4]=VS(cur, "avg_price_initial");                 //sector initial average price

		v[0]=v[0]+v[2]*v[3];                               //current nominal prices of the sector
		v[1]=v[1]+v[2]*v[4];                               //initial prices of the sector
	}
	if (v[1]!=0)                                         //if initial prices is not zero
		v[5]=v[0]/v[1];                                    //price index will be current prices over initial prices, 
	else                                                 //if initial prices is zero
		v[5]=VL("Price_Index", 1);                         //use last period price index
RESULT(v[5])


EQUATION("Consumer_Price_Index")
/*
Paasche price index of consumption goods sector. Used for inflation target and income classes real income.
*/
//	cur = SEARCH_CND("id_consumption_goods_sector", 1);
//	v[0]=VS(cur, "Avg_Price");
//RESULT(v[0])
	
	v[0]=0;
	v[1]=V("foreign_cpi_share");
	v[2]=V("Exchange_Rate");
	CYCLE(cur, "SECTORS")                                //CYCLE trough all sectors 
	{
		v[3]=VS(cur, "id_consumption_goods_sector");
		if (v[3]==1)
			{
			v[4]=VS(cur, "Avg_Price");                      
			v[5]=VS(cur, "Foreign_Price");
			v[0]=v[0]+v[4]*(1-v[1])+v[5]*v[2]*v[1];
			}
		else
			v[0]=v[0];
	}
RESULT(v[0])



EQUATION("Annual_Inflation")
/*
Annual growth of the consumer price index
*/
	v[0]=V("Consumer_Price_Index");
	v[1]=VL("Consumer_Price_Index",4);
	v[2]=(v[0]/v[1])-1;
RESULT(v[2])


EQUATION("Q_Inflation")
/*
Annual growth of the consumer price index
*/
	v[0]=V("Consumer_Price_Index");
	v[1]=VL("Consumer_Price_Index",1);
	v[2]=(v[0]/v[1])-1;
RESULT(v[2])



EQUATION("Avg_Wage")
/*
Average Wage of the economy weighted by the employment of each sector 
*/
	v[0]=WHTAVE("Wage", "Employment_Sector");
	v[1]=SUM("Employment_Sector");
	v[2]=v[0]/v[1];
RESULT(v[2])


EQUATION("Avg_Real_Wage")
/*
Average Wage of the economy weighted by the employment of each sector 
*/
	v[0]=V("Avg_Wage");
	v[1]=V("Consumer_Price_Index");
	v[2]=v[0]/v[1];
RESULT(v[2])




EQUATION("Avg_Productivity")
/*
Average Productivity of the economy weighted by the employment of each sector 
*/
	v[0]=WHTAVE("Avg_Productivity_Sector", "Employment_Sector");
	v[1]=SUM("Employment_Sector");
	v[2]=v[0]/v[1];
RESULT(v[2])


EQUATION("Total_Workers")
/*
Sums up the workers of each income class
*/
	v[0]=SUM("Class_Number_Workers");
RESULT(v[0])


EQUATION("Total_Employment")
/*
Sums up the employment of each sector.
*/
	v[0]=SUM("Employment_Sector");
RESULT(v[0])



EQUATION("Total_Employment_Growth_Rate")
/*
Sums up the employment of each sector.
*/
	v[0]=V("Total_Employment");
	v[1]=VL("Total_Employment",4);
	v[2]=(v[0]-v[1])/v[1];
RESULT(v[2])




/************************ OTHERS ******************************************/


EQUATION("Price_Capital_Goods")
/*
Price of capital goods for the firms is the average price of the capital goods sector
*/
	cur = SEARCH_CND("id_capital_goods_sector", 1);
	v[0]=VLS(cur, "Avg_Price", 1);
RESULT(v[0])


EQUATION("Aggregate_Rate_Capacity_Utilization")
/*

*/
	v[0]=0;                                                //initializes the CYCLE
	CYCLE(cur, "SECTORS")                                  //CYCLE trough all sectors                         
	{
		v[1]=VLS(cur,"Productive_Capacity_Sector",1);        //sector productive capacity in the last period
  	v[2]=VS(cur,"Effective_Production_Sector");          //sector effective production
  	v[3]=V("Gross_Value_Production");                    //gross value of production
  	v[4]=VS(cur,"Sales_Sector");                         //sector sales
  	v[5]=VS(cur,"Avg_Price");                            //sector average price
 		v[0]=v[0]+((v[4]*v[5]/v[3])*(v[2]/v[1]));            //calculates and sums up rate of capacity utilization of all sectors. The rate of capacity utilization is given by sales multiplyed by the price and divided by the gross value of production, multiplyed by the ratio between effective production and productive capacit
	}
RESULT(v[0])



EQUATION("Likelihood_Crisis")
/*
Counts the number of crisis ocurrances. 
*/
	v[0]= fmod((double) t,4);           //divides the time period by four
	if(v[0]==0)                         //if the rest of the above division is zero (begenning of the year)
		{
		v[1]=V("Real_Growth_Rate");       //real growth rate
		v[2]=V("crisis_threshold");       //parameter that defines crisis
		if(v[1]<v[2])                     //if the real growth rate is lower the the crisis threshold
			v[3]=1;                         //counts a crisis
		else                              //if the real growth rate is not lower the the crisis threshold
			v[3]=0;                         //do not count a crisis
		}
	else                                //if the rest of the division is not zero
		v[3]=0;                           //do not count a crisis   
	v[4]=VL("Likelihood_Crisis",1);     //crisis counter in the last period
	v[5]=v[4]+v[3];                     //acumulates the crisis counters
	v[6]=(v[5]/t);                      //gives the probability, total crisis counter divided by the number of time periods
RESULT(v[5])



EQUATION("Gross_Value_Production")
/*
Nominal value of total sales of the economy
*/
	v[0]=0;                                                //initializes the CYCLE
	CYCLE(cur, "SECTORS")                                  //CYCLE trough all sectors
	{
		v[1]=VS(cur,"Avg_Price");                            //sector average price
  	v[2]=VS(cur,"Sales_Sector");                         //sector sales
  	v[0]=v[0]+v[1]*v[2];                                 //calculates and sums up nominal value of all sectors effective sales
	}
RESULT(v[0])

EQUATION("Avg_Herf_Index")
/*
Comment
*/
	v[0]=SUM("Herf_Index");
	v[1]=v[0]/4;
RESULT(v[1])


EQUATION("K_P")
/*
Comment
*/
	v[0]=V("Avg_Markup");
	v[1]=V("Avg_Productivity");
	v[2]=v[0]/v[1];

RESULT(v[2])


