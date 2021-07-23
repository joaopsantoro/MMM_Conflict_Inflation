/*****SECTOR VARIABLES RELATED TO THE EXTERNAL SECTOR*****/


EQUATION("Foreign_Price")
/*
External price of the sector's goods. 
*/
	v[0]=VL("Foreign_Price",1);
	v[1]=V("foreign_price_growth");
	v[2]=(1+v[1])*v[0];
RESULT(v[2])


EQUATION("Exports")
/*
Exports are defined for each sector based on the application of an export coefficient on external income, and will be subject to random shocks (related, for example, to economic policies). The division by price observed in the past period allows to transform the value of exports into units of exported products.
*/
v[0]=V("External_Income");
v[1]=V("exports_coefficient");
v[2]=VL("Avg_Price",1);
v[3]=V("Foreign_Price");
v[4]=V("income_elasticity_exports");
v[5]=V("price_elasticity_exports");
v[6]=V("Exchange_Rate");
v[7]=v[1]*pow((v[3]*v[6])/v[2],v[5])*pow(v[0],v[4]);
v[8]=v[7]/v[2]; 
RESULT(v[8])


EQUATION("exports_coefficient")
/*
está como parâmetro
*/
v[0]=(double)t;
v[1]=V("Competitivness_shock");
v[2]=V("Per_comp_shock");
v[3]=VL("exports_coefficient",1);
v[4]=V("Dur_comp_shock");

   if(v[0]>v[2]&&v[0]<(v[2]+v[4]))
   v[5]=(1+v[1])*v[3];
   else
   v[5]=v[3];
RESULT(v[5])


EQUATION("Extra_Imports")
/*
The extra import, if the sector can not meet its internal demand, is determined by the difference between the actual orders of the sector and its actual production plus the available stock of products. The value of these imports is obtained by multiplying the previous result by the external price of the inputs of the sector in question.
*/
v[0]=V("Domestic_Consumption_Demand");
v[1]=V("Domestic_Capital_Demand");
v[2]=V("Domestic_Intermediate_Demand");
v[3]=V("Demand_Met");
v[4]=(v[0]+v[1]+v[2])*(1-v[3]);
v[5]=VL("International_Reserves",1);
if(v[4]>0)
	{
  if(v[5]>0)
  	{
   	v[6]=v[4];
   	v[7]=1;
   	}
  else
  	{
   	v[6]=0;
   	v[7]=0;
   	}
	WRITE("Demand_Met_By_Imports",v[7]);
	}
else
	v[6]=0;
RESULT(v[6])


EQUATION("Demand_Met_By_Imports")
/*
This variable assumes values 0 or 1.
*/
RESULT(CURRENT)


EQUATION("Observed_Imports")
/*
The import of the intermediate goods sector is defined in the macro level variable, which is then transformed into a variable of the first level. The imports of the consumption goods sector is defined as the sum for all product classes of the propensity to import of each income class applied on the average of lagged class income. The imports of the capital goods sector is defined by the product of the import coefficient by the domestic demand for capital goods.
*/

v[1]=VL("International_Reserves", 1);
if (v[1]>0)
{
	v[20]=V("id_consumption_goods_sector");
	v[21]=V("id_intermediate_goods_sector");
	if(v[21]==1)
		v[19]=V("Intermediate_Imports_Function");
	else
		{
		if(v[20]==1)
			{
			v[0]=V("Consumption_Imports");
    	v[27]=V("price_elasticity_imports");
    	v[28]=V("Avg_Price");
    	v[29]=V("Foreign_Price");
    	v[30]=V("Exchange_Rate");
    	v[19]=pow(v[28]/(v[29]*v[30]),v[27])*(v[0]);
    	}
		else 
			{
		/*
		v[23]=V("propensity_to_import_capital_goods");	
		v[24]=V("Domestic_Capital_Demand");
		v[35]=V("Government_Investment");
		v[36]=VL("Avg_Price",1);
		v[19]=v[23]*((v[24]-(v[35]/v[36]))/(1-v[23]));
		*/
			v[23]=V("propensity_to_import_capital_goods");	
			v[24]=V("Domestic_Capital_Demand");
			v[25]=v[23]*(v[24]/(1-v[23]));
			v[27]=V("price_elasticity_imports");
    	v[28]=V("Avg_Price");
    	v[29]=V("Foreign_Price");
    	v[30]=V("Exchange_Rate");
    	v[19]=pow(v[28]/(v[29]*v[30]),v[27])*(v[25]);
			}
		}
}
else
	v[19]=0;

v[18]=V("Extra_Imports");
v[50]=v[19]+v[18];
RESULT(v[50])


EQUATION("Input_Imports_Sector")
/*

*/
	v[0]=SUM("Input_Imports_Firm");
RESULT(v[0])






