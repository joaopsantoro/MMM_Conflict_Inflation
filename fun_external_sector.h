/*****EXTERNAL SECTOR*****/


EQUATION("External_Income")
/*
External Sector Variable
*/
v[0]=VL("External_Income",1);
v[1]=V("external_income_growth");
v[2]=(1+v[1])*v[0];
RESULT(v[2])



EQUATION("Trade_Balance")
/*
External Sector Variable
The trade balance is obtained by the difference between total exports and total imports.
*/
v[0]=V("Total_Exports");
v[1]=V("Total_Imports");
v[2]=v[0]-v[1];
RESULT(v[2])


EQUATION("International_Reserves")
/*
External Sector Variable
The stock of foreign exchange in the period will be calculated by adding to the stock of the past period the current balance of payments (in this case, only the trade balance)
*/
v[0]=VL("International_Reserves", 1);
v[1]=V("Trade_Balance");
v[2]=v[0]+v[1];
RESULT(v[2])


EQUATION("Exchange_Rate")
/*
External Sector Variable
*/
//	v[5]=VL("Exchange_Rate",1);
//	v[6]= fmod((double) t,4);
//	if(v[6]==0)
//		{
//		v[0]=V("er_media");
//		v[1]=V("alpha_er");
//		v[2]=V("beta_er");
//		v[3]=beta(v[1], v[2])*2;
//		v[4]=v[0]+v[3];
//		}
//	else
//	v[4]=v[5];	
//RESULT(max(v[4],0.01))

	v[0]=V("er");
	v[1]=V("er_shock");
	v[2]=V("shock_period");
	if(t>v[2])
		v[3]=v[0]*(1+v[1]);
	else
		v[3]=v[0];
RESULT(v[3])












