/*****PUBLIC SECTOR*****/


EQUATION("Government_Expenses")
/*
Government expenses is the sum of all components: consumption, investment, wages and unemployment benefits
*/
		v[0]=V("Government_Wages");                           //current government wages
		v[1]=V("Government_Investment");                      //current government investment
		v[2]=V("Government_Consumption");                     //current government consumption
		v[3]=v[0]+v[1]+v[2]; 			                            //sums up all four
RESULT(v[3])


EQUATION("Government_Wages")
/*
Government wages payed to government workers may follow an counter cyclical rule
*/
	v[0]= fmod((double) t,4);                               //divides the time period by four (adjust annualy)
	if(v[0]==0)                                             //if the rest of the division is zero (adjust government wages)
   	{
   	v[1]=VL("Government_Wages", 1);                       //government wages in the last period
   	v[2]=V("government_wages_growth");                    //government wages growth
   	v[3]=VL("Price_Index", 1);                					   //price index in the last period
   	v[4]=VL("Price_Index", 5);                					   //price index five periods before
   	v[5]=(v[1]*(1+v[2])*(v[3]/v[4]));                     //current government wages will be the last period's multiplyed by the growth rate and by inflation rate 	
   	}
	else                                                    //if the rest of the division is not zero (do not adjust government wages)
   	v[5]=VL("Government_Wages", 1);                      //use government wages of the last period
RESULT(v[5])


EQUATION("Desired_Government_Consumption")
/*
Desired governemt consumption, based on a exogenous desired growth rate
*/
	v[0]= fmod((double) t,4);                                   //divides the time period by four (adjust annualy)  
	if(v[0]==0)                                                 //if the rest of the division is zero (adjust desired consumption)
		{
		v[1]=VL("Desired_Government_Consumption",1);              //desired consumption in the last period
		v[2]=V("government_consumption_growth");                  //growth rate for government consumption
		v[3]=VL("Price_Index",5);                                 //price index lagged 5
		v[4]=VL("Price_Index",1);                                 //price index in the last period
		v[5]=v[1]*(1+v[2])*(v[4]/v[3]);                           //new desired consumption is the last period's multiplyed by the growth rate and by inflation rate
		}
	else                                                        //if the rest of the division is not zero (do not adjust desired consumption)
		v[5]=VL("Desired_Government_Consumption",1);              //use last period's
RESULT(v[5])


EQUATION("Government_Consumption")
/*
Effective Government Consumption. May be constrained by a fiscal rule.
*/
	v[0]= fmod((double) t,4);                                       //divides the time period by four (adjust annualy) 
	if(v[0]==0)                                                     //if the rest of the division is zero (adjust consumption)
		{
		v[1]=V("Desired_Government_Consumption");                     //desired government consumption
		v[2]=v[1];                                               			//government consumption is the desired one
	}
	else                                                            //if the rest of the division is not zero (do not adjust consumption)
		v[2]=VL("Government_Consumption", 1);                         //use last period's
RESULT(max(0,v[2]))


EQUATION("Desired_Government_Investment")
/*
Desired government investment, based on an exogenous desired rate of growth.
*/
	v[0]= fmod((double) t,4);                              //divides the time period by four (adjust annualy)    
	if(v[0]==0)                                            //if the rest of the division is zero (adjust desired investment)
		{
		v[1]=VL("Desired_Government_Investment",1);          //desired investment in the last period
		v[2]=V("government_investment_growth");              //growth rate for government investment
		v[3]=VL("Price_Index",5);                            //price index lagged 5
		v[4]=VL("Price_Index",1);                            //price index in the last period
		v[5]=v[1]*(1+v[2])*(v[4]/v[3]);                      //new desired investment is the last period's multiplyed by the growth rate and by inflation rate
		}
	else                                                   //if the rest of the division is not zero (do not adjust desired investment)
		v[5]=VL("Desired_Government_Investment",1);          //use last period's
RESULT(v[5])
    
      
EQUATION("Government_Investment")
/*
Effective government investment. May be constrained by some fiscal rule.
*/
	v[0]= fmod((double) t,4);                                    //divides the time period by four (adjust annualy) 
	if(v[0]==0)                                                  //if the rest of the division is zero (adjust investment)
	{
		v[1]=V("Desired_Government_Investment");                   //desired government investment
		v[2]=v[1];		                                             //government investment is the desired value
		
	}
	else                                                         //if the rest of the division is not zero (do not adjust investment)
		v[2]=VL("Government_Investment", 1);                      //use last period's
RESULT(max(0,v[2]))


EQUATION("Income_Taxes")
/*
Stores the value of the function
*/
	v[0]=V("Income_Taxes_Function");
RESULT(v[0])


EQUATION("Indirect_Taxes")
/*
Stores the value of the function
*/
	v[0]=V("Indirect_Taxes_Function");
RESULT(v[0])


EQUATION("Total_Taxes")
/*
Sum of income and indirect taxes
*/
	v[0]=V("Income_Taxes");
	v[1]=V("Indirect_Taxes");
	v[2]=v[0]+v[1];
RESULT(v[2])


EQUATION("Primary_Surplus")
/*
Total Taxes minus Government Expenses
*/
	v[0]=V("Government_Expenses");
	v[1]=V("Total_Taxes");
	v[2]=v[1]-v[0];
RESULT(v[2])


EQUATION("Surplus_GDP_Ratio")
/*
Primary Surplus over GDP
*/
	v[0]=V("Primary_Surplus");
	v[1]=V("GDP");
	v[2]=v[0]/v[1];
RESULT(v[2])


EQUATION("Government_Interest_Payment")
/*
Defined as the government stock of public debt in the last period multipyed by the interest rate
*/
	v[0]=VL("Public_Debt",1);
	v[1]=V("Interest_Rate");
	v[2]=v[0]*v[1];
RESULT(v[2])


EQUATION("Public_Deficit")
/*
Government expenses minus taxes plus interest payments
*/
	v[0]=V("Government_Expenses");
	v[1]=V("Total_Taxes");
	v[2]=V("Government_Interest_Payment");
	v[3]=v[0]-v[1]+v[2];
RESULT(v[3])


EQUATION("Public_Debt")
/*
Defined as the stock of debt in the last period plus current government deficit
*/
	v[0]=VL("Public_Debt",1);
	v[1]=V("Public_Deficit");
	v[2]=max(0,v[0]+v[1]);
RESULT(v[2])


EQUATION("Public_Debt_GDP_Ratio")
/*
Public deficit over annual GDP
*/
	v[0]=V("Public_Debt");
	v[1]=V("GDP");
	v[2]=v[0]/v[1];
RESULT(v[2])


EQUATION("Interest_Rate")
/*
Nominal Interest rate is set by the central bank following a (possible) dual mandate Taylor Rule, considering the inflation and unemployment gaps.
*/
//v[0]=V("interest_rate");
//	v[1]=V("inflation_target");
//	v[3]=VL("Annual_Inflation",1);
//	v[5]=V("inflation_sensitivity");
//	v[7]=v[0]+v[5]*(v[3]-v[1]);
//	v[8]=V("interest_rate_adjustment");
//	v[9]=VL("Interest_Rate", 1);
//	if (abs(v[7]-v[9])>v[8])
//		{
//		if (v[7]>v[9])
//			v[10]=v[9]+v[8];
//		else
//			v[10]=v[9]-v[8];
//		}
//	else
//		v[10]=v[7]
//RESULT(max(0,v[10]))

	v[0]=V("interest_rate");
	v[1]=V("interest_rate_shock");
	if(t>200)
		v[2]=v[1];
	else
		v[2]=v[0];
		
RESULT(v[2])










