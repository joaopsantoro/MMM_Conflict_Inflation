/*****INCOME CLASSES*****/ 


EQUATION("Class_Nominal_Income")
/*
Class nominal income shall be calculated by summing the ratio of the total surplus to the proportion of the net salary that is allocated to the class plus the payment of government interest on the domestic public debt.
*/
	v[0]=V("Distributed_Profits");                         //total distributed profits
	v[1]=V("Total_Wages");                                 //total wages
	v[2]=V("Total_Salaries");												   //total direct wages
	v[3]=v[1]-v[2];																				 //total indirect wages
	v[4]=V("class_profit_distribution");                   //profit share of each class
	v[5]=V("class_wage_distribution");                     //wage share of each class
	v[6]=V("class_salary_distribution");									 
	v[7]=V("class_direct_tax");                            //income tax percentage for each claass
	v[8]=(v[0]*v[4]+v[2]*v[6]+v[1]*v[5])*(1-v[7]); 				 //class' net nominal income will be the class profits plus the class wages, minus the income tax
RESULT(v[8])


EQUATION("Class_Real_Income")
/*
Class real income is the nominal income divided by the class price index
*/
	v[0]=V("Class_Nominal_Income");
	v[1]=V("Consumer_Price_Index");
	v[2]=v[0]/v[1];
RESULT(v[2])


EQUATION("Class_Real_Domestic_Consumption")
/*
Class real domestic conumption is based on average past real income and on the class' propensity to consume, plus autonomous consumption
*/
		v[1]=VL("Class_Real_Income", 1);                //class' income lagged 1
  	v[2]=VL("Class_Real_Income", 2);                //class' income lagged 2
  	v[3]=VL("Class_Real_Income", 3);                //class' income lagged 3
  	v[4]=VL("Class_Real_Income", 4);                //class' income lagged 4
  	v[5]=(v[1]+v[2]+v[3]+v[4])/4;                   //class average income in the last four periods
  	v[6]=V("class_propensity_to_consume");          //class propensity to consume on income
  	v[7]=v[5]*v[6];                                 //class real induced consumption
		v[8]=V("Class_Autonomous_Consumption");         //class real autonomous consumption
		v[9]=v[7]+v[8];                                 //class real domestic consumption
RESULT(v[9])


EQUATION("Class_Real_External_Consumption")
/*
Class real external conumption is based on average past real income and on the class' propensity to import
*/
		v[1]=VL("Class_Real_Income", 1);                //class' income lagged 1
  	v[2]=VL("Class_Real_Income", 2);                //class' income lagged 2
  	v[3]=VL("Class_Real_Income", 3);                //class' income lagged 3
  	v[4]=VL("Class_Real_Income", 4);                //class' income lagged 4
  	v[5]=(v[1]+v[2]+v[3]+v[4])/4;                   //class average income in the last four periods
  	v[6]=V("class_propensity_to_import");           //class propensity to import
  	v[7]=v[5]*v[6];
RESULT(v[7])


EQUATION("Class_Expenses")
/*
Stores the value of the Function
*/
	v[0]=V("Class_Expenses_Function");
RESULT(v[0])


EQUATION("Class_Current_Debt")
/*
Class current debt is the diference between current nominal income and current expenses
*/
	v[0]=V("Class_Nominal_Income");
	v[1]=V("Class_Expenses");
	v[2]=v[0]-v[1];
RESULT(v[2])


EQUATION("Class_Financial_Assets")
/*
Financial Assets of each income class.
*/
	v[0]=VL("Class_Financial_Assets",1);                                                       //class financial assets in the last period
	v[1]=V("Class_Current_Debt");                                                              //class current debt
	v[2]=VL("Class_Debt_Payment",1);                                                           //class debt payment in the last period
	v[3]=V("Class_Financial_Asset_Return");                                                    //return on the class financial assets
	v[4]=VL("Class_Debt",1);                                                                   //class stock of debt in the last period
	v[5]=V("Interest_Rate");                                                                   //interest rate
	v[6]=max(0,v[4]*v[5]);                                                                     //class interest payment, interest rate multiplied by the stock of debt, can never be negative
	v[7]=V("class_direct_tax");                                                                //income taxes of each class
	v[8]=V("Government_Interest_Payment_Class");                                               //government interest payment for each class
	v[9]=max((v[3]+v[8])*(1-v[7])-v[6],0);                                                     //net financial income in the period, given by total interest received, discounted income taxes over it, minus class interest payment, and it can never be negative
	if(v[1]>0)                                                                                 //if class current debt is positive (income higher then expenses)
     v[10]=v[1];                                                                             //the diference becomes the class new financial assets
	else                                                                                       //if the current debt is negative (expenses higher then income)
     v[10]=0;                                                                                //class new financial assets will be zero
	v[11]=v[0]+v[10]+v[9]-v[2];                                                                //the stock of class financial assets will be the stock in the last period plus new financial assets plus net financial income, minus the debt payment
	v[12]=max(v[11], 0);                                                                       //stock of financial assets can never be negative
RESULT(v[12])


EQUATION("Government_Interest_Payment_Class")
/*
Distributes government interest payment for the classes given by the total amount of government interest payment mutiplied by the class share on intrest payment
*/
	v[0]=V("Government_Interest_Payment");
	v[1]=V("class_interest_payment_share");
	v[2]=v[0]*v[1];
RESULT(v[2])


EQUATION("Class_Financial_Asset_Return")
/*
Return on the financial assets of each income class, given by the stock of financial assets in the last period multiplied by the return rate
*/
	v[0]=VL("Class_Financial_Assets",1);
	v[1]=V("return_rate");
	v[2]=v[0]*v[1];
RESULT(v[2])


EQUATION("Class_Debt")
/*
Stock of debt of each income class
*/
	v[0]=VL("Class_Debt",1);                                                                   //stock of debt in the last period
	v[1]=V("Class_Current_Debt");                                                              //class current debt
	v[2]=VL("Class_Debt_Payment",1);                                                           //debt payment in the last period
	v[3]=V("Class_Financial_Asset_Return");                                                    //class financial assets return                                                                    
	v[5]=V("Interest_Rate");                                                                   //interest rate
	v[99]=V("class_spread");
	v[6]=max(0,v[0]*(v[5]+v[99]));                                                                     //class interest payment, can never be negative
	v[7]=V("class_direct_tax");                                                                //class income tax
	v[8]=-min(v[3]*(1-v[7])-v[6],0);                                                           //net financial income, given by the assets return discounted the income tax, minus interest payments, and can never be negative
	//v[8]=v[3]-v[6];
	if(v[1]>0)                                                                                 //if class income is higher then expenses
     v[9]=0;                                                                                 //class current debt is zero
	else                                                                                       //if class expenses is higher then income
     v[9]=v[1];                                                                             //current debt will be de diference                                                
	v[10]=v[0]+v[9]-v[2]+v[8];                                                                 //class stock of debt will be the stock of debt in the last period plus new debts minus debt payment of the last period minus net financial income
	v[11]=max(v[10],0);                                                                        //class stock of debt can never be negative
RESULT(v[11])


EQUATION("Class_Debt_Ratio")
/*
Is the retio between class stock of debt and class financial assets
*/
	v[0]=V("Class_Debt");
	v[1]=V("Class_Financial_Assets");
	if(v[1]!=0)
		v[2]=v[0]/v[1];
	else
		v[2]=0;
RESULT(v[2])


EQUATION("Class_Debt_Payment")
/*
Defines a priority between debt payment with financial assets, selling properties and possibilities of autonomous consumption.
*/
	v[0]=V("Class_Debt_Ratio");                                                               //current class debt ratio                                
	v[1]=V("class_min_debt_ratio");                                                           //minimum debt ratio of the class
	v[2]=V("Class_Financial_Assets");                                                         //stock of financial assets
	v[3]=V("Class_Debt");                                                                     //stock of debt
	v[4]=v[3]-v[1]*v[2];                                                                      //current debt minus the minimum debt, based on the minimum debt ratio and the current stock of financial assets                                                                    
	v[5]=max(min(v[2],v[4]),0);                                                               //debt payment will be the diference but can not be higher then the financial assets, and can never be negative
RESULT(v[5])


EQUATION("Class_Autonomous_Consumption")
/*
Class autonomous consumption depends on the propensity to consume autonomously and the financial wealth (checar essa equação)
*/
	v[0]=VL("Class_Autonomous_Consumption",1);                                                //class autonomous consumption in the last period
	v[1]=V("class_autonomous_consumption_propensity");                                        //class autonomous consumption propensity

	v[2]=fmod((double) t,10);                                                                 //devides the time priod by ten
	if(v[2]==0)                                                                               //if the rest of the above division is zero, adjust autonomous consumption
  	{
  	v[3]=V("Autonomous_Consumption_Variation_Rate");                                        //exogenous rate of growth of autonomous consumption
  	v[5]=VL("Class_Financial_Assets",1);                                                    //stock of financial assets in the last period
  	v[6]=VL("Class_Financial_Assets",10);                                                   //stock of financial assets ten periods before
  	v[7]=V("class_autonomous_consumption_variation_propensity");                            //pronpensity to change the autonomous consumption                           
  	if(v[6]>0)                                                                              //if the stock of financial assets ten periods before is not zero
     v[8]=v[7]*(v[5]-v[6])/v[6];                                                            //induced (by financial income) rate of growth of autonomous consumption will be the rate of growth of financial assets multiplied by the propensity to change 
  	else                                                                                    //if the stock of financial assets ten periods before is zero
     v[8]=0;                                                                                //induced (by financial income) rate of growth of autonomous consumption will be zero
  	//v[9]=max(0,v[3]+v[8]);                                                                  //effective rate of growth of autonomous consumption will be the exogenous rate of growth plus the indiced rate of growth, and it can never be negative
  	v[9]=max(0,v[3]);
  	v[4]=(1+v[9])*v[0];                                                                     //current autonomous consumption will be the last period's multiplied by the rate of growth 
  	}
	else                                                                                      //if the rest of the above division is not zero, do not adjust autonomous consumption
  	v[4]=v[0];                                                                              //current autonomous consumption will be the last period's
  
	v[10]=v[4]*v[1];                                                                          //effective autonomous consumption will be the current autonomous consumption multiplied by the propensity (???)
RESULT(v[10])


EQUATION("Class_Number_Workers")
/*
Population of workers of each income class
*/
	v[0]=VL("Class_Number_Workers", 1);
	v[1]=V("population_growth_rate");
	v[2]=v[0]*(1+v[1]);
RESULT(v[2])

