/*
 *  Scilab ( http://www.scilab.org/ ) - This file is part of Scilab
 *  Copyright (C) 2008-2008 - INRIA - Allan SIMON
 *
 *  This file must be used under the terms of the CeCILL.
 *  This source file is licensed as described in the file COPYING, which
 *  you should have received as part of this distribution.  The terms
 *  are also available at
 *  http://www.cecill.info/licences/Licence_CeCILL_V2-en.txt
 *
 */

#include "atan2.h"
#include <assert.h>
#include <stdio.h>
#define SIZE 100 


static void satan2sTest ( void ) 
{


   int i = 0 ;
   float Fin1[SIZE] = 
{0.0373321f,0.4293466f,0.3157233f,0.3682477f,0.1458774f,0.6768379f,0.5261979f,0.4003626f,
0.0029108f,0.3068181f,0.7902694f,0.9577950f,0.6689271f,0.2929616f,0.8223899f,0.0179846f,
0.8710701f,0.3181024f,0.5724473f,0.5738658f,0.3492018f,0.7067298f,0.3599201f,0.4052311f,
0.6140811f,0.6524047f,0.0295171f,0.5668896f,0.7114017f,0.4588491f,0.4720517f,0.0623731f,
0.0854401f,0.0134564f,0.3543002f,0.6719395f,0.1360619f,0.2119744f,0.4015942f,0.4036219f,
0.5628382f,0.5531093f,0.0768984f,0.5360758f,0.0900212f,0.6218026f,0.0001215f,0.7219727f,
0.6661293f,0.6799288f,0.9514125f,0.1206901f,0.7318910f,0.0831662f,0.8021909f,0.0290492f,
0.6502991f,0.7427882f,0.2176611f,0.9788486f,0.8925237f,0.3511275f,0.4745619f,0.7699462f,
0.0734342f,0.5894619f,0.2378993f,0.4076361f,0.4304818f,0.0370717f,0.6404148f,0.4130743f,
0.8396902f,0.0002195f,0.5085374f,0.4754997f,0.9625065f,0.9798011f,0.0785698f,0.9150032f,
0.6172610f,0.9964195f,0.0468599f,0.9245926f,0.9689865f,0.4916290f,0.2977053f,0.0603055f,
0.6313472f,0.0241030f,0.1527438f,0.9481178f,0.2744266f,0.4794727f,0.4855768f,0.6764004f,
0.8321250f,0.0125876f,0.5453780f,0.8426717f};
   float Fin2[]  = 
{0.9029165f,0.4409482f,0.8332359f,0.7233976f,0.4377150f,0.3080607f,0.8749813f,0.5355882f,
0.3085999f,0.3354632f,0.2342486f,0.2589412f,0.8521509f,0.4821739f,0.6095218f,0.9872823f,
0.9811427f,0.3303114f,0.3589146f,0.2780528f,0.9583482f,0.0156363f,0.2964352f,0.4685935f,
0.4262021f,0.4217656f,0.1034854f,0.4279759f,0.7860729f,0.8568082f,0.1993437f,0.7131302f,
0.5208952f,0.9311723f,0.4143836f,0.5980196f,0.5549106f,0.8552953f,0.3097751f,0.9446128f,
0.2442680f,0.8760447f,0.4874215f,0.3844019f,0.0922345f,0.0705419f,0.7338807f,0.7792181f,
0.7827638f,0.2161568f,0.3420198f,0.4300938f,0.6261753f,0.9554251f,0.4541551f,0.0029223f,
0.0106921f,0.9746371f,0.7704261f,0.6396631f,0.9535886f,0.4148483f,0.4661540f,0.2238455f,
0.3456973f,0.2340624f,0.6619341f,0.2691180f,0.9830249f,0.7393351f,0.2902136f,0.3995950f,
0.9792278f,0.0075514f,0.7021023f,0.8907506f,0.6526974f,0.4136229f,0.8581691f,0.2396090f,
0.4820042f,0.9848586f,0.4469722f,0.2329814f,0.2234514f,0.8002565f,0.7750734f,0.4825007f,
0.7844883f,0.1534679f,0.7722877f,0.8952022f,0.9467326f,0.6981826f,0.9559161f,0.0484017f,
0.5323521f,0.2946867f,0.6977137f,0.9376204f};

   float Fout[SIZE] ;

   float Result[] = 
{0.0413226f,0.7720683f,0.3621962f,0.4708637f,0.3216938f,1.1436704f,0.5414350f,0.6419116f,
0.0094320f,0.7408287f,1.2826307f,1.3067571f,0.6655192f,0.5459780f,0.9329774f,0.0182142f,
0.7260404f,0.7665715f,1.0107725f,1.1196046f,0.3494266f,1.5486751f,0.8818216f,0.7130133f,
0.9640758f,0.9969006f,0.2778515f,0.9241318f,0.7355747f,0.4916683f,1.1712215f,0.0872419f,
0.1625778f,0.0144500f,0.7073927f,0.8435390f,0.2404522f,0.2429425f,0.9137623f,0.4038071f,
1.1613329f,0.5631677f,0.1564760f,0.9487081f,0.7732547f,1.4578319f,0.0001656f,0.7472834f,
0.7050723f,1.2629896f,1.2256956f,0.2735775f,0.8630843f,0.0868274f,1.0556435f,1.4705351f,1.554356f,
0.6512114f,0.2753444f,0.9919749f,0.7523326f,0.7024002f,0.7943357f,1.2878668f,0.2093122f,
1.1928114f,0.3450245f,0.9872899f,0.4127591f,0.0501000f,1.1453135f,0.8019831f,0.7088335f,
0.0290531f,0.6268536f,0.4903355f,0.9749046f,1.1713423f,0.0913007f,1.3146805f,0.9078258f,
0.7912332f,0.1044568f,1.3239524f,1.3441551f,0.5508964f,0.3667243f,0.1243404f,0.6776540f,
0.1557832f,0.1952610f,0.8140970f,0.2821348f,0.6017738f,0.4700034f,1.4993603f,1.0016604f,
0.0426892f,0.6634603f,0.7321154f} ;


   
	

	
	

   for ( i = 0 ; i < SIZE ; ++i)
      {
            Fout[i] =    satan2s( Fin1[i], Fin2[i] ); 
		 printf ( "%e - %e\n"  , Fout[i] , Result[i] );
         assert (  fabs ( Fout[i] - Result[i] ) / fabs( Fout[i]) < 3e-4 );
      }

}

static void datan2sTest ( void ) 
{


   int i = 0 ;
   double Fin1[SIZE] = 
{0.70964269945397973061,0.6610225578770041465759,0.7252350724302232265472,
0.510143497958779335022,0.2824866441078484058380,0.2214915128424763679504,
0.5767575385980308055878,0.7048253491520881652832,0.5607945644296705722809,
0.3628880484029650688171,0.3088326244615018367767,0.9813414867967367172241,
0.7428482254035770893097,0.1616391474381089210510,0.3652521963231265544891,
0.3835070468485355377197,0.1169181005097925662994,0.8911246126517653465271,
0.0634272000752389431000,0.6263941843062639236450,0.6807702076621353626251,
0.2588596837595105171204,0.4394804346375167369843,0.8598818778991699218750,
0.5482823201455175876617,0.8135995296761393547058,0.4898237003944814205170,
0.0240026097744703292847,0.7369195525534451007843,0.2411156157031655311584,
0.1529693226329982280731,0.2648359201848506927490,0.4298193217255175113678,
0.7673939457163214683533,0.8753260499797761440277,0.3796988371759653091431,
0.3062356826849281787872,0.3880051793530583381653,0.1047293278388679027557,
0.7603831812739372253418,0.0340930395759642124176,0.1423966242000460624695,
0.5554559468291699886322,0.8031897451728582382202,0.5183992316015064716339,
0.1518561029806733131409,0.5884730662219226360321,0.2545093484222888946533,
0.9992679939605295658112,0.6398976957425475120544,0.5506716123782098293304,
0.4607007671147584915161,0.5933007937856018543243,0.6538193570449948310852,
0.4168340521864593029022,0.9910155385732650756836,0.3720780410803854465485,
0.7061824081465601921082,0.5780865414999425411224,0.602319641038775444031,
0.5715096746571362018585,0.0549629041925072669983,0.1205854485742747784,
0.0143620483577251434326,0.0257951230742037296295,0.8411248764023184776306,
0.4381882525049149990082,0.4643401596695184707642,0.4197426405735313892365,
0.8023654492571949958801,0.5228588166646659374237,0.5095121040940284729004,
0.4531980180181562900543,0.7817818326875567436218,0.776557037141174077988,
0.0466059204190969467163,0.5113326688297092914581,0.7502101892605423927307,
0.6883628661744296550751,0.0167756117880344390869,0.9345410899259150028229,
0.5609863763675093650818,0.2205847105942666530609,0.7648540753871202468872,
0.4816976976580917835236,0.1558785634115338325500,0.2476022052578628063202,
0.5216529071331024169922,0.0805230387486517429352,0.4409417239949107170105,
0.8911933614872395992279,0.9780590813606977462769,0.4588093762286007404327,
0.5510440031066536903381,0.0960960905067622661591,0.4196785055100917816162,
0.7502556503750383853912,0.7218149593099951744080,0.2895541018806397914886,
0.3907764498144388198853}
;
   double Fin2[SIZE] = 
{0.6686618146486580371857,0.4877656819298863410950,0.4685971769504249095917,
0.3562648519873619079590,0.3442325466312468051910,0.4253307832404971122742,
0.5588058172725141048431,0.3304864969104528427124,0.4157403339631855487823,
0.1595822656527161598206,0.3883102680556476116180,0.9415460713207721710205,
0.4722979352809488773346,0.8533652639016509056091,0.1207739165984094142914,
0.8999380934983491897583,0.4384902161546051502228,0.8976056622341275215149,
0.4911110657267272472382,0.3402217179536819458008,0.9966153600253164768219,
0.0215395865961909294128,0.6876890822313725948334,0.0044924151152372360229,
0.6397854541428387165070,0.5416147718206048011780,0.2247649203054606914520,
0.7364005260169506072998,0.4496364505030214786530,0.9678138038143515586853,
0.6489060199819505214691,0.2544666919857263565063,0.1923975017853081226349,
0.6861492367461323738098,0.4231455805711448192596,0.6734441593289375305176,
0.8270696722902357578278,0.9360805852338671684265,0.8326222090981900691986,
0.7424779590219259262085,0.0194640238769352436066,0.8016031915321946144104,
0.2554539437405765056610,0.2688109613955020904541,0.7558490769006311893463,
0.4347589677199721336365,0.6425966522656381130219,0.6957868058234453201294,
0.6499576461501419544220,0.2303190128877758979797,0.5504368054680526256561,
0.3038997054100036621094,0.0371030517853796482086,0.1703881053254008293152,
0.5698686256073415279388,0.0036411266773939132690,0.4491547052748501300812,
0.0576810697093605995178,0.4956056098453700542450,0.1888933442533016204834,
0.5641230703331530094147,0.8562210192903876304626,0.0794764286838471889496,
0.6196198705583810806274,0.2241039988584816455841,0.8582094730809330940247,
0.7114551994018256664276,0.8026027604937553405762,0.6153324418701231479645,
0.8958183480426669120789,0.8721761344932019710541,0.8389767911285161972046,
0.2040955354459583759308,0.3166538262739777565002,0.7006825651042163372040,
0.2073105163872241973877,0.5222550616599619388580,0.9416420971974730491638,
0.52116033947095274925,0.4509841967374086380005,0.3961292845197021961212,
0.7240869747474789619446,0.6724055963568389415741,0.2386146038770675659180,
0.7124841609038412570953,0.3286493895575404167175,0.4837769134901463985443,
0.7662767004221677780151,0.3153839264996349811554,0.3489987561479210853577,
0.7413818310014903545380,0.9702721945941448211670,0.1276510567404329776764,
0.3828862151131033897400,0.4882477498613297939301,0.5191949699074029922485,
0.0906856027431786060333,0.6833897503092885017395,0.5022272053174674510956,
0.0540433898568153381348}

 ;
   double Fout[SIZE]  ;
   
double  Result[] = 
{0.8151222298353714146302,0.9350871051642664077974,0.997145470042032466829,
0.9611705131081605957277,0.6871926567255678408586,0.48011041457317088499,
0.8012054946208865269242,1.132343901220193460588,0.9328596693816280094325,
1.1564937347686861102147,0.6718834468335361798097,0.8060908633813578250127,
1.00447314922565955619,0.1871960989477313985763,1.25145462350922120898,
0.4028428263783953022781,0.2605755136377292391359,0.781774911019853857574,
0.1284394521185465987134,1.073232720478735968683,0.5992812665317298614909,
1.4877780687994013320008,0.5686520903625903455847,1.5655719182360376962038,
0.7085314645036139280521,0.9834619198256084882104,1.140591448484360226345,
0.0325829683756781798842,1.0229420689159220980713,0.2441637219657823987262,
0.2315075947889858876128,0.805363112922971136065,1.1499199282073593320064,
0.8412343166232832958329,1.1205046812517129861675,0.5133888656295326757828,
0.3546137657219728400726,0.3929433432393027447738,0.1251254110872664360166,
0.7973116893083483924798,1.0520419606393343059381,0.1758058639068769690716,
1.1397404905667376517897,1.2478349146446092721163,0.6011661864384908460224,
0.336040406143340686373,0.7414617770855178591205,0.35066862507579671382,
0.994116233357116407809,1.225301837543258720586,0.7856114093437986944934,
0.9876695123648748797507,1.5083409965621017434501,1.3158623593693956621564,
0.6315271916809107599633,1.5671222065095873343665,0.6918174612768925868522,
1.4892971216950183777072,0.8620674912261098166155,1.2669007116100525767166,
0.7919024670030506696250,0.0641044712091229373918,0.9880588227443989346455,
0.0231746556747607738991,0.1145990356665423787197,0.7753448027391854902035,
0.5520317684396915947076,0.5244928157781221234046,0.5986382937223412303851,
0.730422528982288210564,0.5400426833033002971263,0.5457711699419741657735,
1.1476553996273199942380,1.1859516842120860768972,0.8367154013891151542737,
0.2211356254003243038131,0.7748311007637324054897,0.6727280587907351616650,
0.9227659311220508531193,0.0371806395770535452749,1.16987833340959523909,
0.6591538541213141089159,0.3169908006212094342402,1.2683907108855461132180,
0.5944925989956957312899,0.4428774366489620084586,0.4730514714397818787361,
0.5976982909559278578371,0.2499770826480406105130,0.9012690725036259786762,
0.8769058262572594353301,0.7893948375778501169719,1.2994367291712400902526,
0.9635433198261218468161,0.1943343662922066283905,0.6797968572652465235606,
1.4505069462951736269929,0.8127362698086932901731,0.5229909037180106023968,
1.4333705873570850020116};

	
	
   for ( i = 0 ; i < SIZE ; ++i)
      {
            Fout[i] =    datan2s( Fin1[i], Fin2[i] ); 
		 printf ( "%e - %e\n"  , Fout[i] , Result[i] );
         assert (  fabs ( Fout[i] - Result[i] ) / fabs( Fout[i]) < 1e-16 );
      }

}


static void satan2aTest ( void ) 
{


   int i = 0 ;
   float Fin1[SIZE] = 
{0.0373321f,0.4293466f,0.3157233f,0.3682477f,0.1458774f,0.6768379f,0.5261979f,0.4003626f,
0.0029108f,0.3068181f,0.7902694f,0.9577950f,0.6689271f,0.2929616f,0.8223899f,0.0179846f,
0.8710701f,0.3181024f,0.5724473f,0.5738658f,0.3492018f,0.7067298f,0.3599201f,0.4052311f,
0.6140811f,0.6524047f,0.0295171f,0.5668896f,0.7114017f,0.4588491f,0.4720517f,0.0623731f,
0.0854401f,0.0134564f,0.3543002f,0.6719395f,0.1360619f,0.2119744f,0.4015942f,0.4036219f,
0.5628382f,0.5531093f,0.0768984f,0.5360758f,0.0900212f,0.6218026f,0.0001215f,0.7219727f,
0.6661293f,0.6799288f,0.9514125f,0.1206901f,0.7318910f,0.0831662f,0.8021909f,0.0290492f,
0.6502991f,0.7427882f,0.2176611f,0.9788486f,0.8925237f,0.3511275f,0.4745619f,0.7699462f,
0.0734342f,0.5894619f,0.2378993f,0.4076361f,0.4304818f,0.0370717f,0.6404148f,0.4130743f,
0.8396902f,0.0002195f,0.5085374f,0.4754997f,0.9625065f,0.9798011f,0.0785698f,0.9150032f,
0.6172610f,0.9964195f,0.0468599f,0.9245926f,0.9689865f,0.4916290f,0.2977053f,0.0603055f,
0.6313472f,0.0241030f,0.1527438f,0.9481178f,0.2744266f,0.4794727f,0.4855768f,0.6764004f,
0.8321250f,0.0125876f,0.5453780f,0.8426717f};
   float Fin2[]  = 
{0.9029165f,0.4409482f,0.8332359f,0.7233976f,0.4377150f,0.3080607f,0.8749813f,0.5355882f,
0.3085999f,0.3354632f,0.2342486f,0.2589412f,0.8521509f,0.4821739f,0.6095218f,0.9872823f,
0.9811427f,0.3303114f,0.3589146f,0.2780528f,0.9583482f,0.0156363f,0.2964352f,0.4685935f,
0.4262021f,0.4217656f,0.1034854f,0.4279759f,0.7860729f,0.8568082f,0.1993437f,0.7131302f,
0.5208952f,0.9311723f,0.4143836f,0.5980196f,0.5549106f,0.8552953f,0.3097751f,0.9446128f,
0.2442680f,0.8760447f,0.4874215f,0.3844019f,0.0922345f,0.0705419f,0.7338807f,0.7792181f,
0.7827638f,0.2161568f,0.3420198f,0.4300938f,0.6261753f,0.9554251f,0.4541551f,0.0029223f,
0.0106921f,0.9746371f,0.7704261f,0.6396631f,0.9535886f,0.4148483f,0.4661540f,0.2238455f,
0.3456973f,0.2340624f,0.6619341f,0.2691180f,0.9830249f,0.7393351f,0.2902136f,0.3995950f,
0.9792278f,0.0075514f,0.7021023f,0.8907506f,0.6526974f,0.4136229f,0.8581691f,0.2396090f,
0.4820042f,0.9848586f,0.4469722f,0.2329814f,0.2234514f,0.8002565f,0.7750734f,0.4825007f,
0.7844883f,0.1534679f,0.7722877f,0.8952022f,0.9467326f,0.6981826f,0.9559161f,0.0484017f,
0.5323521f,0.2946867f,0.6977137f,0.9376204f};

   float Fout[SIZE] ;

   float Result[] = 
{0.0413226f,0.7720683f,0.3621962f,0.4708637f,0.3216938f,1.1436704f,0.5414350f,0.6419116f,
0.0094320f,0.7408287f,1.2826307f,1.3067571f,0.6655192f,0.5459780f,0.9329774f,0.0182142f,
0.7260404f,0.7665715f,1.0107725f,1.1196046f,0.3494266f,1.5486751f,0.8818216f,0.7130133f,
0.9640758f,0.9969006f,0.2778515f,0.9241318f,0.7355747f,0.4916683f,1.1712215f,0.0872419f,
0.1625778f,0.0144500f,0.7073927f,0.8435390f,0.2404522f,0.2429425f,0.9137623f,0.4038071f,
1.1613329f,0.5631677f,0.1564760f,0.9487081f,0.7732547f,1.4578319f,0.0001656f,0.7472834f,
0.7050723f,1.2629896f,1.2256956f,0.2735775f,0.8630843f,0.0868274f,1.0556435f,1.4705351f,1.554356f,
0.6512114f,0.2753444f,0.9919749f,0.7523326f,0.7024002f,0.7943357f,1.2878668f,0.2093122f,
1.1928114f,0.3450245f,0.9872899f,0.4127591f,0.0501000f,1.1453135f,0.8019831f,0.7088335f,
0.0290531f,0.6268536f,0.4903355f,0.9749046f,1.1713423f,0.0913007f,1.3146805f,0.9078258f,
0.7912332f,0.1044568f,1.3239524f,1.3441551f,0.5508964f,0.3667243f,0.1243404f,0.6776540f,
0.1557832f,0.1952610f,0.8140970f,0.2821348f,0.6017738f,0.4700034f,1.4993603f,1.0016604f,
0.0426892f,0.6634603f,0.7321154f} ;


   
	

	
	satan2a( Fin1, SIZE , Fin2 , SIZE , Fout ); 

   for ( i = 0 ; i < SIZE ; ++i)
      {
		 printf ( "%e - %e\n"  , Fout[i] , Result[i] );
         assert (  fabs ( Fout[i] - Result[i] ) / fabs( Fout[i]) < 3e-4 );
      }

}

static void datan2aTest ( void ) 
{


   int i = 0 ;
   double Fin1[SIZE] = 
{0.70964269945397973061,0.6610225578770041465759,0.7252350724302232265472,
0.510143497958779335022,0.2824866441078484058380,0.2214915128424763679504,
0.5767575385980308055878,0.7048253491520881652832,0.5607945644296705722809,
0.3628880484029650688171,0.3088326244615018367767,0.9813414867967367172241,
0.7428482254035770893097,0.1616391474381089210510,0.3652521963231265544891,
0.3835070468485355377197,0.1169181005097925662994,0.8911246126517653465271,
0.0634272000752389431000,0.6263941843062639236450,0.6807702076621353626251,
0.2588596837595105171204,0.4394804346375167369843,0.8598818778991699218750,
0.5482823201455175876617,0.8135995296761393547058,0.4898237003944814205170,
0.0240026097744703292847,0.7369195525534451007843,0.2411156157031655311584,
0.1529693226329982280731,0.2648359201848506927490,0.4298193217255175113678,
0.7673939457163214683533,0.8753260499797761440277,0.3796988371759653091431,
0.3062356826849281787872,0.3880051793530583381653,0.1047293278388679027557,
0.7603831812739372253418,0.0340930395759642124176,0.1423966242000460624695,
0.5554559468291699886322,0.8031897451728582382202,0.5183992316015064716339,
0.1518561029806733131409,0.5884730662219226360321,0.2545093484222888946533,
0.9992679939605295658112,0.6398976957425475120544,0.5506716123782098293304,
0.4607007671147584915161,0.5933007937856018543243,0.6538193570449948310852,
0.4168340521864593029022,0.9910155385732650756836,0.3720780410803854465485,
0.7061824081465601921082,0.5780865414999425411224,0.602319641038775444031,
0.5715096746571362018585,0.0549629041925072669983,0.1205854485742747784,
0.0143620483577251434326,0.0257951230742037296295,0.8411248764023184776306,
0.4381882525049149990082,0.4643401596695184707642,0.4197426405735313892365,
0.8023654492571949958801,0.5228588166646659374237,0.5095121040940284729004,
0.4531980180181562900543,0.7817818326875567436218,0.776557037141174077988,
0.0466059204190969467163,0.5113326688297092914581,0.7502101892605423927307,
0.6883628661744296550751,0.0167756117880344390869,0.9345410899259150028229,
0.5609863763675093650818,0.2205847105942666530609,0.7648540753871202468872,
0.4816976976580917835236,0.1558785634115338325500,0.2476022052578628063202,
0.5216529071331024169922,0.0805230387486517429352,0.4409417239949107170105,
0.8911933614872395992279,0.9780590813606977462769,0.4588093762286007404327,
0.5510440031066536903381,0.0960960905067622661591,0.4196785055100917816162,
0.7502556503750383853912,0.7218149593099951744080,0.2895541018806397914886,
0.3907764498144388198853}
;
   double Fin2[SIZE] = 
{0.6686618146486580371857,0.4877656819298863410950,0.4685971769504249095917,
0.3562648519873619079590,0.3442325466312468051910,0.4253307832404971122742,
0.5588058172725141048431,0.3304864969104528427124,0.4157403339631855487823,
0.1595822656527161598206,0.3883102680556476116180,0.9415460713207721710205,
0.4722979352809488773346,0.8533652639016509056091,0.1207739165984094142914,
0.8999380934983491897583,0.4384902161546051502228,0.8976056622341275215149,
0.4911110657267272472382,0.3402217179536819458008,0.9966153600253164768219,
0.0215395865961909294128,0.6876890822313725948334,0.0044924151152372360229,
0.6397854541428387165070,0.5416147718206048011780,0.2247649203054606914520,
0.7364005260169506072998,0.4496364505030214786530,0.9678138038143515586853,
0.6489060199819505214691,0.2544666919857263565063,0.1923975017853081226349,
0.6861492367461323738098,0.4231455805711448192596,0.6734441593289375305176,
0.8270696722902357578278,0.9360805852338671684265,0.8326222090981900691986,
0.7424779590219259262085,0.0194640238769352436066,0.8016031915321946144104,
0.2554539437405765056610,0.2688109613955020904541,0.7558490769006311893463,
0.4347589677199721336365,0.6425966522656381130219,0.6957868058234453201294,
0.6499576461501419544220,0.2303190128877758979797,0.5504368054680526256561,
0.3038997054100036621094,0.0371030517853796482086,0.1703881053254008293152,
0.5698686256073415279388,0.0036411266773939132690,0.4491547052748501300812,
0.0576810697093605995178,0.4956056098453700542450,0.1888933442533016204834,
0.5641230703331530094147,0.8562210192903876304626,0.0794764286838471889496,
0.6196198705583810806274,0.2241039988584816455841,0.8582094730809330940247,
0.7114551994018256664276,0.8026027604937553405762,0.6153324418701231479645,
0.8958183480426669120789,0.8721761344932019710541,0.8389767911285161972046,
0.2040955354459583759308,0.3166538262739777565002,0.7006825651042163372040,
0.2073105163872241973877,0.5222550616599619388580,0.9416420971974730491638,
0.52116033947095274925,0.4509841967374086380005,0.3961292845197021961212,
0.7240869747474789619446,0.6724055963568389415741,0.2386146038770675659180,
0.7124841609038412570953,0.3286493895575404167175,0.4837769134901463985443,
0.7662767004221677780151,0.3153839264996349811554,0.3489987561479210853577,
0.7413818310014903545380,0.9702721945941448211670,0.1276510567404329776764,
0.3828862151131033897400,0.4882477498613297939301,0.5191949699074029922485,
0.0906856027431786060333,0.6833897503092885017395,0.5022272053174674510956,
0.0540433898568153381348}

 ;
   double Fout[SIZE]  ;
   
double  Result[] = 
{0.8151222298353714146302,0.9350871051642664077974,0.997145470042032466829,
0.9611705131081605957277,0.6871926567255678408586,0.48011041457317088499,
0.8012054946208865269242,1.132343901220193460588,0.9328596693816280094325,
1.1564937347686861102147,0.6718834468335361798097,0.8060908633813578250127,
1.00447314922565955619,0.1871960989477313985763,1.25145462350922120898,
0.4028428263783953022781,0.2605755136377292391359,0.781774911019853857574,
0.1284394521185465987134,1.073232720478735968683,0.5992812665317298614909,
1.4877780687994013320008,0.5686520903625903455847,1.5655719182360376962038,
0.7085314645036139280521,0.9834619198256084882104,1.140591448484360226345,
0.0325829683756781798842,1.0229420689159220980713,0.2441637219657823987262,
0.2315075947889858876128,0.805363112922971136065,1.1499199282073593320064,
0.8412343166232832958329,1.1205046812517129861675,0.5133888656295326757828,
0.3546137657219728400726,0.3929433432393027447738,0.1251254110872664360166,
0.7973116893083483924798,1.0520419606393343059381,0.1758058639068769690716,
1.1397404905667376517897,1.2478349146446092721163,0.6011661864384908460224,
0.336040406143340686373,0.7414617770855178591205,0.35066862507579671382,
0.994116233357116407809,1.225301837543258720586,0.7856114093437986944934,
0.9876695123648748797507,1.5083409965621017434501,1.3158623593693956621564,
0.6315271916809107599633,1.5671222065095873343665,0.6918174612768925868522,
1.4892971216950183777072,0.8620674912261098166155,1.2669007116100525767166,
0.7919024670030506696250,0.0641044712091229373918,0.9880588227443989346455,
0.0231746556747607738991,0.1145990356665423787197,0.7753448027391854902035,
0.5520317684396915947076,0.5244928157781221234046,0.5986382937223412303851,
0.730422528982288210564,0.5400426833033002971263,0.5457711699419741657735,
1.1476553996273199942380,1.1859516842120860768972,0.8367154013891151542737,
0.2211356254003243038131,0.7748311007637324054897,0.6727280587907351616650,
0.9227659311220508531193,0.0371806395770535452749,1.16987833340959523909,
0.6591538541213141089159,0.3169908006212094342402,1.2683907108855461132180,
0.5944925989956957312899,0.4428774366489620084586,0.4730514714397818787361,
0.5976982909559278578371,0.2499770826480406105130,0.9012690725036259786762,
0.8769058262572594353301,0.7893948375778501169719,1.2994367291712400902526,
0.9635433198261218468161,0.1943343662922066283905,0.6797968572652465235606,
1.4505069462951736269929,0.8127362698086932901731,0.5229909037180106023968,
1.4333705873570850020116};

	
	
	datan2a( Fin1, SIZE , Fin2 , SIZE , Fout ); 

   for ( i = 0 ; i < SIZE ; ++i)
      {
		 printf ( "%e - %e\n"  , Fout[i] , Result[i] );
         assert (  fabs ( Fout[i] - Result[i] ) / fabs( Fout[i]) < 1e-17 );
      }

}




static int testAtan2   (void) {

  printf("\n>>>> Float a Tests\n");
  satan2aTest();
printf("\t>>>> Double a Tests\n");
  datan2aTest();
printf("\t>>>> Double s Tests\n");
  datan2sTest();
printf("\t>>>> Float s Tests\n");
  satan2sTest();

  return 0;
}


int main(void) {
  assert(testAtan2() == 0);
  return 0;
}
