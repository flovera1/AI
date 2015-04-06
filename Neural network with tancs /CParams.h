#ifndef CPARAMS_H
#define CPARAMS_H
/**  Desc: Class design to hold all the parameters used in this project. The values
*        are loaded in from an ini file when an instance of the class is
*        created.
*/
#include <fstream>
#include <windows.h>
using namespace std;	
class CParams{
    public:
      //General parameters
      static double dPi;
      static double dHalfPi;
      static double dTwoPi;
      static int    WindowWidth;
      static int    WindowHeight;
      static int    iFramesPerSecond;
      //Used for the neural network
      static int    iNumInputs;
      static int    iNumHidden;
      static int    iNeuronsPerHiddenLayer;
      static int    iNumOutputs;
      //For tweeking the sigmoid function
      static double dActivationResponse;
      //Bias value
      static double dBias;
      //Used to define the sweepers
      //limits how fast the sweepers can turn
      static double dMaxTurnRate;
      static double dMaxSpeed;
      //for controlling the size
      static int   iSweeperScale;
      //Controller parameters
      static int    iNumSweepers;
      static int    iNumMines;
      //Number of time steps we allow for each generation to live
      static int    iNumTicks;
      //Scaling factor for mines
      static double dMineScale;
      //GA parameters
      static double dCrossoverRate;
      static double dMutationRate;
      //The maximum amount the ga may mutate each weight by
      static double dMaxPerturbation;
      //used for elitism
      static int    iNumElite;
      static int    iNumCopiesElite;
      CParams(){
        if(!LoadInParameters("params.ini")){
            MessageBox(NULL, "Cannot find ini file!", "Error", 0);
        }
      }
      bool LoadInParameters(char* szFileName);
    };
#endif