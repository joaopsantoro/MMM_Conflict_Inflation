/*****STOCK-FLOW CONSISTENCY*****/


EQUATION("Total_Classes_Expenses")
	v[0]=SUM("Class_Expenses");
RESULT(v[0])

EQUATION("Total_Variation_Financial_Assets_Classes")
	v[0]=SUM("Class_Financial_Assets");
	v[1]=SUML("Class_Financial_Assets", 1);
	v[2]=v[0]-v[1];
RESULT(v[2])

EQUATION("Total_Variation_Debt_Classes")
	v[0]=SUM("Class_Debt");
	v[1]=SUML("Class_Debt", 1);
	v[2]=v[0]-v[1];
RESULT(v[2])

EQUATION("Total_Financial_Assets_Return_Classes")
	v[0]=SUM("Class_Financial_Asset_Return");
RESULT(v[0])

EQUATION("Total_Interest_Payments_Classes")
	v[0]=SUML("Class_Debt",1);
	v[1]=V("Interest_Rate");
	v[2]=v[4]*v[5];
RESULT(v[2])

EQUATION("Total_Variation_Financial_Assets_Firms")
	v[0]=0;
	v[1]=V("return_rate");
	CYCLE(cur, "SECTORS")
	{
		v[2]=0;
		CYCLES(cur, cur1, "FIRMS")
		{
			v[3]=VLS(cur1,"Financial_Assets",1);
			v[2]=v[2]+v[3]*v[1];
		}
	v[0]=v[0]+v[2];
	}
RESULT(v[0])

EQUATION("Total_Interest_Payments_Firms")
	v[0]=0;
	CYCLE(cur, "SECTORS")
	{
		v[1]=0;
		CYCLES(cur, cur1, "FIRMS")
		{
			v[2]=VS(cur1,"Interest_Rate_Firm");
			v[3]=VLS(cur1,"Debt",1);
			v[1]=v[1]+v[2]*v[3];
		}
	v[0]=v[0]+v[1];
	}
RESULT(v[0])

EQUATION("Total_Variation_Debt_Firms")
	v[0]=0;
	CYCLE(cur, "SECTORS")
	{
		v[1]=0;
		CYCLES(cur, cur1, "FIRMS")
		{
			v[2]=VS(cur1,"Debt_2");
			v[1]=v[1]+v[2];
		}
	v[0]=v[0]+v[1];
	}
RESULT(v[0])

EQUATION("Total_Financial_Assets_Return_Firms")
	v[0]=0;
	CYCLE(cur, "SECTORS")
	{
		v[1]=0;
		CYCLES(cur, cur1, "FIRMS")
		{
   	v[2]=VS(cur1,"Financial_Asset_2");
   	v[1]=v[1]+v[2];
		}
	v[0]=v[0]+v[1];
	}
RESULT(v[0])

EQUATION("Net_Rentability_Financial_Assets")
	v[0]=0;
	CYCLE(cur, "SECTORS")
	{
		v[1]=0;
		CYCLES(cur, cur1, "FIRMS")
		{
			v[2]=VS(cur1, "Firm_Financial_Assets_Return");
			v[1]=v[1]+v[2];
		}
	v[0]=v[0]+v[1];
	}
RESULT(v[0])

EQUATION("Financial_Sector_Wealth")
	v[0]=V("Total_Financial_Assets_Return_Classes");
	v[1]=V("Total_Financial_Assets_Return_Firms");
	v[2]=V("Total_Interest_Payments_Firms");
	v[3]=V("Total_Interest_Payments_Classes");
	v[4]=V("Government_Interest_Payment");
	v[5]=v[2]+v[3]+v[4]-v[0]-v[1];
RESULT(v[5])

EQUATION("Financial_Sector_Wealth_2")
	v[0]=V("Total_Variation_Debt_Classes");
	v[1]=V("Total_Variation_Debt_Firms");
	v[2]=V("Public_Deficit");
	v[3]=V("Total_Variation_Financial_Assets_Classes");
	v[4]=V("Total_Variation_Financial_Assets_Firms");
	v[5]=v[0]+v[1]+v[2]-v[3]-v[4];
RESULT(v[5])