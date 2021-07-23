
EQUATION("Interest_Rate_Firm")
/*
Firm Variable
*/
v[0]=V("Interest_Rate");
v[1]=V("Spread_Firm");
v[2]=v[0]*v[1];
RESULT(v[2])


EQUATION("Spread_Firm")
/*
Firm Variable
*/
v[1]=V("id_firm_number");
v[0]=fmod((double) t,6); 
if(v[1]==v[0]||v[1]==(v[0]+6)||v[1]==(v[0]+12)||v[1]==(v[0]+18))
   {
   v[2]=V("percent_spread");
   v[3]=VL("Debt_Rate",1);
   v[4]=VL("Debt_Rate",2);
   v[5]=VL("Debt_Rate",3);
   v[6]=VL("Debt_Rate",4);
   v[7]=VL("Debt_Rate",5);
   v[8]=VL("Debt_Rate",6);
   v[9]=(v[3]+v[4]+v[5]+v[6]+v[7]+v[8])/6;
   if(v[9]>0.5)    //dúvida: pq número fixo?
      v[10]=1+v[9]*v[2];
   else
      v[10]=VL("Spread_Firm",1);
   }
else
   v[10]=VL("Spread_Firm",1);
RESULT(v[10])


EQUATION("Funds")
/*
Firm Variable
*/
v[0]=V("Internal_Funds");
v[1]=V("Pool_Financial_Assets");
v[2]=V("Pool_Debt");
v[3]=VL("Debt", 1);
v[4]=VL("Financial_Assets", 1);
v[5]=max(v[0],-v[4]);
v[6]=V("return_rate");
v[7]=V("Interest_Rate_Firm");
if (v[0]-v[1]+v[2]>0)//enought internal funds to invest
	{
	WRITE("financial_asset_1", 0);
	WRITE("debt_1", 0);
	}
else
	{
	if (v[4]+v[0]<0||(v[7]>v[6]&&v[3]-v[4]-v[0]>=0))//external funds will be used to reduce debt
		{
		WRITE("financial_asset_1", -v[4]);
		WRITE("debt_1", -v[4]-v[0]);
		}
	else
		{
		WRITE("financial_asset_1", v[0]);
		WRITE("debt_1", 0);
		}
	}
v[8]=v[0]-v[1]+v[2];
RESULT(v[8])


EQUATION("Internal_Funds")
/*
Firm Variable
*/
v[0]=V("Retained_Profits");
v[1]=V("Depreciation_Expenses");
v[2]=v[0]+v[1];
RESULT(v[2])


EQUATION("Pool_Financial_Assets")
/*
Firm Variable
Minimum liquid financial aplication in order to keep the desired amount, if the amount is already larger than desired the excess will be avilable for investment expenses.
*/
v[0]=VL("Capital",1);
v[1]=V("desired_financial_rate");
v[2]=VL("Financial_Assets",1);
if(v[1]*v[0]-v[2]>=0)
	v[3]=(1/4)*((v[1]*v[0])-v[2]);//positive value
else 
	v[3]=v[1]*(v[0])-v[2];//negative value (reduce liquid assets) increasing available funds.
RESULT(v[3])


EQUATION("Pool_Debt")
/*
Firm Variable
Maximum External funds available
*/
v[0]=VL("Capital",1);
v[1]=V("desired_debt_rate");
v[2]=VL("Debt",1);
v[3]=VL("Financial_Assets",1);
if(v[1]*(v[0]+v[3])-v[2]<=0)//If Debt is higher than desired the adjustment is done gradually (1/4) towards the target. 
	v[4]=(1/4)*(v[1]*(v[0])-v[2]);//negative value (try to pay part of the debt)
else
	v[4]=v[1]*(v[0]+v[3])-v[2];//positive value (increase debt)
v[5]=max(0,v[4]);
RESULT(v[5])


EQUATION("Debt")
/*
Firm Variable
Stock of Debt
*/
v[0]=V("Debt_2");
v[1]=VL("Debt", 1);
v[2]=v[0]+v[1];
v[3]=V("switch_debt");
if (v[3]==1)
	{
	v[4]=V("id_firm_number");
	v[5]= fmod((double) t,6);
	if(v[4]==v[5]+1||v[4]==(v[5]+7)||v[4]==(v[5]+13)||v[4]==(v[5]+19))
		{
		v[6]=VL("Capital", 1);
		v[7]=VL("Financial_Assets", 1);
		v[8]=V("desired_debt_rate_2");
		v[9]=v[2]/(v[6]+v[7]);
			if (v[9]<=v[8])
				{
				if (v[2]>0)
					v[15]=v[2];
				else
					{
					v[15]=0;
					plog("\nERROR: Debt lower than 0");
					}
				}
			else
				{
				plog("\nERROR: Debt_Rate greater than desiered 2");
				v[10]=V("Productive_Capacity");
				v[11]=v[8]*(v[6]+v[7]);
				v[12]=V("Price_Capital_Goods");
				v[13]=V("discount");
				SORT("CAPITAL", "Capital_Good_Productivity", "UP");
				v[14]=0;
				CYCLE(cur, "CAPITAL")
				{
					if (v[2]-v[14]>=v[11])
						{
						WRITES(cur, "to_die_capital_good", 1);
						v[14]=v[14]+v[12]*(1-v[13]);
						}
					else
						{
						WRITES(cur, "to_die_capital_good", 0);
						v[14]=v[14];
						}		
				}
				v[15]=v[2]-v[14];
				}
		}
	else
		v[15]=v[2];
	}
else
	v[15]=v[2];
RESULT(v[15])


EQUATION("Debt_Rate")
/*
Firm Variable
Degree of indebtedness, calculated by the ratio of the debt to the capital of the sector.
*/
	v[0]=V("Debt");                                                                    //firm's stock of debt 
	v[1]=V("Capital");                                                                 //firm fisical capital
	v[2]=VL("Financial_Assets",1);                                                     //firm's stock of financial assets in the last period
	if(v[1]+v[2]>0)                                                                    //if the sum of the fisical capital plus the financial assets is positive
		v[3]=v[0]/(v[1]+v[2]);                                                           //debt rate is the stock of debt over the total capital
	else                                                                               //if the sum of the fisical capital plus the financial assets is not positive
		v[3]=1.1;                                                                        //debt rate is 1.1 (dúvida, pq 1.1?)
RESULT(v[3])


EQUATION("Financial_Assets")
/*
Firm Variable
Current Value of the stock of financial assets
*/
v[0]=V("Financial_Asset_2");
v[1]=V("rest");
v[2]=VL("Financial_Assets", 1);
v[3]=v[0]+v[1]+v[2];
RESULT(v[3])


EQUATION("Firm_Financial_Assets_Return")
/*
Firm Variable 
Net return on firm's financial assets
*/
	v[0]=VL("Debt", 1);                                                               //firm's stock of debt in the last period
	v[1]=V("Interest_Rate_Firm");                                                     //interest rate paid by the firm
	v[2]=VL("Financial_Assets", 1);                                                   //firm's stock of financial assets in the last period
	v[3]=V("return_rate");                                                            //return rate on financial assets
	v[4]=v[2]*v[3]-v[0]*v[1];                                                         //net return on firm's financial assets                           
RESULT(v[4])


EQUATION("Investment_Expenses_1")
/*
Firm Variable
*/
v[0]=V("Desired_Investment_Expenses");
v[1]=V("Funds");
if(v[1]<=0)//no available funds
	{
	v[2]=0;
	WRITE("Available_Funds_Replacement", 0);
	}
else
	{
	if(v[1]-v[0]>=0) //available funds and enought for the investment
		{
		v[2]=v[0];
		WRITE("Available_Funds_Replacement", v[1]-v[0]);
		}
	else //available funds but not enought for the investment
		{
		v[2]=0;
		WRITE("Available_Funds_Replacement", 0);
		}
	}
RESULT(v[2])


EQUATION("Investment_Expenses_2")
/*
Firm Variable
*/
v[0]=V("Investment_Expenses_1");
v[1]=V("Desired_Investment_Expenses");
v[2]=V("Funds");
v[3]=V("Pool_Debt");
v[4]=V("Pool_Financial_Assets");
if(v[0]==0 && v[1]>0)
	{
	if(v[2]<=0)
		{
		v[5]=0;
		WRITE("financial_asset_2", 0); 
		WRITE("debt_2", 0);
		}
	else
		{
		v[5]=v[2];
		WRITE("financial_asset_2", v[4]); 
		WRITE("debt_2", v[3]);
		}
	}
else
	{
	v[5]=0;
	WRITE("financial_asset_2", 0); 
	WRITE("debt_2", 0);
	}
RESULT(v[5])


EQUATION("Available_Funds_Replacement")
/*
Firm Variable
*/
	V("Investment_Expenses_1");
RESULT(CURRENT)


EQUATION("Investment_Expenses")
/*
Firm Variable
*/
v[0]=V("Investment_Expenses_1");
v[1]=V("Investment_Expenses_2");
v[2]=v[0]+v[1];
RESULT(v[2])


EQUATION("Financial_Asset_2")
/*
Firm Variable
*/
V("Funds");
V("Investment_Expenses_2");
V("Replecement_2");
v[0]=V("financial_asset_1");
v[1]=V("financial_asset_2");
v[2]=V("financial_asset_3");
v[3]=v[0]+v[1]+v[2];
RESULT(v[3])


EQUATION("Debt_2")
/*
Firm Variable
*/
V("Funds");
V("Investment_Expenses_2");
V("Replecement_2");
v[0]=V("debt_1");
v[1]=V("debt_2");
v[2]=V("debt_3");
v[3]=v[0]+v[1]+v[2];
RESULT(v[3])
