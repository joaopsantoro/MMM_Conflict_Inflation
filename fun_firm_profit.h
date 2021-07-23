
EQUATION("Revenue")
/*
Revenue depends on sales and price
*/
	v[0]=V("Sales");                                                  //firm's sales 
	v[1]=V("Exports");                                                //sector exports
	v[2]=V("Price");                                                  //firm's price
	v[4]=V("Exchange_Rate");                                          //exchange rate
	v[5]=V("Effective_Market_Share");                                 //firm's effective market share
	v[6]=v[2]*(v[0]-v[5]*v[1])+v[5]*v[1]*v[2]/v[4];                   //revenue is given by firm's price multiplied by domestic sales plus exports (weighted by firm's market share) multiplied by firm's price over the exchange rate
RESULT(v[6])


EQUATION("Indirect_Tax")
/*
Indirect Tax of the firm is the revenue multiplied by the tax parameter
*/
	v[0]=V("Revenue");
	v[1]=V("indirect_tax");
	v[2]=v[0]*v[1];
RESULT(v[2])



EQUATION("Profits")
/*
Profit of each firm, difference between revenue and costs, being revenue as a function of price and sales and cost of total inputs and labor used in production
*/
	v[0]=V("Revenue");               									             										      //firm's revenue
	v[1]=V("Effective_Production");                                 										    //firm's effective production
	v[3]=V("indirect_tax");                                   										          //firm's indirect tax parameter
	v[4]=V("UDC");                                 	  	 									   					     //firm's variable cost
	v[5]=V("Productive_Capacity");          		               										          //firm's productive capacity in the last period
	v[6]=V("productive_capacity_cost");                               									   	//firm's capacity cost
	v[7]=VL("Consumer_Price_Index",1);
	v[8]=V("imitation_revenue_proportion");           	               										  //share of revenue destinated to imitation 
	v[9]=V("innovation_revenue_proportion");            											              //share of revenue destinanted to innovation
	v[10]=V("id_innovative_firm");                                        				 				 	//identifies if the firm is innovative or not
	v[11]=V("quality_innovation_revenue_proportion");             											    //share of revenue destinated to product innovation
	v[12]=V("quality_imitation_revenue_proportion");                											  //share of revenue destinanted to product imitation
	v[13]=V("Depreciation_Expenses");
	v[14]=(1-v[3])*v[0]-(v[4]*v[1])-(v[5]*v[6]*v[7])-(v[0])*(v[8]+v[9]*v[10]+v[11]+v[12])-v[13];
RESULT(v[14])


EQUATION("Retained_Profits")
/*
Profit retained by the sector after being distributed to class and paid interest on the debt and separate the expense for depreciation.
*/
	v[0]=V("Profits");                                                               //firm's profits            
	v[1]=V("profits_distribution_rate");                                             //firm's profit distribution parameter
	v[2]=VL("Debt",1);                                                               //firm's stock of debt in the last period
	v[3]=V("Interest_Rate_Firm");                                                    //interest rate paid by the firm
	v[7]=VL("Financial_Assets",1);                                                   //stock of financial assets in the last period
	v[8]=V("return_rate");                                                           //return rate of financial assets
	v[5]=v[0]+v[7]*v[8]-v[2]*v[3];		 																			   			 //firm's net profits is calculated suming up gross profits and financial asset return, minus depreciation expenses, interest payments, and discounting innovation and imitation expenses
  if(v[5]>0)                                                                       //if net profits is positive
     {
     v[6]=(1-v[1])*v[5];                                                           //retained profits
     v[13]=(v[1])*v[5];        																										 //distributed profits
     WRITE("Profits_Distribution",v[13]);
     }
   else                                                                            //if net profits is zero or negative                                                                     
     {
     v[6]=v[5];                                                                    //retained profits equals net profits                                                             
     WRITE("Profits_Distribution",0);                                              //distributed profits is zero
     }
RESULT(v[6])


EQUATION("Profits_Distribution")
/*
Amount of profits distributed to the income classes
*/
	V("Retained_Profits");
RESULT(CURRENT)


EQUATION("Wage_Bill")
/*
Total wages paid by the firm
*/
	v[0]=V("Wage");                                                   //nominal wage
	v[1]=V("Firm_Avg_Productivity");       		                        //firm's productitvity in the last period
	v[2]=V("Effective_Production");                                   //firm's effective production	
	v[3]=V("productive_capacity_cost");                               //productive capacity cost
	v[4]=V("Productive_Capacity");       		                          //firm's productive capacity in the last period
	v[5]=VL("Consumer_Price_Index",1);
	v[6]=V("Revenue");               									             		//firm's revenue
	v[7]=V("imitation_revenue_proportion");           	             	//share of revenue destinated to imitation 
	v[8]=V("innovation_revenue_proportion");            							//share of revenue destinanted to innovation
	v[9]=V("id_innovative_firm");                                     //identifies if the firm is innovative or not
	v[10]=V("quality_innovation_revenue_proportion");             	  //share of revenue destinated to product innovation
	v[11]=V("quality_imitation_revenue_proportion");                	//share of revenue destinanted to product imitation
	v[12]=v[2]*(v[0]/v[1]);																						// total direct wages	
	v[13]=v[3]*v[4]*v[5];																							// total overhead wages
	v[14]=v[6]*(v[7]+v[8]*v[9]+v[10]+v[11]);													// total R&D wages	
	v[15]=v[12]+v[13]+v[14];
RESULT(v[15])

EQUATION("Profit_Rate")
/*
Firm Profit Rate
*/
	v[0]=V("Profits");																										
	v[1]=V("Capital");
	v[2]=v[0]/v[1];
RESULT(v[2])





