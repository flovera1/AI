#include "CController.h"


//---------------------------- Render ------------------------------------
//
//------------------------------------------------------------------------
void CController::Render(HDC surface)
{
  m_pSOM->Render(surface);
}
              
      
//--------------------------- Train --------------------------------------
//
// trains the network given a std::vector of input vectors
//------------------------------------------------------------------------
bool CController::Train()
{
  if (!m_pSOM->FinishedTraining())
  {
    if (!m_pSOM->Epoch(m_TrainingSet))
    {
      return false;
    }
  }

  return true;
}

//-------------------------- CreateDataSet -------------------------------
//
//------------------------------------------------------------------------
void CController::CreateDataSet()
{

#ifndef RANDOM_TRAINING_SETS
  
  //create a data set
  vector<double> red, green, blue, yellow, orange, purple, dk_green, dk_blue;

  red.push_back(1);
  red.push_back(0);
  red.push_back(0);

  green.push_back(0);
  green.push_back(1);
  green.push_back(0);

  dk_green.push_back(0);
  dk_green.push_back(0.5);
  dk_green.push_back(0.25);

  blue.push_back(0);
  blue.push_back(0);
  blue.push_back(1);

  dk_blue.push_back(0);
  dk_blue.push_back(0);
  dk_blue.push_back(0.5);

  yellow.push_back(1);
  yellow.push_back(1);
  yellow.push_back(0.2);

  orange.push_back(1);
  orange.push_back(0.4);
  orange.push_back(0.25);

  purple.push_back(1);
  purple.push_back(0);
  purple.push_back(1);

  m_TrainingSet.push_back(red);
  m_TrainingSet.push_back(green);
  m_TrainingSet.push_back(blue);
  m_TrainingSet.push_back(yellow);
  m_TrainingSet.push_back(orange);
  m_TrainingSet.push_back(purple);
  m_TrainingSet.push_back(dk_green);
  m_TrainingSet.push_back(dk_blue);
  

#else

  //choose a random number of training sets
  int NumSets = RandInt(constMinNumTrainingSets, constMaxNumTrainingSets);

  for (int s=0; s<NumSets; ++s)
  {

    vector<double> set;

    set.push_back(RandFloat());
    set.push_back(RandFloat());
    set.push_back(RandFloat());

    m_TrainingSet.push_back(set);
  }

#endif

}