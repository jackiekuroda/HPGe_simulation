#include "BackgroundGeneratorAction.hh"
#include "G4GeneralParticleSource.hh"
#include "G4SystemOfUnits.hh"
#include "G4Gamma.hh"

Background::Background()
{
   fBackgroundSource = new G4GeneralParticleSource();

   fBackgroundSource->ClearAll();

   G4int id =1;
   //creating background radiation

   auto addSource = [this](G4double energy,G4double intensity, G4int sourceId)
   {

           fBackgroundSource->AddaSource(intensity);
           fBackgroundSource->GetCurrentSource();

           auto gamma = fBackgroundSource->GetCurrentSource();
           gamma->SetParticleDefinition(G4Gamma::Gamma());

           auto ene = gamma->GetEneDist();
           ene->SetEnergyDisType("Mono");
           ene->SetMonoEnergy(energy);

           auto pos = gamma->GetPosDist();
           pos->SetPosDisType("Surface");
           pos->SetPosDisShape("Para");
           pos->SetHalfX(.5 *m);
           pos->SetHalfY(.5 *m);
           pos->SetHalfZ(.5 *m);

           auto ang = gamma->GetAngDist();
           ang->SetAngDistType("planar");
           ang->SetParticleMomentumDirection(G4ThreeVector(0, 0, 1));


   };
	addSource(92.890289* keV, 0.085630, id++);
	addSource(98.389687* keV, 0.000784, id++);
	addSource(109.496970* keV, 0.002959, id++);
	addSource(129.641321* keV, 0.004220, id++);
	addSource(186.401825* keV, 0.015188, id++);
	addSource(209.658806* keV, 0.007433, id++);
	addSource(239.025704* keV, 0.083348, id++);
	addSource(242.230719* keV, 0.023486, id++);
	addSource(270.595196* keV, 0.009569, id++);
	addSource(277.927441* keV, 0.003554, id++);
	addSource(295.634473* keV, 0.045784, id++);
	addSource(300.535773* keV, 0.006740, id++);
	addSource(328.423160* keV, 0.006918, id++);
	addSource(338.773677* keV, 0.023241, id++);
	addSource(352.410727* keV, 0.095753, id++);
	addSource(388.923948* keV, 0.002970, id++);
	addSource(402.215653* keV, 0.001300, id++);
	addSource(409.991799* keV, 0.004306, id++);
	addSource(439.604206* keV, 0.001553, id++);
	addSource(463.621701* keV, 0.011020, id++);
	addSource(475.263000* keV, 0.001461, id++);
	addSource(480.304968* keV, 0.007363, id++);
	addSource(487.852319* keV, 0.006941, id++);
	addSource(511.506881* keV, 0.040100, id++);
	addSource(561.419592* keV, 0.000865, id++);
	addSource(572.337476* keV, 0.001740, id++);
	addSource(584.041881* keV, 0.080214, id++);
	addSource(610.231230* keV, 0.153776, id++);
	addSource(666.529211* keV, 0.006598, id++);
	addSource(703.726897* keV, 0.001880, id++);
	addSource(720.691851* keV, 0.000948, id++);
	addSource(728.411716* keV, 0.020944, id++);
	addSource(744.056080* keV, 0.001434, id++);
	addSource(756.380066* keV, 0.002290, id++);
	addSource(764.366667* keV, 0.002450, id++);
	addSource(769.572910* keV, 0.019114, id++);
	addSource(773.499267* keV, 0.004299, id++);
	addSource(783.187207* keV, 0.001353, id++);
	addSource(787.009111* keV, 0.010809, id++);
	addSource(796.178939* keV, 0.013536, id++);
	addSource(807.459729* keV, 0.004861, id++);
	addSource(827.211513* keV, 0.002236, id++);
	addSource(831.682344* keV, 0.001147, id++);
	addSource(841.508157* keV, 0.012611, id++);
	addSource(861.998876* keV, 0.013885, id++);
	addSource(895.115681* keV, 0.001805, id++);
	addSource(905.579422* keV, 0.001956, id++);
	addSource(912.710650* keV, 0.087923, id++);
	addSource(935.626828* keV, 0.013629, id++);
	addSource(951.540441* keV, 0.005449, id++);
	addSource(966.437201* keV, 0.020796, id++);
	addSource(970.621814* keV, 0.053024, id++);
	addSource(1002.825653* keV, 0.003175, id++);
	addSource(1080.836846* keV, 0.001785, id++);
	addSource(1122.252473* keV, 0.073421, id++);
	addSource(1135.567512* keV, 0.001532, id++);
	addSource(1157.203322* keV, 0.007599, id++);
	addSource(1208.874711* keV, 0.003666, id++);
	addSource(1240.315024* keV, 0.031174, id++);
	addSource(1283.376177* keV, 0.007092, id++);
	addSource(1380.201709* keV, 0.021813, id++);
	addSource(1388.095870* keV, 0.006152, id++);
	addSource(1404.084019* keV, 0.008440, id++);
	addSource(1410.556448* keV, 0.012109, id++);
	addSource(1463.466957* keV, 1.000000, id++);
	addSource(1498.842386* keV, 0.006587, id++);
	addSource(1504.488724* keV, 0.002407, id++);
	addSource(1512.078661* keV, 0.011715, id++);
	addSource(1541.511993* keV, 0.004291, id++);
	addSource(1545.998000* keV, 0.003161, id++);
	addSource(1586.866292* keV, 0.049723, id++);
	addSource(1591.171456* keV, 0.012519, id++);
	addSource(1595.745550* keV, 0.007941, id++);
	addSource(1602.406402* keV, 0.002782, id++);
	addSource(1623.661190* keV, 0.006221, id++);
	addSource(1633.683490* keV, 0.007572, id++);
	addSource(1664.446810* keV, 0.007708, id++);
	addSource(1668.605942* keV, 0.004841, id++);
	addSource(1687.231515* keV, 0.003173, id++);
	addSource(1697.717097* keV, 0.015779, id++);
	addSource(1732.860462* keV, 0.018331, id++);
	addSource(1767.826533* keV, 0.101450, id++);
	addSource(1841.724300* keV, 0.001971, id++);
	addSource(1851.050998* keV, 0.013217, id++);
	addSource(1876.675091* keV, 0.001361, id++);
	addSource(1940.567922* keV, 0.001285, id++);
	addSource(2107.621971* keV, 0.023872, id++);
	addSource(2122.647352* keV, 0.008263, id++);
	addSource(2208.398284* keV, 0.038366, id++);
	addSource(2297.857645* keV, 0.002979, id++);
	addSource(2452.640611* keV, 0.013372, id++);
	
}
void Background::GeneratePrimaryVertex(G4Event* anEvent)
{
	fBackgroundSource->GeneratePrimaryVertex(anEvent);
}
