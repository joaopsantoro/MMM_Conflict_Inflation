/*****CAPITAL GOODS VARIABLES*****/


EQUATION("Capital_Good_Production")
/*
Depends on the rule form using capital goods and the firm's effective production
*/
	V("Effective_Production");
RESULT(CURRENT)


EQUATION("Capital_Good_Acumulated_Production")
/*
Acumulated Production of one capital good, calculated in the middle of the period
*/
	v[0]=V("Capital_Good_Production");                     //current production of the capital good
	v[1]=VL("Capital_Good_Acumulated_Production",1);       //acumulated production of the capital good in the last period
	v[2]=V("capital_good_date_birth");                     //capital good date of birth
	if(v[2]==(double)t)                                    //if t is equal to the capital good date of birth
		v[3]=0;                                              //acumulated production is zero
	else                                                   //if t is higher then capital good date of birth
		v[3]=v[1]+v[0];                                      //acumulated production is the acumulated production in the last period plus the urrent period production
RESULT(v[3])


EQUATION("Learning")
/*
Capital good's productivity increase with accumulated production due to a learning process.
*/
	v[0]=V("bonus");                                       //??
	v[1]=V("speed_learning");                              //speed of learning of the capital good
	v[2]=VL("Capital_Good_Acumulated_Production",1);       //capital good's acumulated production
	v[3]=1+v[0]*(1-exp(-v[1]*v[2]));                       //the learning of the capital good depends on the acumulated production and the speed
RESULT(v[3])


EQUATION("Capital_Good_Productivity")
/*
Capital good's productivity increase with accumulated production due to a learning process.
*/   
	v[0]=V("capital_good_productivity_initial");           //initial productivity of the capital good
	v[1]=V("Learning");                                    //learning of the capital good
	v[2]=V("capital_good_date_birth");                     //capital good date of birth
	if((double)t==v[2])                                    //if t equals the capital good date of birth
		v[3]=v[0];                                           //capital good's productivity equals the initial one
	else                                                   //if t is higher then capital good date of birth
		v[3]=v[0]*v[1];                                      //current productivity depends on the initial value multiplied by the learning factor
RESULT(v[3])


EQUATION("Capital_Good_Replacement")
	V("Replecement_2");
RESULT(CURRENT)


EQUATION("Sum_Id_A_2")
/*
Capital Variable
*/
	v[0]=V("id_a_2");
	v[1]=VL("Sum_Id_A_2",1);
	v[2]=v[1]+v[0];
RESULT(v[2])
