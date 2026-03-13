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
//addSource(92.890290* keV, 0.363247, id++);
addSource(98.389686* keV, 0.003513, id++);
addSource(104.842624* keV, 0.008929, id++);
addSource(109.496972* keV, 0.011931, id++);
addSource(129.641425* keV, 0.016765, id++);
addSource(186.401826* keV, 0.054564, id++);
addSource(209.658807* keV, 0.025444, id++);
addSource(239.025705* keV, 0.269011, id++);
addSource(242.230720* keV, 0.074954, id++);
addSource(270.595196* keV, 0.029239, id++);
addSource(277.927444* keV, 0.010722, id++);
addSource(295.634474* keV, 0.134014, id++);
addSource(300.535773* keV, 0.019567, id++);
addSource(328.423162* keV, 0.019176, id++);
addSource(338.773677* keV, 0.063458, id++);
addSource(352.410727* keV, 0.256036, id++);
addSource(389.342800* keV, 0.002873, id++);
addSource(402.215654* keV, 0.003233, id++);
addSource(409.991799* keV, 0.010594, id++);
addSource(439.604199* keV, 0.003670, id++);
addSource(463.621701* keV, 0.025241, id++);
addSource(475.263001* keV, 0.003275, id++);
addSource(480.304964* keV, 0.013926, id++);
addSource(487.852322* keV, 0.012897, id++);
addSource(511.506881* keV, 0.086542, id++);
addSource(563.305992* keV, 0.004338, id++);
addSource(572.337473* keV, 0.003499, id++);
addSource(584.041881* keV, 0.159219, id++);
addSource(610.231231* keV, 0.296654, id++);
addSource(666.529212* keV, 0.011833, id++);
addSource(703.726900* keV, 0.003297, id++);
addSource(720.691854* keV, 0.001635, id++);
addSource(728.411716* keV, 0.035856, id++);
addSource(744.056085* keV, 0.002420, id++);
addSource(756.380066* keV, 0.003818, id++);
addSource(764.366634* keV, 0.003988, id++);
addSource(769.572910* keV, 0.031270, id++);
addSource(773.499265* keV, 0.007019, id++);
addSource(783.187206* keV, 0.002199, id++);
addSource(787.009110* keV, 0.015807, id++);
addSource(796.178940* keV, 0.021675, id++);
addSource(807.459729* keV, 0.007739, id++);
addSource(827.211514* keV, 0.003133, id++);
addSource(831.682343* keV, 0.001788, id++);
addSource(839.226140* keV, 0.291986, id++);
addSource(841.508182* keV, 0.016317, id++);
addSource(861.998876* keV, 0.021083, id++);
addSource(895.115682* keV, 0.002658, id++);
addSource(905.579421* keV, 0.002865, id++);
addSource(912.710650* keV, 0.127985, id++);
addSource(935.626828* keV, 0.019475, id++);
addSource(951.540441* keV, 0.007689, id++);
addSource(966.437201* keV, 0.028099, id++);
addSource(970.621814* keV, 0.073638, id++);
addSource(1002.825610* keV, 0.004245, id++);
addSource(1080.836846* keV, 0.002284, id++);
addSource(1122.252472* keV, 0.091231, id++);
addSource(1135.567512* keV, 0.001886, id++);
addSource(1157.203320* keV, 0.009215, id++);
addSource(1185.600491* keV, 0.012749, id++);
addSource(1208.874731* keV, 0.004292, id++);
addSource(1240.315023* keV, 0.035757, id++);
addSource(1283.376176* keV, 0.007911, id++);
addSource(1380.201709* keV, 0.022559, id++);
addSource(1388.095868* keV, 0.006266, id++);
addSource(1404.084021* keV, 0.008534, id++);
addSource(1410.556447* keV, 0.012483, id++);
addSource(1463.466956* keV, 1.000000, id++);
addSource(1498.842391* keV, 0.006194, id++);
addSource(1504.488724* keV, 0.002324, id++);
addSource(1512.078660* keV, 0.011394, id++);
addSource(1541.512452* keV, 0.003684, id++);
addSource(1545.998003* keV, 0.002863, id++);
addSource(1586.866614* keV, 0.028406, id++);
addSource(1591.171455* keV, 0.011575, id++);
addSource(1595.745547* keV, 0.007050, id++);
addSource(1602.406404* keV, 0.002488, id++);
addSource(1623.661190* keV, 0.005690, id++);
addSource(1633.683489* keV, 0.006877, id++);
addSource(1664.446793* keV, 0.006799, id++);
addSource(1668.605338* keV, 0.003077, id++);
addSource(1687.231577* keV, 0.002568, id++);
addSource(1697.717325* keV, 0.009645, id++);
addSource(1732.860462* keV, 0.015836, id++);
addSource(1767.826532* keV, 0.086103, id++);
addSource(1841.724301* keV, 0.001613, id++);
addSource(1851.050998* keV, 0.010764, id++);
addSource(1876.675113* keV, 0.001095, id++);
addSource(1940.567913* keV, 0.001003, id++);
addSource(2107.621969* keV, 0.017271, id++);
addSource(2122.647352* keV, 0.005938, id++);
addSource(2208.398283* keV, 0.026573, id++);
addSource(2297.857633* keV, 0.001979, id++);
addSource(2452.640610* keV, 0.008345, id++);
addSource(2619.726504* keV, 0.142598, id++);

}

Background::~Background()
{
	delete fBackgroundSource;
}

void Background::GeneratePrimaryVertex(G4Event* anEvent)
{
	fBackgroundSource->GeneratePrimaryVertex(anEvent);
}
