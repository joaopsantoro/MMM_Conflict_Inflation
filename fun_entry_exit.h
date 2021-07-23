/*****ENTRY AND EXIT VARIABLES*****/
//all these variable are sector variables


EQUATION("Total_Investment_Expenses")
/*
Delete Firms
Versão proposta pelo Marcelo Pereira
*/
  i = COUNT( "FIRMS" );																																		// count the existing number of firms
  v[2] = v[3] = v[5] = 0;																																	// initialize the counters as before
  CYCLE_SAFE( cur, "FIRMS" )																															// use a robust cycle to delete objects
  {
     v[0]=VS(cur, "Productive_Capacity");
     v[1]=VS(cur, "Market_Share");
     v[6]=VLS(cur, "Effective_Market_Share",1);
     if ( ( v[1] <= 0.01 || v[0] <= 1 ) && i > 1 )																				// don't kill last firm
     {
      v[2]=v[2];
      v[3]=v[3]+v[0];
      v[5]=v[5]+v[6];
      plog("\nFirm Deleted - Small Market Share");
      cur->delete_obj(); 
     
	  --i;
     }
     else
     {
     v[10]=VS(cur, "Debt_Rate");
     v[11]=VLS(cur, "Debt_Rate",1);
     v[12]=VLS(cur, "Debt_Rate",2);
     v[13]=VLS(cur, "Debt_Rate",3);
     v[14]=VLS(cur, "Debt_Rate",4);
     v[15]=VLS(cur, "Debt_Rate",5);
     v[16]=VLS(cur, "Debt_Rate",6);
     v[4]=(v[10]+v[11]+v[12]+v[13]+v[14]+v[15]+v[16])/7;
	 
        if ( v[4] > 1.5 && v[10] - v[11] > 0 && v[11] - v[12] > 0 && i > 1 )								// don't kill last firm
        {
        v[2]=v[2]+1;
        v[3]=v[3]+v[0];
        v[5]=v[5]+v[6];
        plog("\nFirm Deleted - High Debt");
        cur->delete_obj(); 																																//kill the current object
		    --i;	
        }
        else
        {
        v[2]=v[2];
        v[3]=v[3];
        v[5]=v[5];
        }
     }
  }
  
 WRITE("number_exit_temporary",v[2]);
 WRITE("productive_capacity_exit_temporary",v[3]);
 WRITE("effective_market_share_exit_temporary",v[5]);
v[34]=SUM("Investment_Expenses"); 
RESULT(v[34])


EQUATION("Number_Exit")
/*
Sector Variable
*/
v[0]=V("number_exit_temporary");
v[1]=V("number_exit_temporary_2");
v[2]=VL("Number_Exit", 1);
v[3]=v[0]+v[1]+v[2];
RESULT(v[3])


EQUATION("Number_Entry")
/*
Sector Variable
*/
v[0]=V("To_Entry");
v[1]=VL("Number_Entry", 1);
v[2]=v[0]+v[1];
RESULT(v[2])



EQUATION("To_Entry")
/*
Sector Variable
*/
v[14]=V("id_sector_number");
v[15]= fmod((double) t,6); 
if(v[14]==v[15]||v[14]==(v[15]+6)||v[14]==(v[15]+12))
{
  v[2]=VL("Effective_Orders_Sector",1);
  v[3]=VL("Effective_Orders_Sector",2);
  v[4]=VL("Effective_Orders_Sector",3);
  v[5]=VL("Effective_Orders_Sector",8);
  v[6]=v[2]-v[5];
  v[7]=(v[2]-v[3])/v[3];
  v[8]=(v[3]-v[4])/v[4];
  
     if(v[6]>0&&v[7]>0&&v[8]>0)
     {
     v[9]=V("Number_Exit");
     v[10]=VL("Number_Entry",1);
     v[11]=v[9]-v[10];
     //v[12]=1;
     }
     else
     v[11]=0;
     //v[12]=0;
     if(v[11]>0)
     v[12]=1;
     else
     v[12]=0;
 }
 else
 v[12]=0;
   
RESULT(v[12])


EQUATION("Effective_Market_Share_Exit")
/*
Sector Variable
*/
v[0]=V("effective_market_share_exit_temporary");
v[1]=V("effective_market_share_exit_temporary_2");
v[2]=v[0]+v[1];
WRITE("effective_market_share_exit_temporary", 0);
WRITE("effective_market_share_exit_temporary_2", 0);
RESULT(v[2])


EQUATION("Productive_Capacity_Exit")
/*
Sector Variable
*/
v[0]=V("productive_capacity_exit_temporary");
v[1]=V("productive_capacity_exit_temporary_2");
v[2]=VL("Productive_Capacity_Exit", 1);
v[3]=v[0]+v[1]+v[2];
WRITE("productive_capacity_exit_temporary", 0);
WRITE("productive_capacity_exit_temporary_2", 0);
RESULT(v[3])


EQUATION("Productive_Capacity_To_Entry")
/*
Sector Variable
*/
v[8]=V("id_sector_number");
v[9]= fmod((double) t,6); 
  if(v[8]==v[9]||v[8]==(v[9]+6)||v[8]==(v[9]+12))
  {
  v[0]=V("Number_Exit");
  v[1]=VL("Number_Entry",1);
  v[2]=V("To_Entry");
  v[3]=V("Productive_Capacity_Exit");
  v[4]=VL("Productive_Capacity_Entry",1);
  v[5]=v[0]-v[1];//Number of firms that will eventually enter
  v[6]=v[3]-v[4];//Productive capacity lost
     if(v[5]>0)
     v[7]=(v[6]/v[5])*v[2];
     else
     v[7]=0;
  }
  else
  v[7]=0;
RESULT(v[7])


EQUATION("Productive_Capacity_Entry")
/*
Sector Variable
*/
v[0]=VL("Productive_Capacity_Entry",1);
v[1]= fmod((double) t,6);
v[2]=V("id_sector_number");
if(v[2]==v[1]||v[2]==(v[1]+6)||v[2]==(v[1]+12))
  {
  v[3]=V("Productive_Capacity_To_Entry");
  v[4]=v[3]+v[0];
  }
else
  v[4]=v[0];
RESULT(v[4])


EQUATION("Entry")
/*
Sector Variable
Não alterei os v[] nem os cycles
*/
v[0]=V("entry_parameter");
  if(v[0]==1)
  {
   V("Sum_Market_Share");
   v[1]=V("To_Entry");
      if(v[1]>0)
      {
      v[20]=V("Effective_Orders_Sector");
      v[32]=V("imitation_revenue_proportion_sector");
      v[33]=v[32]/2;
      v[34]=V("Productive_Capacity_To_Entry");
      v[36]=V("Avg_Price");
      v[38]=V("depreciation");
      v[39]=V("Avg_Productivity_Sector");   
      v[42]=uniform_int(1, 6);
      v[4]=(double) t;
           for(v[5]=0,v[6]=0,cur3=p->search("FIRMS"); cur3!=NULL; cur3=brother(cur3) )
           {
           v[5]=v[5]+1;
           v[7]=VS(cur3, "Market_Share");
           v[6]=v[6]+v[7];
           }
     			 v[8]=v[6]/v[5];
           for(v[10]=1,v[12]=0,cur4=p->search("FIRMS"); cur4!=NULL; cur4=brother(cur4) )
           {
           v[9]=VS(cur4, "Market_Share");
           v[11]=abs(v[9]-v[8]);
           v[10]=min(v[11],v[10]);
               if(v[11]==v[10])
               v[12]=v[9];
               else
               v[12]=v[12];
           }
      		   v[25]=round(v[34]/v[1])+1;
             for(v[15]=v[1],v[14]=0,v[31]=1; v[15]>0; v[15]=v[14] )
             {
              plog("\nFirm Created");
              v[14]=v[15]-1;
              cur=p->search_var_cond("Market_Share",v[12],0);
              v[22]=VS(cur, "desired_degree_capacity_utilization");
              v[23]=VS(cur, "desired_inventories_proportion");
              v[35]=(v[22]*v[25])/v[20];
              cur=ADDOBJ_EX("FIRMS",cur);             
              WRITES(cur, "firm_date_birth",v[4]);
              WRITES(cur, "id_firm_number",v[42]);
              WRITELS(cur, "Market_Share",v[35],v[4]);
              WRITELS(cur, "Debt",0.2*1.33*v[25],v[4]);
              WRITELS(cur, "Financial_Assets",0.33*v[25],v[4]);
              WRITELS(cur, "Market_Share",v[35],v[4]);
              WRITELS(cur, "Effective_Market_Share",v[35],v[4]);
              WRITELS(cur, "Target_Market_Share",v[35],v[4]);
              WRITELS(cur, "Firm_Avg_Market_Share",v[35],v[4]);
              WRITELS(cur, "Effective_Orders",v[25]*v[22],v[4]);
              WRITELS(cur, "Inventories",v[25]*v[22]*v[23],v[4]);
              WRITELS(cur, "Price",v[36],v[4]);
              WRITELS(cur, "Max_Capital_Goods_Productivity",v[39],v[4]);
              WRITELS(cur, "Frontier_Productivity",v[39],v[4]);
                   if(v[31]==1)
                   {
                   WRITES(cur, "id_innovative_firm",1);
                   WRITES(cur, "innovation_revenue_proportion",v[33]);
                   WRITES(cur, "imitation_revenue_proportion",v[32]);
                   v[31]=v[31]-1;
                   }
                   else
                   {
                   v[31]=v[31]+1;
                   WRITES(cur, "id_innovative_firm",0);
                   WRITES(cur, "innovation_revenue_proportion",0);
                   WRITES(cur, "imitation_revenue_proportion",v[32]);
                   }
              					for(v[26]=0,v[37]=0,cur1=cur->search("CAPITAL"); cur1!=NULL;)
                        {
                           v[26]=v[26]+1;
                             if(v[26]<=v[25])
                             {
                             WRITES(cur1, "to_die_capital_good",0);
                             WRITES(cur1, "capital_good_date_birth",v[4]-v[37]);
                             WRITES(cur1, "id_a_2",0);
                             WRITES(cur1, "capital_good_productivity_initial",v[39]);
                             WRITES(cur1, "Capital_Good_Replacement",0);
                             WRITELS(cur1, "Sum_Id_A_2",0,v[4]);
                             WRITELS(cur1, "Capital_Good_Acumulated_Production",0,v[4]);
                             WRITES(cur1, "pay_test",0);
                             WRITES(cur1, "pay_test_2",0);
                             cur1=brother(cur1);
                             v[37]=v[37]+6;
                             }
                             else
                             {
                             cur2=brother(cur1);
                             cur1->delete_obj();
                             cur1=cur2;
                             v[37]=v[37];
                             }
                                if(v[37]>=v[38])
                                v[37]=0;
                                else
                                v[37]=v[37];
                         }
                        if(v[26]<v[25])
                        {
                         plog("\nAdded B_K");
                         
                            v[27]=v[25]-v[26];
                                 for(v[37]=0,v[28]=v[27],v[29]=0; v[28]>0; v[28]=v[29],v[37]=v[40])
                            					{
                                 cur2=cur->search("CAPITAL");
                                 cur2=ADDOBJ_EXS(cur, "CAPITAL", cur2);
                            
                                 WRITES(cur2, "capital_good_date_birth",v[4]-v[37]);
                                 WRITES(cur2, "capital_good_productivity_initial",v[39]);
                                 WRITELS(cur2, "Sum_Id_A_2",0,v[4]);
                                 WRITES(cur2, "id_a_2",0);
                                 WRITES(cur2, "to_die_capital_good",0);
                                 WRITES(cur2, "Capital_Good_Replacement",0);
                                 WRITELS(cur2, "Capital_Good_Acumulated_Production",0,v[4]);
                                 WRITES(cur2, "pay_test",0);
                                 WRITES(cur2, "pay_test_2",0);
                                 v[29]=v[28]-1;
                                 v[37]=v[37]+6;
                                    if(v[37]>=v[38])
                                    v[40]=0;
                                    else
                                    v[40]=v[37];          
                             				}
                             
                        }
                  } 
            WRITE("number_exit_temporary", 0);
            v[50]=v[1];
       }
       else
       v[50]=0;
  }
  else 
  v[50]=0;
RESULT(v[50])


EQUATION("Productive_Capacity_Appendix")
/*
Its is just to make it possible to delete the firm before it calculates CP if there are no more Capital Goods
*/
USE_ZERO_INSTANCE
CYCLE(cur3, "SECTORS")
{
	v[0]=VS(cur3, "depreciation");
	v[1]=VS(cur3, "Avg_Productivity_Sector");
	i = COUNT( "FIRMS" );
	v[2]=0;
	v[3]=0;
	v[4]=0;
	CYCLE_SAFES(cur3, cur, "FIRMS")
	{
		v[5]=0;
		v[6]=0;
		v[7]=0;
		CYCLES(cur, cur1, "CAPITAL")
		{
			v[8]=VS(cur1, "capital_good_date_birth");
			v[9]=VS(cur1, "capital_good_productive_capacity");
					if((double)t>=v[8]+v[0])
          {
          v[5]=v[5]+v[9];
          v[10]=0;
          v[11]=0;
          }
          else
          {
          v[5]=v[5];
          v[10]=VS(cur1,"to_die_capital_good");
          v[11]=1;
          }
       v[6]=v[6]+v[10];
       v[7]=v[7]+v[11];
		}
	WRITES(cur, "Productive_Capacity_Depreciated", v[5]);
	v[12]=VLS(cur, "Productive_Capacity", 1);
	v[13]=VS(cur, "Effective_Productive_Capacity_Variation");
		if (v[12]-v[5]<0 && v[13]>=0)
		{
		v[14]=0;
		v[15]=v[12];
		CYCLES(cur, cur1, "CAPITAL")
		{
			v[16]=VS(cur1, "capital_good_date_birth");
			v[17]=VS(cur1, "capital_good_productive_capacity");
				if((double)t>=v[16]+v[0])
				{
				v[14]=v[14]+v[17];
				v[15]=v[15]-v[17];
				DELETE(cur1);
				}
				else
				{
				v[14]=v[14];
				v[15]=v[15];
				}
		}
		}
		else
		{
		v[14]=0;
		CYCLES(cur, cur1, "CAPITAL")
		{
			v[16]=VS(cur1, "capital_good_date_birth");
			v[17]=VS(cur1, "capital_good_productive_capacity");
				if((double)t>=v[16]+v[0])
				{
				v[14]=v[14]+v[17];
				DELETE(cur1);
				}
				else
				v[14]=v[14];
		}
		}
		v[18]=v[12]+v[13]-v[5];
			if (v[18]<1 && i>1)	 //firm must be deleted
			{
			v[3]=v[3];
			v[2]=v[2];
			v[19]=VLS(cur, "Effective_Market_Share", 1);
			v[4]=v[4]+v[19];
			plog("\nFirm Deleted - all capital depreciated physically");
			DELETE(cur);
		--i;
      }
      else
      {
      v[2]=v[2];
      v[3]=v[3];
      v[4]=v[4];
      }			
}
WRITES(cur3, "number_exit_temporary_2", v[2]);
WRITES(cur3, "productive_capacity_exit_temporary_2", v[3]);
WRITES(cur3, "effective_market_share_exit_temporary_2", v[4]);
}
RESULT(0)

