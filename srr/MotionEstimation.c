#include "MotionEstimation.h"
#include <enerc.h>

accept_roi_begin();
MV mv[l*l] ;

HRESULT GetMotionVectors()
{
	HRESULT hr = SUCCESS;

    //MVs for New Emilly X and Y sign inverted ...
	#ifdef NEW_EMILLY
    mv[0].x = 0.0;             mv[0].y = 0.0;
     mv[1].x = 0.009148403;     mv[1].y = -0.086757677;		//EmillyCropped1.yuv
	//mv[1].x = -1.827204478;     mv[1].y = -0.761884276;			//37
    mv[2].x = 0.040733158;     mv[2].y = 0.011492507;			//EmillyCropped2.yuv     
	//mv[2].x = -1.802421578;     mv[2].y = -1.230462666;			//38
    mv[3].x = -0.048875302;    mv[3].y = -0.186323436;		//EmillyCropped3.yuv
	//mv[3].x = 1.449516433;     mv[3].y = 0.660153588;			//41
    mv[4].x = 0.005573949;     mv[4].y = 0.386189328;
    mv[5].x = 0.045842018;     mv[5].y = -0.518102983;
    mv[6].x = 0.02965692;      mv[6].y = -0.414463995;//same as 5
    mv[7].x = 0.09061336;      mv[7].y = -0.75197438;

    mv[8].x = 0.207462823;    mv[8].y = -0.548811938; //29
    mv[9].x = -0.343860522;   mv[9].y = -0.467559657; //39
    mv[10].x = 0.32647443;    mv[10].y = 0.284443098; //40
    mv[11].x = 0.759654339;   mv[11].y = 0.347553879; //43
    mv[12].x = 0.229607765;   mv[12].y = 0.441814728; //44
    mv[13].x = -0.447298949;  mv[13].y = 0.415895238; //45
    mv[14].x = 0.934070209;   mv[14].y = 0.732540133; //51
    mv[15].x = 0.62258976;    mv[15].y = 0.953930012; //54
	#endif

    // MVs for Text, X and Y sign inverted
	#ifdef NEW_TEXT
    mv[0].x = 0.0;           mv[0].y = 0.0;
    mv[1].x = -0.40312963;     mv[1].y = -0.327684712;  
    mv[2].x = 0.369518421;     mv[2].y = 0.123605471; 
    mv[3].x = 0.005521061;     mv[3].y = 0.236812995;   
    mv[4].x = 0.39572904;      mv[4].y = 0.054107018;
    mv[5].x = -0.344631221;    mv[5].y = 0.015067881;

    mv[6].x = 0.048842692;     mv[6].y = -0.355711012;
    mv[7].x = -0.282097671;    mv[7].y = 0.160583365;
    mv[8].x = -0.573036483;    mv[8].y = 0.458705302;
    mv[9].x = -0.507088846;    mv[9].y = 0.457264554;
    mv[10].x = 0.084349387;    mv[10].y = -0.181000754;

    mv[11].x = 0.368631451;    mv[11].y = 0.093344973;
    mv[12].x = -0.187997499;   mv[12].y = -0.046971113;
    mv[13].x = -0.43772425;    mv[13].y = -0.207956537;
    mv[14].x = -0.16304156;    mv[14].y = -0.062272953;
    mv[15].x = 0.325152457;    mv[15].y = 0.053911277;
	#endif
	
    //MVs for Disk X and Y inverted..
	#ifdef DISC
    mv[0].x = 0.0;            mv[0].y = 0.0;
    mv[1].x = 0.324907329;      mv[1].y = 0.017724103;  
    mv[2].x = 0.491087527;      mv[2].y = -0.291600108; 
    mv[3].x = -0.103722459;     mv[3].y = -0.077036535;   
    mv[4].x = 0.252868971;      mv[4].y = -0.244973091;
    mv[5].x = -0.403087388;     mv[5].y = 0.169310682;

    mv[6].x = -0.100701385;     mv[6].y = 0.048505268;
    mv[7].x = 0.200306454;      mv[7].y = 0.211738679;
    mv[8].x = -0.259893637;     mv[8].y = 0.627925343;
    mv[9].x = 0.070004641;      mv[9].y = -0.059632949;
    mv[10].x = -0.525034406;    mv[10].y = 0.399370331;

    mv[11].x = -0.365356807;    mv[11].y = 0.858043154;
    mv[12].x = 0.029812749;     mv[12].y = -0.182717363;
    mv[13].x = 0.349747382;     mv[13].y = -0.635002092;
    mv[14].x = -0.496331635;    mv[14].y = 0.716291858;
    mv[15].x = 0.310864634;     mv[15].y = 0.146176664;
	#endif
	
	//alpaca
	#ifdef ALPACA
	mv[0].x = 0.0;              mv[0].y = 0.0; // 0 0
	mv[1].x = -0.02843056;      mv[1].y = -0.2743666246; // 0 75 
	mv[2].x = -0.058024477;     mv[2].y = -0.3655778419; // 0 75
	mv[3].x = -0.043927980;     mv[3].y = -0.1224764155; // 0 75
	mv[4].x = 1.275429984;    mv[4].y = -0.6050229161; //25 50 - 19
	mv[5].x = 0.016445465;      mv[5].y = 0.03444616; // 0 0

	mv[6].x = 0.194892835;     mv[6].y = -0.162128182; // 25 75
	mv[7].x = 1.300001062;     mv[7].y = -0.229766909; // 25 75
	mv[8].x = 2.158751811;     mv[8].y = 0.08457027; // 25 0
	mv[9].x = 2.09199199;      mv[9].y = -0.0135341827; // 0 0
	mv[10].x = 1.986179460;    mv[10].y = -0.078173724; // 0 0

	mv[11].x = 1.928547066;    mv[11].y = -0.0947577692; // 0 0
	//mv[12].x = 1.913917012;    mv[12].y = -0.1996146342;
	mv[12].x = 1.728815676;    mv[12].y = -0.672244286; // 75 50 - 20
	mv[13].x = 1.768826559;    mv[13].y = -0.327647024; //75 25
	mv[14].x = 1.304180292;    mv[14].y = -0.473484152; // 25 50
	mv[15].x = 1.297546810;    mv[15].y = -0.5607566290; //25 50
	#endif

	//alpaca
	#ifdef ALPACA2
	mv[0].x = 0.0;              mv[0].y = 0.0;				// 00 00 - 00
	mv[1].x = 1.020149247;      mv[1].y = -0.822487852;		// 00 25 - 25
	mv[2].x = 1.967090921;      mv[2].y = -0.573479683414;	// 00 50 - 30
	mv[3].x = -0.02843056;      mv[3].y = -0.2743666246;	// 00 75 - 01

	mv[4].x = 2.158751811;      mv[4].y = 0.08457027;		// 25 00 - 08
	mv[5].x = 0.266172101;      mv[5].y = -0.8614852;		// 25 25 - 38
	mv[6].x = 1.279399105;      mv[6].y = -0.489758743;		// 25 50 - 16
	mv[7].x = 1.300001062;      mv[7].y = -0.229766909;		// 25 75 - 07

	mv[8].x = 1.557908057;      mv[8].y = -0.07136310946;	// 50 00 - 32
	mv[9].x = 1.275429984;      mv[9].y = -0.6050229161;	// 50 25 - 19 - erroneous
	mv[10].x = 1.695538581;     mv[10].y = -0.45663599155;	// 50 50 - 21
	mv[11].x = 1.408386000;     mv[11].y = -1.33156216864;	// 50 75 - 28

	mv[12].x = -0.846709936;    mv[12].y = -0.0842109682;		// 75 00 - 33
	mv[13].x = -1.768826559;    mv[13].y = 0.327647024;		// 75 25 - 13
	mv[14].x = -1.728815676;    mv[14].y = 0.672244286;		// 75 50 - 20
	mv[15].x = -0.755006420;    mv[15].y = 1.218292846;		// 75 75 - 41
	#endif

	//bookcase
	#ifdef BOOKCASE
	mv[0].x = 0;					mv[0].y = 0;
	mv[1].x = 0.531137868870443;	mv[1].y = -0.0117688640951985;
	mv[2].x = 0.634886139062255;	mv[2].y = 0.0873882534147330;
	mv[3].x = 0.143068262303510;	mv[3].y = 0.223712373286199;
	mv[4].x = -0.68289667533228;	mv[4].y = -0.129959521844261;
	mv[5].x = -0.98377957861640;	mv[5].y = -0.0718553305112248;
	mv[6].x = -0.84252216927058; 	mv[6].y = 0.327220892072816;
	mv[7].x = -0.57988579581242; 	mv[7].y = 0.435059768736935;
	mv[8].x = -0.46640086692112; 	mv[8].y = 0.207584250951015;
	mv[9].x = -0.34733646529133; 	mv[9].y = 0.0886764537836455;
	mv[10].x = -0.41276343344593; 	mv[10].y = 0.0771081166068011;
	mv[11].x = -0.27153253669202; 	mv[11].y = 0.345829486400742;
	mv[12].x = -0.09380648686397; 	mv[12].y = 0.677513149830428;
	mv[13].x = 0.199582495552306;	mv[13].y = 0.934656643140873;
	mv[14].x = 0.239663325378564;	mv[14].y = 0.935931507429273;
	mv[15].x = 0.314868950652527;	mv[15].y = 1.04927675328939;
	#endif

	//LightHouse
	#ifdef LIGHTHOUSE
	mv[0].x = 0; mv[0].y = 0;
	mv[1].x = 0.2822; mv[1].y = -0.0045;
	mv[2].x = 0.5553; mv[2].y = -0.0064;
	mv[3].x = 0.7783; mv[3].y = -0.0076;
	mv[4].x = 0.0014;   mv[4].y = 0.2633;
	mv[5].x = 0.2760;   mv[5].y = 0.2590;
	mv[6].x = 0.5548;   mv[6].y = 0.2600;
	mv[7].x = 0.7792;   mv[7].y = 0.2647;
	mv[8].x = -0.0013;   mv[8].y = 0.5024;
	#endif

	//Face_adyoron
	#ifdef FACE
	mv[0].x = 0;         mv[0].y = 0;
	mv[1].x = -0.0075;    mv[1].y = 0.0009;
	mv[2].x = -0.1542;    mv[2].y = 0.0699;
	mv[3].x = -0.2861;    mv[3].y = 0.1367;
	mv[4].x = -0.2982;    mv[4].y = 0.1514;
	mv[5].x = -0.3458;    mv[5].y = 0.1722;
	mv[6].x = -0.4354;    mv[6].y = 0.2261;
	mv[7].x = -0.4842;    mv[7].y = 0.2276;
	mv[8].x = -0.4883;    mv[8].y = 0.2293;
	mv[9].x = -0.4881;    mv[9].y = 0.2293;
	mv[10].x = -0.5358;    mv[10].y = 0.2286;
	mv[11].x = -0.6708;    mv[11].y = 0.3610;
	mv[12].x = -0.6920;    mv[12].y = 0.3843;
	mv[13].x = -0.6906;    mv[13].y = 0.3835;
	mv[14].x = -0.7101;    mv[14].y = 0.4114;
	mv[15].x = -0.7091;    mv[15].y = 0.4076;
	#endif

// eia
	#ifdef EIA
	mv[0].x = 0; mv[0].y = 0;
	mv[1].x = 0.2516;    mv[1].y = 0.0096;
	mv[2].x = 0.5033;    mv[2].y = 0.0036;
	mv[3].x = 0.7614;    mv[3].y = 0.0024;
	mv[4].x = 0.0022;    mv[4].y = 0.2426;
	mv[5].x = 0.2531;    mv[5].y = 0.2489;
	mv[6].x = 0.5018;    mv[6].y = 0.2412;
	mv[7].x = 0.7561;   mv[7].y = 0.2446;
	mv[8].x = 0.0055;   mv[8].y = 0.5070;
	mv[9].x = 0.2430;   mv[9].y = 0.5162;
	mv[10].x = 0.5106;   mv[10].y = 0.5218;
	mv[11].x = 0.7654;   mv[11].y = 0.5108;
	mv[12].x = -0.0036;   mv[12].y = 0.770;
	mv[13].x = 0.2457;    mv[13].y = 0.776;
	mv[14].x = 0.5030;   mv[14].y = 0.7729;
	mv[15].x = 0.7603;    mv[15].y = 0.7720;
	#endif

	// synthetic
	#ifdef SYNTHETIC1
	mv[0].x = 0; mv[0].y = 0;
	mv[1].x = 0.25;    mv[1].y = 0;
	mv[2].x = 0.50;    mv[2].y = 0.0;
	mv[3].x = 0.75;    mv[3].y = 0.0;
	mv[4].x = 0.0;    mv[4].y = 0.25;
	mv[5].x = 0.25;    mv[5].y = 0.25;
	mv[6].x = 0.50;    mv[6].y = 0.25;
	mv[7].x = 0.75;   mv[7].y = 0.25;
	mv[8].x = 0.00;   mv[8].y = 0.50;
	mv[9].x = 0.25;   mv[9].y = 0.50;
	mv[10].x = 0.50;   mv[10].y = 0.50;
	mv[11].x = 0.75;   mv[11].y = 0.50;
	mv[12].x = 0.0;   mv[12].y = 0.75;
	mv[13].x = 0.25;    mv[13].y = 0.75;
	mv[14].x = 0.50;   mv[14].y = 0.75;
	mv[15].x = 0.75;    mv[15].y = 0.75;
	#endif

	accept_roi_end();
    return hr;	
}