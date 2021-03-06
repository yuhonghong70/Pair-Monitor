#ifndef MonoPhotonProcessor_h
#define MonoPhotonProcessor_h 1

#include "marlin/Processor.h"
#include <EVENT/MCParticle.h>
#include "lcio.h"
#include <string>

#include "UTIL/LCRelationNavigator.h"

class TFile;
class TTree;
class TH2D;
class TH1D;
class TH2F;
class TVector3;
const int NMAX_BeamCalS   = 50000;
const int NMAX_BeamCalStep   =11000;
const int NMAX_BeamCalcont   =11000;
const int NMAX_MCPS   = 50000;
const int NMAX_CLRS   = 430;
const int NMAX_PARENTS   = 430;
const int NMAX_DAUGHTERS = 430;

using namespace lcio ;
using namespace marlin ;


/**  Example processor for marlin.
 * 
 *  If compiled with MARLIN_USE_AIDA 
 *  it creates a histogram (cloud) of the MCParticle energies.
 * 
 *  <h4>Input - Prerequisites</h4>
 *  Needs the collection of MCParticles.
 *
 *  <h4>Output</h4> 
 *  A histogram.
 * 
 * @param CollectionName Name of the MCParticle collection
 * 
 * @author F. Gaede, DESY
 * @version $Id: MonoPhotonProcessor.h,v 1.4 2005-10-11 12:57:39 gaede Exp $ 
 */

class MonoPhotonProcessor : public Processor {
  
 public:
  
  virtual Processor*  newProcessor() { return new MonoPhotonProcessor ; }
  
  
  MonoPhotonProcessor() ;
  
  /** Called at the begin of the job before anything is read.
   * Use to initialize the processor, e.g. book histograms.
   */
  virtual void init() ;
  
  /** Called for every run.
   */
  virtual void processRunHeader( LCRunHeader* run ) ;
  
  /** Called for every event - the working horse.
   */
  virtual void processEvent( LCEvent * evt ) ; 
  
  
  virtual void check( LCEvent * evt ) ; 
  
  
  /** Called after data processing for clean up.
   */
  virtual void end() ;
  
  
 protected:

 /** Prepare NTuple 
  */ 
  void makeNTuple() ;

 /** utility functions 
  */ 
  TVector3 getIP(EVENT::MCParticle* p); 

  /** Input collection name.
   */
  std::string _colMCP ;
  std::string _colBeamCal ;
  //std::string _colMCBeamCalRelation ;
  //LCRelationNavigator* _navBeamCal;

  int _nRun ;
  int _nEvt ;

  TFile* _otfile;
  TTree* _evtdata;
  TTree* _evtdata_step;
  TTree* _evtdata_cont;
  TH2D* h;
  TH2D* hp2;
  TH1D* h4;
  TH1D* hphi;
  TH1D* henergycont;

  TH2F* testDaniel;
  TH2F* h2;
  TH2F* h3;
  TH2F* hrophi;
  TH2F* hrophi2;

  struct EVTFILLSTEPDATA {
    int    nBeamCalstep ;     // # of BeamCals 

    float  BeamCal_stepx[NMAX_BeamCalStep];
    float  BeamCal_stepy[NMAX_BeamCalStep];
    float  BeamCal_stepz[NMAX_BeamCalStep];
    float  BeamCal_stepro[NMAX_BeamCalStep];
    float  BeamCal_stepphi[NMAX_BeamCalStep];

    float  BeamCal_energystep[NMAX_BeamCalStep];
    float  BeamCal_timestep[NMAX_BeamCalStep];
    int    BeamCal_pdgstep[NMAX_BeamCalStep];
    float amaxro; //maximum value of array for radius ro
    float amaxphi; //maximum value of array for phi
    float amaxenergycont; //maximum value of array for phi

    float aminro; //minimum value of array for radius ro
    float aminphi; //minimum value of array for phi



  };

  struct EVTFILLDATA {
    int    evt ;       // event number
    int    nBeamCals ;     // # of BeamCals 
    int    BeamCal_phiindx[NMAX_BeamCalS] ;     // # of BeamCals 
    int    BeamCal_rindx[NMAX_BeamCalS];     // # of BeamCals 
    int    BeamCal_layer[NMAX_BeamCalS];     // # of BeamCals 
    
    //int    BeamCal_nmcp;
    

    float  BeamCal_e[NMAX_BeamCalS];
    float  BeamCal_cid0[NMAX_BeamCalS];
    float  BeamCal_cid1[NMAX_BeamCalS];
    //float  BeamCal_cid0[NMAX_BeamCalS];
    //float  BeamCal_econt[NMAX_BeamCalS];
    float BeamCal_x[NMAX_BeamCalS];
    float BeamCal_y[NMAX_BeamCalS];
    float BeamCal_z[NMAX_BeamCalS];

     int    BeamCal_nmccont[NMAX_BeamCalS];
     int    BeamCal_nmcp[NMAX_BeamCalS];

    
     // MC Info
    int    nmcps ;     // # of MC Particles 
    float  ipx;
    float  ipy;
    float  ipz;
    int    mcp_index[NMAX_MCPS];
    float  mcp_e[NMAX_MCPS];
    float  mcp_px[NMAX_MCPS];
    float  mcp_py[NMAX_MCPS];
    float  mcp_pz[NMAX_MCPS];
    float  mcp_phi[NMAX_MCPS];
    float  mcp_theta[NMAX_MCPS];
    float  mcp_chrg[NMAX_MCPS];
    float  mcp_startx[NMAX_MCPS];
    float  mcp_starty[NMAX_MCPS];
    float  mcp_startz[NMAX_MCPS];
    float  mcp_endx[NMAX_MCPS];
    float  mcp_endy[NMAX_MCPS];
    float  mcp_endz[NMAX_MCPS];
    int    mcp_pdg[NMAX_MCPS];
    int    mcp_nparents[NMAX_MCPS];
    int    mcp_parentIndex[NMAX_MCPS][NMAX_PARENTS];
    int    mcp_ndaughters[NMAX_MCPS];
    int    mcp_daughterIndex[NMAX_MCPS][NMAX_DAUGHTERS];
    int    mcp_genstatus[NMAX_MCPS];
    int    mcp_simstatus[NMAX_MCPS];
    bool   mcp_iscreatedinsim[NMAX_MCPS];

    int    nclrhits ;    // # of Cal hit clusters;
    float  clr_x[NMAX_CLRS];
    float  clr_y[NMAX_CLRS];
    float  clr_z[NMAX_CLRS];
  };
    
  struct EVTFILLCONTDATA{
    float  BeamCal_contx[NMAX_BeamCalStep];
    int    nBeamCalcont ;     // # of BeamCals 
    float  BeamCal_conty[NMAX_BeamCalStep];
    float  BeamCal_contz[NMAX_BeamCalStep];
    float  BeamCal_contro[NMAX_BeamCalStep];
    float  BeamCal_contphi[NMAX_BeamCalStep];
    float  BeamCal_energycont[NMAX_BeamCalStep];
    float  BeamCal_timecont[NMAX_BeamCalStep];
    int    BeamCal_pdgcont[NMAX_BeamCalStep];

  };

  EVTFILLDATA _data;
  EVTFILLSTEPDATA _stepdata;
  EVTFILLCONTDATA _contdata;

 // output root file name
  std::string _rootfilename;

} ;

#endif



