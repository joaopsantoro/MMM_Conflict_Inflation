EQUATION("Initialization")
/*
Initializes the initial values for endogenous variables
Located at Root
Must be the first variable to be calculated
Depends on some Hypoteses:
1-All firms starts the same (implies that all average and maximum values are the same and equal to the firm value)
2-All capital goods start the same, except for the date_birth (implies that all average and maximum values are the same)
3-All demand is met initally (implies that effective orders, production and sales are the same)
4-There is no growth initally 
5-The Structure of the 4 sectors must remain (the rest below can be change, except for input because each instance represents onE sector
*/

//Macro Control Parameters

V[14]=V("unemployment_target");

CYCLE(cur, "SECTORS")
{
	//Sector Control Parameters
	v[0]=VS(cur, "investment_period");
	v[1]=VS(cur, "number_object_firms");                  //number of firms of the sector, defined by parameter
	v[2]=1/v[1];                                          //initial market share of each firm, to be written as firm's initial MS, to be written as firm's MS, desired MS, effective MS and Avg MS
	v[3]=VS(cur, "avg_price_initial");                    //initial price of the sector (the same for all firms)
	v[4]=VS(cur, "foreign_price_initial");                //initial foreign price for the sector
	v[5]=VS(cur, "quality_initial");
	v[6]=VS(cur, "productivity_initial");
	v[7]=VS(cur, "number_object_capitals");
	v[8]=VS(cur, "markup_initial");
	v[9]=VS(cur, "capital_output_ratio_initial");
	v[11]=VS(cur, "desired_inventories_proportion");	
	v[12]=VS(cur, "desired_degree_capacity_utilization");
	v[13]=(v[7]*v[9]*v[12]*v[1]);
	v[10]=v[13]/v[1];
	v[15]=VS(cur, "input_tech_relationship_sector_3");
	v[16]=VS(cur, "input_tech_relationship_sector_4");
	v[17]=VS(cur, "input_tech_relationship_imports_sector_3");
	v[18]=VS(cur, "input_tech_relationship_imports_sector_3");

	//Begin Writting Sector Variables
	WRITELS(cur, "Demand_Met", 1, 1);                                  //it is assumed that all demand is met initially. Equals 1 by definition
	WRITELS(cur, "Demand_Met_By_Imports", 1, 1);                       //it is assumed thatt all imports are met initially. Equals 1 by definition
	WRITELS(cur, "Number_Exit", 0, 1);                                 //it is assumed that there is no entry or exit initially. Equals 0 by definition
	WRITELS(cur, "Number_Entry", 0, 1);                                //it is assumed that there is no entry or exit initially. Equals 0 by definition
	WRITELS(cur, "Productive_Capacity_Entry", 0, 1);                   //it is assumed that there is no entry or exit initially. Equals 0 by definition
	WRITELS(cur, "Productive_Capacity_Exit", 0, 1);                    //it is assumed that there is no entry or exit initially. Equals 0 by definition
	WRITELS(cur, "Avg_Competitiveness", 1, 1);                         //if all firms are the same, equals 1 by definition
	WRITELS(cur, "Avg_Price", v[3], 1);                                //Avg Price equals avg_price_initial parameter for all lags
	WRITELS(cur, "Avg_Price", v[3], 2);                                //Avg Price equals avg_price_initial parameter for all lags
  	WRITELS(cur, "Foreign_Price", v[4], 1);                            //Foreign Price equals foregn_price_initial parameter
	WRITELS(cur, "Avg_Quality_Sector", v[5], 1);                       //If all firms are the same, Avg Quality will be the initial quality for all firms in all lags
	WRITELS(cur, "Avg_Quality_Sector", v[5], 2);                       //If all firms are the same, Avg Quality will be the initial quality for all firms in all lags
	WRITELS(cur, "Avg_Quality_Sector", v[5], 3);                       //If all firms are the same, Avg Quality will be the initial quality for all firms in all lags
	WRITELS(cur, "Avg_Quality_Sector", v[5], 4);                       //If all firms are the same, Avg Quality will be the initial quality for all firms in all lags
	WRITELS(cur, "Avg_Quality_Sector", v[5], 5);                       //If all firms are the same, Avg Quality will be the initial quality for all firms in all lags
	WRITELS(cur, "Avg_Quality_Sector", v[5], 6);                       //If all firms are the same, Avg Quality will be the initial quality for all firms in all lags
	WRITELS(cur, "Avg_Quality_Sector", v[5], 7);                       //If all firms are the same, Avg Quality will be the initial quality for all firms in all lags
	WRITELS(cur, "Avg_Quality_Sector", v[5], 8);                       //If all firms are the same, Avg Quality will be the initial quality for all firms in all lags
	WRITELS(cur, "Avg_Quality_Sector", v[5], 9);                       //If all firms are the same, Avg Quality will be the initial quality for all firms in all lags
	WRITELS(cur, "Avg_Quality_Sector", v[5], 10);                      //If all firms are the same, Avg Quality will be the initial quality for all firms in all lags
	WRITELS(cur, "Max_Quality", v[5], 1);                              //If all firms are the same, Max equals Avg
	WRITELS(cur, "Avg_Productivity_Sector", v[6], 1);                  //If all firms are the same, Avg Productivity will be the initial productivivity for all firms in all lags
	WRITELS(cur, "Avg_Productivity_Sector", v[6], 2);                  //If all firms are the same, Avg Productivity will be the initial productivivity for all firms in all lags
	WRITELS(cur, "Avg_Productivity_Sector", v[6], 3);                  //If all firms are the same, Avg Productivity will be the initial productivivity for all firms in all lags
	WRITELS(cur, "Avg_Productivity_Sector", v[6], 4);                  //If all firms are the same, Avg Productivity will be the initial productivivity for all firms in all lags
	WRITELS(cur, "Avg_Productivity_Sector", v[6], 5);                  //If all firms are the same, Avg Productivity will be the initial productivivity for all firms in all lags
  	WRITELS(cur, "Max_Productivity", v[6], 1);                         //If all firms are the same, Max equals Avg
	WRITELS(cur, "Effective_Orders_Sector", v[13], 1);
	WRITELS(cur, "Effective_Orders_Sector", v[13], 2);
	WRITELS(cur, "Effective_Orders_Sector", v[13], 3);
	WRITELS(cur, "Effective_Orders_Sector", v[13], 4);
	WRITELS(cur, "Effective_Orders_Sector", v[13], 5);
	WRITELS(cur, "Effective_Orders_Sector", v[13], 6);
	WRITELS(cur, "Effective_Orders_Sector", v[13], 7);
	WRITELS(cur, "Effective_Orders_Sector", v[13], 8);
	WRITELS(cur, "Inventories_Sector", (V[13]*v[11]), 1);
	WRITELS(cur, "Productive_Capacity_Sector", (v[1]*v[7]*v[9]) , 1);  //Sector productive capacity equals the productivity of each capital good (alls starts the same) time the number of capital goods per firm times the number of firms
  
	//Begin Writting Firm Variables
	CYCLES(cur, cur1, "FIRMS")
	{
	  WRITELS(cur1, "Competitiveness", 1, 1);                           //if all firms are the same
	  WRITELS(cur1, "Delivery_Delay", 1, 1);                            //it is assumed that all demand is met initially, so equals 1 by definition
	  WRITELS(cur1, "Imitation_Probability", 0, 1);
	  WRITELS(cur1, "Innovation_Probability", 0, 1);
	  WRITELS(cur1, "Pay_Test_Quality", 0, 1);
	  WRITELS(cur1, "Pay_Test_Quality", 0, 2);
	  WRITELS(cur1, "Pay_Test_Quality", 0, 3);
	  WRITELS(cur1, "Pay_Test_Quality", 0, 4);
	  WRITELS(cur1, "Pay_Test_Quality", 0, 5);
	  WRITELS(cur1, "Pay_Test_Quality", 0, 6);
	  WRITELS(cur1, "Autonomous_Investment_Quality", 0, 1);
	  WRITELS(cur1, "Autonomous_Investment_Quality", 0, 2);
	  WRITELS(cur1, "Autonomous_Investment_Quality", 0, 3);
	  WRITELS(cur1, "Autonomous_Investment_Quality", 0, 4);
	  WRITELS(cur1, "Autonomous_Investment_Quality", 0, 5);
	  WRITELS(cur1, "Autonomous_Investment_Quality", 0, 6);
	  WRITELS(cur1, "Desired_Autonomous_Investment_Quality", 0, 1);
	  WRITELS(cur1, "Desired_Autonomous_Investment_Quality", 0, 2);
	  WRITELS(cur1, "Desired_Autonomous_Investment_Quality", 0, 3);
	  WRITELS(cur1, "Desired_Autonomous_Investment_Quality", 0, 4);
	  WRITELS(cur1, "Desired_Autonomous_Investment_Quality", 0, 5);
	  WRITELS(cur1, "Desired_Autonomous_Investment_Quality", 0, 6);
	  WRITELS(cur1, "Demand_Productive_Capacity_Quality", 0, 1);
	  WRITELS(cur1, "Demand_Productive_Capacity_Quality", 0, 2);
	  WRITELS(cur1, "Demand_Productive_Capacity_Quality", 0, 3);
	  WRITELS(cur1, "Demand_Productive_Capacity_Quality", 0, 4);
	  WRITELS(cur1, "Demand_Productive_Capacity_Quality", 0, 5);
	  WRITELS(cur1, "Demand_Productive_Capacity_Quality", 0, 6);
	  WRITELS(cur1, "Replacement", 0, 1);
	  WRITELS(cur1, "Replacement", 0, 2);
	  WRITELS(cur1, "Replacement", 0, 3);
	  WRITELS(cur1, "Replacement", 0, 4);
	  WRITELS(cur1, "Replacement", 0, 5);
	  WRITELS(cur1, "Replacement", 0, 6);
	  WRITELS(cur1, "Productive_Capacity_Depreciated", 0, 1);
	  WRITELS(cur1, "Productive_Capacity_Scrapped", 0, 1);
	  WRITELS(cur1, "Market_Share", v[2], 1);
	  WRITELS(cur1, "Market_Share", v[2], 1);             
	  WRITELS(cur1, "Market_Share", v[2], 2);
	  WRITELS(cur1, "Market_Share", v[2], 3);
	  WRITELS(cur1, "Market_Share", v[2], 4);
	  WRITELS(cur1, "Market_Share", v[2], 5);
	  WRITELS(cur1, "Market_Share", v[2], 6);
	  WRITELS(cur1, "Market_Share", v[2], 7);
	  WRITELS(cur1, "Effective_Market_Share", v[2], 1);
	  WRITELS(cur1, "Desired_Market_Share", v[2], 1);
	  WRITELS(cur1, "Firm_Avg_Market_Share", v[2], 1);
	  WRITELS(cur1, "Price", v[3], 1);
	  WRITELS(cur1, "Quality", v[5], 1);
	  WRITELS(cur1, "Potential_Quality", v[5], 1);
	  WRITELS(cur1, "Potential_Quality", v[5], 2);
	  WRITELS(cur1, "Potential_Quality", v[5], 3);
	  WRITELS(cur1, "Potential_Quality", v[5], 4);
	  WRITELS(cur1, "Potential_Quality", v[5], 5);
	  WRITELS(cur1, "Potential_Quality", v[5], 6);
	  WRITELS(cur1, "Firm_Avg_Productivity", v[6], 1);
	  WRITELS(cur1, "Frontier_Productivity", v[6], 1);
	  WRITELS(cur1, "Frontier_Productivity", v[6], 2);
	  WRITELS(cur1, "Frontier_Productivity", v[6], 3);
	  WRITELS(cur1, "Frontier_Productivity", v[6], 4);
	  WRITELS(cur1, "Frontier_Productivity", v[6], 5);
	  WRITELS(cur1, "Frontier_Productivity", v[6], 6);
	  WRITELS(cur1, "Max_Capital_Goods_Productivity", v[6], 1);
	  WRITELS(cur1, "Max_Capital_Goods_Productivity", v[6], 2);
	  WRITELS(cur1, "Max_Capital_Goods_Productivity", v[6], 3);
	  WRITELS(cur1, "Max_Capital_Goods_Productivity", v[6], 4);
	  WRITELS(cur1, "Max_Capital_Goods_Productivity", v[6], 5);
	  WRITELS(cur1, "Max_Capital_Goods_Productivity", v[6], 6);
	  WRITELS(cur1, "Capital", (v[7]*v[9]), 1);
	  WRITELS(cur1, "Productive_Capacity", (v[7]*v[9]*v[6]), 1);
	  WRITELS(cur1, "Avg_Potential_Markup", v[8], 1);
	  WRITELS(cur1, "Desired_Markup", v[8], 1);
	  WRITELS(cur1, "Strategic_Markup", v[8], 1);
	  WRITELS(cur1, "Potential_Markup", v[8], 1);
	  WRITELS(cur1, "Potential_Markup", v[8], 2);
	  WRITELS(cur1, "Potential_Markup", v[8], 3);
	  WRITELS(cur1, "Potential_Markup", v[8], 4);
	  WRITELS(cur1, "Potential_Markup", v[8], 5);
	  WRITELS(cur1, "Potential_Markup", v[8], 6);
	  WRITELS(cur1, "Potential_Markup", v[8], 7);
	  WRITELS(cur1, "Effective_Orders", v[10], 1);
	  WRITELS(cur1, "Effective_Orders", v[10], 2);
	  WRITELS(cur1, "Effective_Orders", v[10], 3);
	  WRITELS(cur1, "Effective_Orders", v[10], 4);
	  WRITELS(cur1, "Effective_Orders", v[10], 5);
	  WRITELS(cur1, "Effective_Orders", v[10], 6);
  	  WRITELS(cur1, "Effective_Orders", v[10], 7);
	  WRITELS(cur1, "Effective_Orders", v[10], 8);
	  WRITELS(cur1, "Effective_Orders", v[10], 9);
	  WRITELS(cur1, "Effective_Orders", v[10], 10);
	  WRITELS(cur1, "Effective_Orders", v[10], 11);
  	  WRITELS(cur1, "Effective_Orders", v[10], 12);
	  WRITELS(cur1, "Sales", v[10], 1);
	  WRITELS(cur1, "Revenue", (v[10]*v[3]), 1);
	  WRITELS(cur1, "Productive_Capacity_Variation", 0, 7);
	  WRITELS(cur1, "Demand_Productive_Capacity", 0, 7);
	  WRITELS(cur1, "Sum_Id_A_3", 1, 7);
		
	  WRITELS(cur1, "Spread_Firm", 1, 1);
	  WRITELS(cur1, "Financial_Assets", 4, 1);
	  WRITELS(cur1, "Debt", 3.2, 1);
	  v[21]=V("Debt")/(V("Capital")+V("Financial_Assets"));
	  WRITELS(cur1, "Debt_Rate", v[21], 1);
	  WRITELS(cur1, "Inventories", (v[10]*v[11]), 1);

	V[23]=SEARCH_INST(cur1);
	WRITES(cur1, "id_firm_number", v[23]);                             //writes the parameter id_firm_number
	v[20]= fmod((double) (v[23]+6), 6);
		if (v[20]==1)
			{
			WRITELS(cur1, "Productive_Capacity_Variation", 0, 1);
			WRITELS(cur1, "Productive_Capacity_Variation", 0, 2);
			WRITELS(cur1, "Productive_Capacity_Variation", 0, 3);
			WRITELS(cur1, "Productive_Capacity_Variation", 0, 4);
			WRITELS(cur1, "Productive_Capacity_Variation", 0, 5);
			WRITELS(cur1, "Productive_Capacity_Variation", 2, 6);
			WRITELS(cur1, "Depreciation_Productive_Capacity", 0, 1);
			WRITELS(cur1, "Depreciation_Productive_Capacity", 0, 2);
			WRITELS(cur1, "Depreciation_Productive_Capacity", 0, 3);
			WRITELS(cur1, "Depreciation_Productive_Capacity", 0, 4);
			WRITELS(cur1, "Depreciation_Productive_Capacity", 0, 5);
			WRITELS(cur1, "Depreciation_Productive_Capacity", 2, 6);
			WRITELS(cur1, "Demand_Productive_Capacity", 0, 1);
			WRITELS(cur1, "Demand_Productive_Capacity", 0, 2);
			WRITELS(cur1, "Demand_Productive_Capacity", 0, 3);
			WRITELS(cur1, "Demand_Productive_Capacity", 0, 4);
			WRITELS(cur1, "Demand_Productive_Capacity", 0, 5);
			WRITELS(cur1, "Demand_Productive_Capacity", 5.78, 6);
			WRITELS(cur1, "Sum_Id_A_3", 3, 1);
			WRITELS(cur1, "Sum_Id_A_3", 3, 2);
			WRITELS(cur1, "Sum_Id_A_3", 3, 3);
			WRITELS(cur1, "Sum_Id_A_3", 3, 4);
			WRITELS(cur1, "Sum_Id_A_3", 3, 5);
			WRITELS(cur1, "Sum_Id_A_3", 3, 6);
			}
		if else (v[20]==2)
			{
			WRITELS(cur1, "Productive_Capacity_Variation", 0, 1);
			WRITELS(cur1, "Productive_Capacity_Variation", 0, 2);
			WRITELS(cur1, "Productive_Capacity_Variation", 0, 3);
			WRITELS(cur1, "Productive_Capacity_Variation", 0, 4);
			WRITELS(cur1, "Productive_Capacity_Variation", 2, 5);
			WRITELS(cur1, "Productive_Capacity_Variation", 0, 6);
			WRITELS(cur1, "Depreciation_Productive_Capacity", 0, 1);
			WRITELS(cur1, "Depreciation_Productive_Capacity", 0, 2);
			WRITELS(cur1, "Depreciation_Productive_Capacity", 0, 3);
			WRITELS(cur1, "Depreciation_Productive_Capacity", 0, 4);
			WRITELS(cur1, "Depreciation_Productive_Capacity", 2, 5);
			WRITELS(cur1, "Depreciation_Productive_Capacity", 0, 6);
			WRITELS(cur1, "Demand_Productive_Capacity", 0, 1);
			WRITELS(cur1, "Demand_Productive_Capacity", 0, 2);
			WRITELS(cur1, "Demand_Productive_Capacity", 0, 3);
			WRITELS(cur1, "Demand_Productive_Capacity", 0, 4);
			WRITELS(cur1, "Demand_Productive_Capacity", 5.78, 5);
			WRITELS(cur1, "Demand_Productive_Capacity", 0, 6);
			WRITELS(cur1, "Sum_Id_A_3", 3, 1);
			WRITELS(cur1, "Sum_Id_A_3", 3, 2);
			WRITELS(cur1, "Sum_Id_A_3", 3, 3);
			WRITELS(cur1, "Sum_Id_A_3", 3, 4);
			WRITELS(cur1, "Sum_Id_A_3", 3, 5);
			WRITELS(cur1, "Sum_Id_A_3", 1, 6);
			}
		if else (v[20]==3)
			{
			WRITELS(cur1, "Productive_Capacity_Variation", 0, 1);
			WRITELS(cur1, "Productive_Capacity_Variation", 0, 2);
			WRITELS(cur1, "Productive_Capacity_Variation", 0, 3);
			WRITELS(cur1, "Productive_Capacity_Variation", 2, 4);
			WRITELS(cur1, "Productive_Capacity_Variation", 0, 5);
			WRITELS(cur1, "Productive_Capacity_Variation", 0, 6);
			WRITELS(cur1, "Depreciation_Productive_Capacity", 0, 1);
			WRITELS(cur1, "Depreciation_Productive_Capacity", 0, 2);
			WRITELS(cur1, "Depreciation_Productive_Capacity", 0, 3);
			WRITELS(cur1, "Depreciation_Productive_Capacity", 2, 4);
			WRITELS(cur1, "Depreciation_Productive_Capacity", 0, 5);
			WRITELS(cur1, "Depreciation_Productive_Capacity", 0, 6);
			WRITELS(cur1, "Demand_Productive_Capacity", 0, 1);
			WRITELS(cur1, "Demand_Productive_Capacity", 0, 2);
			WRITELS(cur1, "Demand_Productive_Capacity", 0, 3);
			WRITELS(cur1, "Demand_Productive_Capacity", 5.78, 4);
			WRITELS(cur1, "Demand_Productive_Capacity", 0, 5);
			WRITELS(cur1, "Demand_Productive_Capacity", 0, 6);
			WRITELS(cur1, "Sum_Id_A_3", 3, 1);
			WRITELS(cur1, "Sum_Id_A_3", 3, 2);
			WRITELS(cur1, "Sum_Id_A_3", 3, 3);
			WRITELS(cur1, "Sum_Id_A_3", 3, 4);
			WRITELS(cur1, "Sum_Id_A_3", 1, 5);
			WRITELS(cur1, "Sum_Id_A_3", 1, 6);
			}
		if else (v[20]==4)
			{
			WRITELS(cur1, "Productive_Capacity_Variation", 0, 1);
			WRITELS(cur1, "Productive_Capacity_Variation", 0, 2);
			WRITELS(cur1, "Productive_Capacity_Variation", 2, 3);
			WRITELS(cur1, "Productive_Capacity_Variation", 0, 4);
			WRITELS(cur1, "Productive_Capacity_Variation", 0, 5);
			WRITELS(cur1, "Productive_Capacity_Variation", 0, 6);
			WRITELS(cur1, "Depreciation_Productive_Capacity", 0, 1);
			WRITELS(cur1, "Depreciation_Productive_Capacity", 0, 2);
			WRITELS(cur1, "Depreciation_Productive_Capacity", 2, 3);
			WRITELS(cur1, "Depreciation_Productive_Capacity", 0, 4);
			WRITELS(cur1, "Depreciation_Productive_Capacity", 0, 5);
			WRITELS(cur1, "Depreciation_Productive_Capacity", 0, 6);
			WRITELS(cur1, "Demand_Productive_Capacity", 0, 1);
			WRITELS(cur1, "Demand_Productive_Capacity", 0, 2);
			WRITELS(cur1, "Demand_Productive_Capacity", 5.78, 3);
			WRITELS(cur1, "Demand_Productive_Capacity", 0, 4);
			WRITELS(cur1, "Demand_Productive_Capacity", 0, 5);
			WRITELS(cur1, "Demand_Productive_Capacity", 0, 6);
			WRITELS(cur1, "Sum_Id_A_3", 3, 1);
			WRITELS(cur1, "Sum_Id_A_3", 3, 2);
			WRITELS(cur1, "Sum_Id_A_3", 3, 3);
			WRITELS(cur1, "Sum_Id_A_3", 1, 4);
			WRITELS(cur1, "Sum_Id_A_3", 1, 5);
			WRITELS(cur1, "Sum_Id_A_3", 1, 6);
			}
		if else (v[20]==5)
			{
			WRITELS(cur1, "Productive_Capacity_Variation", 0, 1);
			WRITELS(cur1, "Productive_Capacity_Variation", 2, 2);
			WRITELS(cur1, "Productive_Capacity_Variation", 0, 3);
			WRITELS(cur1, "Productive_Capacity_Variation", 0, 4);
			WRITELS(cur1, "Productive_Capacity_Variation", 0, 5);
			WRITELS(cur1, "Productive_Capacity_Variation", 0, 6);
			WRITELS(cur1, "Depreciation_Productive_Capacity", 0, 1);
			WRITELS(cur1, "Depreciation_Productive_Capacity", 2, 2);
			WRITELS(cur1, "Depreciation_Productive_Capacity", 0, 3);
			WRITELS(cur1, "Depreciation_Productive_Capacity", 0, 4);
			WRITELS(cur1, "Depreciation_Productive_Capacity", 0, 5);
			WRITELS(cur1, "Depreciation_Productive_Capacity", 0, 6);
			WRITELS(cur1, "Demand_Productive_Capacity", 0, 1);
			WRITELS(cur1, "Demand_Productive_Capacity", 5.78, 2);
			WRITELS(cur1, "Demand_Productive_Capacity", 0, 3);
			WRITELS(cur1, "Demand_Productive_Capacity", 0, 4);
			WRITELS(cur1, "Demand_Productive_Capacity", 0, 5);
			WRITELS(cur1, "Demand_Productive_Capacity", 0, 6);
			WRITELS(cur1, "Sum_Id_A_3", 3, 1);
			WRITELS(cur1, "Sum_Id_A_3", 3, 2);
			WRITELS(cur1, "Sum_Id_A_3", 1, 3);
			WRITELS(cur1, "Sum_Id_A_3", 1, 4);
			WRITELS(cur1, "Sum_Id_A_3", 1, 5);
			WRITELS(cur1, "Sum_Id_A_3", 1, 6);
			}	
		if else (v[20]==0)
			{
			WRITELS(cur1, "Productive_Capacity_Variation", 2, 1);
			WRITELS(cur1, "Productive_Capacity_Variation", 0, 2);
			WRITELS(cur1, "Productive_Capacity_Variation", 0, 3);
			WRITELS(cur1, "Productive_Capacity_Variation", 0, 4);
			WRITELS(cur1, "Productive_Capacity_Variation", 0, 5);
			WRITELS(cur1, "Productive_Capacity_Variation", 0, 6);
			WRITELS(cur1, "Depreciation_Productive_Capacity", 2, 1);
			WRITELS(cur1, "Depreciation_Productive_Capacity", 0, 2);
			WRITELS(cur1, "Depreciation_Productive_Capacity", 0, 3);
			WRITELS(cur1, "Depreciation_Productive_Capacity", 0, 4);
			WRITELS(cur1, "Depreciation_Productive_Capacity", 0, 5);
			WRITELS(cur1, "Depreciation_Productive_Capacity", 0, 6);
			WRITELS(cur1, "Demand_Productive_Capacity", 5.78, 1);
			WRITELS(cur1, "Demand_Productive_Capacity", 0, 2);
			WRITELS(cur1, "Demand_Productive_Capacity", 0, 3);
			WRITELS(cur1, "Demand_Productive_Capacity", 0, 4);
			WRITELS(cur1, "Demand_Productive_Capacity", 0, 5);
			WRITELS(cur1, "Demand_Productive_Capacity", 0, 6);
			WRITELS(cur1, "Sum_Id_A_3", 3, 1);
			WRITELS(cur1, "Sum_Id_A_3", 1, 2);
			WRITELS(cur1, "Sum_Id_A_3", 1, 3);
			WRITELS(cur1, "Sum_Id_A_3", 1, 4);
			WRITELS(cur1, "Sum_Id_A_3", 1, 5);
			WRITELS(cur1, "Sum_Id_A_3", 1, 6);
			}	

	//Begin Wirtting Firm Parameters
	WRITES(cur1, "antecipation", 0.5); 									//firm control parameter
	WRITES(cur1, "aprop", 0.5);        									//firm control parameter
	WRITES(cur1, "expand", 1);         									//firm control parameter
	WRITES(cur1, "desired_autonomous_investment_parameter", 3.7841);    //necessary to guarantee initial investment, must be revised
	WRITES(cur1, "desired_financial_rate", 0.05);                       //firm control parameter
	WRITES(cur1, "desired_debt_rate", 0.6);                             //firm control parameter
	WRITES(cur1, "desired_debt_rate_2", 0.1);                           //firm control parameter
	WRITES(cur1, "parameter1", 0.5);                                    //firm control parameter
	WRITES(cur1, "imitation_revenue_proportion", 0.005);                //firm control parameter
	WRITES(cur1, "innovation_revenue_proportion", 0.01);                //firm control parameter
	WRITES(cur1, "quality_imitation_revenue_proportion", 0.0075);
	WRITES(cur1, "quality_innovation_revenue_proportion", 0.015);
	WRITES(cur1, "imitation_success", 0);                               //zero by definition, overwritten during simulation
	WRITES(cur1, "innovation_success", 0);                              //zero by definition, overwritten during simulation
	WRITES(cur1, "rest", 0);       			                       		//zero by definition
	WRITES(cur1, "innovation", 0);                             			//zero by definition
	WRITES(cur1, "imitation", 0);                                       //zero by definition
	WRITES(cur1, "frontier_productivity_initial", v[6]);                //equals control parameter
	WRITES(cur1, "debt_1", 0);                             				//zero by definition, overwritten during simulation
	WRITES(cur1, "debt_2", 0);                              			//zero by definition, overwritten during simulation
	WRITES(cur1, "debt_3", 0);                              			//zero by definition, overwritten during simulation
	WRITES(cur1, "financial_assets_1", 0);                              //zero by definition, overwritten during simulation
	WRITES(cur1, "financial_assets_2", 0);                              //zero by definition, overwritten during simulation
	WRITES(cur1, "financial_assets_3", 0);                              //zero by definition, overwritten during simulation
	WRITES(cur1, "capital_goods_effective_orders_firm_temporary", 0);	//all temporary parameters starts at zero
	WRITES(cur1, "capital_goods_production_temporary", 0);				//all temporary parameters starts at zero
	WRITES(cur1, "consumption_effective_orders_firm_temporary", 0);	    //all temporary parameters starts at zero
	WRITES(cur1, "equivalent_price_variation_temporary", 0);			//all temporary parameters starts at zero
	WRITES(cur1, "intermediate_effective_orders_firm_temporary", 0);	//all temporary parameters starts at zero
	WRITES(cur1, "intermediate_production_firm_temporary", 0);			//all temporary parameters starts at zero
	WRITES(cur1, "id_a_3", 0);											//zero by definition
	WRITES(cur1, "firm_date_birth", 0);
	v[25]= fmod((double) (v[23]+1), 2);                                 
	if (v[25]==0);                                                      //if firm number is odd
		WRITES(cur1, "id_innovative_firm", 1);                          //write as innovative firm
	else                                                                //if firm number is even
		WRITES(cur1, "id_innovative_firm", 0);                          //write as imitative firm
	//End Writting Firm Parameters
	
//Begin Writing Capital Goods Variables and parameters
		CYCLES(cur1, cur2, "CAPITAL")
		{
			WRITELS(cur2, "Capital_Good_Acumulated_Production", 0, 1);      //zero by definition
			WRITELS(cur2, "Sum_Id_A_2", 0, 1);                              //zero by definition
			WRITES(cur2, "capital_good_productive_capacity", (1/v[9]));     //inverse of the capital output ratio  
			WRITES(cur2, "capital_good_productivity_initial", v[6]);        //defined in the control parameters
			WRITES(cur2, "capital_good_replacemente temporary", 0);         //all temmporay variable atarts at zero
			WRITES(cur2, "id_a_2", 0);
			WRITES(cur2, "pay_test", 0);
			WRITES(cur2, "pay_test_2", 0);
			WRITES(cur2, "to_die_capital_good", 0]);                        //zero by definition, no capital goods to die at the beginning
			//begin writing capital_good_date_birth
			v[110]=VS(PARENT, "id_firm_number");                            //firm number
			v[111]=fmod((double) (v[110]+v[0]), v[0]);                      //the rest of the division of the firm umber plus investment period, over investment period (possible results:1,2,3,4,5,0)
			v[112]=SEARCH_INST(cur2);                                       //capital good number
			v[113]=v[111]-(v[0]*v[112]);                                    //takes the rest of the division and substracts the investment period times the number of the capital good
			v[114]=VS(GRANDPARENT, "depreciation");                         //depreciation parameter, life time of the capital good
			if (v[113]>(-114))                                              //if the value is higher than depreciation parameter
				WRITES(cur2, "capital_good_date_birth", v[113]);            //writes the value as capital_good_date_birth                  
			else                                                            //if the value is lower than depreciation parameter
				WRITES(cur2, "capital_good_date_birth", (v[113]+v[114]));   //add the depreciation period to the value and starts another sequence os values
			//end writting capital_good_date_birth
		}//end CYCLE on CAPITAL
		
//Begin Writing Input Variables and Parameters
		v[91]=0;
		CYCLES(cur1, cur2, "INPUTS")                                        
		{
			WRITELS(cur2, "Demand_Met_Input", 1, 1);                        //equals 1 by definition, all demand is met initally
			WRITELS(cur2, "Demand_Met_By_Imports_Input", 1, 1);             //equals 1 by definition, all import is met initally
			V[95]=SEARCH_INST(cur2);                                        //checks the instance position of the current input object
			WRITES(cur2, "id_input_sector", v[94]);                         //wirtes the current position of the input as "id_input_sector"
			v[90]=VS(cur2, "id_input_sector");                              //value of the id_input_sector
			if (v[90]==3)                                                   //if the input sector is 3
				{
				WRITELS(cur2, "Remaining_Inputs", 1.688, 1);                //writes Remaining_Inputs
				WRITES(cur2, "input_technical_relationship", v[15]);        //writes technical relationship as defined by the sector control parameter
				WRITES(cur2, "input_technical_relationship_imports", v[17]);//writes imports technical relationship as defined by the sector control parameter
				}
			if else (v[90]==4) 												//if the input sector is 3
				{
				WRITELS(cur2, "Remaining_Inputs", 2.813, 1);				//writes Remaining_Inputs
				WRITES(cur2, "input_technical_relationship", v[16]);        //writes technical relationship as defined by the sector control parameter
				WRITES(cur2, "input_technical_relationship_imports", v[18]);//writes imports technical relationship as defined by the sector control parameter
				}
			else                                                            //if the input sector is 1 or 2
				{
				WRITELS (cur2, "Remaining_Inputs", 0, 1);                   //wirtes 0 in Remaining_Inputs
				WRITES(cur2, "input_technical_relationship", 0);        	//writes technical relationship as zero
				WRITES(cur2, "input_technical_relationship_imports", 0);	//writes imports technical relationship as zero
				}
			v[92]=VS(cur2, "input_techinal_relationship_imports");          //input control parameters
			v[93]=VS(cur2, "input_technical_relationship");                 //input control parameters
			v[91]=v[91]+v[92]+v[93];                                        //sum up the input cost, assuming input prices are 1 (CHANGE EQUATION IF INITIAL PICES ARE NOT 1)
			if(v[90]==2)                                                    //if the input sector is 2
				WRITES(cur2, "capital_output_ratio", v[9]);                 //wirtes the capital-output_ratio parameter as the initial control parameter
			else                                                            //if the input sector is not 2
				WRITES(cur2, "capital_output_ratio", 0); 					//wirtes 0 in the capital-output_ratio
		}//End CYCLE on INPUTS
	}//End CYCLE on FIRMS
	v[94]=(v[3]/v[8])-v[91];                                                //sector wage is calculated subtracting nput cost from the variable cost defined by the initial price over the initial markup
	WRITELS(cur, "Wage", v[94], 1);                                         //writes Wage Sector Variable      
}//End CYCLE on SECTORS

//Begin Writting Macro Variables
	WRITEL("Likelihood_Crisis", 0, 1);                  //zero by definition
	WRITEL("Real_Growth_Rate", 0, 1);                   //zero by definition, no grwoth initally
v[41]=SUML("Inventories_Sector", 1);                    //sum up the inventories of all sectors lagged 1 (already written)
	WRITEL("Aggregate_Inventories", v[41], 1);          //writes Aggregate_Inventories 
v[42]=AVEL("Avg_Productivity_Sector", 1);               //calcultes the average productivity between sectors (CORRIGIR, PONDERAR, nao precisa ponderar se todos os setores começarem com a mesma produtividade)
	WRITEL("Avg_Productivity", v[42], 1);               //writes Avg_Productivity
	WRITEL("Avg_Productivity", v[42], 2);				//writes Avg_Productivity
	WRITEL("Avg_Productivity", v[42], 3);				//writes Avg_Productivity
	WRITEL("Avg_Productivity", v[42], 4);				//writes Avg_Productivity
	WRITEL("Avg_Productivity", v[42], 5);				//writes Avg_Productivity
v[43]=AVEL("Wage", 1);                                  //calcultes the average wage between sectors (CORRIGIR, PONDERAR, nao precisa ponderar se todos os setores comecarem com o mesmo wage)
	WRITEL("Avg_Wage", v[43], 1);						//writes Avg_Wage
	WRITEL("Avg_Wage", v[43], 2);						//writes Avg_Wage	
	WRITEL("Avg_Wage", v[43], 3);						//writes Avg_Wage
	WRITEL("Avg_Wage", v[43], 4);						//writes Avg_Wage
v[44]=AVEL("Avg_Price", 1);                             //calcultes the average price between sectors (CORRIGIR, PONDERAR, nao precisa ponderar se todos os setores comecarem com o mesmo preço)
	WRITEL("Price_Index", v[44], 1);					//writes Price_Index
	WRITEL("Price_Index", v[44], 2);					//writes Price_Index
	WRITEL("Price_Index", v[44], 3);					//writes Price_Index
	WRITEL("Price_Index", v[44], 4);					//writes Price_Index
	WRITEL("Price_Index", v[44], 5);					//writes Price_Index
cur = SEARCH_CND("id_consumption_goods_sector", 1);     //searchs for the consumption goods sector
v[45]=VLS(cur, "Avg_Price", 1);                         //searchs for the avg price of the consumption goods sector
	WRITEL("Consumer_Price_Index", v[45], 1);           //writes Consumper_Price_Index
	WRITEL("Consumer_Price_Index", v[45], 2);			//writes Consumper_Price_Index
	WRITEL("Consumer_Price_Index", v[45], 3);			//writes Consumper_Price_Index
	WRITEL("Consumer_Price_Index", v[45], 4);			//writes Consumper_Price_Index
	WRITEL("Consumer_Price_Index", v[45], 5);			//writes Consumper_Price_Index
v[46]=SUML("Employment_Sector", 1);                     //sum up the employment of all sectors lagged 1 (already written)
	WRITEL("Total_Employment", v[46], 1); 				//writes Total_Employment
	WRITEL("Total_Employment", v[46], 2);				//writes Total_Employment
	WRITEL("Total_Employment", v[46], 3);				//writes Total_Employment
	WRITEL("Total_Employment", v[46], 4);				//writes Total_Employment
	WRITEL("Total_Employment", v[46], 5);				//writes Total_Employment
	WRITEL("Total_Employment", v[46], 6);				//writes Total_Employment
	WRITEL("Total_Employment", v[46], 7);				//writes Total_Employment
	WRITEL("Total_Employment", v[46], 8);				//writes Total_Employment
	WRITEL("Total_Employment", v[46], 9);				//writes Total_Employment
	WRITEL("Total_Employment", v[46], 10);				//writes Total_Employment
	WRITEL("Total_Employment", v[46], 11);				//writes Total_Employment
	WRITEL("Unemployment", v[14], 1);                   //writes Unemployment as "unemployment_target" defined as macro control paramemter
	WRITEL("Unemployment", v[14], 2);					//writes Unemployment as "unemployment_target" defined as macro control paramemter
	WRITEL("Unemployment", v[14], 3);					//writes Unemployment as "unemployment_target" defined as macro control paramemter
	WRITEL("Unemployment", v[14], 4);					//writes Unemployment as "unemployment_target" defined as macro control paramemter
	WRITEL("Unemployment", v[14], 5);					//writes Unemployment as "unemployment_target" defined as macro control paramemter
v[47]=v[46]/(1-v[14]);                                  //total number of workers is the initial emplopyment adjusted by the target unemployment rate
	WRITEL("Total_Workers", v[47], 1);			        //writes Total Workers		
	WRITEL("Total_Workers", v[47], 2);					//writes Total Workers
	WRITEL("Total_Workers", v[47], 3);					//writes Total Workers
	WRITEL("Total_Workers", v[47], 4);					//writes Total Workers
	
//Begin GDP calculation
v[50]=v[51]=v[52]=0;
v[60]=0;
CYCLE(cur, "SECTORS")
{
	v[53]=VLS(cur, "Wage", 1);
	v[54]=VS(cur, "productivity_initial");
	v[55]=VLS(cur, "Effective_Orders_Sector", 1);
	v[56]=VS(cur, "indirect_tax");
	v[59]=VS(cur, "avg_price_initial");
	v[57]=v[55]*v[59]*v[56];
	v[58]=v[53]*v[55]/v[54];
	
	v[61]=(v[59]*(1-v[56])-(v[53]/v[54]-v[94]))*v[55];
	v[50]=v[50]+v[57];//total indirect taxes
	v[51]=v[51]+v[58];//total wages
	v[52]=v[52]+v[61];//total surplus
	v[62]=VS(cur, "profit_distribution_rate");
	v[60]=v[60]+(v[62]*v[61];//distributed profits
}


v[990]=0;                                                    //initializes the CYCLE
	CYCLE(cur, "SECTORS")                                      //CYCLE trought all sectors
	{
		v[991]=0;
		v[992]=VS(cur,"productive_capacity_cost");
		v[993]=VS(cur,"Avg_Price");								                                   
		CYCLES(cur, cur1, "FIRMS")                                //initializes the second CYCLE
		{
			v[994]=VS(cur1, "Productive_Capacity");               					   //firm's wage bill
			v[995]=VS(cur1,"imitation_revenue_proportion");
			v[996]=VS(cur1,"innovation_revenue_proportion");
			v[997]=VS(cur1,"id_innovative_firm");
			v[998]=VS(cur1,"quality_innovation_revenue_proportion");
			v[999]=VS(cur1,"quality_imitation_revenue_proportion");
			v[991]=v[991]+(v[994]*v[992]*v[993])+(v[3]*v[10])*(v[995]+v[996]*v[997]+v[998]+v[999]);
		}
		v[990]=v[990]+v[991];                                          
	}
	                									             										   

//Begin Writing Classes Variables
v[77]=0;
v[74]=0;
CYCLE(cur, "CLASSES")
{
	v[70]=VS(cur, "class_profit_distribution");                						    //class parameter
	v[71]=VS(cur, "class_wage_distribution"); 												//class parameter
	v[98]=VS(cur, "class_salary_distribution");
	v[75]=VS(cur, "class_direct_tax");												//class parameter
	v[72]=(v[70]*v[60]+v[999]*v[98]+v[71]*v[51])*(1-v[75]);             							//class nominal income
		//WRITELS(cur, "Class_Nominal_Income", v[72], 1);                             //writes Class_Nominal_Income
		//WRITELS(cur, "Class_Nominal_Income", v[72], 2);								//writes Class_Nominal_Income
		//WRITELS(cur, "Class_Nominal_Income", v[72], 3);								//writes Class_Nominal_Income
		//WRITELS(cur, "Class_Nominal_Income", v[72], 4);								//writes Class_Nominal_Income
	v[73]=v[72]/v[45];                                     							//class real income is the nominal income divided by the consumer price index
		//WRITELS(cur, "Class_Real_Income", v[73], 1);								//writes Class_Real_Income
		//WRITELS(cur, "Class_Real_Income", v[73], 2);								//writes Class_Real_Income
		//WRITELS(cur, "Class_Real_Income", v[73], 3);								//writes Class_Real_Income
		//WRITELS(cur, "Class_Real_Income", v[73], 4);								//writes Class_Real_Income
	//WRITELS(cur, "Class_Debt", 0, 1);                                               //0, no debt initially
	//WRITELS(cur, "Class_Debt_Payment", 0, 1);										//0, no debt initially
	//WRITELS(cur, "Class_Autonomous_Consumption", 0, 1);	                            //TO BE ADJUSTED
	//WRITELS(cur, "Class_Financial_Assets", 0, 1);									//0, no financial assets initially
	//WRITELS(cur, "Class_Financial_Assets", 0, 2);									//0, no financial assets initially
	//WRITELS(cur, "Class_Financial_Assets", 0, 3);									//0, no financial assets initially
	//WRITELS(cur, "Class_Financial_Assets", 0, 4);									//0, no financial assets initially
	//WRITELS(cur, "Class_Financial_Assets", 0, 5);									//0, no financial assets initially
	//WRITELS(cur, "Class_Financial_Assets", 0, 6);									//0, no financial assets initially
	//WRITELS(cur, "Class_Financial_Assets", 0, 7);									//0, no financial assets initially
	//WRITELS(cur, "Class_Financial_Assets", 0, 8);									//0, no financial assets initially
	//WRITELS(cur, "Class_Financial_Assets", 0, 9);									//0, no financial assets initially
	//WRITELS(cur, "Class_Financial_Assets", 0, 10);									//0, no financial assets initially
	
	V[78]=SEARCH_INST(cur);                                                         //search the position of the current class object
	v[74]=v[74]+v[78];                                                              //sum up the number of each class	
	WRITELS(cur, "Class_Number_Workers", (v[47]*(v[78]/v[74])), 1);					//class number workers is the total number of workers time the class number, divided by the sum 
	WRITELS(cur, "Class_Number_Workers", (v[47]*(v[78]/v[74])), 2);					//class number workers is the total number of workers time the class number, divided by the sum
	WRITELS(cur, "Class_Number_Workers", (v[47]*(v[78]/v[74])), 3);					//class number workers is the total number of workers time the class number, divided by the sum
	WRITELS(cur, "Class_Number_Workers", (v[47]*(v[78]/v[74])), 4);					//class number workers is the total number of workers time the class number, divided by the sum
	
	v[76]=v[75]*v[72];                                     							//class income tax payment
	v[77]=v[77]+v[76];                                      						//total income taxes, to be used by Government
}//End CYCLE on CLASSES

//Begin Writing Government Variables
WRITEL("Unemployment_Benefits", 0, 1);
WRITEL("Goverment_Surplus_Target", 0, 1);							//initial balanced budget
WRITEL("Goverment_Surplus_Rate_Target", 0, 1);						//initial balanced budget
WRITEL("Public_Debt", 0, 1);                                        //no debt initially
WRITEL("Public_Debt", 0, 2);										//no debt initially
WRITEL("Public_Debt", 0, 3);										//no debt initially
WRITEL("Public_Debt", 0, 4);										//no debt initially
v[80]=v[77]+v[50]; 													//total taxes is the sum of income taxes and indirect taxes
	WRITEL("Total_Taxes", v[80], 1);
	WRITEL("Max_Government_Expenses_Ceiling", v[80], 1);
	WRITEL("Max_Government_Expenses_Surplus_Target", v[80], 1);
	WRITEL("Government_Expenses", v[80], 1);						//initial balanced budget
	WRITEL("Government_Wages", (0.8*v[80]), 1);						//initially, wages are 80% of government expense
	WRITEL("Government_Investment", (0.1*v[80]), 1);				//initially, investments are 10% of government expense
	WRITEL("Desired_Government_Investment", (0.1*v[80]), 1);		//initially, investments are 10% of government expense
	WRITEL("Government_Consumption", (0.1*v[80]), 1);				//initially, consumption is 10% of government expense
	WRITEL("Desired_Government_Consumption", (0.1*v[80]), 1);		//initially, consumption is 10% of government expense

//Final GDP Caculation
v[99]=VL("Government_Wages", 1);
v[100]=v[50]+v[51]+v[52]+v[99];
WRITEL("Q_GDP", v[100], 1);
WRITEL("Q_GDP", v[100], 2);	
WRITEL("Q_GDP", v[100], 3);
WRITEL("Q_GDP", v[100], 4);
WRITEL("Q_GDP", v[100], 5);
WRITEL("Q_GDP", v[100], 6);
WRITEL("Q_GDP", v[100], 7);
WRITEL("Q_GDP", v[100], 8);
WRITEL("Q_GDP", v[100], 9);
WRITEL("Q_GDP", v[100], 10);
WRITEL("GDP", (4*v[100]), 1);
WRITEL("Real_Q_GDP", (v[100]/v[44]), 1);
WRITEL("Real_Q_GDP", (v[100]/v[44]), 2);
WRITEL("Real_Q_GDP", (v[100]/v[44]), 3);
WRITEL("Real_Q_GDP", (v[100]/v[44]), 4);
WRITEL("Real_Q_GDP", (v[100]/v[44]), 5);
WRITEL("Real_Q_GDP", (v[100]/v[44]), 6);
WRITEL("Real_Q_GDP", (v[100]/v[44]), 7);
WRITEL("Real_Q_GDP", (v[100]/v[44]), 8);


PARAMETER
RESULT(0)
