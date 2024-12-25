#include "FitLib.hh"

void DrawResponse()
{
	vector<double> Peaks={263,278,305.5,355.5,385};
	
	ResponseFunction resp;
	
	
	resp.ReadResponse("LaBr");
	resp.UseExternal=true;
	resp.SubstrateFunction=TF1("sub","pol1",0,10000);
	resp.GenerateResponseFunction(220,500,Peaks);
	resp.SetNpx(2000);
	
	
	/*resp.SetParameter(0,0);
	resp.SetParameter(1,0);
	resp.SetParameter(2,0);
	resp.SetParameter(3,0);
	resp.SetParameter(4,0.2);
	resp.SetParameter(5,5000);
	resp.SetParameter(6,0.2);
	resp.SetParameter(7,5000);
	resp.SetParameter(8,0.2);
	resp.SetParameter(9,5000);
	resp.SetParameter(10,0.2);
	resp.SetParameter(11,5000);*/
	
	/*resp.SetParameter(0,0);
	resp.SetParameter(1,0.2);
	resp.SetParameter(2,5000);
	resp.SetParameter(3,0.2);
	resp.SetParameter(4,5000);
	resp.SetParameter(5,0.2);
	resp.SetParameter(6,5000);
	resp.SetParameter(7,0.2);
	resp.SetParameter(8,5000);*/
	
	
	/*par0 200000
par1 -0.1
par2 0.135902
par3 0.4878
par4 4.75842e+06
par5 9.99996e+06
par6 0.458399
par7 5.23115e+06
par8 9.99998e+06
par9 0.498138
par10 6.13842e+06
par11 9.99999e+06
par12 0.494848
par13 5.1607e+06
par14 9.99998e+06
par15 0.468554
par16 4.5638e+06
par17 9.99996e+06
*/
	
resp.SetParameter(0,200000);
resp.SetParameter(1,-0.1);
resp.SetParameter(2,0.135902);
resp.SetParameter(3,0.4878);
resp.SetParameter(4,4.75842e+06);
resp.SetParameter(5,9.99996e+06);
resp.SetParameter(6,0.458399);
resp.SetParameter(7,5.23115e+06);
resp.SetParameter(8,9.99998e+06);
resp.SetParameter(9,0.498138);
resp.SetParameter(10,6.13842e+06);
resp.SetParameter(11,9.99999e+06);
resp.SetParameter(12,0.494848);
resp.SetParameter(13,5.1607e+06);
resp.SetParameter(14,9.99998e+06);
resp.SetParameter(15,0.468554);
resp.SetParameter(16,4.5638e+06);
resp.SetParameter(17,9.99996e+06);
	
	/*resp.SetParameter(0,200000);
	resp.SetParameter(1,0.2);
	resp.SetParameter(2,5000);
	resp.SetParameter(3,5000);
	resp.SetParameter(4,0.2);
	resp.SetParameter(5,5000);
	resp.SetParameter(6,5000);
	resp.SetParameter(7,0.2);
	resp.SetParameter(8,5000);
	resp.SetParameter(9,5000);
	resp.SetParameter(10,0.2);
	resp.SetParameter(11,5000);
	resp.SetParameter(12,5000);*/
	
	resp.Draw();
	resp.PrintParameters();
	gPad->GetCanvas()->Print("func.pdf","pdf");
}
