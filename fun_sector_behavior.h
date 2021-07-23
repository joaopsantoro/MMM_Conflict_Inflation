/*****SECTOR BEHAVIOUR VARIABLES*****/


EQUATION("Gama")
/*
This variable determines how the expectation parameter is adjusted in each sector, beased on past effective orders. To turn it constant, the value of gama_variation must be zero.
*/
	v[0]=VL("Gama",1);                        //value of the expectation parameter in the last period
	v[1]= fmod((double) t-1,8);               //t-1 divided by 8 (it adjusts only in 8 periods)
	if(v[1]==0)                               // if the rest of the above division is zero                            
		{
		v[2]=VL("Effective_Orders_Sector",1);   //sector effective orders lagged 1
		v[3]=VL("Effective_Orders_Sector",2);   //sector effective orders lagged 2
		v[4]=VL("Effective_Orders_Sector",3);   //sector effective orders lagged 3
		v[5]=VL("Effective_Orders_Sector",4);   //sector effective orders lagged 4
		v[6]=v[2]-v[5];                         //gives the difference between effective orders of the last period and from 4 periods
		v[7]=(v[2]-v[3])/v[3];                  //growth rate of effective orders of the last two periods
		v[8]=(v[3]-v[4])/v[4];                  //growth rate of effective orders of the last two periods before
  	
  	if(v[6]>0&&v[7]>0&&v[8]>0&&v[7]>v[8])   //if the difference is positive, both grwoth rates are positive and the growth rateis increasing
   		{
   		v[9]=V("gama_variation");             //parameter to increase or decrease gama
   		v[10]=V("max_gama");                  //maximum gama
   		v[11]=min(v[10],v[0]+v[9]);           //current gama is the last period's plus the parameter, or the maximum
   		}
   	else                                    //if the difference is not positive, or any grwoth rates is negative or the growth rate is decreeasing
   		{
      if(v[6]<0&&v[7]<0&&v[8]<0)            //if the difference is negative and both growth rates are negatives
      	{
      	v[9]=V("gama_variation");           //parameter to increase or decrease gama
      	v[10]=V("min_gama");                //minimum gama
      	v[11]=max(v[10],v[0]-v[9]);         //current gama is the last period's minus the parameter or the minimum
      	}
      else                                  //if the difference is positve or ant growth rate is positive
      	v[11]=v[0];                         //use the same gama from the last period
   		}
		}
	else                                      //if the rest of the division is not 0
	v[11]=v[0];                               //use the same gama from the last period
RESULT(v[11])



EQUATION("Wage")
/*
Sector Variable
*/
	v[0]=VL("Wage",1);
	v[17]=V("wage_freq");                                                                 //sector wage in the last period
	v[1]= fmod((double) t,v[17]);                                                          //divide the time period by four
	if(v[1]==0)                                                                        //if the rest of the above division is zero (beggening of the year, adjust wages)
   	 {
   	v[2]=VL("Consumer_Price_Index", 1);                                              //price index in the last period
   	v[3]=VL("Consumer_Price_Index", (1+v[17]));                                              //price index five periods before
   	v[4]=(v[2]-v[3])/v[3];                                                           //annual growth of price index (annual inflation)
   	v[5]=max(v[4],0);
   	v[6]=V("wage_CPI");                                            							        	
   	v[7]=V("Target_Real_Wage");
   	v[8]=VL("Avg_Sector_Real_Wage",1);
   	v[9]=(v[7]-v[8])/v[8];
   	v[10]=V("wage_aspiration_bargain");
   	v[11]=max(v[9],0);
   	v[12]=VL("Avg_Productivity_Sector",1);
   	v[13]=VL("Avg_Productivity_Sector",(1+v[17]));
   	v[14]=(v[12]-v[13])/v[13];
   	v[15]=V("wage_productivity");
   	v[16]=v[0]*(1+v[6]*v[5]+v[10]*v[9]+v[14]*v[15]);        					                          //current wage will be the last period's multiplied by a rate of growth which is an expected rate on productivity plus an inflation adjustment in the wage price index
   	}
	else                                                                               //if the rest of the division is not zero, do not adjust wages
   	v[16]=v[0];                                                                      //current wages will be the last period's
RESULT(v[16])


EQUATION("Real_Wage")
/*
Comment
*/
	v[0]=V("Wage");
	v[1]=V("Consumer_Price_Index");
	v[2]=v[0]/v[1];
RESULT(v[2])


EQUATION("Target_Real_Wage")
/*
Sector Variable
*/
	v[0]=VL("Target_Real_Wage",1);
	v[9]=V("wage_freq");
	v[1]= fmod((double) t,v[9]);                                                         
	v[2]=V("alpha_beta_distribution");
	v[3]=V("beta_beta_distribution");
	v[9]=V("wage_freq");
	if(v[1]==0)                                                                        
   	 {
			v[4]=VL("Sector_Employment_Growth_Rate",1);
			v[5]=v[9]*(beta(v[2], v[3])/40);
			v[6]=V("wage_bargain_interval");
			v[7]=VL("Avg_Sector_Real_Wage",1);
				if(v[4]>v[6])
				v[8]=v[7]*(1+v[5]);
				else
				v[8]=v[0];
			}
		else
		v[8]=v[0];
RESULT(v[8])


EQUATION("Avg_Sector_Real_Wage")
/*
Sector Variable
*/
	v[0]=V("wage_freq");
	v[1]=V("Real_Wage");
	v[2]=AVEL("Real_Wage",v[0]);
RESULT(v[2])



EQUATION("Workers_Aspiration_Gap")
/*
Sector Variable
*/
v[0]=V("Target_Real_Wage");
v[1]=VL("Avg_Sector_Real_Wage",1);
v[2]=v[0]-v[1];
RESULT(v[2])



EQUATION("Annual_Wage_Inflation")
	v[0]=VL("Wage",4);
	v[1]=V("Wage");
	v[2]=(v[1]-v[0])/v[0];
RESULT(v[2])


EQUATION("Sector_Employment_Growth_Rate")
	v[3]=V("wage_freq");
	v[0]=VL("Employment_Sector",(1+v[3]));
	v[1]=VL("Employment_Sector",1);
	v[2]=(v[1]-v[0])/v[0];
RESULT(v[2])


