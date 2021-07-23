/*****INNOVATION/IMITATION*****/



EQUATION("Frontier_Productivity")
/*
Firm Variable
The new productivity is the maximum among the previous one and the ones possibly obtained imitation and innovation. The latters are assigned the value 0 if the research fails to provide a new productivity 
*/
	v[0]=VL("Frontier_Productivity", 1);       //frontier productivity of the firm in the last period
	v[1]=V("Imitation_Productivity");          //productivity archivied with imitation in that period
	v[2]=V("Innovation_Productivity");         //productivity archivied with innovation in that period
	v[3]=max(v[0],max(v[1],v[2]));             //current frontier productivity is the maximum between the three

	if (v[3]==v[0])                            //if the current frontier productivity is the same form the last period
		{
		WRITE("imitation", 0);                   //imitation is not implemented
		WRITE("innovation", 0);                  //innovation is not implemented
		}
	if (v[3]==v[1])                            //if the current productivity is the imitation productivity
		{
		WRITE("innovation", 0);                  //inovation is not implemented
		WRITE("imitation", 1);                   //imitation is implemented
		}
	if (v[3]==v[2])                            //if the current productivity is the innovation productivity
		{
		WRITE("innovation", 1);                  //innovation is implemented
		WRITE("imitation", 0);                   //imitation is not implemented
		}
RESULT(v[3])


EQUATION("Imitation_Productivity")
/*
Firm Variable
*/
	v[0]=VL("Revenue", 1);                      //firm's revenue from the last period
	v[1]=V("imitation_revenue_proportion");     //firm's share of revenue destinated to imitation R&D
	v[2]=VL("Max_Productivity", 1);             //maximum productivity of the sector in the last period
	v[3]=V("imitation_success_parameter");      //parameter that defines the sucess of imitation
	v[4]=(v[0]*v[1]);                           //amount of recources for imitation R&D
	v[5]=(1-exp(-v[4]*v[3]));                   //probability of success of the imitation depends on the parameter and the amount of recources available
	WRITE("Imitation_Probability", v[5]);       //imitation probability
  	if(RND<v[5])                              //draws a randon number. if it is lower then imitation probability
     	v[6]=v[2];                              //imitation has succeded and the firm can implement the maximum probability of the sector in the last period
  	else                                      //if the randon number is not lower than imitation probability
     	v[6]=0;                                 //imitation failed and return a productivity zero
RESULT(v[6])


EQUATION("Innovation_Productivity")
/*
Firm Variable
*/
	v[0]=VL("Revenue", 1);                      //firm's revenue from the last period                         
	v[1]=V("innovation_revenue_proportion");    //firm's share of revenue destinated to innovation R&D
	v[2]=V("id_innovative_firm");               //identifies if it is a innovative firm
	v[3]=V("innovation_success_parameter");     //parameter that defines the sucess of innovation
	v[6]=(v[0]*v[1]*v[2]);                      //amount of recources for innovation R&D (if the firm is not innovative, the parameter is zero, thus the amount of recources is zero)
	v[7]=V("frontier_productivity_initial");    //initial frontier productivity
	v[8]=v[2]*(1-exp(-v[6]*v[3]));              //probability of success of the innovation depends on the parameter and the amount of recources available
  WRITE("Innovation_Probability",v[8]);       //innovation probability
  
	v[9]=V("tech_regime");                      //identifies the technological regime
	v[10]=VL("Frontier_Productivity",1);        //frontier productivity in the last period
	v[11]=V("std_dev_innovation");              //innovation standard deviation

	if(v[9]==1)                                 //if it is a science-based regime
		{
		v[12]=V("tech_opportunity");              //techonological opportunity parameter
		v[13]=log(v[7])+(double)t*(v[12]);        //the average of the innovation distribution will be the initial frontier productivity plus the opportunity parameter times the time period
		}
	else                                        //if it is a cumulative regime
		v[13]=log(v[10]);                         //the average of the innovation distribution will be the frontier productivity of the last period
	
	if(RND<(1-exp(-v[6]*v[3])) && v[2]==1)      //draws a randon nuumber. if it is lower then innovation probability and the firm is innovative
  	{
  	v[14]=exp(norm(v[13],v[11]));             //the innovation productivity will be a draw from a normal distribution with average depending of the tech regime and std. dev fixed
  	WRITE("innovation_success",1);            //WRITES if innovation has succeded
  	}
	else                                        //if the randon number is not lower then  the innovation probability
		{
		v[14]=0;                                  //the productivity is zero
		WRITE("innovation_success",0);            //WRITES that innovation did not occur
		} 
RESULT(v[14])


EQUATION("Innovation_Probability")
/*
Firm Variable
stores the value of the innovation productivity
*/
	V("Innovation_Productivity");               
RESULT(CURRENT)


EQUATION("Imitation_Probability")
/*
Firm Variable
stores the value of the imitation productivity
*/
	V("Imitation_Productivity");                
RESULT(CURRENT)



/*****PRODUCT INNOVATION*****/



EQUATION("Potential_Quality")
/*
Firm Variable
*/
	v[0]=V("Innovation_Quality");                          //quality from product innovation
	v[1]=V("Imitation_Quality");                           //quality from product imitation
	v[2]=VL("Potential_Quality",1);                        //firm's potential quality in the last period
	v[3]=max(v[0],v[1]);                                   //maximum quality between innovation and imitation
	v[4]=max(v[3],v[2]);                                   //maximum quality of the three
RESULT(v[4])


EQUATION("Innovation_Quality")
/*
Firm Variable
*/
	v[0]=VL("Revenue", 1);                                 //firm's revenue in the last period      
	v[1]=V("quality_innovation_revenue_proportion");       //desired share of revenue destinated to product innovation
	v[2]=V("quality_innovation_success_parameter");        //product innovation sucess parameter
	v[3]=v[0]*v[1];                                        //available recources for product innovation
	v[4]=V("quality_initial");                             //inital quality of the product
	v[5]=V("std_dev_quality");                             //standard deviation of the product innovation distribution
	v[6]=V("tech_opportunity_quality");                    //tech opportunity for quality parameter
	v[7]=V("tech_regime_quality");                         //identifies the technological regime for product quality
	v[8]=VL("Potential_Quality",1);                        //potential quality in the last period
	v[9]=(1-exp(-v[3]*v[2]));                              //product innovation probability depends on the availabe recources

	if(v[7]==1)                                            //if it is a science based regime
  	v[10]=log(v[4])+(double)t*(v[6]);                    //the average of the distribution depends on the time periods and technical oportunity paramter
	else                                                   //if it is a cumulative regime
  	v[10]=log(v[8]);                                     //the average of the distribution is the maximum quality of the last period
   
	if(RND<v[9])                                           //draws a randon number. if it is lower then product innovation probability
  	v[11]=exp(norm(v[10],v[5]));                         //returns a quality drawn from a nomal distribution with average depending on the tech regime
	else                                                   //if the randon number is not lower then product innovation probability
  	v[11]=0;                                             //the new quaity is zero
RESULT(v[11])


EQUATION("Imitation_Quality")
/*
Firm Variable
*/
	v[0]=VL("Revenue", 1);                                 //firm's revenue in the last period
	v[1]=V("quality_imitation_revenue_proportion");        //desired share of revenue destinated to product imitation
	v[2]=VL("Max_Quality", 1);                             //maximum product quality of the sector in the last period
	v[3]=V("quality_imitation_success_parameter");         //product imitation sucess parameter
	v[4]=(v[0]*v[1]);                                      //available recources for product imitation
	v[5]=(1-exp(-v[4]*v[3]));                              //product imitation probability depends on the availabe recources
	if(RND<v[5])                                           //draws a randon number. if it is lower then product imitation probability
		v[6]=v[2];                                           //firm's new quality will be the maximum quality of the sector. imitation had succeded
	else                                                   //if the randon number is not lower then product imitation probability
		v[6]=0;                                              //the new quaity is zero
RESULT(v[6])


EQUATION("Quality")
/*
Firm Variable
*/
v[0]=VL("Quality",1);
v[1]=V("id_firm_number");
v[2]= fmod((double) t,6); 
if(v[1]==v[2]||v[1]==(v[2]+6)||v[1]==(v[2]+12)||v[1]==(v[2]+18))
  {
   v[3]=VL("Pay_Test_Quality",6);
   v[4]=VL("Potential_Quality",6);
   if(v[3]==1)
     {
     v[5]=VL("Desired_Autonomous_Investment_Quality",6);
     v[6]=VL("Autonomous_Investment_Quality",6);
     if(v[5]==0)
     	v[7]=0;
     else
     	v[7]=v[6]/v[5];
     v[8]=v[7]*(v[4]-v[0])+v[0];
     }
   else
     v[8]=v[0];
   }
else
  v[8]=v[0];
RESULT(v[8])


EQUATION("Pay_Test_Quality")
/*
Firm Variable
*/
v[0]=VL("Price",1);
v[1]=V("e_price");
v[2]=V("Potential_Quality");
v[3]=V("e_quality");
v[4]=VL("Competitiveness",1);
v[5]=VL("Delivery_Delay",1);
v[6]=V("e_delay");
v[7]=V("Quality"); 
 
if(v[2]>v[7]&&v[0]!=0&&v[5]!=0)//potential_quality greater than actual one.
    {
    v[9]=(pow(v[2],v[3]))*(1/pow(v[0],v[1]))*(1/pow(v[5],v[6]));
    v[10]=-(((pow(v[7],(v[3]/v[1])))*(1/pow(v[9],(1/v[1])))*(1/pow(v[5],(v[6]/v[1]))))-v[0]);
    v[11]=V("Price_Capital_Goods");
    v[15]=V("quality_investment_parameter");
    v[12]=(v[15]*v[11])/v[10];
    v[13]=V("payback");
       if(v[12]<=v[13])
       	v[14]=1;
       else
       	v[14]=0;
    }
else
    {
    v[10]=0;
    v[14]=0;
    }
RESULT(v[14])



